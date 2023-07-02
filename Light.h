#pragma once

//�C���N���[�h
#include "Direct3D.h"
#include <DirectXMath.h>

//using�錾
using namespace DirectX;

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
	void SetIntensity(XMFLOAT4 intensity);

}