#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <SDL\SDL.h>
#include <vector>

class Input
{
public:
	static void CheckInput();

	static bool GetInput();
	static std::vector<SDL_Event>& GetKeyPressedUp();
	static std::vector<SDL_Event>& GetKeyPressedDown();
	static std::vector<SDL_Event>& GetKeyPressed();

	static void EraseKeyUp();
	static void EraseKeyDown();
	static void EraseKeyPressed(SDL_Keycode _key);

	static bool CheckKeyDown(SDL_Keycode _key);
	static bool CheckKeyUp(SDL_Keycode _key);
	static bool CheckKeyPressed(SDL_Keycode _key);

private:
	static SDL_Event m_event;
	static std::vector <SDL_Event> m_keyPressedUp;
	static std::vector <SDL_Event> m_keyPressedDown;
	static std::vector <SDL_Event> m_keyPressed;
	static bool m_eventIsTrue;

};

#endif