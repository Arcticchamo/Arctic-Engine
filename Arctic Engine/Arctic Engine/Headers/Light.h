#ifndef LIGHT_H
#define LIGHT_H

#include "Component.h"
#include "Resources.h"

class Light : public Component
{
private:
	GLuint m_shader; 

	GLint m_direction;
	GLint m_colour;

	Vector3 m_directionLightDir;
	Vector3 m_directionLightColour;

public:
	void Awake();
	void Start();
	void Update();
	void Destroy();

	Light(){};
	~Light(){};

};


#endif 