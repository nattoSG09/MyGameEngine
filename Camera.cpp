//インクルード
#include "Camera.h"

//定数宣言
const XMVECTOR INITIAL_POSITION = XMVectorSet(0, 3, -10, 0);//カメラの位置
const XMVECTOR INITIAL_TARGET = XMVectorSet(0, 0, 0, 0);	//カメラの焦点
const float NEAR_Z = 0.1f;	//近クリッピング面までの距離
const float FAR_Z = 100.0f;	//遠クリッピング面までの距離

//変数
namespace Camera {
	XMVECTOR position_;	//カメラの位置（視点）
	XMVECTOR target_;	//見る位置（焦点）
	XMMATRIX viewMatrix_;	//ビュー行列
	XMMATRIX projMatrix_;	//プロジェクション行列
}

//初期化
void Camera::Initialize(int winW,int winH)
{
	position_ = INITIAL_POSITION;	//カメラの位置
	target_ = INITIAL_TARGET;	//カメラの焦点

	//プロジェクション行列
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)winW / (FLOAT)winH, NEAR_Z, FAR_Z);
}

//更新
void Camera::Update()
{
	//ビュー行列の作成
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
}

//位置を設定
void Camera::SetPosition(XMVECTOR position)
{
	Camera::position_ = position;
}
void Camera::SetPosition(XMFLOAT3 position){
	SetPosition(XMLoadFloat3(&position));
}

//焦点を設定
void Camera::SetTarget(XMVECTOR target)
{
	Camera::target_ = target;
}
void Camera::SetTarget(XMFLOAT3 target){
	SetTarget(XMLoadFloat3(&target));
}

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix()
{
	return Camera::viewMatrix_;
}

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix()
{
	return Camera::projMatrix_;
}