#include <SDL\SDL.h>;
#include <GL\glew.h>
#include <GL\GL.h>
#include <GLM\glm.hpp>

#include "..\Headers\Engine_Core.h"

int main(int argc, char *argv[])
{
	//Create Engine Core
	std::shared_ptr<Engine_Core> Engine;
	Engine.reset(new Engine_Core);

	Engine->Init();
	Engine->Run();
	Engine->Destroy();
	
	return 0;
}