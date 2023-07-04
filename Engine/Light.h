#pragma once

//�C���N���[�h
#include "Direct3D.h"
#include <DirectXMath.h>

//using�錾
using namespace DirectX;

struct COLOR {
	float R, G, B;
};

//-----------------------------------------------------------
//���C�g
//-----------------------------------------------------------
namespace Light
{
	//������
	void Initialize();

	//�X�V
	void Update();

	//���C�g�̈ʒu��ݒ�
	void SetPosition(XMFLOAT4 position);

	//���C�g�̋��x��ݒ�
	void SetIntensity(float intensity);

	//���C�g�̐F��ݒ�
	void SetColor(COLOR color);

	//���C�g�̈ʒu���擾
	XMFLOAT4 GetPosition();

	//���C�g�̋��x�E�F���擾
	XMFLOAT4 GetworldLight();
}