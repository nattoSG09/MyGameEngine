#include "Input.h"

namespace Input 
{
	//デバイスの入力情報を格納する変数(デバイス一つに一つ変数を用意する)
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;

	//１byte(256bit)の情報が入れられる変数
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
		pKeyDevice->Acquire();//<-なんか書かなきゃいけないやつ
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

