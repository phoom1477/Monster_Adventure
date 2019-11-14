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
	if (!this->textures["SKELETON_SHEET"].loadFromFile("src/Resource/Charector/Enemy/Skeleton/Skeleton_Idle.png")) {
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

void GameState::initEnemy()
{
	for (short unsigned i = 1; i < 3; i++) {
		this->enemy.push_back(new Enemy(200 * i, 0, this->textures["SKELETON_SHEET"], "1"));
	}
}

void GameState::initView()
{
	this->view.setSize(this->window->getSize().x, this->window->getSize().y);
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
		this->updateCollision();
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
			this->player->attack(Player::ATTACK_MELEE);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ATTACK_RANGE"))) && !this->player->getAttacking()) {
			this->player->attack(Player::ATTACK_RANGE);
		}
	}

	//Update all player component
	this->player->updateEntity(dt);

	//Check attack collision
	/*if (!this->enemy.empty()) {
		for (int i = 0; i < this->enemy.size(); i++) {
			if (this->player->checkHitCollision(enemy[i]) && this->getKeyTime()) {
				
				enemy[i]->decreaseHP(this->player->getATK());
				
				if (enemy[i]->getCurrHP() <= 0.0f) {
					delete enemy[i];
					enemy.erase(enemy.begin() + i);
				}
			}
		}
	}*/
}

void GameState::updateEnemy(const float &dt)
{
	//Update all Entity component
	if (!this->enemy.empty()) {
		for (int i = 0; i < this->enemy.size(); i++) {
			this->enemy[i]->updateEntity(dt);
		}
	}

	//Check attack collision
	/*if (!this->enemy.empty()) {
		for (int i = 0; i < this->enemy.size(); i++) {
			if (this->enemy[i]->checkHitCollision(this->player)) {
		
			}
		}
	}*/
}

void GameState::updateCollision()
{
	this->updatePlayerCollisionFrame();
	this->updateEnemyCollisionFrame();
}

void GameState::updatePlayerCollisionFrame()
{
	if (this->player) {
		if (this->player->getPosition().x < 0.0f) {
			this->player->setPosition(
				0.0f,
				this->player->getPosition().y
			);

			this->player->stopEntityX();
		}
		else if (this->player->getPosition().x + this->player->getGlobalBounds().width > this->window->getSize().x) {
			this->player->setPosition(
				this->window->getSize().x - this->player->getGlobalBounds().width,
				this->player->getPosition().y
			);

			this->player->stopEntityX();
		}
		if (this->player->getPosition().y < 0.0f) {
			this->player->setPosition(
				this->player->getPosition().x,
				0.0f
			);

			this->player->stopEntityY();
		}
		else if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window->getSize().y) {
			this->player->setPosition(
				this->player->getPosition().x,
				this->window->getSize().y - this->player->getGlobalBounds().height
			);

			this->player->stopEntityY();
		}
	}
}

void GameState::updateEnemyCollisionFrame()
{
	for (int i = 0; i < this->enemy.size(); i++) {
		if (this->enemy[i]->getPosition().x < 0.0f) {
			this->enemy[i]->setPosition(
				0.0f,
				this->enemy[i]->getPosition().y
			);

			this->enemy[i]->stopEntityX();
		}
		else if (this->enemy[i]->getPosition().x + this->enemy[i]->getGlobalBounds().width > this->window->getSize().x) {
			this->enemy[i]->setPosition(
				this->window->getSize().x - this->enemy[i]->getGlobalBounds().width,
				this->enemy[i]->getPosition().y
			);

			this->enemy[i]->stopEntityX();
		}
		if (this->enemy[i]->getPosition().y < 0.0f) {
			this->enemy[i]->setPosition(
				this->enemy[i]->getPosition().x,
				0.0f
			);

			this->enemy[i]->stopEntityY();
		}
		else if (this->enemy[i]->getPosition().y + this->enemy[i]->getGlobalBounds().height > this->window->getSize().y) {
			this->enemy[i]->setPosition(
				this->enemy[i]->getPosition().x,
				this->window->getSize().y - this->enemy[i]->getGlobalBounds().height
			);

			this->enemy[i]->stopEntityY();
		}
	}
}

void GameState::updateView()
{
	this->view.setSize(this->window->getSize().x, this->window->getSize().y);
	this->view.setCenter(this->player->getCenter().x, this->window->getSize().y / 2.0f);

	this->window->setView(this->view);

	if (this->getQuit()) {
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
