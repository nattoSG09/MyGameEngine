#include "Input.h"

namespace Input 
{
	//�f�o�C�X�̓��͏����i�[����ϐ�(�f�o�C�X��Ɉ�ϐ���p�ӂ���)
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;

	//�Pbyte(256bit)�̏�񂪓������ϐ�
	BYTE keyState[256] = { 0 };

	void Input::Initialize(HWND _hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(_hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}

	void Input::Update()
	{
		pKeyDevice->Acquire();//<-�Ȃ񂩏����Ȃ��Ⴂ���Ȃ����
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
	}

	bool Input::IsKey(int _keyCord)
	{
		if (keyState[_keyCord] & 0x80 )
		{
			return true;
		}
		return false;
	}

	void Input::Release()
	{
		SAFE_RELEASE(pDInput);
	}
}

