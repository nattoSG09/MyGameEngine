#pragma once
//インクルード
#include <dinput.h>

//リンカ
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

//マクロ定義
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Input
{
	void Initialize(HWND _hWnd);
	void Update();
	bool IsKey(int _keyCord);
	void Release();
}