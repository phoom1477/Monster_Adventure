//////////////////////////////////////////////////
//	Object list that used by dynamic allocated  //
//		-player									//
//////////////////////////////////////////////////

#pragma once

#include "State.h"
#include "Player.h"

class GameState : public State
{
private:
	//variable
	Player* player;

	//Intialization
	void initKeybinds();
	void initTexture();
	void initPlayer();

public:
	//Constructor , Destructor
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//update
	void updateState(const float &dt);
	void updateInput(const float &dt);

	//render
	void renderState(sf::RenderTarget* target = NULL);

	//end
	void endState();
};

