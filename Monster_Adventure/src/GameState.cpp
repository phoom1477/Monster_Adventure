#include "GameState.h"

//Initialization
void GameState::initVariable()
{
	this->maxStage = 10;
	this->currStage = 1;
}

void GameState::initKeybinds()
{
	std::ifstream fileconfig("src/Config/gamestate_keybinds.ini");
	if (fileconfig.is_open()) {
		std::string key = "";
		std::string key2 = "";

		while (fileconfig >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	fileconfig.close();
}

void GameState::initFonts()
{
	//load font for this state
	if (!this->font.loadFromFile("src/Resource/Font/Planes_ValMore.ttf")) {
		throw("[GAME State] >> ..ERROR.. Could't load font");
	}
}

void GameState::initTexture()
{
	//load all player texture
	if (!this->textures["PLAYER_SHEET_DUDE"].loadFromFile("src/Resource/Charector/Player/Dude/Dude_Animation_List.png")) {
		throw("[Game State] >> ERROR can't load player texture");
	}
	if (!this->textures["PLAYER_SHEET_PINK"].loadFromFile("src/Resource/Charector/Player/Pink/Pink_Animation_List.png")) {
		throw("[Game State] >> ERROR can't load player texture");
	}
	if (!this->textures["PLAYER_SHEET_OWLET"].loadFromFile("src/Resource/Charector/Player/Owlet/Owlet_Animation_List.png")) {
		throw("[Game State] >> ERROR can't load player texture");
	}

	//load all enemy texture
	if (!this->textures["ENEMY_SHEET_SKELETON"].loadFromFile("src/Resource/Charector/Enemy/Skeleton/Skeleton_Animation_List.png")) {
		throw("[Game State] >> ERROR can't load Enemy texture");
	}
	if (!this->textures["ENEMY_SHEET_MINOTAUR"].loadFromFile("src/Resource/Charector/Enemy/Minotaur/Minotaur_Animation_List.png")) {
		throw("[Game State] >> ERROR can't load Enemy texture");
	}
	if (!this->textures["ENEMY_SHEET_KNIGHT"].loadFromFile("src/Resource/Charector/Enemy/Knight/Knight_Animation_List.png")) {
		throw("[Game State] >> ERROR can't load Enemy texture");
	}
	if (!this->textures["ENEMY_SHEET_VIKING"].loadFromFile("src/Resource/Charector/Enemy/Viking/Viking_Animation_List.png")) {
		throw("[Game State] >> ERROR can't load Enemy texture");
	}
	if (!this->textures["ENEMY_SHEET_KING"].loadFromFile("src/Resource/Charector/Enemy/King/King_Animation_List.png")) {
		throw("[Game State] >> ERROR can't load Enemy texture");
	}

	//load all UIAnimation texture
	if (!this->textures["UI_SHEET_WBUTTON"].loadFromFile("src/Resource/UI/Keyboard/Wbutton.png")) {
		throw("[Game State] >> ERROR can't load UIAnimation texture");
	}
	if (!this->textures["UI_SHEET_ABUTTON"].loadFromFile("src/Resource/UI/Keyboard/Abutton.png")) {
		throw("[Game State] >> ERROR can't load UIAnimation texture");
	}
	if (!this->textures["UI_SHEET_SBUTTON"].loadFromFile("src/Resource/UI/Keyboard/Sbutton.png")) {
		throw("[Game State] >> ERROR can't load UIAnimation texture");
	}
	if (!this->textures["UI_SHEET_DBUTTON"].loadFromFile("src/Resource/UI/Keyboard/Dbutton.png")) {
		throw("[Game State] >> ERROR can't load UIAnimation texture");
	}
	if (!this->textures["UI_SHEET_JBUTTON"].loadFromFile("src/Resource/UI/Keyboard/Jbutton.png")) {
		throw("[Game State] >> ERROR can't load UIAnimation texture");
	}
}

void GameState::initPlayer()
{
	if (this->playerIndex == 0) {
		this ->player = new Player(600, 0, this->textures["PLAYER_SHEET_DUDE"], this->playerName);
	}
	if (this->playerIndex == 1) {
		this->player = new Player(600, 0, this->textures["PLAYER_SHEET_PINK"], this->playerName);
	}
	if (this->playerIndex == 2) {
		this->player = new Player(600, 0, this->textures["PLAYER_SHEET_OWLET"], this->playerName);
	}
}

void GameState::initView()
{
	this->view.setSize(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y));
	
	this->view.setCenter(this->player->getCenter().x, this->window->getSize().y / 2.0f);

	this->window->setView(this->view);
}

void GameState::initUI()
{
	//convertor
	std::stringstream int_to_string;

	//create nameText
	this->nameText.setFont(this->font);
	this->nameText.setCharacterSize(30);
	this->nameText.setOutlineThickness(2.0f);
	this->nameText.setOutlineColor(sf::Color::Black);
	this->nameText.setString(this->player->getName());
	this->nameText.setPosition(
		this->view.getCenter().x + 300.0f,
		10.0f
	);
	//create ATKText
	this->ATKText.setFont(this->font);
	this->ATKText.setCharacterSize(20);
	this->ATKText.setOutlineThickness(2.0f);
	this->ATKText.setOutlineColor(sf::Color::Black);
	this->ATKText.setString("ATK :");
	this->ATKText.setLetterSpacing(1.5f);
	this->ATKText.setPosition(
		this->view.getCenter().x - this->view.getSize().x / 2.0f + 15.0f,
		50.0f
	);
	//create DEFText
	this->DEFText.setFont(this->font);
	this->DEFText.setCharacterSize(20);
	this->DEFText.setOutlineThickness(2.0f);
	this->DEFText.setOutlineColor(sf::Color::Black);
	this->DEFText.setString("DEF : ");
	this->DEFText.setLetterSpacing(2.0f);
	this->DEFText.setPosition(
		this->view.getCenter().x - this->view.getSize().x / 2.0f + 15.0f,
		80.0f
	);
	//create HPText
	this->HPText.setFont(this->font);
	this->HPText.setCharacterSize(30);
	this->HPText.setOutlineThickness(2.0f);
	this->HPText.setOutlineColor(sf::Color::Black);
	this->HPText.setString("HP");
	this->HPText.setPosition(
		this->view.getCenter().x - this->view.getSize().x / 2.0f + 20.0f,
		10.0f
	);
	//create scoreText
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(30);
	this->scoreText.setOutlineThickness(2.0f);
	this->scoreText.setOutlineColor(sf::Color::Black);
	this->scoreText.setString("SCORE :");
	this->scoreText.setPosition(
		this->view.getCenter().x + 300.0f,
		50.0f
	);


	//create playerShowATKText
	int_to_string << this->player->getATK();
	this->playerShowATKText.setFont(this->font);
	this->playerShowATKText.setCharacterSize(20);
	this->playerShowATKText.setOutlineThickness(2.0f);
	this->playerShowATKText.setOutlineColor(sf::Color::Black);
	this->playerShowATKText.setString(int_to_string.str());
	this->DEFText.setLetterSpacing(2.0f);
	this->playerShowATKText.setPosition(
		this->view.getCenter().x - this->view.getSize().x / 2.0f + 90.0f,
		50.0f
	);
	int_to_string.str("");
	//create playerShowDEFText
	int_to_string << this->player->getDEF();
	this->playerShowDEFText.setFont(this->font);
	this->playerShowDEFText.setCharacterSize(20);
	this->playerShowDEFText.setOutlineThickness(2.0f);
	this->playerShowDEFText.setOutlineColor(sf::Color::Black);
	this->playerShowDEFText.setString(int_to_string.str());
	this->DEFText.setLetterSpacing(2.0f);
	this->playerShowDEFText.setPosition(
		this->view.getCenter().x - this->view.getSize().x / 2.0f + 90.0f,
		80.0f
	);
	int_to_string.str("");
	//create playerShowHPBar
	this->playerShowHPBar.setOutlineThickness(5.0f);
	this->playerShowHPBar.setOutlineColor(sf::Color::Black);
	this->playerShowHPBar.setFillColor(sf::Color::Green);
	this->playerShowHPBar.setSize(sf::Vector2f(
		(this->view.getSize().x / 2.0f)*(this->player->getCurrHP() / this->player->getMaxHP()) , 
		20.0f
	));
	this->playerShowHPBar.setPosition(
		this->view.getCenter().x - this->view.getSize().x / 2.0f + 80.0f, 
		20.0f
	);
	//create playerShowScoreText
	int_to_string << this->player->getScore();
	this->playerShowScoreText.setFont(this->font);
	this->playerShowScoreText.setCharacterSize(30);
	this->playerShowScoreText.setOutlineThickness(2.0f);
	this->playerShowScoreText.setOutlineColor(sf::Color::Black);
	this->playerShowScoreText.setString(int_to_string.str());
	this->playerShowScoreText.setPosition(
		this->view.getCenter().x + 420.0f,
		50.0f
	);
	int_to_string.str("");

	//create stageNumberText
	int_to_string << this->currStage;
	this->stageNumberText.setFont(this->font);
	this->stageNumberText.setCharacterSize(40);
	this->stageNumberText.setOutlineThickness(2.0f);
	this->stageNumberText.setOutlineColor(sf::Color::Black);
	this->stageNumberText.setString("STAGE : " + int_to_string.str());
	this->stageNumberText.setPosition(
		this->view.getCenter().x - this->stageNumberText.getGlobalBounds().width / 2.0f,
		this->view.getSize().y / 16.0f * 2.0f
	);
}

void GameState::initUIAnimation()
{
	//create UIAnimation
	this->wButton = new UIAnimation(
		this->view.getCenter().x + 325.0f,
		100.0f,
		this->textures["UI_SHEET_WBUTTON"]
	);
	this->wButton->setScale(2.0f, 2.0f);

	this->aButton = new UIAnimation(
		this->view.getCenter().x + 300.0f,
		130.0f,
		this->textures["UI_SHEET_ABUTTON"]
	);
	this->aButton->setScale(2.0f, 2.0f);

	this->sButton = new UIAnimation(
		this->view.getCenter().x + 325.0f,
		130.0f,
		this->textures["UI_SHEET_SBUTTON"]
	);
	this->sButton->setScale(2.0f, 2.0f);

	this->dButton = new UIAnimation(
		this->view.getCenter().x + 350.0f,
		130.0f,
		this->textures["UI_SHEET_DBUTTON"]
	);
	this->dButton->setScale(2.0f, 2.0f);

	this->jButton = new UIAnimation(
		this->view.getCenter().x + 325.0f,
		170.0f,
		this->textures["UI_SHEET_JBUTTON"]
	);
	this->jButton->setScale(2.0f, 2.0f);

	//create description text
	this->moveText.setFont(this->font);
	this->moveText.setCharacterSize(20);
	this->moveText.setOutlineThickness(2.0f);
	this->moveText.setOutlineColor(sf::Color::Black);
	this->moveText.setString("MOVE");
	this->moveText.setPosition(
		this->view.getCenter().x + 425.0f,
		120.0f
	);

	this->attackText.setFont(this->font);
	this->attackText.setCharacterSize(20);
	this->attackText.setOutlineThickness(2.0f);
	this->attackText.setOutlineColor(sf::Color::Black);
	this->attackText.setString("ATTACK");
	this->attackText.setPosition(
		this->view.getCenter().x + 425.0f,
		177.0f
	);
}

void GameState::initPopUpMenu()
{
	this->pauseMenu = new PopUpMenu(this->view, this->font);
	this->pauseMenu->setMenuTextString("PAUSED");
	this->pauseMenu->setMenuTextPosition(0.5f);
	this->pauseMenu->addButton("Resume", 4.5f, "RESUME");
	this->pauseMenu->addButton("Quit", 6.5f, "QUIT");

	this->gameOverMenu = new PopUpMenu(this->view, this->font);
	this->gameOverMenu->setMenuTextString("GAME OVER");
	this->gameOverMenu->setWidth((this->view.getSize().x / 16.0f) * 6.0f);
	this->gameOverMenu->setMenuTextPosition(0.5f);
	this->gameOverMenu->setDescriptTextPosition(7.0f);
	this->gameOverMenu->addButton("Quit", 14.25f, "EXIT TO MENU");

	this->gameWinMenu = new PopUpMenu(this->view, this->font);
	this->gameWinMenu->setMenuTextString("!! Congratulation !!");
	this->gameWinMenu->setWidth((this->view.getSize().x / 16.0f) * 8.0f);
	this->gameWinMenu->setMenuTextPosition(0.5f);
	this->gameWinMenu->setDescriptTextPosition(7.0f);
	this->gameWinMenu->addButton("Quit", 14.25f, "EXIT TO MENU");
}

//load
void GameState::loadStage()
{
	srand((int)time(NULL));
	
	//create new stage
	if (this->currStage == 1) {
		this->stages = new Stage(this->window, this->font, this->player);

		//set up background
		this->stages->addBackground("1");

		//set up enemy
		for (int i = 0; i < 2; i++) {
			this->stages->addEnemy((float)(rand() % this->stages->getStageSize().x), 50.0f, this->textures["ENEMY_SHEET_SKELETON"], "1");
		}
		
		//return enemy address to enemy in gamestate
		this->enemy = &this->stages->getEnemy();
	}
	if (this->currStage == 2){
		this->stages = new Stage(this->window, this->font, this->player);

		//set up background
		this->stages->addBackground("2");

		//set up enemy
		for (int i = 0; i < 3; i++) {
			this->stages->addEnemy((float)(rand() % this->stages->getStageSize().x), 50.0f, this->textures["ENEMY_SHEET_SKELETON"], "1");
		}

		//return enemy address to enemy in gamestate
		this->enemy = &this->stages->getEnemy();
	}
	if (this->currStage == 3) {
		this->stages = new Stage(this->window, this->font, this->player);

		//set up background
		this->stages->addBackground("2");

		//set up enemy
		for (int i = 0; i < 5; i++) {
			this->stages->addEnemy((float)(rand() % this->stages->getStageSize().x), 50.0f, this->textures["ENEMY_SHEET_SKELETON"], "1");
		}

		//return enemy address to enemy in gamestate
		this->enemy = &this->stages->getEnemy();
	}
	if (this->currStage == 4) {
		this->stages = new Stage(this->window, this->font, this->player);

		//set up background
		this->stages->addBackground("3");

		//set up enemy
		for (int i = 0; i < 3; i++) {
			this->stages->addEnemy((float)(rand() % this->stages->getStageSize().x), 50.0f, this->textures["ENEMY_SHEET_MINOTAUR"], "2");
		}

		//return enemy address to enemy in gamestate
		this->enemy = &this->stages->getEnemy();
	}
	if (this->currStage == 5) {
		this->stages = new Stage(this->window, this->font, this->player);

		//set up background
		this->stages->addBackground("3");

		//set up enemy
		for (int i = 0; i < 5; i++) {
			this->stages->addEnemy((float)(rand() % this->stages->getStageSize().x), 50.0f, this->textures["ENEMY_SHEET_MINOTAUR"], "2");
		}

		//return enemy address to enemy in gamestate
		this->enemy = &this->stages->getEnemy();
	}
	if (this->currStage == 6) {
		this->stages = new Stage(this->window, this->font, this->player);

		//set up background
		this->stages->addBackground("4");

		//set up enemy
		for (int i = 0; i < 3; i++) {
			this->stages->addEnemy((float)(rand() % this->stages->getStageSize().x), 50.0f, this->textures["ENEMY_SHEET_KNIGHT"], "3");
		}

		//return enemy address to enemy in gamestate
		this->enemy = &this->stages->getEnemy();
	}
	if (this->currStage == 7) {
		this->stages = new Stage(this->window, this->font, this->player);

		//set up background
		this->stages->addBackground("4");

		//set up enemy
		for (int i = 0; i < 5; i++) {
			this->stages->addEnemy((float)(rand() % this->stages->getStageSize().x), 50.0f, this->textures["ENEMY_SHEET_KNIGHT"], "3");
		}

		//return enemy address to enemy in gamestate
		this->enemy = &this->stages->getEnemy();
	}
	if (this->currStage == 8) {
		this->stages = new Stage(this->window, this->font, this->player);

		//set up background
		this->stages->addBackground("5");

		//set up enemy
		for (int i = 0; i < 3; i++) {
			this->stages->addEnemy((float)(rand() % this->stages->getStageSize().x), 50.0f, this->textures["ENEMY_SHEET_VIKING"], "4");
		}

		//return enemy address to enemy in gamestate
		this->enemy = &this->stages->getEnemy();
	}
	if (this->currStage == 9) {
		this->stages = new Stage(this->window, this->font, this->player);

		//set up background
		this->stages->addBackground("5");

		//set up enemy
		for (int i = 0; i < 5; i++) {
			this->stages->addEnemy((float)(rand() % this->stages->getStageSize().x), 50.0f, this->textures["ENEMY_SHEET_VIKING"], "4");
		}

		//return enemy address to enemy in gamestate
		this->enemy = &this->stages->getEnemy();
	}
	if (this->currStage == 10) {
		this->stages = new Stage(this->window, this->font, this->player);

		//set up background
		this->stages->addBackground("6");

		//set up enemy
		for (int i = 0; i < 1; i++) {
			this->stages->addEnemy(this->window->getSize().x / 2.0f, 50.0f, this->textures["ENEMY_SHEET_KING"], "5");
		}

		//return enemy address to enemy in gamestate
		this->enemy = &this->stages->getEnemy();
	}

	//fit size vector
	this->enemy->shrink_to_fit();
}

void GameState::loadMusic()
{
	//stop song
	if (this->currStage % 2 == 0 || this->currStage == 1) {
		if (this->music.getStatus() == sf::Sound::Playing) {
			this->music.stop();
		}
	}

	//select song to play
	if (this->currStage == 1) {
		this->music = this->musicList->at("MUSIC_1");
	}
	if (this->currStage == 2) {
		this->music = this->musicList->at("MUSIC_2");
	}
	if (this->currStage == 4) {
		this->music = this->musicList->at("MUSIC_3");
	}
	if (this->currStage == 6) {
		this->music = this->musicList->at("MUSIC_4");
	}
	if (this->currStage == 8) {
		this->music = this->musicList->at("MUSIC_5");
	}
	if (this->currStage == 10) {
		this->music = this->musicList->at("MUSIC_6");
	}

	//play that song
	if (this->music.getStatus() != sf::Sound::Playing) {
		this->music.play();
	}
}

//Constructor , Destructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, std::map<std::string, sf::Sound>* musicList,
	short unsigned player_index, std::string player_name)
	:State(window, supportedKeys, states, musicList), playerIndex(player_index), playerName(player_name)
{
	std::cout << "[Game State] >> On" << std::endl;
	this->initVariable();
	this->initKeybinds();
	this->initFonts();

	this->initTexture();

	this->initPlayer();

	this->initView();
	this->initUI();
	this->initUIAnimation();
	this->initPopUpMenu();

	//load first stage
	this->loadStage();
	this->loadMusic();
}

GameState::~GameState()
{
	delete this->wButton;
	delete this->aButton;
	delete this->sButton;
	delete this->dButton;
	delete this->jButton;

	delete this->pauseMenu;
	delete this->gameOverMenu;
	delete this->gameWinMenu;

	delete this->player;
	delete this->stages;
}

//Function
void GameState::updateState(const float &dt)
{
	this->updateMousePosition();
	this->updateKeyTime(dt);

	//game over 
	if (this->gameover) {
		this->updateGameOverMenuButton();
	}
	//win this game
	else if (this->gamewin) {
		this->updateGameWinButton();
	}
	//not gameover
	else {
		this->updateInput(dt);

		//Unpaused update
		if (!this->paused) {
			this->updatePlayer(dt);
			this->updateStage(dt);

			this->updateUI();
			this->updateUIAnimation(dt);
		}
		//Paused update
		else if (this->paused) {
			this->updatePauseMenuButton();
		}
	}

	this->updateView();
}

void GameState::updateInput(const float &dt)
{
	//Update paused input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime()) {
		if (!this->paused) {
			this->pausedState();
		}
		else {
			this->unpausedState();
		}
	}
}

void GameState::updatePlayer(const float & dt)
{
	//Control player
	if (!this->player->getAttacking()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
			this->player->moveEntity(-1.0f, 0.0f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
			this->player->moveEntity(1.0f, 0.0f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))) && !this->player->getJumpping()) {
			this->player->jump();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
			this->player->moveEntity(0.0f,1.0f,dt);
		}
	}
	if (!this->player->getJumpping() && !this->player->getHurting()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ATTACK"))) && !this->player->getAttacking()) {
			if (!this->enemy->empty()) {
				srand(int(time(NULL)));
				for (int i = 0; i < this->enemy->size(); i++) {
					//random attack style [chance to double is 40%]
					if (rand() % 100 <= 40) {
						this->player->attack(dt, Player::ATTACK_DOUBLE, this->enemy->at(i));
					}
					else {
						this->player->attack(dt, Player::ATTACK_ONCE, this->enemy->at(i));
					}
				}
			}
		}
	}

	//Update all player component
	this->player->updateEntity(dt, *this->window);

	//clear player when died
	if (this->player->getDied()) {
		this->gameOverState();

		//write score in score.data
		std::fstream scorefile("src/Config/Data/Score.data", std::ios::app);
		scorefile << "\n" << this->player->getName();
		scorefile << "\t\t" << this->player->getScore();
		scorefile.close();
	}
}

void GameState::updateStage(const float & dt)
{
	this->stages->updateStage(dt);

	//add new stage 
	if (this->stages->getClear()) {
		if (this->currStage < this->maxStage) {
			//bonus for player cleared stage [heal 10% HP]
			this->player->increaseHP(10);

			//clear old stage for create new
			if (this->stages) {
				delete this->stages;
				this->stages = NULL;
			}

			//create new stage
			currStage++;
			this->loadStage();
			this->loadMusic();
		}
		else {
			this->gameWinState();

			//write score in score.data
			std::fstream scorefile("src/Config/Data/Score.data", std::ios::app);
			scorefile << "\n" << this->player->getName();
			scorefile << "\t\t" << this->player->getScore();
			scorefile.close();
		}
	}
}

void GameState::updateView()
{
	this->view.setSize(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y));
	this->view.setCenter(this->player->getCenter().x, this->window->getSize().y / 2.0f);

	this->window->setView(this->view);

	//limit left view frame
	if (this->view.getCenter().x <= this->view.getSize().x / 2.0f || this->getQuit()) {
		this->view.setSize(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y));
		this->view.setCenter(
			this->window->getSize().x / 2.0f,
			this->window->getSize().y / 2.0f
		);
		this->window->setView(this->view);
	}
	//limit right view frame
	if (this->view.getCenter().x >= this->stages->getStageSize().x - this->view.getSize().x / 2.0f) {
		this->view.setSize(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y));
		this->view.setCenter(
			this->stages->getStageSize().x - this->window->getSize().x / 2.0f,
			this->window->getSize().y / 2.0f
		);
		this->window->setView(this->view);
	}
}

void GameState::updateUI()
{
	//convertor
	std::stringstream int_to_string;

	//update nameText
	this->nameText.setPosition(
		this->view.getCenter().x + 300.0f,
		10.0f
	);
	//update ATKText
	this->ATKText.setPosition(
		this->view.getCenter().x - this->view.getSize().x / 2.0f + 15.0f,
		50.0f
	);
	//update DEFText
	this->DEFText.setPosition(
		this->view.getCenter().x - this->view.getSize().x / 2.0f + 15.0f,
		80.0f
	);
	//update HPText
	this->HPText.setPosition(
		this->view.getCenter().x - this->view.getSize().x / 2.0f + 20.0f,
		10.0f
	);
	//update scoreText
	this->scoreText.setPosition(
		this->view.getCenter().x + 300.0f,
		50.0f
	);



	//update playerShowATKText
	int_to_string << this->player->getATK();
	this->playerShowATKText.setString(int_to_string.str());
	this->playerShowATKText.setPosition(
		this->view.getCenter().x - this->view.getSize().x / 2.0f + 90.0f,
		50.0f
	);
	int_to_string.str("");

	//update playerShowDEFText
	int_to_string << this->player->getDEF();
	this->playerShowDEFText.setString(int_to_string.str());
	this->playerShowDEFText.setPosition(
		this->view.getCenter().x - this->view.getSize().x / 2.0f + 90.0f,
		80.0f
	);
	int_to_string.str("");

	//update playerShowHPBar
	if ((this->player->getCurrHP() / this->player->getMaxHP()) * 100.0f > 50.0f) {
		this->playerShowHPBar.setFillColor(sf::Color::Green);
	}
	if ((this->player->getCurrHP() / this->player->getMaxHP()) * 100.0f <= 50.0f) {
		this->playerShowHPBar.setFillColor(sf::Color::Yellow);
	}
	if ((this->player->getCurrHP() / this->player->getMaxHP()) * 100.0f <= 20.0f) {
		this->playerShowHPBar.setFillColor(sf::Color::Red);
	}

	if (this->player->getCurrHP() <= 0.0f) {
		this->playerShowHPBar.setSize(sf::Vector2f(
			0.0f,
			20.0f
		));
	}
	else {
		this->playerShowHPBar.setSize(sf::Vector2f(
			(this->view.getSize().x / 2.0f)*(this->player->getCurrHP() / this->player->getMaxHP()),
			20.0f
		));
	}
	this->playerShowHPBar.setPosition(
		this->view.getCenter().x - this->view.getSize().x / 2.0f + 80.0f,
		20.0f
	);

	//update playerShowScoreText
	int_to_string << this->player->getScore();
	this->playerShowScoreText.setString(int_to_string.str());
	this->playerShowScoreText.setPosition(
		this->view.getCenter().x + 420.0f,
		50.0f
	);
	int_to_string.str("");

	int_to_string << this->currStage;
	if (this->currStage == 10) {
		int_to_string << " [BOSS] ";
	}
	this->stageNumberText.setString("STAGE : " + int_to_string.str());
	this->stageNumberText.setPosition(
		this->view.getCenter().x - this->stageNumberText.getGlobalBounds().width / 2.0f,
		this->view.getSize().y / 16.0f * 2.0f
	);
	int_to_string.str("");
}

void GameState::updateUIAnimation(const float &dt)
{
	//update UIAnimation
	this->wButton->updateEntity(dt);
	this->wButton->setPosition(
		this->view.getCenter().x + 325.0f,
		100.0f
	);

	this->aButton->updateEntity(dt);
	this->aButton->setPosition(
		this->view.getCenter().x + 300.0f,
		130.0f
	);

	this->sButton->updateEntity(dt);
	this->sButton->setPosition(
		this->view.getCenter().x + 325.0f,
		130.0f
	);

	this->dButton->updateEntity(dt);
	this->dButton->setPosition(
		this->view.getCenter().x + 350.0f,
		130.0f
	);

	this->jButton->updateEntity(dt);
	this->jButton->setPosition(
		this->view.getCenter().x + 325.0f,
		170.0f
	);

	//update description text
	this->moveText.setPosition(
		this->view.getCenter().x + 425.0f,
		120.0f
	);
	this->attackText.setPosition(
		this->view.getCenter().x + 425.0f,
		177.0f
	);
}

void GameState::updatePauseMenuButton()
{
	//Update all the buttons in Paused Menu
	this->pauseMenu->updatePauseMenu(this->mousePosView, this->view);

	//Action button
	if (this->pauseMenu->isButtonPreesed("Resume")) {
		this->unpausedState();
	}
	if (this->pauseMenu->isButtonPreesed("Quit")) {
		this->endState();
	}
}

void GameState::updateGameOverMenuButton()
{
	//update content
	std::stringstream int_to_string;
	int_to_string << this->player->getScore();
	this->gameOverMenu->setDescriptTextString("Score : " + int_to_string.str());

	//Update all the buttons in Game Over Menu
	this->gameOverMenu->updatePauseMenu(this->mousePosView, this->view);

	//Action button
	if (this->gameOverMenu->isButtonPreesed("Quit")) {
		this->endState();
	}
}

void GameState::updateGameWinButton()
{
	//update content
	std::stringstream int_to_string;
	int_to_string << this->player->getScore();
	this->gameWinMenu->setDescriptTextString("Score : " + int_to_string.str());

	//Update all the buttons in Game Over Menu
	this->gameWinMenu->updatePauseMenu(this->mousePosView, this->view);

	//Action button
	if (this->gameWinMenu->isButtonPreesed("Quit")) {
		this->endState();
	}
}

//render
void GameState::renderState(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	//render stages
	this->renderStage(target);
	
	//render player
	this->renderPlayer(target);
	
	//render UI
	this->renderUI(target);

	//render UIAnimation
	this->renderUIAnimation(target);

	//paused menu render
	if (this->paused) {		
		this->pauseMenu->renderPauseMenu(*target);
	}

	//gameover menu render
	if (this->gameover) {
		this->gameOverMenu->renderPauseMenu(*target);
	}

	//win menu render
	if (this->gamewin) {
		this->gameWinMenu->renderPauseMenu(*target);
	}
}

void GameState::renderPlayer(sf::RenderTarget * target)
{
	this->player->renderEntity(*target);
}

void GameState::renderStage(sf::RenderTarget * target)
{
	this->stages->renderStage();
}

void GameState::renderUI(sf::RenderTarget * target)
{
	target->draw(this->nameText);

	target->draw(this->HPText);
	target->draw(this->ATKText);
	target->draw(this->DEFText);
	target->draw(this->scoreText);

	target->draw(this->playerShowHPBar);
	target->draw(this->playerShowATKText);
	target->draw(this->playerShowDEFText);
	target->draw(this->playerShowScoreText);

	target->draw(this->stageNumberText);
}

void GameState::renderUIAnimation(sf::RenderTarget * target)
{
	this->wButton->renderUIAnimation(*target);
	this->aButton->renderUIAnimation(*target);
	this->sButton->renderUIAnimation(*target);
	this->dButton->renderUIAnimation(*target);
	this->jButton->renderUIAnimation(*target);

	target->draw(this->moveText);
	target->draw(this->attackText);
}

