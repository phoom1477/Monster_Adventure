//////////////////////////////////////////////////
//	Object list that used by dynamic allocated  //
//		- buttons								//
//////////////////////////////////////////////////

#pragma once

#include "GameState.h"
#include "Button.h"

class MainMenuState : public State
{
private:
	//variable
	sf::Texture backgroundTexture;
	sf::RectangleShape background;    
	sf::Font font;

	std::map<std::string, Button*> buttons;

	//Initialization
	void initFonts();
	void initKeybinds();
	void initButton();
	void initBackground();

public:
	//Constructor , Destructor
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	//update
	void updateState(const float &dt);
	void updateInput(const float &dt);
	void updateButton();

	//render
	void renderState(sf::RenderTarget* target = NULL);
	void renderButton(sf::RenderTarget* target = NULL);

	//end
	void endState();
};

