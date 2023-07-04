#include "Input.h"


namespace Input 
{
	//デバイスの入力情報を格納する変数(デバイス一つに一つ変数を用意する)
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;

	BYTE keyState[256] = { 0 };//現在の各キーの状態
	BYTE prevKeyState[256];    //前フレームでの各キーの状態

	void Input::Initialize(HWND _hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(_hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}

	void Input::Update()
	{
		//常に前フレームの状態を取得
		memcpy(prevKeyState, keyState, sizeof(BYTE) * 256);

		//memcpyについて
		/*
			メモリをコピーするやつ
			引数(コピー先の変数,コピー元の変数,サイズ)
		*/


		pKeyDevice->Acquire();//<-なんか書かなきゃいけないやつ
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
	}

	bool Input::IsKey(int keyCode)
	{
		if (keyState[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}


	bool IsKeyDown(int keyCode)
	{
		//今は押してて、前回は押してない
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;

		//今は押してて、前回は押してない
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//今は押してなくて、前回は押してる
		if (!IsKey(keyCode) && (prevKeyState[keyCode] & 0x80))
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

