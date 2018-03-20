#include "..\Headers\Light.h"

void Light::Awake()
{}

void Light::Start()
{
	m_directionLightDir = Vector3(-1, -1, -1);
	m_directionLightColour = Vector3(1, 1, 1);

	m_shader = Resources::GetShader();

	m_direction = glGetUniformLocation(m_shader, "directionLight.m_direction");
	m_colour = glGetUniformLocation(m_shader, "directionLight.m_colour");

	glUniform3f(m_direction, m_directionLightDir.x, m_directionLightDir.y, m_directionLightDir.z);
	glUniform3f(m_colour, m_directionLightColour.x, m_directionLightColour.y, m_directionLightColour.z);
}

void Light::Update()
{
	glUniform3f(m_direction, m_directionLightDir.x, m_directionLightDir.y, m_directionLightDir.z);
	glUniform3f(m_colour, m_directionLightColour.x, m_directionLightColour.y, m_directionLightColour.z);
}

void Light::Destroy()
{

}


