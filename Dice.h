#pragma once

//�C���N���[�h
#include "Quad.h"

class Dice : public Quad
{
public:
	//�R���X�g���N�^
	Dice();

	//�f�X�g���N�^
	~Dice();

	//���_���̏�����
	void InitVertexData() override;

	//�C���f�b�N�X���̏�����
	void InitIndexData() override;
};

