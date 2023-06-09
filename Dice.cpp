#include "Dice.h"

Dice::Dice()
{
}

Dice::~Dice()
{
    Release();
}

VERTEX_DATE Dice::SetVertexDate()
{
	VERTEX vers[] =
	{
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) },	// 四角形の頂点（左上）
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },	// 四角形の頂点（右上）
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) },	// 四角形の頂点（右下）
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) }	// 四角形の頂点（左下）
		//XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f)		//追加頂点(五角形)
	};

	VERTEX_DATE ret;
	ret.vertices = vers;
	ret.num = 4;
	return ret;
}