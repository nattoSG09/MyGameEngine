#pragma once

//インクルード
#include "Quad.h"

class Dice : public Quad
{
public:
	//コンストラクタ
	Dice();

	//デストラクタ
	~Dice();

	//初期化
	HRESULT Initialize() override;

	//描画
	void Draw(XMMATRIX& worldMatrix) override;
};

