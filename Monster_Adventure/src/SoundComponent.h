#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <map>

class SoundComponent
{
private:
	//Resource
	std::map<std::string, sf::SoundBuffer> soundBuffers;
	std::map<std::string, sf::Sound> sounds;

public:
	//Destuctor , Destructor
	SoundComponent();
	virtual ~SoundComponent();
	
	//Modifier
	void setSoundVolume(std::string key, const float volume);

	//Function
	void addSound(std::string key, std::string path);
	void play(std::string key);
};

