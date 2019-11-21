#include "MainMenuState.h"

//Initialization
void MainMenuState::initKeybinds()
{
	std::ifstream ifs("src/Config/mainmenustate_keybinds.ini");
	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void MainMenuState::initFonts()
{
	//load font for this state
	if (!this->font.loadFromFile("src/Resource/Font/Planes_ValMore.ttf")) {
		throw("[Main Menu State] >> ..ERROR.. Could't load font");
	}
}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("src/Resource/Background/MainMenuState/background.png")) {
		throw("[Main Menu State] >> ..ERROR.. Could't load backgroundTexture");
	}
	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initLogo()
{
	if (!this->logoTexture.loadFromFile("src/Resource/Gamelogo/Gamelogo.png")) {
		throw("[Main Menu State] >> ..ERROR.. Could't load logoTexture");
	}

	this->logo.setSize(sf::Vector2f(static_cast<float>(this->logoTexture.getSize().x / 2), static_cast<float>(this->logoTexture.getSize().y / 2)));
	this->logo.setPosition(sf::Vector2f(static_cast<float>((this->window->getSize().x / 2) - (this->logo.getSize().x / 2)), static_cast<float>(this->window->getSize().y / 8)));
	this->logo.setTexture(&this->logoTexture);
}

void MainMenuState::initMusic()
{
	if (!musicBuffer.loadFromFile("src/Resource/Music/MainMenuState/twinkle_twinkle_little_star.ogg")) {
		throw("[Main Menu State] >> ..ERROR.. Could't load musicBuffer");
	}

	this->music.setBuffer(this->musicBuffer);
	this->music.setLoop(true);
	this->music.setVolume(50);
	this->music.play();
}

void MainMenuState::initButton()
{
	//variable to set button size
	float button_width = 150.0f;
	float button_height = 0.0f;

	this->buttons["New Game"] = new gui::Button(
		(this->window->getSize().x / 2) - (button_width / 2), 
		(this->window->getSize().y / 8) * 4.0f, 
		button_width, button_height,
		this->font, "NEW GAME", 40,
		sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255), sf::Color(0, 0, 0, 255)
	);

	this->buttons["Score"] = new gui::Button(
		(this->window->getSize().x / 2) - (button_width / 2),
		(this->window->getSize().y / 8) * 5.0f, 
		button_width, button_height,
		this->font, "SCORE", 40,
		sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255), sf::Color(0, 0, 0, 255)
	);
	
	this->buttons["Quit"] = new gui::Button(
		(this->window->getSize().x / 2) - (button_width / 2),
		(this->window->getSize().y / 8) * 6.0f, 
		button_width, button_height,
		this->font, "QUIT", 40,
		sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255), sf::Color(0, 0, 0, 255)
	);
}

//Constructor , Destructor
MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) 
	:State(window, supportedKeys, states)
{
	std::cout << "[Main Menu State] >> On" << std::endl;
	this->initKeybinds();
	this->initFonts();
	
	this->initBackground();
	this->initLogo();
	this->initMusic();
	
	this->initButton();
}

MainMenuState::~MainMenuState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		delete it->second;
	}
}

//Function
void MainMenuState::updateState(const float &dt)
{
	this->updateKeyTime(dt);

	this->updateInput(dt);
	this->updateMousePosition();

	this->updateButton();
	this->updateMusic();
}

void MainMenuState::updateInput(const float & dt)
{
}

void MainMenuState::updateButton()
{
	//Update all the buttons in this state
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		it->second->updateButton(this->mousePosView);
	}

	//Go Game State
	if (this->buttons["New Game"]->isPressed() && this->getKeyTime()) {
		this->states->push(new GetInfoState(this->window, this->supportedKeys, this->states));
		this->music.stop();
	}
	//Go Score 
	if (this->buttons["Score"]->isPressed() && this->getKeyTime()) {
		this->states->push(new ScoreState(this->window, this->supportedKeys, this->states));
	}
	
	//Exit this state
	if (this->buttons["Quit"]->isPressed() && this->getKeyTime()) {
		this->endState();
	}
}

void MainMenuState::updateMusic()
{
	if (this->states->top() == this && this->music.getStatus()!=sf::Sound::Playing) {
		this->music.play();
	}
}

void MainMenuState::renderState(sf::RenderTarget* target)
{
	if (target == NULL) {
		target = this->window;
	}

	target->draw(this->background);
	target->draw(this->logo);	

	this->renderButton(*target);
}

void MainMenuState::renderButton(sf::RenderTarget& target)
{
	for (auto it = this->buttons.begin(); it!=this->buttons.end(); it++) {
		it->second->renderButton(target);
	}
}



