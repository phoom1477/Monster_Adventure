////////////////////////////////////////////////
//	 This class is Abstract class of states.  //
////////////////////////////////////////////////

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

class State
{
private:
	//Intialization
	void initVariable();

protected:
	//Variable
	sf::RenderWindow* window;
	std::stack<State*>* states;

	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	bool quit;

	//Resource
	std::map<std::string, sf::Texture> textures;

	//Intialization
	virtual void initKeybinds() = 0;

public:
	//Constructor , Destructor
	State(sf::RenderWindow* window, std::map<std::string ,int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	//Accessor
	const bool& getQuit();

	//Function

	//update
	virtual void updateState(const float &dt) = 0;
	virtual void updateInput(const float &dt) = 0;
	virtual void updateMousePosition();
	
	//render
	virtual void renderState(sf::RenderTarget* target = NULL) = 0;
	
	//end
	virtual void endState() = 0;
};

