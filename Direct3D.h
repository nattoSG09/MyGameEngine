#pragma once
//�C���N���[�h
#include <d3d11.h>

//�����J
#pragma comment(lib, "d3d11.lib")

//�萔�錾
const int WINDOW_WIDTH = 1280;  //�E�B���h�E�̕�
const int WINDOW_HEIGHT = 720; //�E�B���h�E�̍���

namespace Direct3D
{
	//������
	void Initialize(int winW, int winH, HWND hWnd);

	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();
};