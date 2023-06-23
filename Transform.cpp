#include "Transform.h"

Transform::Transform():
	matTranslate_{}, matRotate_{}, matScale_{}, position_{0,0,0}, rotate_{0,0,0}, scale_{1,1,1}
{
}

Transform::~Transform()
{
}

void Transform::Calclation()
{
    //変形：移動
    matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

	//変形：回転
	XMMATRIX rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
	XMMATRIX rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
	XMMATRIX rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
	matRotate_ = rotateZ * rotateX * rotateY;

	//変形：拡大縮小
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix()
{
	Calclation();
    return matRotate_ * matTranslate_ * matScale_;
}

XMMATRIX Transform::GetNormalMatrix()
{
	return matRotate_ * XMMatrixInverse(nullptr, matScale_);
}
