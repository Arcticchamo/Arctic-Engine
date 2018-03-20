#include "..\Headers\GameObject.h"

std::weak_ptr<Transform> GameObject::GetTransform()
{
	return this->m_transform;
}

GameObject* GameObject::GetGameObject()
{
	return this;
}