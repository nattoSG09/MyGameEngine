#include "Light.h"

namespace Light {
	XMFLOAT4 position_;
	XMFLOAT4 color_;
	float intensity_;
}

void Light::Initialize()
{

	float i = intensity_;
	position_ = { 0.0f,3.0f,-2.0f,0.0f };
	color_ = { 1.0f*i,1.0f*i ,1.0f*i ,1.0f*i };

}

void Light::Update()
{
}

void Light::SetPosition(XMFLOAT4 position)
{
}

void Light::SetIntensity(XMFLOAT4 intensity)
{
}
