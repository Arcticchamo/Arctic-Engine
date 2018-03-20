#include "..\Headers\Transform.h"


void Transform::Awake()
{
	m_transformMoved = false;
}

void Transform::Start()
{
	
}

void Transform::Update()
{

}

void Transform::Destroy()
{

}

Transform::Transform()
{
	//Set default values
	m_worldPosition = Vector3(0.0f, 0.0f, 0.0f);
	m_worldRotation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
	m_worldScale = Vector3(1.0f, 1.0f, 1.0f);
	
	m_localPosition = Vector3(0.0f, 0.0f, 0.0f);
	m_localRotation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
	m_localScale = Vector3(1.0f, 1.0f, 1.0f);	
}

void Transform::Translate(Vector3 _pos)
{
	m_transformMoved = true; 

	btRigidBody* body = m_object.lock()->GetComponent<BoxCollider>().lock()->GetRigidBody();

	//Update the position of the object
	m_worldPosition += _pos;
	m_localPosition += _pos;

	body->applyForce(btVector3(_pos.x, _pos.y, _pos.z), btVector3(m_worldPosition.x, m_worldPosition.y, m_worldPosition.z));

	//If the object has any children, update their positions
	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children.at(i).lock()->TranslateChildren(_pos, m_worldPosition);
	}
}

void Transform::TranslateChildren(Vector3 _pos, Vector3 _parentPos)
{
	//Translates Child
	m_transformMoved = true; 

	btRigidBody* body = m_object.lock()->GetComponent<BoxCollider>().lock()->GetRigidBody();

	//Update the position of the object
	m_worldPosition += _pos;

	body->applyForce(btVector3(_pos.x, _pos.y, _pos.z), btVector3(m_worldPosition.x, m_worldPosition.y, m_worldPosition.z));

	//Checks if child has any children and repeats 
	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children.at(i).lock()->TranslateChildren(_pos, m_worldPosition);
	}
}

void Transform::Rotate(glm::quat _rot)
{
	m_transformMoved = true; 

	//glm::quat q; 

	//float pitchC = std::cos(_rot.x);
	//float pitchS = std::sin(_rot.x);

	//float yawC = std::cos(_rot.y);
	//float yawS = std::sin(_rot.y);

	//float rollC = std::cos(_rot.z);
	//float rollS = std::sin(_rot.z);

	//Mat4 pitch(1, 0, 0, 0, 
	//		   0, pitchC, pitchS, 0, 
	//		   0, -pitchS, pitchC, 0, 
	//		   0, 0, 0, 1);

	//Mat4 yaw(yawC, 0, -yawS, 0, 
	//		 0, 1, 0, 0, 
	//		 yawS, 0, yawC, 0,
	//		 0, 0, 0, 1);

	//Mat4 roll(rollC, rollS, 0, 0,
	//		  -rollS, rollC, 0, 0, 
	//		  0, 0, 1, 0, 
	//		  0, 0, 0, 1);

	//Mat4 rotation = (roll * yaw) * pitch;
	//q = glm::quat_cast(rotation);

	////Update the rotation of the object
	//m_worldRotation += q;
	//m_localRotation += q;

	m_worldRotation += _rot;
	m_localRotation += _rot; 

	//Checks if there are any children to rotate
	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children.at(i).lock()->RotateChildren(_rot, m_worldRotation);
	}
}

void Transform::RotateChildren(glm::quat _rot, glm::quat _parentRot)
{
	//Rotates child
	m_worldRotation += _rot;

	//Checks if child has any children to rotate
	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children.at(i).lock()->RotateChildren(_rot, m_worldRotation);
	}
}

void Transform::Scale(Vector3 _scale)
{
	m_transformMoved = true; 

	//Updates the scale value of the object
	m_worldScale += _scale;
	m_localScale += _scale;
	
	//Checks for children to scale
	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children.at(i).lock()->ScaleChildren(_scale, m_worldScale);
	}
}

void Transform::ScaleChildren(Vector3 _scale, Vector3 _parentScale)
{
	//Scales child
	m_worldScale += _scale;

	//Checks if child has any children to scale
	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children.at(i).lock()->ScaleChildren(_scale, m_worldScale);
	}
}

bool Transform::GetMoved()
{
	return m_transformMoved;
}

void Transform::SetMoved(bool _moved)
{
	m_transformMoved = _moved;
}

Vector3 Transform::GetWorldPosition()
{
	return m_worldPosition;
}

Vector3 Transform::GetLocalPosition()
{
	return m_localPosition;
}

glm::quat Transform::GetWorldRotation()
{
	return m_worldRotation;
}

glm::quat Transform::GetLocalRotation()
{
	return m_localRotation;
}

Vector3 Transform::GetWorldScale()
{
	return m_worldScale;
}

Vector3 Transform::GetLocalScale()
{
	return m_localScale;
}

void Transform::SetWorldPosition(Vector3 _pos)
{
	m_worldPosition = _pos;
}

void Transform::SetLocalPosition(Vector3 _pos)
{
	m_localPosition = _pos;
}

void Transform::SetWorldRotation(glm::quat _rot)
{
	m_worldRotation = _rot;
}

void Transform::SetLocalRotation(glm::quat _rot)
{
	m_localRotation = _rot;
}

void Transform::SetWorldScale(Vector3 _scale)
{
	m_worldScale = _scale;
}

void Transform::SetLocalScale(Vector3 _scale)
{
	m_localScale = _scale;
}

void Transform::SetParent(std::shared_ptr<GameObject> _parent)
{
	m_parent = _parent->GetTransform();
}

void Transform::AddChild(std::shared_ptr<GameObject> _child)
{
	m_children.push_back(_child->GetTransform());
}

std::weak_ptr<Transform> Transform::GetParent()
{
	return m_parent;
}

void Transform::SetStartingTransform(Vector3 _pos, glm::quat _rot, Vector3 _scale)
{
	m_worldPosition = _pos; 
	m_localPosition = _pos;

	m_worldRotation = _rot;
	m_localRotation = _rot;

	m_worldScale = _scale; 
	m_localScale = _scale; 
}

	void Transform::SetPositionWithPhysics(const btVector3 &_pos)
	{
		m_worldPosition.x = _pos.getX(); 
		m_worldPosition.y = _pos.getY(); 
		m_worldPosition.z = _pos.getZ(); 
	}

	void Transform::SetRotationWithPhysics(const btQuaternion &_rot)
	{
		m_worldRotation.w = _rot.getW();
		m_worldRotation.x = _rot.getX();
		m_worldRotation.y = _rot.getY();
		m_worldRotation.z = _rot.getZ();
	}

	void Transform::SetScaleWithPhysics(const btVector3 &_scale)
	{
		m_worldScale.x = _scale.getX(); 
		m_worldScale.y = _scale.getY(); 
		m_worldScale.z = _scale.getZ(); 
	}