#pragma once

#include œœœœœ
#include "Fbx.h"
#include "Transform.h"

class GameObject
{
	œœœœœœœœ childList_;
	Transform	transform_;
	GameObject*	pParent_;
	string	objectName_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
};