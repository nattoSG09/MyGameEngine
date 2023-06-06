#pragma once

//インクルード
#include <DirectXMath.h>
#include "Direct3D.h"

using namespace DirectX;

class Quad
{
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
public:
	Quad();
	~Quad();
	HRESULT Initialize();
	void Draw();
	void Release();
};

