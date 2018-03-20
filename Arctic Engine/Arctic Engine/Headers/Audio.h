#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <SDL\SDL_mixer.h>
#include <string>
#include <vector>

class Audio
{
private:
	static Mix_Music *m_music;

public:
	Audio(){}
	~Audio(){}

	static void Awake();
	static void Start(); 
	static void Update();
	static void Destroy();

	static void PlayMusic();
	static void StopMusic();
};
#endif