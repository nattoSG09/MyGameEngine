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

	//������
	HRESULT Initialize() override;

	//�`��
	void Draw(XMMATRIX& worldMatrix) override;
};

