#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Component.h"
#include "Bounds.h"
#include "Transform.h"
#include "Physics.h"
#include "CustomMotionState.h"
#include <Bullet\btBulletDynamicsCommon.h>

class BoxCollider : public Component
{
private:
	btRigidBody* m_objRigidBody;

public:
	BoxCollider() {}

	void CreateRigidBody(float _mass, Vector3 _size);

	void Awake();
	void Start();
	void Update();
	void Destroy();

	btRigidBody* GetRigidBody()
	{
		return m_objRigidBody;
	}

};

#endif