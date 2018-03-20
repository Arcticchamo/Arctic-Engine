#include "..\Headers\MeshRenderer.h"

void MeshRenderer::Awake()
{

}

void MeshRenderer::Start()
{

}

void MeshRenderer::Update()
{

}

void MeshRenderer::Destroy()
{

}

void MeshRenderer::CreateVAO()
{
	//VERTEX 
	glGenVertexArrays(1, &m_vao);  //Generate a VAO
	glBindVertexArray(m_vao); //Bind the VAO

	glGenBuffers(1, &m_vaoPosition);  //Generate a VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_vaoPosition); //Bind the VBO to the VAO
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_vertex.size(), &m_vertex[0], GL_STATIC_DRAW); //Assign VBOs data 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //Assign position of data in the VAO 
	glEnableVertexAttribArray(0); //Enable VBO in the VAO

	//UV
	glGenBuffers(1, &m_uvPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvPosition);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2) * m_uv.size(), &m_uv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//NORMAL
	glGenBuffers(1, &m_normPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_normPosition);
	glBufferData(GL_ARRAY_BUFFER, sizeof(int) * m_normal.size(), &m_normal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

}

void MeshRenderer::CreateShaders()
{
	m_shader = Resources::GetShader();
}

void MeshRenderer::Render()
{
	glUseProgram(m_shader); //Use the shader

	glBindTexture (GL_TEXTURE_2D, m_texBufferID); //Bind the texture, if not done, same texture will be used for each object

	glUniformMatrix4fv(m_modelMatLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix)); 
	glUniformMatrix4fv(m_viewMatLocation, 1, GL_FALSE, glm::value_ptr(m_viewingMatrix));
	glUniformMatrix4fv(m_projectionMatLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

	glBindVertexArray(m_vao); //Bind the VAO for use
	glDrawArrays(GL_TRIANGLES, 0, m_NumberOfVertex); //Draw the current bound VAO
	glBindVertexArray(0); //Unbind the VAO
	glUseProgram(0); //Unbind the shader
}

void MeshRenderer::SetUpMVP()
{
	//Grab data from shader infomation
	m_modelMatLocation = glGetUniformLocation(m_shader, "ModelMat"); 
	m_viewMatLocation = glGetUniformLocation(m_shader, "ViewMat"); 
	m_projectionMatLocation = glGetUniformLocation(m_shader, "ProjectionMat");
	m_texSamplerLocation = glGetUniformLocation(m_shader, "TexSampler");
	m_viewposLocation = glGetUniformLocation(m_shader, "viewingPos");
	
	//Set default values ////TODO////Adjust so that it takes transform parameters 
	m_modelMatrix = Mat4(1.0f); 

	m_viewingMatrix = glm::translate(Mat4(1.0f), glm::vec3(0.0f, 10.0f, -10.0f));
	m_projectionMatrix = glm::perspective(45.0f, ((float)SCREENWIDTH / (float)SCREENHEIGHT), 0.1f, 100.0f);

	glUniform3f(m_viewposLocation, 0.0f, 0.0f, -5.0f);
}

void MeshRenderer::UpdateMVP(Vector3 _pos, glm::quat _rot, Vector3 _scale)
{
	//Translating the models 
	m_modelMatrix = Mat4(1.0f);
	m_modelMatrix = glm::translate(m_modelMatrix, _pos);

	//Rotating the models
	m_modelMatrix = glm::rotate(m_modelMatrix, _rot.y, Vector3(0.0f, 1.0f, 0.0f));
	m_modelMatrix = glm::rotate(m_modelMatrix, _rot.z, Vector3(0.0f, 0.0f, 1.0f));
	m_modelMatrix = glm::rotate(m_modelMatrix, _rot.x, Vector3(1.0f, 0.0f, 0.0f));

	//Scale the models
	m_modelMatrix = glm::scale(m_modelMatrix, _scale);

	//Camera Matrix
	m_viewingMatrix = glm::translate(Mat4(1.0f), glm::vec3(0, -2.5f, -10.0f)); //Position of camera 
	//m_viewingMatrix = glm::translate(_rot, _pos); 
	m_projectionMatrix = glm::perspective(45.0f, ((float)SCREENWIDTH / (float)SCREENHEIGHT), 0.1f, 100.0f); //FOV, Screen dimensions, near, far
}

void MeshRenderer::ObjectName(std::string _name)
{
	m_objName = _name;
}

void MeshRenderer::OBJFile(std::string _obj)
{
	m_objName = _obj;

	OBJLoader::GetOBJFile(
	m_vertex, 
	m_uv, 
	m_normal, 
	m_vertexIndices,
	m_uvIndices,
	m_normalIndices,
	_obj);

	NumberOfPoints();
}

void MeshRenderer::NumberOfPoints()
{
	if (!m_vertex.empty() && !m_uv.empty() && !m_normal.empty())
	{
		m_NumberOfVertex = m_vertex.size();
		m_NumberOfUV = m_uv.size();
		m_NumberOfNormal = m_normal.size();

		std::cout << "Number of Vertices in " << m_objName << ": " << m_NumberOfVertex << std::endl;
		std::cout << "Number of UV in " << m_objName << ": " << m_NumberOfUV << std::endl;
		std::cout << "Number of Vertices in " << m_objName << ": " << m_NumberOfNormal << std::endl;
		std::cout << "Number of Faces in " << m_objName << ": " << m_vertexIndices.size() / 3 << std::endl << std::endl;
	}
}

void MeshRenderer::LoadTexture()
{
	//Use SDL_Image to load the .jpg file 
	SDL_Surface* Texture = IMG_Load(("Assets/Textures/" + m_objName + "Texture.jpg").c_str());

	glGenTextures (1, &m_texBufferID); //Generate the texture
	glBindTexture (GL_TEXTURE_2D, m_texBufferID); //Bind the texture
	//Assign Texture data 
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, Texture->w, Texture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, Texture->pixels);

	//Set texture parameters 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}