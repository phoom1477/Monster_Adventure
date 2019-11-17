#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>

#include "Gui.h"

class PopUpMenu
{
private:
	sf::Font& font;
	sf::Text menuText;
	sf::Text descriptText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

public:
	//Constructor , Destructor
	PopUpMenu(sf::View& view, sf::Font& font);
	virtual ~PopUpMenu();

	//Accessor
	std::map<std::string, gui::Button*>& getButtons();
	const bool isButtonPreesed(const std::string key);

	//Function
	void addButton(const std::string key, float grid_y, const std::string text);
	
	//Modifier
	void setMenuTextString(std::string menu_text);
	void setDescriptTextString(std::string descript_text);

	void setWidth(float width);

	void updatePauseMenu(const sf::Vector2f& mousePos,sf::View& view);
	void renderPauseMenu(sf::RenderTarget& target);
};

