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
	//初期化
	void Initialize(HWND _hWnd);
	
	//更新
	void Update();
	
	//キーを押しているかどうか
	bool IsKey(int keyCode);

	//今キーを押したかどうか
	bool IsKeyDown(int keyCode);

	//今キーを離したかどうか
	bool IsKeyUp(int keyCode);

	//解放
	void Release();
}