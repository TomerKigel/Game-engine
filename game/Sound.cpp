#include "Sound.h"


Sound::Sound(std::string filename)
{
	if (filename.size() > 0) {
		if (filename.find(".wav") != std::string::npos) {
			sbuffer *nbuf = new sbuffer;
			nbuf->name = filename;
			nbuf->sbuf.loadFromFile(filename);
			//nbuf->sound.setBuffer(nbuf->sbuf);
			ListOfSongs.push_back(*nbuf);
		}	
	}
}

void Sound::SetMusicBuffer(std::string filename)
{
	if (filename.size() > 0) {
		if (filename.find(".wav") != std::string::npos) {
			sbuffer *nbuf = new sbuffer;
			nbuf->name = filename;
			nbuf->sbuf.loadFromFile(filename);
			//nbuf->sound.setBuffer(nbuf->sbuf);
			ListOfSongs.push_back(*nbuf);
			//PlaySoundLooped(filename);
		}
	}
}
void Sound::SetSFXBuffer(std::string filename)
{
	if (filename.size() > 0) {
		if (filename.find(".wav") != std::string::npos) {
			sbuffer *nbuf = new sbuffer;
			nbuf->name = filename;
			nbuf->sbuf.loadFromFile(filename);
			//nbuf->sound.setBuffer(nbuf->sbuf);
			ListOfSfx.push_back(*nbuf);
		}
	}
}

sf::SoundBuffer *Sound::GetBuffer(std::string filename)
{
	for (short i = 0; i < ListOfSongs.size(); i++)
	{
		if (ListOfSongs.at(i).name == filename)
			return &ListOfSongs.at(i).sbuf;
	}
	return nullptr;
}


/*void Sound::PlaySoundLooped(std::string filename,sf::Sound sound)
{
	for (short i = 0; i < ListOfSongs.size(); i++)
	{
		if (ListOfSongs.at(i).name == filename) {
			ListOfSongs.at(i).sound.setLoop(true);
			sound.play();
		}
	}
	
}

void Sound::PlaySoundOnce(std::string filename, sf::Sound sound)
{
	for (short i = 0; i < ListOfSfx.size(); i++)
	{
		if (ListOfSfx.at(i).name == filename)
			sound.play();
	}
}

void Sound::pauseSound(std::string filename, sf::Sound sound)
{
	for (short i = 0; i < ListOfSongs.size(); i++)
	{
		if (ListOfSongs.at(i).name == filename)
			sound.pause();
	}
}

void Sound::resumePause(std::string filename, sf::Sound sound)
{
	for (short i = 0; i < ListOfSongs.size(); i++)
	{
		if (ListOfSongs.at(i).name == filename)
			sound.play();
	}
}
*/

std::vector<sbuffer>* Sound::reSfx()
{
	return &ListOfSfx;
}

std::vector<sbuffer>* Sound::reSound()
{
	return &ListOfSongs;
}



