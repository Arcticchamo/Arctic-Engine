#include "..\Headers\Physics.h"

btBroadphaseInterface* Physics::m_broadphase;
btDefaultCollisionConfiguration* Physics::m_collisionConfiguration;
btCollisionDispatcher* Physics::m_dispatcher;
btSequentialImpulseConstraintSolver* Physics::m_solver;
btDiscreteDynamicsWorld* Physics::m_dynamicWorld;

GLDebugDrawer Physics::m_debug; 


Physics::Physics()
{

}

Physics::~Physics()
{

}

void Physics::Start()
{
	m_broadphase = new btDbvtBroadphase();
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	m_solver = new btSequentialImpulseConstraintSolver();
	m_dynamicWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);

	m_dynamicWorld->setGravity(btVector3(0.0f, -5.0f, 0.0f));
}

void Physics::Update(double dt)
{
	m_dynamicWorld->stepSimulation(dt, 10);
}

void Physics::DrawDebugWorld()
{
	m_dynamicWorld->debugDrawWorld();
}

void Physics::InitializeDebug()
{
	m_debug.Initialise();
	m_debug.setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	m_dynamicWorld->setDebugDrawer(&m_debug);
}

void Physics::AddRigidBody(btRigidBody* _rigid)
{
	m_dynamicWorld->addRigidBody(_rigid);
}

void Physics::DestroyRigidBody(btRigidBody* _rigid)
{
	m_dynamicWorld->removeRigidBody(_rigid);
}

void Physics::Destroy()
{
	delete m_dynamicWorld;
	delete m_solver;
	delete m_collisionConfiguration;
	delete m_dispatcher;
	delete m_broadphase;
}