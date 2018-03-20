#ifndef PHYSICS_H
#define PHYSICS_H

#include <Bullet\btBulletDynamicsCommon.h>
#include <iostream>
#include <vector>

#include "DebugDrawer.h"
#include "Transform.h"

class Physics
{
private:
	static btBroadphaseInterface *m_broadphase; 
	static btDefaultCollisionConfiguration *m_collisionConfiguration;
	static btCollisionDispatcher *m_dispatcher;
	static btSequentialImpulseConstraintSolver *m_solver;
	static btDiscreteDynamicsWorld *m_dynamicWorld;

	static GLDebugDrawer m_debug; 
public:
	Physics();
	~Physics();

	static void Start();
	static void Update(double dt);
	static void Destroy();
	static void InitializeDebug();
	static void DrawDebugWorld();
	static void AddRigidBody(btRigidBody* _rigid);
	static void DestroyRigidBody(btRigidBody* _rigid);
};


#endif