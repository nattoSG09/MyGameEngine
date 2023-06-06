#pragma once

//インクルード
#include <DirectXMath.h>
#include "Direct3D.h"

using namespace DirectX;

//コンスタントバッファー
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
};

class Quad
{
private:
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
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

