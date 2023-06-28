#pragma once

//インクルード
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include <vector>

using std::vector;

//前方宣言
class Texture;

//リンカ
#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

//using宣言
using std::string;

class Fbx
{
private:

	//マテリアル
	struct MATERIAL
	{
		Texture* pTexture_;
		XMFLOAT4 diffuse_;
	};

	//コンスタントバッファに情報を渡すための構造体
	struct CONSTANT_BUFFER{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
		XMVECTOR	lightPos;
		XMFLOAT4	diffuseColor;
		bool		isTexture;
	};
	//頂点情報
	struct VERTEX{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};

	//各バッファ情報
	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数
	std::vector<int> indexCount_;

public:
	//コンストラクタ
	Fbx();

	//デストラクタ
	~Fbx();

	//Fbxファイルをロード
	HRESULT Load(string fileName);

	//描画
	void Draw(Transform& transform);
	
	//解放
	void Release();

	//各バッファの初期化
	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void InitConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
};
