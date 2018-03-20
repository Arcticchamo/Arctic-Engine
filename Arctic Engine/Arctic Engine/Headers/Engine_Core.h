#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>

//Game Object Headers
#include "Barrel.h"
#include "Cube.h"
#include "Floor.h"
#include "GameObject.h"
#include "Lighting.h"
#include "Player.h"
#include "SkyBox.h"
#include "Wheel.h"

//Component Headers
#include "Component.h"
#include "Transform.h"


//Static Headers
#include "Audio.h"
#include "Global.h"
#include "Input.h"
#include "Physics.h"
#include "Resources.h"
#include "SDL.h"
#include "Time.h"

class Engine_Core
{
private:
	bool m_engineRunning;
	int m_screenWidth;
	int m_screenHeight;

	std::vector <std::shared_ptr<GameObject>> m_gameobjects; 
	std::vector <std::shared_ptr<Lighting>> m_lights;

	std::shared_ptr<SDL> m_sdl;
public:
	Engine_Core();
	~Engine_Core();

	void Init();
	void Run();
	void Destroy();
	void CreateBaseObjects();
	void InitializeOpenGL();
};
#endif;