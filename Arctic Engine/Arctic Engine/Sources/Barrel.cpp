#include "..\headers\Barrel.h"

Barrel::Barrel()
{

}

Barrel::Barrel(std::string _name, std::string _obj, OBJECT_TYPE _objtype)
{
	m_name = _name;
	m_objName = _obj;
	m_object_Type = _objtype;
}

Barrel::Barrel(std::string _name, std::string _obj, OBJECT_TYPE _objtype, Vector3 _pos, glm::quat _rot, Vector3 _scale, float _mass)
{
	m_name = _name; 
	m_objName = _obj;
	m_object_Type = m_object_Type;
	m_startingPos = _pos; 
	m_startingRot = _rot;
	m_startingScale = _scale; 
	m_mass = _mass; 
}

void Barrel::Awake()
{}

void Barrel::Start()
{
	//Make sure certain parameters are assigned
	if (m_name.empty()) m_name = "Object";
	if (m_objName.empty()) m_objName = "cube";
	if (m_mass <= 0.0f) m_mass = 0.0f; 
 
	m_size = Vector3(2.0f, 1, 2.0f);

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


	//SETUP RIGIDBODY
}

void Barrel::Update()
{
	//Call Update on all Components 
	for(unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components.at(i)->Update();
	}

	m_transform.lock()->Translate(Vector3(0.0f, 0.0f, 10.0f * Time::deltaTime()));

	//Update OBJ model matrix 
	m_meshRenderer.lock()->UpdateMVP(m_transform.lock()->GetWorldPosition(), m_transform.lock()->GetWorldRotation(), m_transform.lock()->GetWorldScale());
}

void Barrel::Render()
{
	//Render OBJ
	m_meshRenderer.lock()->Render();
}

void Barrel::Destroy()
{
	//Call Destroy on all components
	for(unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components.at(i)->Destroy();
	}
}
