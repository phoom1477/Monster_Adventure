#include "SettingState.h"

//Initialization
void SettingState::initVariable()
{
	//initial framerate vector
	this->framerateLimit.push_back(60);
	this->framerateLimit.push_back(120);

	//initial vsync vector
	this->verticalsyncEnabled.push_back(false);
	this->verticalsyncEnabled.push_back(true);
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

void SettingState::initFonts()
{
	//load font for this state
	if (!this->font.loadFromFile("src/Resource/Font/Planes_ValMore.ttf")) {
		throw("[Setting State] >> ..ERROR.. Could't load font");
	}
}

void SettingState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (!this->backgroundTexture.loadFromFile("src/Resource/Background/SettingState/background.png")) {
		throw("[Setting State] >> ..ERROR.. Could't load backgroundTexture");
	}
	this->background.setTexture(&this->backgroundTexture);
}

void SettingState::initDescriptText()
{
	this->descriptText.setFont(this->font);
	this->descriptText.setCharacterSize(50);
	this->descriptText.setOutlineThickness(5.0f);
	this->descriptText.setOutlineColor(sf::Color::Red);

	this->descriptText.setString("Options");

	this->descriptText.setPosition(sf::Vector2f(
		this->window->getSize().x / 2.0f - this->descriptText.getGlobalBounds().width / 2.0f,
		this->window->getSize().y / 16.0f * 1.5f
	));
}

void SettingState::InitOptionText()
{
	this->optionText.setFont(this->font);
	this->optionText.setCharacterSize(40);
	this->optionText.setLineSpacing(1.1f);
	
	this->optionText.setString("Frameratelimit\n\nVsync");

	this->optionText.setPosition(sf::Vector2f(
		this->window->getSize().x / 16.0f * 4.0f,
		this->window->getSize().y / 16.0f * 3.5f)
	);
}

void SettingState::initGui()
{
	this->initButton();
	this->initDropdownBox();
}

void SettingState::initButton()
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
		sf::Color(255, 255, 255, 200), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255)
	);

	this->buttons["Back"] = new gui::Button(
		(this->window->getSize().x / 2) - (button_width / 2) + (button_width / 2),
		(this->window->getSize().y / 8) * 6.50f,
		button_width, button_height,
		this->font, "BACK", 40,
		sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 200), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255)
	);
}

void SettingState::initDropdownBox()
{
	//Load config window from window.ini
	std::ifstream ifs("src/Config/window.ini");

	//set default for load config failed
	int framerate_limit = 60;
	bool verticalsync_enabled = false;

	//Reading file
	while (ifs.is_open()) {
		std::string buff;
		ifs >> buff;
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

	//set dropdownboxs
	float dropdawnbox_width = 200.0f;
	float dropdawnbox_height = 50.0f;
	
	//create frameratelimit dropdownbox
	std::vector<std::string> framerate_limit_list;
	framerate_limit_list.push_back("60");
	framerate_limit_list.push_back("120");
	
	int framerate_index = 0;
	if (framerate_limit == 60) {
		framerate_index = 0;
	}
	if (framerate_limit == 120) {
		framerate_index = 1;
	}
	this->dropDownBoxs["Frameratelimit"] = new gui::DropDownBox(
		this->window->getSize().x / 16.0f * 9.0f,
		this->window->getSize().y / 16.0f * 3.5f,
		dropdawnbox_width, dropdawnbox_height,
		font, framerate_limit_list.data(), (int)framerate_limit_list.size(),framerate_index
	);

	//create vsync dropdownbox
	std::vector<std::string> mode_string;
	mode_string.push_back("OFF");
	mode_string.push_back("ON");
	
	this->dropDownBoxs["Vsync"] = new gui::DropDownBox(
		this->window->getSize().x / 16.0f * 9.0f,
		this->window->getSize().y / 16.0f * 5.5f,
		dropdawnbox_width, dropdawnbox_height,
		font, mode_string.data(), (int)mode_string.size(), verticalsync_enabled
	);	
}

//Constructor , Destructor
SettingState::SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	std::cout << "[Setting State] >> On" << std::endl;
	this->initVariable();
	this->initKeybinds();
	this->initFonts();

	this->initBackground();
	this->initDescriptText();
	this->InitOptionText();

	this->initGui();
}

SettingState::~SettingState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		delete it->second;
	}
	for (auto it = this->dropDownBoxs.begin(); it != this->dropDownBoxs.end(); it++) {
		delete it->second;
	}
}

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
		this->window->setFramerateLimit(this->framerateLimit[this->dropDownBoxs["Frameratelimit"]->getActiveElementId()]);
		this->window->setVerticalSyncEnabled(this->verticalsyncEnabled[this->dropDownBoxs["Vsync"]->getActiveElementId()]);

		//std::ofstream ofs("src/Config/window.ini")
	}
	if (this->buttons["Back"]->isPressed()) {		//quit state
		this->endState();
	}

	//Update all the dropdownboxs in this state
	for (auto it = this->dropDownBoxs.begin(); it != this->dropDownBoxs.end(); ++it) {
		it->second->updateDropDownBox(dt, this->mousePosView);
	}
}

void  SettingState::renderState(sf::RenderTarget* target)
{
	if (target == NULL) {
		target = this->window;
	}

	target->draw(this->background);
	target->draw(this->descriptText);
	target->draw(this->optionText);

	this->renderGui(*target);
}

void  SettingState::renderGui(sf::RenderTarget& target)
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		it->second->renderButton(target);
	}
	for (auto it = this->dropDownBoxs.begin(); it != this->dropDownBoxs.end(); it++) {
		it->second->renderDropDownBox(target);
	}
}
