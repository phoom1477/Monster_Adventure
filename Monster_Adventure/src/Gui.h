#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

enum button_states { BUTTON_IDLE = 0, BUTTON_HOVER, BUTTON_ACTIVE };

namespace gui {
	class Button
	{
	private:
		//Identify
		short unsigned id;

		//Variable
		short unsigned buttonState;

		//Resource
		sf::RectangleShape shape;
		sf::Font& font;
		sf::Text text;
		float charectorSize;

		sf::SoundBuffer pressedSoundBuffer;
		sf::Sound pressedSound;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color shapeIdleColor;
		sf::Color shapeHoverColor;
		sf::Color shapeActiveColor;
		
		//Initialization
		void initPressedSound();

	protected:

	public:
		//Constructor , Destructor
		Button(float x, float y, float width, float height
			, sf::Font& font, std::string text, unsigned charector_size
			, sf::Color text_idle_Color, sf::Color text_hover_color, sf::Color text_active_color
			, sf::Color shape_idle_color = sf::Color::White, sf::Color shape_hover_color = sf::Color::White, sf::Color shape_active_color = sf::Color::White,
			short unsigned id = 0);

		virtual ~Button();

		//Accessor
		const bool isPressed();
		const std::string getText();
		const short unsigned& getId();

		sf::Vector2f getSize();
		sf::Vector2f getPosition();

		//Modifier
		void setText(const std::string text);
		void setId(const short unsigned id);
		void setPosition(const float position_x, const float position_y);

		//Function
		void updateButton(const sf::Vector2f& mousePosition);
		void renderButton(sf::RenderTarget& target);
	};

	class DropDownBox
	{
	private:
		//Variable
		float keyTime;
		float keyTimeMax;

		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;

	public:
		//Constructor , Destructor
		DropDownBox(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned num_Elements, unsigned default_index = 0);
		~DropDownBox();

		//Accessor
		const bool getKeyTime();
		const unsigned short& getActiveElementId();

		//Function
		void updateDropDownBox(const float &dt, const sf::Vector2f& mousePosition);
		void updateKeyTime(const float &dt);
		void renderDropDownBox(sf::RenderTarget& target);
	};
}

