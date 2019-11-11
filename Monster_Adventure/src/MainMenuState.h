//////////////////////////////////////////////////
//	Object list that used by dynamic allocated  //
//		- buttons								//
//////////////////////////////////////////////////

#pragma once

#include "GameState.h"
#include "SettingState.h"
#include "gui.h"

class MainMenuState : public State
{
private:
	//Resource
	sf::Texture logoTexture;
	sf::RectangleShape logo;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;  

	sf::SoundBuffer musicBuffer;
	sf::Sound music;

	sf::Font font;
	std::map<std::string, gui::Button*> buttons;

	//Initialization
	void initFonts();
	void initKeybinds();
	void initButton();
	void initBackground();
	void initLogo();
	void initMusic();

public:
	//Constructor , Destructor
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	//update
	void updateState(const float &dt);
	void updateInput(const float &dt);
	void updateButton();
	void updateMusic();

	//render
	void renderState(sf::RenderTarget* target = NULL);
	void renderButton(sf::RenderTarget& target);
};
