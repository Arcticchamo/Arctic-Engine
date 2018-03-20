#include "..\Headers\BoxCollider.h"


void BoxCollider::Awake()
{
	
}

void BoxCollider::Start()
{
	
}

void BoxCollider::Update()
{
	Transform *trans = m_object.lock()->GetComponent<Transform>().lock().get();

	if (m_object.lock()->GetComponent<Transform>().lock()->GetMoved())
	{
		btTransform transform; 
		m_objRigidBody->getMotionState()->getWorldTransform(transform);
		
		Vector3 p = trans->GetWorldPosition();
		btVector3 pos(p.x, p.y, p.z);
		transform.setOrigin(pos);

		glm::quat r = trans->GetWorldRotation();
		btQuaternion rot(r.x, r.y, r.z, r.w);
		transform.setRotation(rot);

		m_objRigidBody->getMotionState()->setWorldTransform(transform);
		m_objRigidBody->setWorldTransform(transform);
		trans->SetMoved(false);
	}
	
}

void BoxCollider::Destroy()
{
	Physics::DestroyRigidBody(m_objRigidBody);
	delete m_objRigidBody->getMotionState();
	delete m_objRigidBody;
}

void BoxCollider::CreateRigidBody(float _mass, Vector3 _size)
{
	//Vector3 size(3, 0.25, 3);
	btVector3 s(_size.x, _size.y, _size.z);
	btBoxShape *object = new btBoxShape(s);

	Vector3 pos = m_object.lock()->GetComponent<Transform>().lock()->GetWorldPosition();
	btVector3 p(pos.x, pos.y, pos.z);

	btMotionState* motionState = new CustomMotionState(btTransform(btQuaternion(0, 0, 0, 1), p), m_object.lock()->GetComponent<Transform>());

	float m = _mass;

	btVector3 fall(0, 0, 0);

	if (m > 0.0f)
		object->calculateLocalInertia(m, fall);


	btRigidBody::btRigidBodyConstructionInfo rigidbodyCI(m, motionState, object, fall);

	m_objRigidBody = new btRigidBody(rigidbodyCI);
	m_objRigidBody->setActivationState(DISABLE_DEACTIVATION);

	Physics::AddRigidBody(m_objRigidBody);
}