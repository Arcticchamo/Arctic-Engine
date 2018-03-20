#ifndef COMPONENT_H
#define COMPONENT_H

#include "Global.h"
#include "GameObject.h"
#include "Objects.h"
#include <memory>

class GameObject;

class Component : public Objects, public std::enable_shared_from_this<Component>
{
protected:
	std::weak_ptr<GameObject> m_object;


public:
	virtual void Awake(){};
	virtual void Start(){};
	virtual void Update(){};
	virtual void Destroy(){};

	void setObject(std::weak_ptr<GameObject> _object)
	{
		m_object = _object;
	}

	virtual ~Component() {};
};

#endif


