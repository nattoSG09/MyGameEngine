#include "Fbx.h"
#include "Direct3D.h"
#include "Camera.h"
#include "Light.h"
#include "Texture.h"

using std::size;

Fbx::Fbx()
    :vertexCount_(0),polygonCount_(0), materialCount_(0), pMaterialList_(nullptr)
    ,pVertexBuffer_(nullptr),pIndexBuffer_(nullptr),pConstantBuffer_(nullptr)

{
}

Fbx::~Fbx()
{
}

HRESULT Fbx::Load(string fileName)
{
	//マネージャを生成
	FbxManager* pFbxManager = FbxManager::Create();

	//インポーターを生成
	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
	fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

	//シーンオブジェクトにFBXファイルの情報を流し込む
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
	fbxImporter->Import(pFbxScene);
	fbxImporter->Destroy();

	//メッシュ情報を取得
	FbxNode* rootNode = pFbxScene->GetRootNode();
	FbxNode* pNode = rootNode->GetChild(0);
	FbxMesh* mesh = pNode->GetMesh();

	//各情報の個数を取得
	vertexCount_ = mesh->GetControlPointsCount();	//頂点の数
	polygonCount_ = mesh->GetPolygonCount();		//ポリゴンの数
	materialCount_ = pNode->GetMaterialCount();		//マテリアルの数

	//現在のカレントディレクトリを覚えておく
	char defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	//引数のfileNameからディレクトリ部分を取得
	char dir[_MAX_DIR];
	_splitpath_s(fileName.c_str(),nullptr, 0, dir, _MAX_DIR,nullptr, 0,nullptr, 0);
	wsprintf(dir, "%s", dir);

	//カレントディレクトリ変更
	SetCurrentDirectory(dir);

	InitVertex(mesh);		//頂点バッファ準備
	InitIndex(mesh);		//インデックスバッファ準備
	InitConstantBuffer();	//コンスタントバッファ準備
	InitMaterial(pNode);	//マテリアルの初期化

	//カレントディレクトリを元に戻す
	SetCurrentDirectory(defaultCurrentDir);

	//マネージャ解放
	pFbxManager->Destroy();
	return S_OK;
}

void Fbx::Draw(Transform& _transform)
{
	//シェーダーを切り替える
	Direct3D::SetShader(SHADER_3D);

	for (int i = 0; i < materialCount_; i++) 
	{
		//コンスタントバッファをセット
		CONSTANT_BUFFER cb;

		cb.matWVP = XMMatrixTranspose(_transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
		cb.matNormal = XMMatrixTranspose(_transform.GetNormalMatrix());
		cb.LightPos = { 1.0, 0.0, -1.0, 0 };

		cb.diffuseColor = pMaterialList_[i].diffuse_;
		cb.isTexture = pMaterialList_[i].pTexture_ != nullptr;

#if 0
		cb.matWVP = XMMatrixTranspose(_transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
		cb.matNormal = XMMatrixTranspose(_transform.GetNormalMatrix());

		//マテリアルカラー
		cb.diffuseColor = pMaterialList_[i].diffuse_;

		//テクスチャの有無
		cb.isTexture = pMaterialList_[i].pTexture_ != nullptr;

		//ライトの位置・強度
		cb.matLightPos = Light::GetPosition();
		cb.matLight = Light::GetworldLight();
#endif

		D3D11_MAPPED_SUBRESOURCE pdata;
		Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
		memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る

		Direct3D::pContext_->Unmap(pConstantBuffer_, 0);

		//テクスチャとサンプラーをシェーダーへ
		if (pMaterialList_[i].pTexture_)
		{
			ID3D11SamplerState* pSampler = pMaterialList_[i].pTexture_->GetSampler();
			Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

			ID3D11ShaderResourceView* pSRV = pMaterialList_[i].pTexture_->GetSRV();
			Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

		}

		Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開

		//頂点バッファ
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

		// インデックスバッファーをセット
		stride = sizeof(int);
		offset = 0;
		Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_[i], DXGI_FORMAT_R32_UINT, 0);

		//コンスタントバッファ
		Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
		Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用
		
		//描画
		Direct3D::pContext_->DrawIndexed(indexCount_[i], 0, 0);
	}
}

void Fbx::Release()
{
}


void Fbx::InitVertex(fbxsdk::FbxMesh* mesh)
{
	//頂点情報を入れる配列
	VERTEX* vertices = new VERTEX[vertexCount_];

	//全ポリゴン
	for (DWORD poly = 0; poly < polygonCount_; poly++)
	{
		//3頂点分
		for (int vertex = 0; vertex < 3; vertex++)
		{
			//調べる頂点の番号
			int index = mesh->GetPolygonVertex(poly, vertex);

			//頂点の位置
			FbxVector4 pos = mesh->GetControlPointAt(index);
			vertices[index].position = XMVectorSet((float)pos[0], (float)pos[1], (float)pos[2], 0.0f);

			//頂点のUV
			FbxLayerElementUV* pUV = mesh->GetLayer(0)->GetUVs();
			int uvIndex = mesh->GetTextureUVIndex(poly, vertex, FbxLayerElement::eTextureDiffuse);
			FbxVector2  uv = pUV->GetDirectArray().GetAt(uvIndex);
			vertices[index].uv = XMVectorSet((float)uv.mData[0], (float)(1.0f - uv.mData[1]), 0.0f, 0.0f);

			//頂点の法線
			FbxVector4 Normal;
			mesh->GetPolygonVertexNormal(poly, vertex, Normal);	//ｉ番目のポリゴンの、ｊ番目の頂点の法線をゲット
			vertices[index].normal = XMVectorSet((float)Normal[0], (float)Normal[1], (float)Normal[2], 0.0f);
		}
	}

	// 頂点バッファ作成
	D3D11_BUFFER_DESC bd_vertex;

	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexCount_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
}

void Fbx::InitIndex(fbxsdk::FbxMesh* mesh)
{
	pIndexBuffer_ = new ID3D11Buffer * [materialCount_];
	indexCount_ = std::vector<int>(materialCount_);

	int* index = new int[polygonCount_ * 3];

	//マテリアル分
	for (int i = 0; i < materialCount_; i++)
	{
		int count = 0;

		//全ポリゴン
		for (DWORD poly = 0; poly < polygonCount_; poly++)
		{
			FbxLayerElementMaterial* mtl = mesh->GetLayer(0)->GetMaterials();
			int mtlId = mtl->GetIndexArray().GetAt(poly);

			if (mtlId == i) 
			{
				//3頂点分
				for (DWORD vertex = 0; vertex < 3; vertex++)
				{
					index[count] = mesh->GetPolygonVertex(poly, vertex);
					count++;
				}
			}
			
		}
		indexCount_[i] = count;

		// 頂点バッファ作成
		D3D11_BUFFER_DESC   bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int) * count;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = index;
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;

		Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_[i]);
	}
}

void Fbx::InitConstantBuffer()
{
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
}

void Fbx::InitMaterial(fbxsdk::FbxNode* pNode)
{
	pMaterialList_ = new MATERIAL[materialCount_];
	for (int i = 0; i < materialCount_; i++) {

		//i番目のマテリアル情報を取得
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);

		//テクスチャ情報
		FbxProperty lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

		//テクスチャの数数
		int fileTextureCount = lProperty.GetSrcObjectCount<FbxFileTexture>();

		//テクスチャあり
		if (fileTextureCount != 0)
		{
			//テクスチャのファイルパスを取得
			FbxFileTexture* textureInfo = lProperty.GetSrcObject<FbxFileTexture>(0);
			const char* textureFilePath = textureInfo->GetRelativeFileName();

			//ファイル名+拡張子だけにする
			char name[_MAX_FNAME];	//ファイル名
			char ext[_MAX_EXT];	//拡張子
			_splitpath_s(textureFilePath, nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT);
			wsprintf(name, "%s%s", name, ext);

			//ファイルからテクスチャ作成
			pMaterialList_[i].pTexture_ = new Texture;
			pMaterialList_[i].pTexture_->Load(name);
		}

		//テクスチャ無し
		else
		{
			pMaterialList_[i].pTexture_ = nullptr;

			//マテリアルの色
			FbxSurfaceLambert* pMaterial = (FbxSurfaceLambert*)pNode->GetMaterial(i);//i番目のマテリアルを取得
			FbxDouble3  diffuse = pMaterial->Diffuse;
			pMaterialList_[i].diffuse_ = XMFLOAT4((float)diffuse[0], (float)diffuse[1], (float)diffuse[2], 1.0f);
		}
	}
}
	
