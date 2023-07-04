#pragma once

//インクルード
#include "Direct3D.h"
#include <DirectXMath.h>

//using宣言
using namespace DirectX;

struct COLOR {
	float R, G, B;
};

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
	void SetIntensity(float intensity);

	//ライトの色を設定
	void SetColor(COLOR color);

	//ライトの位置を取得
	XMFLOAT4 GetPosition();

	//ライトの強度・色を取得
	XMFLOAT4 GetworldLight();
}