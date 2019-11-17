#include "PopUpMenu.h"

//Constructor , Destructor
PopUpMenu::PopUpMenu(sf::View& view, sf::Font& font)
	:font(font)
{
	//Init background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(view.getSize().x), 
			static_cast<float>(view.getSize().y)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));
	
	//Init contrainer
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(view.getSize().x / 3.0f),
			static_cast<float>(view.getSize().y - (view.getSize().y / 8.0f) * 2)
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		sf::Vector2f(
			static_cast<float>(view.getSize().x / 2.0f - this->container.getSize().x / 2.0f) ,
			static_cast<float>(view.getSize().y / 8.0f)
		)
	);

	//Init menutext
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255,255,255,255));
	this->menuText.setCharacterSize(70);

	this->menuText.setString("");
	
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.0f - this->menuText.getGlobalBounds().width / 2.0f,
		this->container.getPosition().y + this->container.getSize().y / 16.0f - this->menuText.getGlobalBounds().height / 2.0f);

	//Init descriptText
	this->descriptText.setFont(font);
	this->descriptText.setOutlineThickness(0.8f);
	this->descriptText.setOutlineColor(sf::Color::Magenta);
	this->descriptText.setFillColor(sf::Color(255, 255, 255, 255));
	this->descriptText.setCharacterSize(45);

	this->descriptText.setString("");

	this->descriptText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.0f - this->descriptText.getGlobalBounds().width / 2.0f,
		this->container.getPosition().y + this->container.getSize().y / 16.0f * 5.0f  - this->descriptText.getGlobalBounds().height / 2.0f);
}

PopUpMenu::~PopUpMenu()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		delete it->second;
	}
}

//Accessor
std::map<std::string, gui::Button*>& PopUpMenu::getButtons()
{
	return this->buttons;
}

const bool PopUpMenu::isButtonPreesed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

//Function
void PopUpMenu::addButton(const std::string key, float grid_y, const std::string text)
{
	float button_width = 150.0f;
	float button_height = 0.0f;

	float x = this->container.getPosition().x + this->container.getSize().x / 2.0f - button_width / 2.0f;
	float y = this->container.getPosition().y + (this->container.getSize().y / 16.0f) * grid_y;
	this->buttons[key] = new gui::Button(
		x,y,button_width, button_height,
		this->font, text, 40,
		sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255), sf::Color(0, 0, 0, 255));
}

void PopUpMenu::setMenuTextString(std::string menu_text)
{
	this->menuText.setString(menu_text);
}

void PopUpMenu::setDescriptTextString(std::string descript_text)
{
	this->descriptText.setString(descript_text);
}

void PopUpMenu::setWidth(float width)
{
	this->container.setSize(sf::Vector2f(width, this->container.getSize().y));
}

void PopUpMenu::updatePauseMenu(const sf::Vector2f& mousePos, sf::View& view)
{
	//Update all the buttons
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		it->second->updateButton(mousePos);
	}

	//set all new position
	//background
	this->background.setPosition(
		view.getCenter().x - view.getSize().x / 2.0f,
		view.getCenter().y - view.getSize().y / 2.0f
	);
	//contrainer
	this->container.setPosition(
		view.getCenter().x - this->container.getGlobalBounds().width / 2.0f,
		view.getCenter().y - this->container.getGlobalBounds().height / 2.0f
	);
	//manuText
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.0f - this->menuText.getGlobalBounds().width / 2.0f,
		this->container.getPosition().y + this->container.getSize().y / 16.0f - this->menuText.getGlobalBounds().height / 2.0f
	);
	//descriptText
	this->descriptText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.0f - this->descriptText.getGlobalBounds().width / 2.0f,
		this->container.getPosition().y + this->container.getSize().y / 16.0f * 5.0f - this->descriptText.getGlobalBounds().height / 2.0f
	);
	//buttons
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		it->second->setPosition(
			this->container.getPosition().x + this->container.getSize().x / 2.0f - it->second->getSize().x / 2.0f,
			it->second->getPosition().y
		);
	}
}

void PopUpMenu::renderPauseMenu(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		it->second->renderButton(target);
	}

	target.draw(this->menuText);
	target.draw(this->descriptText);
}

