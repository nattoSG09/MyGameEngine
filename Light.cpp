#include "Light.h"

namespace Light {
	XMFLOAT4 position_;
	XMFLOAT4 worldLight_;
	COLOR color_;
	float intensity_;
}

void Light::Initialize()
{
	//位置の初期化
	position_ = { 0.0f,3.0f,-2.0f,0.0f };
	
	//光の強度・色の初期化
	color_ = { 1.0f,1.0f,1.0f };intensity_ = 1.0f;
	worldLight_ = { (color_.R * intensity_),(color_.G * intensity_) ,(color_.B * intensity_),1.0f };
}

void Light::Update()
{
	worldLight_ = { (color_.R * intensity_),(color_.G * intensity_) ,(color_.B * intensity_),1.0f };
}

void Light::SetPosition(XMFLOAT4 position)
{
	Light::position_ = position;
}

void Light::SetIntensity(float intensity)
{
	Light::intensity_ = intensity;
}

void Light::SetColor(COLOR color)
{
}

XMFLOAT4 Light::GetPosition()
{
	return Light::position_;
}

XMFLOAT4 Light::GetworldLight()
{
	return  Light::worldLight_;
}
