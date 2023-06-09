#pragma once

//インクルード
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"

using namespace DirectX;

//コンスタントバッファー
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
};

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};


class Quad
{
private:
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;		//テクスチャ
public:
	//コンストラクタ
	Quad();

	//デストラクタ
	~Quad();

	//初期化
	HRESULT Initialize();

	//描画
	void Draw(XMMATRIX& worldMatrix);

	//解放
	void Release();
};

