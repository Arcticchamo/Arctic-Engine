#include "..\Headers\Input.h"

//Static variable defining
bool Input::m_eventIsTrue = false;
SDL_Event Input::m_event;
std::vector <SDL_Event> Input::m_keyPressedUp;
std::vector <SDL_Event> Input::m_keyPressedDown;
std::vector <SDL_Event> Input::m_keyPressed;

void Input::CheckInput()
{
	m_eventIsTrue = false;

	//Check to see if there is any key presses
	while (SDL_PollEvent(&m_event))
	{
		switch(m_event.type)
		{
		case SDL_KEYDOWN:
			m_keyPressedDown.push_back(m_event);
			m_keyPressed.push_back(m_event);
			break;

		case SDL_KEYUP:
			m_keyPressedUp.push_back(m_event);
			break;
		}
		m_eventIsTrue = true;
	}		
}

bool Input::GetInput()
{
	return m_eventIsTrue;
}

std::vector<SDL_Event>& Input::GetKeyPressedUp()
{
	return m_keyPressedUp;
}

std::vector<SDL_Event>& Input::GetKeyPressedDown()
{
	return m_keyPressedDown;
}

std::vector<SDL_Event>& Input::GetKeyPressed()
{
	return m_keyPressed;
}

void Input::EraseKeyUp()
{
	//Remove any keys from the KeyPressed Vector
	for (unsigned int i = 0; i < m_keyPressedUp.size(); i++)
	{
		EraseKeyPressed(m_keyPressedUp.at(i).key.keysym.sym);
	}

	//Clear the keypressedUp vector 
	if (m_keyPressedUp.size() > 0)
		m_keyPressedUp.clear();
}

void Input::EraseKeyDown()
{
	//Clear the KeyPressedDown vector
	if (m_keyPressedDown.size() > 0)
		m_keyPressedDown.clear();
}

void Input::EraseKeyPressed(SDL_Keycode _key)
{
	//Check through the key pressed vector to see if the key is stored, if so, remove it 
	//Issues are that sometimes the same key is stored multiple times, meaning I have to
	//traverse through it multiple times just to make sure that the key is fully removed
	for (unsigned int i = 0; i < m_keyPressed.size(); i++)
	{
		if (m_keyPressed.at(i).key.keysym.sym == _key)
		{
			m_keyPressed.erase(m_keyPressed.begin() + i);
			i--;
		}
	}
}

bool Input::CheckKeyDown(SDL_Keycode _key)
{
	//Run through the vector to see if a certain key is pressed
	for (unsigned int i = 0; i < m_keyPressedDown.size(); i++)
	{
		if (m_keyPressedDown.at(i).key.keysym.sym == _key) return true;	
	}	
	return false;
}

bool Input::CheckKeyUp(SDL_Keycode _key)
{
	//Run through the vector to see if a certain key is pressed
	for (unsigned int i = 0; i < m_keyPressedUp.size(); i++)
	{
		if (m_keyPressedUp.at(i).key.keysym.sym == _key) return true;	
	}	
	return false;
}

bool Input::CheckKeyPressed(SDL_Keycode _key)
{
	//Run through the vector to see if a certain key is pressed
	for (unsigned int i = 0; i < m_keyPressed.size(); i++)
	{
		if (m_keyPressed.at(i).key.keysym.sym == _key) return true;	
	}	
	return false;
}
