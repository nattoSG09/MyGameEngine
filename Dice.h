#pragma once
#include "Quad.h"

class Dice : public Quad
{
public:
	//�R���X�g���N�^
	Dice();
	//�f�X�g���N�^
	~Dice();

	//���_�f�[�^�̏�����
	VERTEX_DATE SetVertexDate() override;
};

