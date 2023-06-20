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
    //à⁄ìÆçsóÒ
    matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

	//âÒì]çsóÒ
	XMMATRIX rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
	XMMATRIX rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
	XMMATRIX rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
	matRotate_ = rotateZ * rotateX * rotateY;

	//ägëÂèkè¨
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix()
{
	Calclation();
    return matTranslate_ * matRotate_ * matScale_;
}
