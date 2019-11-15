#include "GameState.h"

//Initialization
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
	//load all palyer texture
	if (!this->textures["PLAYER_SHEET_DUDE"].loadFromFile("src/Resource/Charector/Player/Dude/Dude_Animation_List.png")) {
		throw("[Game State] >> ERROR can't load player texture");
	}
	if (!this->textures["PLAYER_SHEET_PINK"].loadFromFile("src/Resource/Charector/Player/Pink/Pink_Animation_List.png")) {
		throw("[Game State] >> ERROR can't load player texture");
	}
	if (!this->textures["PLAYER_SHEET_OWLET"].loadFromFile("src/Resource/Charector/Player/Owlet/Owlet_Animation_List.png")) {
		throw("[Game State] >> ERROR can't load player texture");
	}
	if (!this->textures["SKELETON_SHEET"].loadFromFile("src/Resource/Charector/Enemy/Skeleton/Skeleton_Idle.png")) {
		throw("[Game State] >> ERROR can't load Enemy texture");
	}
}

void GameState::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("src/Resource/Background/MainMenuState/background.png")) {
		throw("[Game State] >> ..ERROR.. Could't load backgroundTexture");
	}

	for (int i = 0; i < 10; i++) {
		sf::RectangleShape buff;
		buff.setTexture(&this->backgroundTexture);
		this->background.push_back(buff);
		this->background[i].setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
		this->background[i].setPosition(static_cast<float>(this->window->getSize().x) * i, 0.0f);
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

void GameState::initEnemy()
{
	for (short unsigned i = 1; i < 20; i++) {
		this->enemy.push_back(new Enemy(200.0f * i, 0.0f, this->textures["SKELETON_SHEET"], "1"));
	}
}

void GameState::initView()
{
	this->view.setSize(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y));
	this->view.setCenter(this->player->getCenter().x, this->window->getSize().y / 2.0f);

	this->window->setView(this->view);
}

void GameState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(this->view, this->font);
	this->pauseMenu->addButton("Resume", 4.0f, "RESUME");
	this->pauseMenu->addButton("Quit", 6.0f, "QUIT");
}

//Constructor , Destructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states,
	short unsigned player_index, std::string player_name)
	:State(window, supportedKeys, states), playerIndex(player_index), playerName(player_name)
{
	std::cout << "[Game State] >> On" << std::endl;
	this->initKeybinds();
	this->initFonts();

	this->initTexture();
	this->initBackground();

	this->initPlayer();
	this->initEnemy();

	this->initView();
	this->initPauseMenu();
}

GameState::~GameState()
{
	delete this->pauseMenu;
	delete this->player;

	if (!this->enemy.empty()) {
		for (int i = 0; i < this->enemy.size(); i++) {
			delete this->enemy[i];
			this->enemy.pop_back();
		}
	}
}

//Function
void GameState::updateState(const float &dt)
{
	this->updateMousePosition();
	this->updateKeyTime(dt);
	this->updateInput(dt);

	//Unpaused update
	if (!this->paused) {
		this->updatePlayer(dt);
		this->updateEnemy(dt);

		//clear enemy when it die
		if (!this->enemy.empty()) {
			for (int i = 0; i < this->enemy.size(); i++) {
				if (this->enemy[i]->getCurrHP() <= 0) {
					delete enemy[i];
					this->enemy.erase(this->enemy.begin() + i);
				}
			}
		}

	}
	//Paused update
	else {
		this->updatePauseMenuButton();
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
	//Update player input
	if (!this->player->getAttacking()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
			this->player->moveEntity(-1.0f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
			this->player->moveEntity(1.0f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))) && !this->player->getJumpping()) {
			this->player->jump();
		}
	}

	if (!this->player->getJumpping()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ATTACK_MELEE"))) && !this->player->getAttacking()) {	
			if (!this->enemy.empty()) {
				for (int i = 0; i < this->enemy.size(); i++) {
					this->player->attack(Player::ATTACK_MELEE, this->enemy[i]);
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ATTACK_RANGE"))) && !this->player->getAttacking()) {
			if (!this->enemy.empty()) {
				for (int i = 0; i < this->enemy.size(); i++) {
					this->player->attack(Player::ATTACK_RANGE, this->enemy[i]);
				}
			}
		}
	}

	//Update all player component
	this->player->updateEntity(dt, *this->window);
}

void GameState::updateEnemy(const float &dt)
{
	//Update all Entity component
	if (!this->enemy.empty()) {
		for (int i = 0; i < this->enemy.size(); i++) {
			this->enemy[i]->updateEntity(dt, *this->window);
		}
	}
} 

void GameState::updateView()
{
	this->view.setSize(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y));
	this->view.setCenter(this->player->getCenter().x, this->window->getSize().y / 2.0f);

	this->window->setView(this->view);

	
	if (this->view.getCenter().x - this->view.getSize().x / 2.0f < 0.0f || this->getQuit()) {
		this->view.setSize(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y));
		this->view.setCenter(
			this->window->getSize().x / 2.0f,
			this->window->getSize().y / 2.0f
		);
		this->window->setView(this->view);
	}
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

//render
void GameState::renderState(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	for (int i = 0; i < this->background.size(); i++) {
		target->draw(this->background[i]);
	}
	
	//render all entity 
	this->renderEnemy(target);
	this->renderPlayer(target);

	//paused menu render
	if (this->paused) {		
		this->pauseMenu->renderPauseMenu(*target);
	}
}

void GameState::renderPlayer(sf::RenderTarget * target)
{
	this->player->renderEntity(*target);
}

void GameState::renderEnemy(sf::RenderTarget* target)
{
	if (!this->enemy.empty()) {
		for (int i = 0; i < this->enemy.size(); i++) {
			this->enemy[i]->renderEntity(*target);
		}
	}
}
