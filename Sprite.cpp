#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite()
	:veritices_(),index_()
	,pVertexBuffer_(nullptr), pTexture_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr)
{
}

Sprite::~Sprite()
{
	Release();
}

HRESULT Sprite::Initialize()
{
	HRESULT hr = S_OK;
	
	//頂点バッファを作成(コンパイル)
	hr = CreateVertexBuffer();
	if (FAILED(hr)) {return hr;
	}

	//インデックスバッファを作成(コンパイル)
	hr = CreateIndexBuffer();
	if (FAILED(hr)) {return hr;
	}

	//テクスチャをロード
	hr = LoadTexture();
	if (FAILED(hr)) {return hr;
	}

	//コンスタントバッファを作成(コンパイル)
	hr = CreateConstantBuffer();
	if (FAILED(hr)) {return hr;
	}

	return S_OK;
}

void Sprite::Draw(XMMATRIX& worldMatrix)
{
	//コンスタントバッファに情報をパス
	PassDataToCB(worldMatrix);
	
	//各バッファ―情報をセット
	SetBufferToPipeline();
}

void Sprite::Release()
{
	SAFE_RELEASE(pTexture_);
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);

}

void Sprite::InitVertexData()
{
	veritices_ = {
	{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) },
	{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },
	{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) },
	{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) }
	};
}

HRESULT Sprite::CreateVertexBuffer()
{
	//頂点情報を設定
	InitVertexData();

	D3D11_BUFFER_DESC bd_vertex;

	bd_vertex.ByteWidth = sizeof(VERTEX)*  veritices_.size();
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

void Sprite::InitIndexData()
{
	//インデックス情報
	index_ = vector<int>{
		 0, 2, 3,  0, 1, 2
	};
}

HRESULT Sprite::CreateIndexBuffer()
{
	//インデックス情報を設定
	InitIndexData();

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

HRESULT Sprite::CreateConstantBuffer()
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

HRESULT Sprite::LoadTexture()
{
	pTexture_ = new Texture;
	HRESULT hr =pTexture_->Load("Assets\\Dice.png");
	if (FAILED(hr)) {

		return hr;//エラー時の戻り値
	}
	return S_OK;
}

void Sprite::PassDataToCB(XMMATRIX& worldMatrix)
{
	//コンスタントバッファをセット
	CONSTANT_BUFFER cb;
	cb.matW = XMMatrixTranspose(worldMatrix);

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

void Sprite::SetBufferToPipeline()
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
