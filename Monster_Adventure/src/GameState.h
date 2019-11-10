//////////////////////////////////////////////////
//	Object list that used by dynamic allocated  //
//		-player									//
//		-pauseMenu								//
//////////////////////////////////////////////////

#pragma once

#include "State.h"
#include "Player.h"
#include "PauseMenu.h"

class GameState : public State
{
private:
	//variable
	sf::Font font;
	PauseMenu* pauseMenu;

	Player* player;

	//Intialization
	void initKeybinds();
	void initFonts();
	void initTexture();
	void initPauseMenu();
	void initPlayer();

public:
	//Constructor , Destructor
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//update
	void updateState(const float &dt);
	void updateInput(const float &dt);
	void updatePlayer(const float &dt);
	void updatePauseMenuButton();

	//render
	void renderState(sf::RenderTarget* target = NULL);
};

