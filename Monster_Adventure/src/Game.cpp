#include "Game.h"

//Initialization
void Game::initVariable()
{
	this->window = NULL;
	this->dt = 0.0f;
}

void Game::initWindow()
{
	//Load config window from window.ini
	std::ifstream ifs("src/Config/window.ini");

	//Set default if can't read file
	std::string title = "Monster Adventure";
	sf::VideoMode window_bounds = sf::VideoMode(1270, 720);
	int framerate_limit = 120;
	bool verticalsync_enabled = false;

	//Reading file
	while (ifs.is_open()) {
		std::string buff;
		ifs >> buff;
		if (buff == "title") {
			getline(ifs, title);
		}
		if (buff == "width") {
			ifs >> window_bounds.width;
		}
		if (buff == "height") {
			ifs >> window_bounds.height;
		}
		if (buff == "frameratelimit") {
			ifs >> framerate_limit;
		}
		if (buff == "vsync") {
			ifs >> verticalsync_enabled;
		}
		if (buff == "") {
			ifs.close();
		}
	}

	//Setup window
	this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(verticalsync_enabled);

	//Setup window icon
	sf::Image icon;
	if (!icon.loadFromFile("src/Resource/Icon/Dude.png")) {
		throw "[Can't load game icon]";
	}
	this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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

void Game::initIntro()
{
	if (!this->introTexture.loadFromFile("src/Resource/Background/intro.png")) {
		throw "ERROR can't load Intro";
	}
	this->intro.setTexture(&this->introTexture);
	this->intro.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	//render intro
	this->window->draw(this->intro);
	this->window->display();
}

void Game::initMusicList()
{
	//load all music
	if (!this->musicBuffer["MUSIC_1"].loadFromFile("src/Resource/Music/music_1.ogg")) {
		throw("ERROR can't load music buffer");
	}
	this->music["MUSIC_1"].setBuffer(musicBuffer["MUSIC_1"]);
	this->music["MUSIC_1"].setLoop(true);
	this->music["MUSIC_1"].setVolume(50);

	if (!this->musicBuffer["MUSIC_2"].loadFromFile("src/Resource/Music/music_2.ogg")) {
		throw("ERROR can't load music buffer");
	}
	this->music["MUSIC_2"].setBuffer(musicBuffer["MUSIC_2"]);
	this->music["MUSIC_2"].setLoop(true);
	this->music["MUSIC_2"].setVolume(50);

	if (!this->musicBuffer["MUSIC_3"].loadFromFile("src/Resource/Music/music_3.ogg")) {
		throw("ERROR can't load music buffer");
	}
	this->music["MUSIC_3"].setBuffer(musicBuffer["MUSIC_3"]);
	this->music["MUSIC_3"].setLoop(true);
	this->music["MUSIC_3"].setVolume(50);

	if (!this->musicBuffer["MUSIC_4"].loadFromFile("src/Resource/Music/music_4.ogg")) {
		throw("ERROR can't load music buffer");
	}
	this->music["MUSIC_4"].setBuffer(musicBuffer["MUSIC_4"]);
	this->music["MUSIC_4"].setLoop(true);
	this->music["MUSIC_4"].setVolume(50);

	if (!this->musicBuffer["MUSIC_5"].loadFromFile("src/Resource/Music/music_5.ogg")) {
		throw("ERROR can't load music buffer");
	}
	this->music["MUSIC_5"].setBuffer(musicBuffer["MUSIC_5"]);
	this->music["MUSIC_5"].setLoop(true);
	this->music["MUSIC_5"].setVolume(50);

	if (!this->musicBuffer["MUSIC_6"].loadFromFile("src/Resource/Music/music_6.ogg")) {
		throw("ERROR can't load music buffer");
	}
	this->music["MUSIC_6"].setBuffer(musicBuffer["MUSIC_6"]);
	this->music["MUSIC_6"].setLoop(true);
	this->music["MUSIC_6"].setVolume(50);
}

void Game::initStates()
{
	//show intro before go to first state
	sf::Clock timer;
	while (timer.getElapsedTime().asMilliseconds() <= 3000) {
		// waiting
	}

	//Push Main Menu state to states stack
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states, &this->music));
}

//Constructor , Destructor
Game::Game()
{
	std::cout << "============== Show Game log in console ==============" << std::endl;
	this->initVariable();
	this->initWindow();
	this->initKeys();
	this->initIntro();

	this->initMusicList();
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
