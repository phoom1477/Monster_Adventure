/////////////////////////////////////////////////
//	 This class is Abstract class of buttons.  //
/////////////////////////////////////////////////

#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

enum button_states { BUTTON_IDLE = 0, BUTTON_HOVER, BUTTON_ACTIVE };

class Button
{
private:
	sf::RectangleShape shape;
	sf::Font& font;
	sf::Text text;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color shapeIdleColor;
	sf::Color shapeHoverColor;
	sf::Color shapeActiveColor;

	short unsigned buttonState;

protected:

public:
	//Constructor , Destructor
	Button(float x, float y, float width, float height
		, sf::Font& font, std::string text,unsigned charector_size
		, sf::Color text_idle_Color, sf::Color text_hover_color, sf::Color text_active_color
		,sf::Color shape_idle_color ,sf::Color shape_hover_color ,sf::Color shape_active_color);

	virtual ~Button();

	//Accessor
	const bool isPressed();

	//Function
	void updateButton(const sf::Vector2f mousePosition);
	void renderButton(sf::RenderTarget* target);
};

