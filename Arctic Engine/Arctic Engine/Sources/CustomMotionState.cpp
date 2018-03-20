#include "..\Headers\CustomMotionState.h"



CustomMotionState::CustomMotionState()
{};

CustomMotionState::CustomMotionState(const btTransform &_initialPosition, std::weak_ptr<Transform> _trans)
{
    m_transform = _trans;
	m_position = _initialPosition;
}

CustomMotionState::~CustomMotionState()
{
}

void CustomMotionState::SetNode(std::weak_ptr<Transform> _trans)
{
    m_transform = _trans;
}

void CustomMotionState::getWorldTransform(btTransform &worldTrans) const
{
    worldTrans = m_position;
}

void CustomMotionState::setWorldTransform(const btTransform &worldTrans)
{
    if(m_transform.expired())
        return; // silently return before we set a node

    btQuaternion rot = worldTrans.getRotation();
	m_transform.lock()->SetRotationWithPhysics(rot);
    btVector3 pos = worldTrans.getOrigin();
	m_transform.lock()->SetPositionWithPhysics(pos);
}