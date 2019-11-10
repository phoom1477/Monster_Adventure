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

class PauseMenu
{
private:
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

public:
	//Constructor , Destructor
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	//Accessor
	std::map<std::string, gui::Button*>& getButtons();
	const bool isButtonPreesed(const std::string key);

	//Function
	void addButton(const std::string key, float grid_y, const std::string text);
	
	void updatePauseMenu(const sf::Vector2f& mousePos);
	void renderPauseMenu(sf::RenderTarget& target);
};

