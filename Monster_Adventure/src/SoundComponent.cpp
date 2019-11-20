#include "SoundComponent.h"

//initialization

//Constructor , Destructor
SoundComponent::SoundComponent()
{
}

SoundComponent::~SoundComponent()
{
}

//Modifier
void SoundComponent::setSoundVolume(std::string key, const float volume)
{
	this->sounds[key].setVolume(volume);
}

//Function
void SoundComponent::addSound(std::string key, std::string path)
{
	this->soundBuffers[key].loadFromFile(path);
	this->sounds[key].setBuffer(this->soundBuffers[key]);
}

void SoundComponent::play(std::string key)
{
	if (this->sounds[key].getStatus() != sf::Sound::Playing) {
		this->sounds[key].play();
	}
}



