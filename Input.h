#pragma once
//�C���N���[�h
#include <dinput.h>

//�����J
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

//�}�N����`
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Input
{
	//������
	void Initialize(HWND _hWnd);
	
	//�X�V
	void Update();
	
	//�L�[�������Ă��邩�ǂ���
	bool IsKey(int keyCode);

	//���L�[�����������ǂ���
	bool IsKeyDown(int keyCode);

	//���L�[�𗣂������ǂ���
	bool IsKeyUp(int keyCode);

	//���
	void Release();
}