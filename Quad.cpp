#include "Quad.h"
#include "Camera.h"
#include <iostream>

using std::size;


Quad::Quad()
	:pVertexBuffer_(nullptr),pTexture_(nullptr),pIndexBuffer_(nullptr),pConstantBuffer_(nullptr)
{
}

Quad::~Quad()
{
	Release();
}

HRESULT Quad::Initialize()
{
	//頂点情報
	VERTEX vers[] =
	{
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) },	// 前面（左上）0
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },	// 前面（右上）1
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) },	// 前面（右下）2
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },	// 前面（左下）3
	};

	//インデックス情報
	int index[] = {
		 0, 2, 3,  0, 1, 2
	};

	HRESULT hr = CreateBuffers(vers,(int)size(vers),index,(int)size(index),"Assets\\Dice.png");
	if (FAILED(hr)) {
		MessageBox(nullptr, "バッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}
	return S_OK;
}

void Quad::Draw(XMMATRIX& worldMatrix)
{
	Quad::SetBuffers(worldMatrix);
	Direct3D::pContext_->DrawIndexed(6, 0, 0);
}

void Quad::Release()
{
	SAFE_DELETE(pTexture_);
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}

HRESULT Quad::CreateBuffers(VERTEX* _ver,int _vn, int* _index, int _in,string _imageData)
{
	HRESULT hr;
	// 頂点データ用バッファ作成
	hr = CreateVertexBuffer(_ver, _vn);
	if (FAILED(hr)) {
		MessageBox(nullptr, "頂点データ用バッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}

	// インデックスバッファ生成
	hr = CreateIndexBuffer(_index, _in);
	if (FAILED(hr)) {
		MessageBox(nullptr, "インデックスバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}

	//コンスタントバッファ作成
	CreateConstantBuffer(_imageData);
	if (FAILED(hr)) {
		MessageBox(nullptr, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;//エラー時の戻り値
	}
	return S_OK;
}

void Quad::SetBuffers(XMMATRIX& worldMatrix)
{
	//カメラの情報からコンスタントバッファをセット
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る

	//テクスチャとサンプラーをシェーダーへ
	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);
	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開

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

}

HRESULT Quad::CreateVertexBuffer(VERTEX* _ver,int _n)
{
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX)* _n;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = _ver;

	HRESULT hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr)) {
		return hr;//エラー時の戻り値
	}
	return S_OK;
}

HRESULT Quad::CreateIndexBuffer(int* _index, int _n)
{
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * _n;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = _index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	HRESULT hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr)) {
		return hr;//エラー時の戻り値
	}
	return S_OK;
}

HRESULT Quad::CreateConstantBuffer(string _imageData)
{
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	pTexture_ = new Texture;
	pTexture_->Load(_imageData);

	HRESULT hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr)) {
		return hr;//エラー時の戻り値
	}
	return S_OK;
}
