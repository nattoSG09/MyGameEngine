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
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) },	// �l�p�`�̒��_�i����j
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },	// �l�p�`�̒��_�i�E��j
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) },	// �l�p�`�̒��_�i�E���j
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) }	// �l�p�`�̒��_�i�����j
		//XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f)		//�ǉ����_(�܊p�`)
	};

	VERTEX_DATE ret;
	ret.vertices = vers;
	ret.num = 4;
	return ret;
}