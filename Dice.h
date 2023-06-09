#pragma once
#include "Quad.h"

class Dice : public Quad
{
public:
	//コンストラクタ
	Dice();
	//デストラクタ
	~Dice();

	//頂点データの初期化
	VERTEX_DATE SetVertexDate() override;
};

