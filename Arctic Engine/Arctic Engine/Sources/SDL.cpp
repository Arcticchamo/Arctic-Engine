#include "..\Headers\SDL.h"

bool SDL::Init(int _width, int _height)
{
	//Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return false;

	//Initialise SDL_Image
	IMG_Init(IMG_INIT_JPG);

	//Create the window
	if (!CreateWindow(_width, _height))
		return false;

	//Create the Renderer
	if (!CreateRenderer())
		return false;

	//Create the OpenGL Context
	if (!CreateContext())
		return false;
	return true;
}

bool SDL::CreateWindow(int _width, int _height)
{
	//Assign window base values
	m_window = SDL_CreateWindow(
		"Game Engine",
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED,
		_width, 
		_height,
		SDL_WINDOW_OPENGL);

	//Error Checking
	if (m_window == nullptr) return false;
	else return true;
}

bool SDL::CreateRenderer()
{
	//Assign Renderers base values
	m_renderer = SDL_CreateRenderer(
		m_window,
		-1,
		0);

	//Error Checking
	if (m_renderer == nullptr) return false;
	else return true;
}

bool SDL::CreateContext()
{
	//Assign OpenGL Context base values
	m_openGLContext = SDL_GL_CreateContext(m_window);

	//Error Checking
	if (m_openGLContext == nullptr) return false;
	else return true;
}

void SDL::Destroy()
{
	//Quit all SDL librarys and Delete all existing SDL properties
	IMG_Quit();
	SDL_GL_DeleteContext(m_openGLContext);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void SDL::SwapWindow()
{
	SDL_GL_SwapWindow(m_window);
}

SDL_Window* SDL::GetWindow()
{
	return m_window;
}

SDL_Renderer* SDL::GetRenderer()
{
	return m_renderer;
}

SDL_GLContext SDL::GetContext()
{
	return m_openGLContext;
}