#include "GameState.h"

//Initialization
void GameState::initFonts()
{
	//load font for this state
	if (!this->font.loadFromFile("src/Resource/Font/Planes_ValMore.ttf")) {
		throw("[GAME State] >> ..ERROR.. Could't load font");
	}
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
}

void GameState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);
	this->pauseMenu->addButton("Resume", 4.0f, "RESUME");
	this->pauseMenu->addButton("Quit", 6.0f, "QUIT");
}

void GameState::initPlayer()
{
	if (this->playerIndex == 0) {
		this->player = new Player(600, 0, this->textures["PLAYER_SHEET_DUDE"], this->playerName);
	}
	if (this->playerIndex == 1) {
		this->player = new Player(600, 0, this->textures["PLAYER_SHEET_PINK"], this->playerName);
	}
	if (this->playerIndex == 2) {
		this->player = new Player(600, 0, this->textures["PLAYER_SHEET_OWLET"], this->playerName);
	}
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
	this->initPauseMenu();

	this->initPlayer();
}

GameState::~GameState()
{
	delete this->pauseMenu;
	delete this->player;
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
		this->updateWindowCollision();
	}
	//Paused update
	else {
		this->updatePauseMenuButton();
	}
}

void GameState::updateWindowCollision()
{
	if (this->player) {
		if (this->player->getHitBoxPosition().x < 0.0f) {
			this->player->stopEntityX();

			this->player->setPosition(-this->player->getHitBoxOffSet().x,
				this->player->getHitBoxPosition().y - this->player->getHitBoxOffSet().y);
		}
		else if (this->player->getHitBoxPosition().x + this->player->getHitBoxSize().x > this->window->getSize().x) {
			this->player->stopEntityX();

			this->player->setPosition(this->window->getSize().x - this->player->getHitBoxSize().x -this->player->getHitBoxOffSet().x,
				this->player->getHitBoxPosition().y - this->player->getHitBoxOffSet().y);
		}
		
		if (this->player->getHitBoxPosition().y < 0.0f) {
			this->player->stopEntityY();

			this->player->setPosition(this->player->getHitBoxPosition().x - this->player->getHitBoxOffSet().x,
				-this->player->getHitBoxOffSet().y);
		}
		else if (this->player->getHitBoxPosition().y + this->player->getHitBoxSize().y > this->window->getSize().y) {
			this->player->stopEntityY();

			this->player->setPosition(this->player->getHitBoxPosition().x - this->player->getHitBoxOffSet().x,
				this->window->getSize().y - this->player->getHitBoxSize().y - this->player->getHitBoxOffSet().y);
		}
	}
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

void GameState::updatePlayer(const float &dt)
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
			this->player->attack(Player::ATTACK_MELEE);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ATTACK_RANGE"))) && !this->player->getAttacking()) {
			this->player->attack(Player::ATTACK_RANGE);
		}
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ATTACK_SKILL"))) && !this->player->getAttacking()) {
		this->player->attack(Player::ATTACK_SKILL);
	}*/
	}
	
	//Update all player component
	this->player->updateEntity(dt);
}

void GameState::updatePauseMenuButton()
{
	//Update all the buttons in Paused Menu
	this->pauseMenu->updatePauseMenu(this->mousePosView);

	//Action button
	if (this->pauseMenu->isButtonPreesed("Resume")) {
		this->unpausedState();
	}
	if (this->pauseMenu->isButtonPreesed("Quit")) {
		this->endState();
	}
}

void GameState::renderState(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	this->player->renderEntity(*target);

	//paused menu render
	if (this->paused) {		
		this->pauseMenu->renderPauseMenu(*target);
	}
}
