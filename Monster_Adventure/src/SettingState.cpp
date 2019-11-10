#include "SettingState.h"

//Initialization
void SettingState::initVariable()
{
	/*this->videoModes = sf::VideoMode::getFullscreenModes();*/
}

void SettingState::initFonts()
{
	//load font for this state
	if (!this->font.loadFromFile("src/Resource/Font/Planes_ValMore.ttf")) {
		throw("[Setting State] >> ..ERROR.. Could't load font");
	}
}

void SettingState::initKeybinds()
{
	std::ifstream ifs("src/Config/settingstate_keybinds.ini");
	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void SettingState::initGui()
{
	//create buttons
	float button_width = 150.0f;
	float button_height = 0.0f;
	
	this->buttons["Apply"] = new gui::Button(
		(this->window->getSize().x / 2) - (button_width / 2) - (button_width / 2),
		(this->window->getSize().y / 8) * 6.50f,
		button_width, button_height,
		this->font, "APPLY", 40,
		sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 200), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255));
	
	this->buttons["Back"] = new gui::Button(
		(this->window->getSize().x / 2) - (button_width / 2) + (button_width / 2),
		(this->window->getSize().y / 8) * 6.50f,
		button_width, button_height,
		this->font, "BACK", 40,
		sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 200), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255));
	
	//create dropdownboxs
	float dropdawnbox_width = 200.0f;
	float dropdawnbox_height = 50.0f;
	/*std::vector<std::string> videomode_str;
	for (auto &i : this->videoModes) {
		videomode_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}
	this->dropDownBoxs["Resolution"] = new gui::DropDownBox(
		this->window->getSize().x / 8.0f * 3.0f, 
		this->window->getSize().y / 8.0f * 1.0f, 
		dropdawnbox_width, dropdawnbox_height,
		font, videomode_str.data(), videomode_str.size());*/
}

void SettingState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("src/Resource/Background/SettingState/background.png")) {
		throw("[Setting State] >> ..ERROR.. Could't load backgroundTexture");
	}
	this->background.setTexture(&this->backgroundTexture);
}

void SettingState::InitText()
{
	/*this->optionText.setFont(this->font);
	this->optionText.setCharacterSize(30);
	this->optionText.setFillColor(sf::Color(255, 255, 255, 200));
	this->optionText.setPosition(sf::Vector2f(
		this->window->getSize().x / 8.0f * 1.0f,
		this->window->getSize().y / 8.0f * 1.0f));
	
	this->optionText.setString("Resolution\n\nFullscreen\n\nVsync\n\nAntialiasing");*/
}

//Constructor , Destructor
SettingState::SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	std::cout << "[Setting State] >> On" << std::endl;
	this->initVariable();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initBackground();
	this->InitText();
}

SettingState::~SettingState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		delete it->second;
	}
	/*for (auto it = this->dropDownBoxs.begin(); it != this->dropDownBoxs.end(); it++) {
		delete it->second;
	}*/
}

//Accessor

//Function
void SettingState::updateState(const float &dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	this->updateGui(dt);
}

void  SettingState::updateInput(const float &dt)
{
}

void  SettingState::updateGui(const float &dt)
{
	//Update all the buttons in this state
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		it->second->updateButton(this->mousePosView);
	}
	//Button Functionality
	if (this->buttons["Apply"]->isPressed()) {		//Apply selected setting
		//test
		/*this->window->create(this->videoModes[this->dropDownBoxs["Resolution"]->getActiveElementId()], "Test");*/
	}
	if (this->buttons["Back"]->isPressed()) {		//quit state
		this->endState();
	}

	//Update all the dropdownboxs in this state
	/*for (auto it = this->dropDownBoxs.begin(); it != this->dropDownBoxs.end(); ++it) {
		it->second->updateDropDownBox(dt, this->mousePosView);
	}*/
}

void  SettingState::renderState(sf::RenderTarget* target)
{
	if (target == NULL) {
		target = this->window;
	}
	target->draw(this->background);

	this->renderGui(*target);

	/*target->draw(this->optionText);*/

	//Show for debug << remove later/////////////////////////////////////
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView + sf::Vector2f(25.f, 25.f));
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
	/////////////////////////////////////////////////////////////////////
}

void  SettingState::renderGui(sf::RenderTarget& target)
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		it->second->renderButton(target);
	}
	/*for (auto it = this->dropDownBoxs.begin(); it != this->dropDownBoxs.end(); it++) {
		it->second->renderDropDownBox(target);
	}*/
}
