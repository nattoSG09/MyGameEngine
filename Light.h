#pragma once

//インクルード
#include "Direct3D.h"
#include <DirectXMath.h>

//using宣言
using namespace DirectX;

//-----------------------------------------------------------
//ライト
//-----------------------------------------------------------
namespace Light
{
	//初期化
	void Initialize();

	//更新
	void Update();

	//ライトの位置を設定
	void SetPosition(XMFLOAT4 position);

	//ライトの強度を設定
	void SetIntensity(XMFLOAT4 intensity);

}