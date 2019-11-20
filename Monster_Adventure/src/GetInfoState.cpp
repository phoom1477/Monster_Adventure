#include "GetInfoState.h"

//initialization
void GetInfoState::initVariable()
{
	this->playerName = "PlayerName";
	this->playerIndex = 0;
	this->showCursor = false;
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

void GetInfoState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("src/Resource/Background/GetInfoState/background.png")) {
		throw("[Get Info State] >> ..ERROR.. Could't load backgroundTexture");
	}
	this->background.setTexture(&this->backgroundTexture);
}

void GetInfoState::initDescriptText()
{
	this->descriptText.setFont(this->font);
	this->descriptText.setCharacterSize(50);
	this->descriptText.setOutlineThickness(5.0f);
	this->descriptText.setOutlineColor(sf::Color::Black);
	
	this->descriptText.setString("Choose Charector");

	this->descriptText.setPosition(sf::Vector2f(
		this->window->getSize().x / 2.0f - this->descriptText.getGlobalBounds().width / 2.0f,
		this->window->getSize().y / 16.0f
	));
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
		(this->window->getSize().y / 8) * 2.5f,
		button_width, button_height,
		this->temporaryFont, "<", 50,
		sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 200), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255)
	);

	this->buttons["Next"] = new gui::Button(
		(this->window->getSize().x / 2) - (button_width / 2) + (button_width / 2) * 1,
		(this->window->getSize().y / 8) * 2.5f,
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

//Constructor , Destructor
GetInfoState::GetInfoState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	std::cout << "[Get Info State] >> on" << std::endl;
	this->initVariable();
	
	this->initKeybinds();
	this->initFonts();
	
	this->initBackground();
	this->initDescriptText();
	
	this->initPreviewName();
	this->initPreviewPlayer();

	this->initButton();
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

	this->updateName();
	this->updatePreviewName(this->playerName); 
	this->updatePreviewPlayer();
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
		if (this->playerIndex > 0) {
			this->playerIndex--;
		}
	}
	if (this->buttons["Next"]->isPressed() && this->getKeyTime()) {	
		if (this->playerIndex < this->previewPlayer.size() - 1) {
			this->playerIndex++;
		}
	}
	if (this->buttons["Start"]->isPressed() && this->getKeyTime()) {	
		this->endState();
		this->states->push(new GameState(this->window, this->supportedKeys, this->states, this->playerIndex, this->playerName));
	}
	if (this->buttons["Back"]->isPressed() && this->getKeyTime()) {	
		this->endState();
	}
}

void GetInfoState::updateName()
{
	this->window->pollEvent(this->eventType);

	if (this->eventType.type == sf::Event::TextEntered) {
		if (eventType.text.unicode < 128 && eventType.text.unicode != 8 && eventType.text.unicode != 32) {	//typing
			this->playerName += char(eventType.text.unicode);
		}
		if (eventType.text.unicode == 8) {									//delete
			if (!this->playerName.empty()) {
				this->playerName.pop_back();
			}
		}
		while (this->eventType.type == sf::Event::TextEntered) {			//debouncing
			this->window->pollEvent(this->eventType);
		}
	}
}

void GetInfoState::updatePreviewName(const std::string name)
{
	std::stringstream ss;
	if (this->timer.getElapsedTime() >= sf::milliseconds(300)) {
		this->timer.restart();
		showCursor = !showCursor;
	}

	if (showCursor) {
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

void GetInfoState::updatePreviewPlayer()
{
	this->previewPlayer[this->playerIndex].setSize(sf::Vector2f(100.0f, 100.0f));
	this->previewPlayer[this->playerIndex].setPosition(
		static_cast<float>(this->window->getSize().x / 2.0f - this->previewPlayer[playerIndex].getSize().x / 2.0f + 13.0f),
		static_cast<float>(this->window->getSize().y / 8 * 1.75f)
	);
}

void GetInfoState::renderState(sf::RenderTarget * target)
{
	if (target == NULL) {
		target = this->window;
	}

	target->draw(this->background);
	target->draw(this->descriptText);
	target->draw(this->previewName);
	target->draw(this->previewPlayer[playerIndex]);

	this->renderButton(*target);
}

void GetInfoState::renderButton(sf::RenderTarget & target)
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		it->second->renderButton(target);
	}
}


