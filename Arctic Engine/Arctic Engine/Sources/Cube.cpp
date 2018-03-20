#include "..\Headers\Cube.h"

Cube::Cube()
{

}

Cube::Cube(std::string _name, std::string _obj, OBJECT_TYPE _objtype)
{
	m_name = _name;
	m_objName = _obj;
	m_object_Type = _objtype;
}

Cube::Cube(std::string _name, std::string _obj, OBJECT_TYPE _objtype, Vector3 _pos, glm::quat _rot, Vector3 _scale, float _mass)
{
	m_name = _name; 
	m_objName = _obj;
	m_object_Type = m_object_Type;
	m_startingPos = _pos; 
	m_startingRot = _rot;
	m_startingScale = _scale; 
	m_mass = _mass; 
}

void Cube::Awake()
{}

void Cube::Start()
{
	//Make sure certain parameters are assigned
	if (m_name.empty()) m_name = "Object";
	if (m_objName.empty()) m_objName = "cube";
	if (m_mass <= 0.0f) m_mass = 0.0f; 

	m_size = Vector3(1, 1, 1);

	//Assign components 
	m_transform = AddComponent<Transform>();
	m_meshRenderer = AddComponent<MeshRenderer>();
	m_boxCollider = AddComponent<BoxCollider>();
	m_bounds = AddComponent<Bounds>();

	m_transform.lock()->SetStartingTransform(m_startingPos, m_startingRot, m_startingScale);

	//Set Obj name in Mesh Renderer
	m_meshRenderer.lock()->OBJFile(m_objName);

	//Call Awake on all components 
	for(unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components.at(i)->Awake();
	}

	//Call Start on all components 
	for(unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components.at(i)->Start();
	}

	//Create OBJ and Texture files
	m_meshRenderer.lock()->CreateVAO();
	m_meshRenderer.lock()->CreateShaders();
	m_meshRenderer.lock()->SetUpMVP();
	m_meshRenderer.lock()->LoadTexture();

	m_bounds.lock()->RecalculateBounds(m_meshRenderer.lock()->GetVertices());
	m_boxCollider.lock()->CreateRigidBody(m_mass, m_size);
}

void Cube::Update()
{
	KeyInput();

	//Call Update on all Components
	for(unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components.at(i)->Update();
	}

	//Update OBJ model matrix 
	m_meshRenderer.lock()->UpdateMVP(m_transform.lock()->GetWorldPosition(), m_transform.lock()->GetWorldRotation(), m_transform.lock()->GetWorldScale());
}

void Cube::Render()
{
	//Render OBJ
	m_meshRenderer.lock()->Render();
}

void Cube::Destroy()
{
	//Call Destroy on all components
	for(unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components.at(i)->Destroy();
	}
}

void Cube::KeyInput()
{
	//Create empty values
	Vector3 Movement = Vector3(0.0f, 0.0f, 0.0f);
	glm::quat Rotation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
	Vector3 Scale = Vector3(0.0f, 0.0f, 0.0f);

	float s = 0.01f; 

	//Input checking ////TODO////Add Keybinding to remove this
	if(Input::CheckKeyDown(SDLK_UP) || Input::CheckKeyPressed(SDLK_UP)) Movement += Vector3(0.0f, 0.0f, -s);  //FORWARD

	if(Input::CheckKeyDown(SDLK_DOWN) || Input::CheckKeyPressed(SDLK_DOWN)) Movement += Vector3(0.0f, 0.0f, s); //BACKWARDS

	if(Input::CheckKeyDown(SDLK_LEFT) || Input::CheckKeyPressed(SDLK_LEFT)) Movement += Vector3(-s, 0.0f, 0.0f); //LEFT

	if(Input::CheckKeyDown(SDLK_RIGHT) || Input::CheckKeyPressed(SDLK_RIGHT)) Movement += Vector3(s, 0.0f, 0.0f); //RIGHT


	if (Movement == Vector3(0,0,0) && Rotation == glm::quat(0, 0, 0, 0) && Scale == Vector3(0, 0, 0))
	{
	
	}
	else
	{
		//Update transform on object
		m_transform.lock()->Translate(Movement);
		m_transform.lock()->Rotate(Rotation);
		m_transform.lock()->Scale(Scale);
	}

}

