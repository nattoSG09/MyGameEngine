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

	void InitVertexData() override;
	void InitIndexData() override;
};

