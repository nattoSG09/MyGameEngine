//インクルード
#include "Dice.h"

//コンストラクタ
Dice::Dice()
{
}

//デストラクタ
Dice::~Dice()
{
    Release();
}

//初期化
HRESULT Dice::Initialize()
{
	//頂点情報
	VERTEX vertices[] =
	{
		//面１
		{XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 前面（左上）0
		{XMVectorSet(1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 前面（右上）1
		{XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 前面（右下）2
		{XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 前面（左下）3

		//面４
		{XMVectorSet(-1.0f, 1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(-1.0f,0.0f,0.0f,0.0f)},	// 測面左（左上）4
		{XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f,0.0f,0.0f,0.0f) },	// 測面左（右上）5
		{XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f,0.0f,0.0f,0.0f) },	// 測面左（右下）6
		{XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(-1.0f,0.0f,0.0f,0.0f)},	// 測面左（左下）7

		//面３
		{XMVectorSet(1.0f, 1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(1.0f,0.0f,0.0f,0.0f)},	// 測面右（左上）8
		{XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(1.0f,0.0f,0.0f,0.0f)},	// 測面右（右上）9
		{XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(1.0f,0.0f,0.0f,0.0f)},	// 測面右（右下）10
		{XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(1.0f,0.0f,0.0f,0.0f)},	// 測面右（左下）11

		//面６
		{XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,1.0f,0.0f)},	// 背面（左上）12
		{XMVectorSet(-1.0f,  1.0f, 1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,1.0f,0.0f)},	// 背面（右上）13
		{XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,1.0f,0.0f)},	// 背面（右下）14
		{XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,0.0f,1.0f,0.0f)},	// 背面（左下）15

		//面５
		{XMVectorSet(-1.0f, 1.0f, 1.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,1.0f,0.0f,0.0f)},	// 上面（左上）16
		{XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,1.0f,0.0f,0.0f)},	// 上面（右上）17
		{XMVectorSet(1.0f, 1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,1.0f,0.0f,0.0f)},	// 上面（右下）18
		{XMVectorSet(-1.0f, 1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,1.0f,0.0f,0.0f)},	// 上面（左下）19

		//面２
		{XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},	// 上面（左上）20
		{XMVectorSet(1.0f,  -1.0f, -1.0f, 0.0f),XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},	// 上面（右上）21
		{XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},	// 上面（右下）22
		{XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) ,XMVectorSet(0.0f,-1.0f,0.0f,0.0f)},	// 上面（左下）23
	};

	//インデックス情報
	int index[] = {
		 0, 2, 3,  0, 1, 2,		//面１
		 4, 6, 7,  4, 5, 6,		//面４
		 8,10,11,  8, 9,10,		//面３
		12,14,15, 12,13,14,		//面６
		16,18,19, 16,17,18,		//面５
		20,22,23, 20,21,22,		//面２
	};

	HRESULT hr = CreateBuffers(SET_ARRAY_DATA(vertices), SET_ARRAY_DATA(index), "Assets\\Dice.png");
	if (FAILED(hr)) {
		MessageBox(nullptr, "バッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}
	return S_OK;
}

//描画
void Dice::Draw(XMMATRIX& worldMatrix)
{
	Quad::SetBuffers(worldMatrix);
	Direct3D::pContext_->DrawIndexed(36, 0, 0);
}
