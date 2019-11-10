#include "Game.h"

//Initialization
void Game::initVariable()
{
	this->window = NULL;
	this->fullscreen = false;
	this->dt = 0.0f;
}

void Game::initWindow()
{
	this->videoModes = sf::VideoMode::getFullscreenModes();

	//Load config window from window.ini
	std::ifstream ifs("src/Config/window.ini");

	//Set default if can't read file
	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	int framerate_limit = 120;
	bool verticalsync_enabled = false;
	unsigned antialising_level = 0;

	//Reading file
	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> verticalsync_enabled;
		ifs >> antialising_level;
	}
	ifs.close();

	//Setup mode
	this->fullscreen = fullscreen;

	//Setup openGL 
	this->windowSetting.antialiasingLevel = antialising_level;

	//Setup window
	if (this->fullscreen) {
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, this->windowSetting);
	}
	else {
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, this->windowSetting);
	}
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(verticalsync_enabled);
}

void Game::initKeys()
{
	std::ifstream ifs("src/Config/supportedKeys.ini");
	if (ifs.is_open()) {
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value) {
			this->supportedKeys[key] = key_value;
		}
	}
	ifs.close();
}

void Game::initStates()
{
	//Push Main Menu state to states stack
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

//Constructor , Destructor
Game::Game()
{
	std::cout << "============== Show Game log in console ==============" << std::endl;
	this->initVariable();
	this->initWindow();
	this->initKeys();
	this->initStates();
}

Game::~Game()
{
	delete this->window;
	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}

//Function
void Game::run()
{
	while (this->window->isOpen()) {
		//update
		this->updateGame();
		//rander
		this->renderGame();
	}
}

void Game::updateGame()
{
	this->updateDeltatime();  //assign new dt value
	this->updateEvent();      //wait for click close buttom

	//Update state
	if (!this->states.empty()) {

		this->states.top()->updateState(this->dt);

		if (this->states.top()->getQuit()) {

			delete this->states.top();
			this->states.pop();
		}
	}
	else {
		this->endGame();
		this->window->close();  //stack is empty so end this application
	}
}

void Game::updateDeltatime()
{
	this->dt = this->clock.restart().asSeconds();
}

void Game::updateEvent()
{
	//Check event closed when click closed buttom 
	if (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->endGame();
			this->window->close();
		}
	}
}

void Game::renderGame()
{
	//Clear old frame
	this->window->clear();
	//Render new object
	if (!this->states.empty()) {
		this->states.top()->renderState(this->window);
	}
	//Draw new object
	this->window->display();
}

void Game::endGame()
{
	std::cout << "!! Exit Game !!" << std::endl;
}
