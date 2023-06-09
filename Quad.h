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

struct VERTEX_DATE
{
	VERTEX* vertices;
	int num;
};

class Quad
{
protected:
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
	virtual HRESULT Initialize();

	//描画
	virtual void Draw(XMMATRIX& worldMatrix);

	//解放
	virtual void Release();

	//頂点データの初期化
	virtual VERTEX_DATE SetVertexDate();
	
	//頂点データ用のバッファを設定・作成する
	//引数１：頂点情報	引数２：頂点数
	HRESULT CreateVertexBuffer(VERTEX* _ver,int _n);


};

