#ifndef SDL_H
#define SDL_H

#include <SDL\SDL.h>
#undef main
#include <SDL\SDL_image.h>

class SDL
{
private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_GLContext m_openGLContext;

public:
	bool Init(int _width, int _height);
	bool CreateWindow(int _width, int _height);
	bool CreateRenderer();
	bool CreateContext();
	void Destroy();
	void SwapWindow();

	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
	SDL_GLContext GetContext();

};

#endif