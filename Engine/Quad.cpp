//インクルード
#include "Quad.h"
#include "Camera.h"

//コンストラクタ
Quad::Quad()
	:veritices_(),index_()
	,pVertexBuffer_(nullptr),pTexture_(nullptr),pIndexBuffer_(nullptr),pConstantBuffer_(nullptr)
{
}

//デストラクタ
Quad::~Quad()
{
	Release();
}

//初期化
HRESULT Quad::Initialize()
{
	HRESULT hr = S_OK;

	//テクスチャをロード
	hr = LoadTexture();
	if (FAILED(hr)) {
		return hr;
	}

	//頂点情報を設定
	InitVertexData();

	//インデックス情報を設定
	InitIndexData();

	//頂点バッファを作成(コンパイル)
	hr = CreateVertexBuffer();
	if (FAILED(hr)) {
		return hr;
	}

	//インデックスバッファを作成(コンパイル)
	hr = CreateIndexBuffer();
	if (FAILED(hr)) {
		return hr;
	}

	//コンスタントバッファを作成(コンパイル)
	hr = CreateConstantBuffer();
	if (FAILED(hr)) {
		return hr;
	}

	return S_OK;
}

//描画
void Quad::Draw(Transform _transform)
{
	

	//シェーダーを切り替える
	Direct3D::SetShader(SHADER_3D);

	//コンスタントバッファに情報をパス
	PassDataToCB(_transform);

	//各バッファ―情報をセット
	SetBufferToPipeline();
}

//解放
void Quad::Release()
{
	SAFE_DELETE(pTexture_);
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}

void Quad::InitVertexData()
{
	//頂点情報
	veritices_ ={
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f,0.0f) },	// 前面（左上）0
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f,0.0f) },	// 前面（右上）1
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f,0.0f) },	// 前面（右下）2
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f,0.0f) },	// 前面（左下）3
	};
}

HRESULT Quad::CreateVertexBuffer()
{
	D3D11_BUFFER_DESC bd_vertex;

	bd_vertex.ByteWidth = sizeof(VERTEX) * veritices_.size();
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = veritices_.data();

	HRESULT hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr)) {
		return hr;//エラー時の戻り値
	}
	return S_OK;
}

void Quad::InitIndexData()
{
	//インデックス情報
	index_ = {
		 0, 2, 3,  0, 1, 2
	};
}

HRESULT Quad::CreateIndexBuffer()
{
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * index_.size();
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index_.data();
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	HRESULT hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr)) {

		return hr;//エラー時の戻り値
	}
	return S_OK;
}

HRESULT Quad::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	HRESULT hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr)) {
		return hr;//エラー時の戻り値
	}
	return S_OK;
}

HRESULT Quad::LoadTexture()
{
	pTexture_ = new Texture;
	HRESULT hr = pTexture_->Load("Assets\\Dice.png");
	if (FAILED(hr)) {
		return hr;//エラー時の戻り値
	}
	return S_OK;
}

void Quad::PassDataToCB(Transform _transform)
{
	//コンスタントバッファをセット
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(_transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.matNormal = XMMatrixTranspose(_transform.GetNormalMatrix());
	cb.lightPos = XMVectorSet(-0.7f, 0.5f, -0.7f, 0.0f);

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る

	//テクスチャとサンプラーをシェーダーへ
	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);
	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);
	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開
}

void Quad::SetBufferToPipeline()
{
	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用
	Direct3D::pContext_->DrawIndexed(index_.size(), 0, 0);
}
