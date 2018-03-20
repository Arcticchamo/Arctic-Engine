#include "..\Headers\Audio.h"

Mix_Music *Audio::m_music;

void Audio::Awake()
{
}

void Audio::Start()
{
	//Init SDL_Mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "Error Init SDL Mixer" << std::endl;
	}

	//Load Music in 
	m_music = Mix_LoadMUS("Assets/bgm/bgm.wav");

	//Error Check Music
	if (m_music == nullptr)
	{
		std::cout << "Error getting music" << std::endl;
	}
}

void Audio::Update()
{

}

void Audio::PlayMusic()
{
	//Start music, -1 makes the song loop
	Mix_PlayMusic(m_music, -1);
}

void Audio::StopMusic()
{
	//Stop music
	Mix_HaltMusic();
}

void Audio::Destroy()
{
	//SDL Mixer Cleanup
	Mix_FreeMusic(m_music);
	Mix_CloseAudio();
}