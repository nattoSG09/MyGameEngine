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
	void Initialize(HWND _hWnd);
	void Update();
	bool IsKey(int _keyCord);
	void Release();
}