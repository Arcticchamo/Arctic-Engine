#include "..\Headers\Engine_Core.h"



Engine_Core::Engine_Core()
{
}

Engine_Core::~Engine_Core()
{
}

void Engine_Core::Init()
{
	srand(time(NULL));

	m_sdl.reset(new SDL);
	
	//If window does not exist, Do not run the engine
	if (!m_sdl->Init(SCREENWIDTH, SCREENHEIGHT))
		m_engineRunning = false;
	else
		m_engineRunning = true;

	InitializeOpenGL();

	Resources::Start();
	Physics::Start();

	CreateBaseObjects();

	Physics::InitializeDebug();
	Audio::Start();
}

void Engine_Core::Run()
{
	Time::Start();
	Audio::PlayMusic();
	while (m_engineRunning)
	{
		//double dt = Time::deltaTime();
		double dt = 1 / 60.0f;

		Input::CheckInput();

		//Close the Engine
		if (Input::CheckKeyDown(SDLK_ESCAPE)) m_engineRunning = false;

		//Set window viewport
		glViewport(0, 0, SCREENWIDTH, SCREENHEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1, 1, 1, 1);

		Physics::Update(dt);
		
		//Update all GameObjects
		for (unsigned int i = 0; i < m_gameobjects.size(); i++)
		{
			m_gameobjects.at(i)->Update();
		}

		//for (unsigned int i = 0; i < m_lights.size(); i++)
		//{
		//	m_lights.at(i)->Update();
		//}

		for (unsigned int i = 0; i < m_gameobjects.size(); i++)
		{
			m_gameobjects.at(i)->Render();
		}

		//Physics::DrawDebugWorld();

		m_sdl->SwapWindow();
		Input::EraseKeyDown();
		Input::EraseKeyUp();
	}
	Audio::StopMusic();
}

void Engine_Core::Destroy()
{
	//Destroy all GameObjects 
	for (unsigned int i = 0; i < m_gameobjects.size(); i++)
	{
		m_gameobjects.at(i)->Destroy();
	}

	//for (unsigned int i = 0; i < m_lights.size(); i++)
	//{
	//	m_lights.at(i)->Destroy();
	//}

	Physics::Destroy();
	Audio::Destroy();

	//Remove all objects from memory
	m_gameobjects.clear();
	m_sdl->Destroy();
}

void Engine_Core::CreateBaseObjects()
{
	//Create new objects
	std::shared_ptr<GameObject> Player1(new Player("Player", "car", PLAYER_TYPE, Vector3(0, 0, 0), glm::quat(1, 0, 0, 0), Vector3(0.025, 0.025, 0.025), 10));
	std::shared_ptr<GameObject> RightWheelF(new Wheel("RightWheelF", "rightwheelcar", PLAYER_TYPE, Vector3(-2.25, 0.3, -3.5), glm::quat(1, 0, 0, 0), Vector3(0.025, 0.025, 0.025), 0));
	std::shared_ptr<GameObject> RightWheelB(new Wheel("RightWheelB", "rightwheelcar", PLAYER_TYPE, Vector3(-2.25, 0.3, 0), glm::quat(1, 0, 0, 0), Vector3(0.025, 0.025, 0.025), 0));
	std::shared_ptr<GameObject> LeftWheelF(new Wheel("LeftWheelF", "leftwheelcar", PLAYER_TYPE, Vector3(1.25, 0.3, -3.5), glm::quat(1, 0, 0, 0), Vector3(0.025, 0.025, 0.025), 0));
	std::shared_ptr<GameObject> LeftWheelB(new Wheel("LeftWheelB", "leftwheelcar", PLAYER_TYPE, Vector3(1.25, 0.3, 0), glm::quat(1, 0, 0, 0), Vector3(0.025, 0.025, 0.025), 0));

	std::shared_ptr<GameObject> Floor1(new Floor("Floor1", "floor", NPC_TYPE, Vector3(2.5, -0.5, 5), glm::quat(1, 0, 0, 0), Vector3(5, 1, 5), 0));
	std::shared_ptr<GameObject> Floor2(new Floor("Floor2", "floor", NPC_TYPE, Vector3(-2.5, -0.5, 5), glm::quat(1, 0, 0, 0), Vector3(5, 1, 5), 0));

	//Push them into the GameObjects Vector
	m_gameobjects.push_back(Player1);
	m_gameobjects.push_back(RightWheelF);
	m_gameobjects.push_back(RightWheelB);
	m_gameobjects.push_back(LeftWheelF);
	m_gameobjects.push_back(LeftWheelB);

	m_gameobjects.push_back(Floor1);
	m_gameobjects.push_back(Floor2);

	for (int i = 0; i < 150; i++)
	{
		m_gameobjects.push_back(std::shared_ptr<GameObject>(new Floor("Floor", "floor", NPC_TYPE, Vector3(2.5, -0.5, -5 * i), glm::quat(1, 0, 0, 0), Vector3(5, 1, 5), 0)));
		m_gameobjects.push_back(std::shared_ptr<GameObject>(new Floor("Floor", "floor", NPC_TYPE, Vector3(-2.5, -0.5, -5 * i), glm::quat(1, 0, 0, 0), Vector3(5, 1, 5), 0)));
	}

	//Create the barrels within the scene. 
	//This gets 2 random numbers, 1 - 2 and 1 - 3
	//The 1 - 3 is for the different textured barrels 
	//The 1 - 2 is the lane which they spawn in 
	for (int i = 8; i < 150; i += 5)
	{
		int type = rand() % 3 + 1;
		int side = rand() % 2 + 1;
		
		switch (type)
		{
		case 1:
			if (side == 1)
			{
				m_gameobjects.push_back(std::shared_ptr<GameObject>(new Barrel("Barrel1", "barrel1", NPC_TYPE, Vector3(2.5, 0, -5 * i), glm::quat(1, 0, 0, 0), Vector3(0.75f, 0.75f, 0.75f), 0)));
			}
			else if (side == 2)
			{
				m_gameobjects.push_back(std::shared_ptr<GameObject>(new Barrel("Barrel1", "barrel1", NPC_TYPE, Vector3(-2.5, 0, -5 * i), glm::quat(1, 0, 0, 0), Vector3(0.75f, 0.75f, 0.75f), 0)));
			}
			break;
		case 2: 
			if (side == 1)
			{
				m_gameobjects.push_back(std::shared_ptr<GameObject>(new Barrel("Barrel2", "barrel2", NPC_TYPE, Vector3(2.5, 0, -5 * i), glm::quat(1, 0, 0, 0), Vector3(0.75f, 0.75f, 0.75f), 0)));
			}
			else if (side == 2)
			{
				m_gameobjects.push_back(std::shared_ptr<GameObject>(new Barrel("Barrel2", "barrel2", NPC_TYPE, Vector3(-2.5, 0, -5 * i), glm::quat(1, 0, 0, 0), Vector3(0.75f, 0.75f, 0.75f), 0)));
			}
			break;

		case 3:
			if (side == 1)
			{
				m_gameobjects.push_back(std::shared_ptr<GameObject>(new Barrel("Barrel3", "barrel3", NPC_TYPE, Vector3(2.5, 0, -5 * i), glm::quat(1, 0, 0, 0), Vector3(0.75f, 0.75f, 0.75f), 0)));
			}																		  
			else if (side == 2)														  
			{																		  
				m_gameobjects.push_back(std::shared_ptr<GameObject>(new Barrel("Barrel3", "barrel3", NPC_TYPE, Vector3(-2.5, 0, -5 * i), glm::quat(1, 0, 0, 0), Vector3(0.75f, 0.75f, 0.75f), 0)));
			}
			break;

		default:
			m_gameobjects.push_back(std::shared_ptr<GameObject>(new Barrel("Barrel3", "barrel3", NPC_TYPE, Vector3(-2.5, 0, -5 * i), glm::quat(1, 0, 0, 0), Vector3(0.75f, 0.75f, 0.75f), 0)));
			break;		
		}
	}

	//std::shared_ptr<Lighting> light1(new Lighting());
	//m_lights.push_back(light1);

	m_gameobjects.push_back(std::shared_ptr<Skybox>(new Skybox("skybox", "skybox", NPC_TYPE, Vector3(0, 0, 0), glm::quat(1, 0, 0, 0), Vector3(100, 100, 100), 0)));

	//Run their Awake and Start Functions
	for (unsigned int i = 0; i < m_gameobjects.size(); i++)
	{
		m_gameobjects.at(i)->Awake();
	}

	//for (unsigned int i = 0; i < m_lights.size(); i++)
	//{
	//	m_lights.at(i)->Awake();
	//}

	for (unsigned int i = 0; i < m_gameobjects.size(); i++)
 	{
		m_gameobjects.at(i)->Start();
	}

	//for (unsigned int i = 0; i < m_lights.size(); i++)
 //	{
	//	m_lights.at(i)->Start();
	//}

	//Assign Parents and Children
	Player1->GetTransform().lock()->AddChild(RightWheelF);
	Player1->GetTransform().lock()->AddChild(RightWheelB);
	Player1->GetTransform().lock()->AddChild(LeftWheelF);
	Player1->GetTransform().lock()->AddChild(LeftWheelB);

	RightWheelF->GetTransform().lock()->SetParent(Player1);
	RightWheelB->GetTransform().lock()->SetParent(Player1);
	LeftWheelF->GetTransform().lock()->SetParent(Player1);
	LeftWheelB->GetTransform().lock()->SetParent(Player1);

	//Player1->GetTransform().lock()->AddChild(Cube1);
	//Cube1->GetTransform().lock()->SetParent(Player1);
} 

void Engine_Core::InitializeOpenGL()
{
	glewExperimental = GL_TRUE;
	GLenum ErrorCheck = glewInit(); //Error Checking 
	
	if (GLEW_OK != ErrorCheck) 
	{
		std::cout << "Error with OpenGL - Creation" << std::endl;
	}

	glEnable(GL_DEPTH_TEST); //Enables depth in the scene 
	glEnable (GL_TEXTURE_2D); //Enables 2D textures for use

	//Display OpenGL infos
	std::cout << "OpenGL Version: " << glGetString( GL_VERSION ) << std::endl;
	std::cout << "OpenGL Renderer: " << glGetString( GL_RENDERER ) << std::endl;
	std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "OpenGL Vendor: " << glGetString( GL_VENDOR ) << std::endl;
	std::cout << "OpenGL Shading Language Version: " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl << std::endl;
}


