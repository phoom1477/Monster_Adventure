//////////////////////////////////////////////////
//	Object list that used by dynamic allocated  //
//		-player									//
//		-pauseMenu								//
//////////////////////////////////////////////////

#pragma once

#include "State.h"
#include "Player.h"
#include "Enemy.h"
#include "PauseMenu.h"

class GameState : public State
{
private:
	//Window
	sf::View view;

	//Variable
	std::string playerName;
	short unsigned playerIndex;

	//Resource
	Player* player;
	std::vector<Enemy*> enemy;

	sf::Font font;
	PauseMenu* pauseMenu;

	//Intialization
	void initFonts();
	void initKeybinds();
	void initTexture();

	void initPlayer();
	void initEnemy();
	
	void initView();
	void initPauseMenu();

public:
	//Constructor , Destructor
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, 
		short unsigned player_index, std::string player_name);
	virtual ~GameState();

	//update
	void updateState(const float &dt);
	void updateInput(const float &dt);
	
	void updatePlayer(const float &dt);
	void updateEnemy(const float &dt);
	
	void updateCollision();
	void updatePlayerCollisionFrame();
	void updateEnemyCollisionFrame();
	
	void updateView();
	void updatePauseMenuButton();

	//render
	void renderState(sf::RenderTarget* target = NULL);
	void renderPlayer(sf::RenderTarget* target = NULL);
	void renderEnemy(sf::RenderTarget* target = NULL);
};

