#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include "GameObject.h"
#include <iostream>
#include <vector>
#include <memory>
#include <GLM\gtx\quaternion.hpp>
#include <Bullet\btBulletDynamicsCommon.h>
#include "BoxCollider.h"

class Transform : public Component
{
private:
	Vector3 m_worldPosition;
	glm::quat m_worldRotation;
	Vector3 m_worldScale;
	
	Vector3 m_localPosition;
	glm::quat m_localRotation;
	Vector3 m_localScale;

	std::weak_ptr<Transform> m_parent; 
	std::vector<std::weak_ptr<Transform>> m_children;

	bool m_transformMoved;
public:
	
	Transform();

	void Awake();
	void Start();
	void Update();
	void Destroy();

	void Translate(Vector3 _pos);
	void Rotate(glm::quat _rot);
	void Scale(Vector3 _scale);

	void TranslateChildren(Vector3 _pos, Vector3 _parentPos);
	void RotateChildren(glm::quat _rot, glm::quat _parentRot);
	void ScaleChildren(Vector3 _scale, Vector3 _parentScale);

	bool GetMoved();
	void SetMoved(bool _moved);

	Vector3 GetWorldPosition();
	glm::quat GetWorldRotation();
	Vector3 GetWorldScale();

	Vector3 GetLocalPosition();
	glm::quat GetLocalRotation();
	Vector3 GetLocalScale();

	void SetWorldPosition(Vector3 _pos);
	void SetWorldRotation(glm::quat _rot);
	void SetWorldScale(Vector3 _scale);

	void SetLocalPosition(Vector3 _pos);
	void SetLocalRotation(glm::quat _rot);
	void SetLocalScale(Vector3 _scale);

	void SetParent(std::shared_ptr<GameObject> _parent);
	void AddChild(std::shared_ptr<GameObject> _child);

	std::weak_ptr<Transform> GetParent();

	void SetStartingTransform(Vector3 _pos, glm::quat _rot, Vector3 _scale);

	void SetPositionWithPhysics(const btVector3 &_pos);
	void SetRotationWithPhysics(const btQuaternion &_rotation);
	void SetScaleWithPhysics(const btVector3 &_scale);

	~Transform(){};
};

#endif