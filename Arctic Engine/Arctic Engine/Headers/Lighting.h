#ifndef LIGHTING_H
#define LIGHTING_H

#include "GameObject.h"
#include "Light.h"
#include "Transform.h"

class Lighting : public GameObject
{
private: 
	std::string m_name; 
	OBJECT_TYPE m_object_Type;
	std::weak_ptr<Light> m_light;

public:
	void Awake();
	void Start();
	void Update();
	void Destroy();

	Lighting();
	Lighting(std::string _name, OBJECT_TYPE _objtype);

	~Lighting();
};


#endif