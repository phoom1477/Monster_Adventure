#include "PauseMenu.h"

//Constructor , Destructor
PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	:font(font)
{
	//Init background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x), 
			static_cast<float>(window.getSize().y)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));
	
	//Init contrainer
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x / 3.0f),
			static_cast<float>(window.getSize().y - (window.getSize().y / 8.0f) * 2)
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		sf::Vector2f(
			static_cast<float>(window.getSize().x / 2.0f - this->container.getSize().x / 2.0f) ,
			static_cast<float>(window.getSize().y / 8.0f)
		)
	);

	//Init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255,255,255,255));
	this->menuText.setCharacterSize(70);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.0f - this->menuText.getGlobalBounds().width / 2.0f, 
		this->container.getPosition().y + this->container.getSize().y / 16.0f * 1.0f - this->menuText.getGlobalBounds().height / 2.0f);
}

PauseMenu::~PauseMenu()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		delete it->second;
	}
}

//Accessor
std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

const bool PauseMenu::isButtonPreesed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

//Function
void PauseMenu::addButton(const std::string key, float grid_y, const std::string text)
{
	float button_width = 150.0f;
	float button_height = 0.0f;

	float x = this->container.getPosition().x + this->container.getSize().x / 2.0f - button_width / 2.0f;
	float y = this->container.getPosition().y + this->container.getSize().y / 16.0f * grid_y;

	this->buttons[key] = new gui::Button(
		x,y,button_width, button_height,
		this->font, text, 40,
		sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255), sf::Color(0, 0, 0, 255));
}

void PauseMenu::updatePauseMenu(const sf::Vector2f& mousePos)
{
	//Update all the buttons
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		it->second->updateButton(mousePos);
	}
}

void PauseMenu::renderPauseMenu(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		it->second->renderButton(target);
	}

	target.draw(this->menuText);
}

