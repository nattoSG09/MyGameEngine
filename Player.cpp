#include "Player.h"
#include "Engine/Fbx.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),pFbx(nullptr)
{
}

void Player::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/Ball2.fbx");
}

void Player::Update()
{
	transform_.rotate_.y += 0.1;
}

void Player::Draw()
{

	pFbx->Draw(this->transform_);
}

void Player::Release()
{
	pFbx->Release();
	delete pFbx;
}
