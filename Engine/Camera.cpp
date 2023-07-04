//�C���N���[�h
#include "Camera.h"

//�萔�錾
const XMVECTOR INITIAL_POSITION = XMVectorSet(0, 3, -10, 0);//�J�����̈ʒu
const XMVECTOR INITIAL_TARGET = XMVectorSet(0, 0, 0, 0);	//�J�����̏œ_
const float NEAR_Z = 0.1f;	//�߃N���b�s���O�ʂ܂ł̋���
const float FAR_Z = 100.0f;	//���N���b�s���O�ʂ܂ł̋���

//�ϐ�
namespace Camera {
	XMVECTOR position_;	//�J�����̈ʒu�i���_�j
	XMVECTOR target_;	//����ʒu�i�œ_�j
	XMMATRIX viewMatrix_;	//�r���[�s��
	XMMATRIX projMatrix_;	//�v���W�F�N�V�����s��
}

//������
void Camera::Initialize(int winW,int winH)
{
	position_ = INITIAL_POSITION;	//�J�����̈ʒu
	target_ = INITIAL_TARGET;	//�J�����̏œ_

	//�v���W�F�N�V�����s��
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)winW / (FLOAT)winH, NEAR_Z, FAR_Z);
}

//�X�V
void Camera::Update()
{
	//�r���[�s��̍쐬
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
}

//�ʒu��ݒ�
void Camera::SetPosition(XMVECTOR position)
{
	Camera::position_ = position;
}
void Camera::SetPosition(XMFLOAT3 position){
	SetPosition(XMLoadFloat3(&position));
}

//�œ_��ݒ�
void Camera::SetTarget(XMVECTOR target)
{
	Camera::target_ = target;
}
void Camera::SetTarget(XMFLOAT3 target){
	SetTarget(XMLoadFloat3(&target));
}

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix()
{
	return Camera::viewMatrix_;
}

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix()
{
	return Camera::projMatrix_;
}