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
	if (!this->textures["PLAYER_SHEET"].loadFromFile("src/Resource/Charector/Player/Dude/Dude_Animation_List.png")) {
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
	this->player = new Player(0, 0,this->textures["PLAYER_SHEET"]);
}

//Constructor , Destructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) 
	:State(window, supportedKeys, states)
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
	}
	//Paused update
	else {
		this->updatePauseMenuButton();
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
	//Update player direction input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
		std::cout << "[Game State] >> Pressed A" << std::endl;
		this->player->moveEntity(-1.0f,0.0f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
		std::cout << "[Game State] >> Pressed D" << std::endl;
		this->player->moveEntity(1.0f, 0.0f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))) {
		std::cout << "[Game State] >> Pressed W" << std::endl;
		this->player->moveEntity(0.0f, -1.0f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
		std::cout << "[Game State] >> Pressed S" << std::endl;
		this->player->moveEntity(0.0f, 1.0f, dt);
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
