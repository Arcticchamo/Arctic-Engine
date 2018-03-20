#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <iostream>
#include <GL\glew.h>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>
#include <vector>
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <fstream>

#include "Component.h"
#include "OBJLoader.h"
#include "Resources.h"
#include "Global.h"


class MeshRenderer : public Component
{
private:
	GLuint m_vao;
	GLuint m_vaoPosition;
	
	GLuint m_indicesBuffer;
	GLuint m_indicesBufferPosition;

	GLuint m_uvVao;
	GLuint m_uvPosition;

	GLuint m_normVao;
	GLuint m_normPosition;

	GLuint m_shader;
	GLint m_viewposLocation;

	//Variables needed for storing Texture data
	GLuint m_texBufferID;
	GLuint m_texSamplerLocation;

	int m_modelMatLocation;
	int m_viewMatLocation;
	int m_projectionMatLocation;

	Mat4 m_modelMatrix;
	Mat4 m_viewingMatrix;
	Mat4 m_projectionMatrix;

	std::string m_objName;

	std::vector<Vector3> m_vertex;
	std::vector<Vector2> m_uv;
	std::vector<Vector3> m_normal;
	std::vector<int> m_vertexIndices;
	std::vector<int> m_uvIndices;
	std::vector<int> m_normalIndices;
	int m_NumberOfVertex;
	int m_NumberOfUV;
	int m_NumberOfNormal;



public:
	void Awake();
	void Start();
	void Update();
	void Destroy();
	
	void CreateVAO();
	void CreateShaders();
	void LoadTexture();
	void SetUpMVP();

	void Render();
	void UpdateMVP(Vector3 _pos, glm::quat _rot, Vector3 _scale);

	void ObjectName(std::string _name);
	void NumberOfPoints();
	void OBJFile(std::string _obj);

	std::vector<Vector3> GetVertices()
	{
		return m_vertex;
	}
};


#endif