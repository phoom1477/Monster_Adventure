#include "GameState.h"

//Initialization
void GameState::initVariable()
{
	this->maxStage = 2;
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
	//create nameText
	this->nameText.setFont(this->font);
	this->nameText.setCharacterSize(30);
	this->nameText.setString(this->player->getName());
	this->nameText.setPosition(
		this->view.getCenter().x + 300.0f,
		10.0f
	);
	//create HPText
	this->HPText.setFont(this->font);
	this->HPText.setCharacterSize(30);
	this->HPText.setString("HP");
	this->HPText.setPosition(
		this->view.getCenter().x - this->view.getSize().x / 2.0f + 20.0f,
		10.0f
	);
	//create scoreText
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(30);
	this->scoreText.setString("SCORE :");
	this->scoreText.setPosition(
		this->view.getCenter().x + 300.0f,
		50.0f
	);


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
	std::stringstream int_to_string;
	int_to_string << this->player->getScore();
	this->playerShowScoreText.setFont(this->font);
	this->playerShowScoreText.setCharacterSize(30);
	this->playerShowScoreText.setString(int_to_string.str());
	this->playerShowScoreText.setPosition(
		this->view.getCenter().x + 420.0f,
		50.0f
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
	//create new stage
	if (this->currStage == 1) {
		this->stages = new Stage(this->window, this->player);
		
		//set up background
		this->stages->addBackground(1);

		//set up enemy
		for (int i = 0; i < 5; i++) {
			this->stages->addEnemy(i * 100.0f, 50.0f, this->textures["ENEMY_SHEET_SKELETON"], "1");
		}

		//return enemy address to enemy in gamestate
		this->enemy = &this->stages->getEnemy();
	}
	if(this->currStage == 2){
		this->stages = new Stage(this->window, this->player);

		//set up background
		this->stages->addBackground(2);

		//set up enemy
		for (int i = 0; i < 10; i++) {
			this->stages->addEnemy(i * 100.0f, 50.0f, this->textures["ENEMY_SHEET_SKELETON"], "1");
		}

		//return enemy address to enemy in gamestate
		this->enemy = &this->stages->getEnemy();
	}
}

//Constructor , Destructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states,
	short unsigned player_index, std::string player_name)
	:State(window, supportedKeys, states), playerIndex(player_index), playerName(player_name)
{
	std::cout << "[Game State] >> On" << std::endl;
	this->initVariable();
	this->initKeybinds();
	this->initFonts();

	this->initTexture();
	//this->initBackground();

	this->initPlayer();

	this->initView();
	this->initUI();
	this->initPopUpMenu();

	//load first stage
	this->loadStage();
}

GameState::~GameState()
{
	delete this->pauseMenu;
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
			//clear old stage for create new
			if (this->stages) {
				delete this->stages;
				this->stages = NULL;
			}

			//create new stage
			currStage++;
			this->loadStage();
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
	
	//update nameText
	this->nameText.setPosition(
		this->view.getCenter().x + 300.0f,
		10.0f
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


	//update playerShowHPBar
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
	std::stringstream int_to_string;
	int_to_string << this->player->getScore();
	this->playerShowScoreText.setString(int_to_string.str());
	this->playerShowScoreText.setPosition(
		this->view.getCenter().x + 420.0f,
		50.0f
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
	target->draw(this->scoreText);

	target->draw(this->playerShowHPBar);
	target->draw(this->playerShowScoreText);
}

