#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>
#include <string>
#include "Component.h"
#include "Objects.h"
#include <GL\glew.h>

//#include "Bounds.h"
//#include "BoxCollider.h"
//#include "Input.h"
//#include "MeshRenderer.h"
//#include "Objects.h"
//#include "OBJLoader.h"
//#include "Time.h"

class Transform;
class Component;

enum OBJECT_TYPE { 
	PLAYER_TYPE,
	NPC_TYPE,
	WORLDOBJECT_TYPE,
	CAMERA_TYPE,
	LIGHT_TYPE
};

class GameObject : public Objects, public std::enable_shared_from_this<GameObject>
{
protected:
	std::string m_name;
	OBJECT_TYPE m_object_Type;
	std::vector<std::shared_ptr<Component>> m_components;
	std::weak_ptr<Transform> m_transform;
	float m_mass;
	Vector3 m_size; 

public:

	virtual void Awake(){};
	virtual void Start(){};
	virtual void Update(){};
	virtual void Destroy(){};
	virtual void Render(){};

	std::weak_ptr<Transform> GetTransform();

	GameObject* GetGameObject();

	template <class CompType>
	std::weak_ptr<CompType> AddComponent()
	{
		std::shared_ptr<CompType> Temp = std::make_shared<CompType>();
		m_components.push_back(Temp);
		Temp->setObject(shared_from_this());
		return Temp;
	}

	//A Template function that gets the type passed in if available
	template <class compType>
	std::weak_ptr<compType> GetComponent()
	{
		for (unsigned int i = 0; i < m_components.size(); i++)
		{
			std::weak_ptr<compType> c = std::dynamic_pointer_cast<compType>(m_components.at(i));

			if (!c.expired())
			{
				return c;
			}
		}
		return std::weak_ptr<compType>();
	}

	float GetMass()
	{
		return m_mass; 
	}

	virtual ~GameObject(){};
};

#endif
