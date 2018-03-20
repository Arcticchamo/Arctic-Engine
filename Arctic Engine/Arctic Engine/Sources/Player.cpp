#include "..\Headers\Player.h"

Player::Player()
{

}

Player::Player(std::string _name, std::string _obj, OBJECT_TYPE _objtype)
{
	m_name = _name;
	m_objName = _obj;
	m_object_Type = _objtype;
}

Player::Player(std::string _name, std::string _obj, OBJECT_TYPE _objtype, Vector3 _pos, glm::quat _rot, Vector3 _scale, float _mass)
{
	m_name = _name; 
	m_objName = _obj;
	m_object_Type = m_object_Type;
	m_startingPos = _pos; 
	m_startingRot = _rot;
	m_startingScale = _scale; 
	m_mass = _mass; 
}

void Player::Awake()
{}

void Player::Start()
{
	//Make sure certain parameters are assigned
	if (m_name.empty()) m_name = "Object";
	if (m_objName.empty()) m_objName = "cube";
	if (m_mass <= 0.0f) m_mass = 0.0f; 
 
	m_size = Vector3(1, 0.25, 1);

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

void Player::Update()
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

void Player::Render()
{
	//Render OBJ
	m_meshRenderer.lock()->Render();
}

void Player::Destroy()
{
	//Call Destroy on all components
	for(unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components.at(i)->Destroy();
	}
}

void Player::KeyInput()
{
	//Create empty values
	Vector3 Movement = Vector3(0.0f, 0.0f, 0.0f);
	glm::quat Rotation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
	Vector3 Scale = Vector3(0.0f, 0.0f, 0.0f);
	float m = 5.0f * Time::deltaTime();

	//Input checking ////TODO////Add Keybinding to remove this
	if(Input::CheckKeyDown(SDLK_w) || Input::CheckKeyPressed(SDLK_w)) Movement += Vector3(0.0f, 0.0f, -m);  //FORWARD

	if(Input::CheckKeyDown(SDLK_s) || Input::CheckKeyPressed(SDLK_s)) Movement += Vector3(0.0f, 0.0f, m); //BACKWARDS

	if(Input::CheckKeyDown(SDLK_a) || Input::CheckKeyPressed(SDLK_a)) Movement += Vector3(-m, 0.0f, 0.0f); //LEFT

	if(Input::CheckKeyDown(SDLK_d) || Input::CheckKeyPressed(SDLK_d)) Movement += Vector3(m, 0.0f, 0.0f); //RIGHT

	if(Input::CheckKeyDown(SDLK_e) || Input::CheckKeyPressed(SDLK_e)) Movement += Vector3(0.0f, -m, 0.0f); //DOWN

	if(Input::CheckKeyDown(SDLK_q) || Input::CheckKeyPressed(SDLK_q)) Movement += Vector3(0.0f, m, 0.0f); //UP

	if(Input::CheckKeyDown(SDLK_r) || Input::CheckKeyPressed(SDLK_r)) Rotation += glm::quat(0.0f, m, 0.0f, 0.0f); //Rotate X positive

	if(Input::CheckKeyDown(SDLK_f) || Input::CheckKeyPressed(SDLK_f)) Rotation += glm::quat(0.0f, -m, 0.0f, 0.0f); //Rotate X positive

	if(Input::CheckKeyDown(SDLK_t) || Input::CheckKeyPressed(SDLK_t)) Rotation += glm::quat(0.0f, 0.0f, m, 0.0f); //Rotate Y positive

	if(Input::CheckKeyDown(SDLK_g) || Input::CheckKeyPressed(SDLK_g)) Rotation += glm::quat(0.0f, 0.0f, -m, 0.0f); //Rotate Y positive

	if(Input::CheckKeyDown(SDLK_y) || Input::CheckKeyPressed(SDLK_y)) Rotation += glm::quat(0.0f, 0.0f, 0.0f, m); //Rotate Z positive

	if(Input::CheckKeyDown(SDLK_h) || Input::CheckKeyPressed(SDLK_h)) Rotation += glm::quat(0.0f, 0.0f, 0.0f, -m); //Rotate Z positive

	if(Input::CheckKeyDown(SDLK_KP_PLUS) || Input::CheckKeyPressed(SDLK_KP_PLUS)) Scale += Vector3(m, m, m); //Scale positive

	if(Input::CheckKeyDown(SDLK_KP_MINUS) || Input::CheckKeyPressed(SDLK_KP_MINUS)) Scale += Vector3(-m, -m, -m); //Scale negative 


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