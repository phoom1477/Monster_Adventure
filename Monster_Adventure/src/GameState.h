//////////////////////////////////////////////////
//	Object list that used by dynamic allocated  //
//		-player									//
//		-Stage									//
//		-wButton								//
//		-aButton								//
//		-sButton								//
//		-dButton								//
//		-jButton								//
//////////////////////////////////////////////////

#pragma once

#include "State.h"
#include "Player.h"
#include "Stage.h"
#include "PopUpMenu.h"
#include "UIAnimation.h"

class GameState : public State
{
private:
	//Window
	sf::View view;

	//Variable
	std::string playerName;
	short unsigned playerIndex;
	int maxStage;
	int currStage;

	//Game Resource
	Player* player;
	std::vector<Enemy*>* enemy;
	Stage* stages;

	//music play
	sf::Sound music;

	//UI Resource
	sf::Text nameText;

	sf::Text ATKText;
	sf::Text playerShowATKText;

	sf::Text DEFText;
	sf::Text playerShowDEFText;


	sf::Text HPText;
	sf::RectangleShape playerShowHPBar;

	sf::Text scoreText;
	sf::Text playerShowScoreText;

	sf::Text stageNumberText;
	
	//UI Resource2 [animation UI]
	UIAnimation* wButton;
	UIAnimation* aButton;
	UIAnimation* sButton;
	UIAnimation* dButton;
	UIAnimation* jButton;
	sf::Text moveText;
	sf::Text attackText;

	//State Resource
	std::map<std::string, sf::Texture> textures;

	sf::Font font;
	PopUpMenu* pauseMenu;
	PopUpMenu* gameOverMenu;
	PopUpMenu* gameWinMenu;
	
	//Intialization
	void initVariable();
	void initKeybinds();
	void initFonts();

	void initTexture();

	void initPlayer();
	
	void initView();
	void initUI();
	void initUIAnimation();
	void initPopUpMenu();

	//load
	void loadStage();
	void loadMusic();

public:
	//Constructor , Destructor
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, std::map<std::string, sf::Sound>* musicList,
		short unsigned player_index, std::string player_name);
	virtual ~GameState();

	//update
	void updateState(const float &dt);
	void updateInput(const float &dt);
	
	void updatePlayer(const float &dt);
	void updateStage(const float &dt);
	
	void updateView();
	void updateUI();
	void updateUIAnimation(const float &dt);
	void updatePauseMenuButton();
	void updateGameOverMenuButton();
	void updateGameWinButton();

	//render
	void renderState(sf::RenderTarget* target = NULL);
	
	void renderPlayer(sf::RenderTarget* target = NULL);
	void renderStage(sf::RenderTarget* target = NULL);
	
	void renderUI(sf::RenderTarget* target = NULL);
	void renderUIAnimation(sf::RenderTarget* target = NULL);
};

