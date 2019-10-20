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

void GameState::initTexture()
{
	if (!this->textures["PLAYER_IDLE_SHEET"].loadFromFile("src/Resource/Charector/Player/Dude/Dude_Idle_4.png")) {
		throw("[Game State] >> ERROR can't load player texture");
	}
}

void GameState::initPlayer()
{
	this->player = new Player(0, 0,this->textures["PLAYER_IDLE_SHEET"]);
}

//Constructor , Destructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) :State(window, supportedKeys, states)
{
	std::cout << "[Game State] >> On" << std::endl;
	this->initKeybinds();
	this->initTexture();
	this->initPlayer();
}

GameState::~GameState()
{
	delete this->player;
}

//Function
void GameState::updateState(const float &dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->player->updateEntity(dt);
}

void GameState::updateInput(const float &dt)
{
	//Update player input
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
		this->quit = true;
	}
}

void GameState::renderState(sf::RenderTarget* target)
{
	if (target == NULL) {
		target = this->window;
	}
	this->player->renderEntity(target);
}

void GameState::endState()
{
	std::cout << "[Game State] >> Exit" << std::endl;
}

