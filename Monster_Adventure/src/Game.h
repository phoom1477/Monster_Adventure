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
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSetting;
	bool fullscreen;

	sf::Clock clock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Initialization
	void initVariable();
	void initWindow();
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

