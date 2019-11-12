#include "GetInfoState.h"

//initialization
void GetInfoState::initVariable()
{
	this->inputName = "Player name";
	this->previewIndex = 0;
	this->cursor = false;
}

void GetInfoState::initFonts()
{
	//load font for this state
	if (!this->font.loadFromFile("src/Resource/Font/Planes_ValMore.ttf")) {
		throw("[Get Info State] >> ..ERROR.. Could't load font");
	}
	if (!this->temporaryFont.loadFromFile("src/Resource/Font/joystix_monospace.ttf")) {
		throw("[Get Info State] >> ..ERROR.. Could't load font");
	}
}

void GetInfoState::initKeybinds()
{
	std::ifstream ifs("src/Config/getinfostate_keybinds.ini");
	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void GetInfoState::initPreviewName()
{
	this->previewName.setFont(this->font);
	this->previewName.setCharacterSize(50);
	this->previewName.setOutlineThickness(5.0f);
}

void GetInfoState::initPreviewPlayer()
{
	if (!this->textures["PLAYER_DUDE"].loadFromFile("src/Resource/Charector/Player/Dude/Dude.png")) {
		throw("[Game State] >> ERROR can't load player texture");
	}
	if (!this->textures["PLAYER_PINK"].loadFromFile("src/Resource/Charector/Player/Pink/Pink.png")) {
		throw("[Game State] >> ERROR can't load player texture");
	}
	if (!this->textures["PLAYER_OWLET"].loadFromFile("src/Resource/Charector/Player/Owlet/Owlet.png")) {
		throw("[Game State] >> ERROR can't load player texture");
	}

	sf::RectangleShape previewPlayerTexture;

	previewPlayerTexture.setTexture(&this->textures["PLAYER_DUDE"]);
	this->previewPlayer.push_back(previewPlayerTexture);

	previewPlayerTexture.setTexture(&this->textures["PLAYER_PINK"]);
	this->previewPlayer.push_back(previewPlayerTexture);

	previewPlayerTexture.setTexture(&this->textures["PLAYER_OWLET"]);
	this->previewPlayer.push_back(previewPlayerTexture);
}

void GetInfoState::initButton()
{
	//create buttons
	float button_width = 150.0f;
	float button_height = 0.0f;

	this->buttons["Previous"] = new gui::Button(
		(this->window->getSize().x / 2) - (button_width / 2) - (button_width / 2) * 1,
		(this->window->getSize().y / 8) * 2.0f,
		button_width, button_height,
		this->temporaryFont, "<", 50,
		sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 200), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255)
	);

	this->buttons["Next"] = new gui::Button(
		(this->window->getSize().x / 2) - (button_width / 2) + (button_width / 2) * 1,
		(this->window->getSize().y / 8) * 2.0f,
		button_width, button_height,
		this->temporaryFont, ">", 50,
		sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 200), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255)
	);

	this->buttons["Back"] = new gui::Button(
		(this->window->getSize().x / 2) - (button_width / 2) - (button_width / 2) * 3,
		(this->window->getSize().y / 8) * 6.50f,
		button_width, button_height,
		this->font, "BACK", 40,
		sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 200), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255)
	);

	this->buttons["Start"] = new gui::Button(
		(this->window->getSize().x / 2) - (button_width / 2) + (button_width / 2) * 3,
		(this->window->getSize().y / 8) * 6.50f,
		button_width, button_height,
		this->font, "START", 40,
		sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 200), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255)
	);
}

void GetInfoState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("src/Resource/Background/MainMenuState/background.png")) {
		throw("[Main Menu State] >> ..ERROR.. Could't load backgroundTexture");
	}
	this->background.setTexture(&this->backgroundTexture);
}

//Constructor , Destructor
GetInfoState::GetInfoState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	std::cout << "[Get Info State] >> on" << std::endl;
	this->initVariable();
	this->initFonts();
	this->initKeybinds();
	this->initPreviewName();
	this->initPreviewPlayer();
	this->initButton();
	this->initBackground();
}

GetInfoState::~GetInfoState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		delete it->second;
	}
}

//Function
void GetInfoState::updateState(const float & dt)
{
	this->updateKeyTime(dt);

	this->updateInput(dt);
	this->updateMousePosition();

	this->updateButton();
	this->updatePreviewPlayer();

	this->updateName();
	this->updatePreviewName(this->inputName);
}

void GetInfoState::updateInput(const float & dt)
{
}

void GetInfoState::updateButton()
{
	//Update all the buttons in this state
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		it->second->updateButton(this->mousePosView);
	}
	//Button Functionality
	if (this->buttons["Previous"]->isPressed() && this->getKeyTime()) {	
		if (this->previewIndex > 0) {
			this->previewIndex--;
		}
	}
	if (this->buttons["Next"]->isPressed() && this->getKeyTime()) {	
		if (this->previewIndex < this->previewPlayer.size() - 1) {
			this->previewIndex++;
		}
	}
	if (this->buttons["Start"]->isPressed() && this->getKeyTime()) {	
		this->endState();
		this->states->push(new GameState(this->window, this->supportedKeys, this->states, this->previewIndex, this->inputName));
	}
	if (this->buttons["Back"]->isPressed() && this->getKeyTime()) {	
		this->endState();
	}
}

void GetInfoState::updatePreviewName(const std::string name)
{
	std::stringstream ss;
	if (this->timer.getElapsedTime() >= sf::milliseconds(300)) {
		this->timer.restart();
		cursor = !cursor;
	}

	if (cursor) {
		ss << name << "|";
	}
	else {
		ss << name << "";
	}

	this->previewName.setString(ss.str());
	this->previewName.setPosition(
		static_cast<float>(this->window->getSize().x / 2.0f - this->previewName.getGlobalBounds().width / 2.0f),
		static_cast<float>(this->window->getSize().y / 2.0f));
}

void GetInfoState::updateName()
{
	this->window->pollEvent(this->event);

	if (this->event.type == sf::Event::TextEntered) {
		if (event.text.unicode < 128 && event.text.unicode != 8) {	//typing
			this->inputName += char(event.text.unicode);
		}
		if (event.text.unicode == 8) {								//delete
			if (!this->inputName.empty()) {
				this->inputName.pop_back();
			}
		}
		while (this->event.type == sf::Event::TextEntered) {		//debouncing
			this->window->pollEvent(this->event);
		}
	}
}

void GetInfoState::updatePreviewPlayer()
{
	this->previewPlayer[this->previewIndex].setSize(sf::Vector2f(100.0f,100.0f));
	this->previewPlayer[this->previewIndex].setPosition(
		static_cast<float>(this->window->getSize().x / 2.0f - this->previewPlayer[previewIndex].getSize().x / 2.0f + 13.0f),
		static_cast<float>(this->window->getSize().y / 8)
	);
}

void GetInfoState::renderState(sf::RenderTarget * target)
{
	if (target == NULL) {
		target = this->window;
	}

	target->draw(this->background);
	target->draw(this->previewPlayer[previewIndex]);
	target->draw(this->previewName);

	this->renderButton(*target);
}

void GetInfoState::renderButton(sf::RenderTarget & target)
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		it->second->renderButton(target);
	}
}


