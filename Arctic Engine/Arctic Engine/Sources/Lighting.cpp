#include "..\Headers\Lighting.h"

Lighting::Lighting()
{

}

Lighting::Lighting(std::string _name, OBJECT_TYPE _objtype)
{
	m_name = _name;
	m_object_Type = _objtype;
}

Lighting::~Lighting()
{

}

void Lighting::Awake()
{

}

void Lighting::Start()
{
	m_light = AddComponent<Light>();

	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components.at(i)->Awake();
	}

	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components.at(i)->Start();
	}
}

void Lighting::Update()
{
	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components.at(i)->Update();
	}
}

void Lighting::Destroy()
{
	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components.at(i)->Destroy();
	}
}