//////////////////////////////////////////
//	 This class is core of this game.   //
//	 It's Game engine.					//
//////////////////////////////////////////

//////////////////////////////////////////////////
//	Object list that used by dynamic allocated  //
//		- window								//
//      - states								//
//////////////////////////////////////////////////

#pragma once

#include "MainMenuState.h"

class Game
{
private:
	//Variable
	sf::RenderWindow* window;
	sf::Event event;
	
	bool fullscreen;
	sf::ContextSettings windowSetting;

	sf::Clock clock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Initialization
	void initVariable();
	void initWindow();
	void initWindowIcon();
	void initKeys();
	void initStates();

public:
	//Constructor , Destructor
	Game();
	virtual ~Game();

	void run();

	//update
	void updateGame();
	void updateDeltatime();
	void updateEvent();

	//render
	void renderGame();

	void endGame();
};

