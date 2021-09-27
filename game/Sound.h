#pragma once
#include <SFML/Audio.hpp>
#include "SFML\Graphics.hpp"

typedef struct 
{
	sf::SoundBuffer sbuf;
	std::string name;
}sbuffer;

static class Sound
{
private:
	//sf::SoundBuffer backgroundsong;
	//sf::Sound sound;
	std::vector<sbuffer>ListOfSongs;
	std::vector<sbuffer>ListOfSfx;
public:
	Sound() {}
	Sound(std::string filename);

	void SetMusicBuffer(std::string filename);

	void SetSFXBuffer(std::string filename);

	sf::SoundBuffer *GetBuffer(std::string filename);

	//void PlaySoundLooped(std::string filename, sf::Sound sound);

	//void PlaySoundOnce(std::string filename, sf::Sound sound);

	//void pauseSound(std::string filename, sf::Sound sound);

	//void resumePause(std::string filename, sf::Sound sound);

	std::vector<sbuffer>* reSfx();

	std::vector<sbuffer>* reSound();

	~Sound() {}
};
