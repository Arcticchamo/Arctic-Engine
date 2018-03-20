#ifndef CUSTOM_MOTION_STATE_H
#define CUSTOM_MOTION_STATE_H

#include <Bullet\btBulletCollisionCommon.h>
#include "Transform.h"

class CustomMotionState : public btMotionState
{
	public:
		CustomMotionState();
		CustomMotionState(const btTransform &_initialPosition, std::weak_ptr<Transform> _trans);

		virtual ~CustomMotionState();

		void SetNode(std::weak_ptr<Transform> _trans);
		virtual void getWorldTransform(btTransform &worldTrans) const;
		virtual void setWorldTransform(const btTransform &worldTrans);

	protected:
		std::weak_ptr<Transform> m_transform;
		btTransform m_position;
};

#endif