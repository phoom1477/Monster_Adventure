#include "MainMenuState.h"

//Initialization
void MainMenuState::initFonts()
{
	//load font for this state
	if (!this->font.loadFromFile("src/Resource/Font/Planes_ValMore.ttf")) {
		throw("[Main Menu State] >> ..ERROR.. Could't load font");
	}
}

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

void MainMenuState::initButton()
{
	this->buttons["New Game"] = new Button(
		565, 300, 150 , 0,
		this->font, "NEW GAME", 40,
		sf::Color(255, 255, 255, 220), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255),
		sf::Color(255, 255, 255, 200), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255));

	this->buttons["Editor"] = new Button(
		565, 400, 150, 0,
		this->font, "EDITOR", 40,
		sf::Color(255, 255, 255, 220), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255),
		sf::Color(255, 255, 255, 200), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255));
	
	this->buttons["Options"] = new Button(
		565, 500, 150, 0,
		this->font, "OPTIONS", 40,
		sf::Color(255, 255, 255, 220), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255),
		sf::Color(255, 255, 255, 200), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255));
	
	this->buttons["Quit"] = new Button(
		565, 600, 150, 0,
		this->font, "QUIT", 40,
		sf::Color(255, 255, 255, 220), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255),
		sf::Color(255, 255, 255, 200), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255));
}

void MainMenuState::initBackground() 
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!backgroundTexture.loadFromFile("src/Resource/Background/MainMenuState/testbackground.png")) {
		throw("[Main Menu State] >> ..ERROR.. Could't load backgroundTexture");
	}
	this->background.setTexture(&this->backgroundTexture);
}

//Constructor , Destructor
MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) :State(window, supportedKeys, states)
{
	std::cout << "[Main Menu State] >> On" << std::endl;
	this->initFonts();
	this->initKeybinds();
	this->initButton();
	this->initBackground();
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
	this->updateMousePosition();
	this->updateInput(dt);
	
	this->updateButton();
}

void MainMenuState::updateInput(const float &dt)
{
}

void MainMenuState::updateButton()
{
	//Update all the buttons in this state
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		it->second->updateButton(this->mousePosView);
	}

	//Go Game State
	if (this->buttons["New Game"]->isPressed()) {
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}
	//Go Editor State
	if (this->buttons["Editor"]->isPressed()) {

	}
	//Go Setting State
	if (this->buttons["Options"]->isPressed()) {
		
	}
	//Exit this state
	if (this->buttons["Quit"]->isPressed()) {
		this->quit = true;
	}
}

void MainMenuState::renderState(sf::RenderTarget* target)
{
	if (target == NULL) {
		target = this->window;
	}
	target->draw(this->background);

	this->renderButton(target);

	//Show for debug << remove later/////////////////////////////////////
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView + sf::Vector2f(25.f,25.f));
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
	/////////////////////////////////////////////////////////////////////
}

void MainMenuState::renderButton(sf::RenderTarget* target)
{
	for (auto it = this->buttons.begin(); it!=this->buttons.end(); it++) {
		it->second->renderButton(target);
	}
}

void MainMenuState::endState()
{
	std::cout << "[Main Menu State] >> Exit" << std::endl;
}


