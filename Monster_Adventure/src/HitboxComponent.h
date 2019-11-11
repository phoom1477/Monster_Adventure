#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>


class HitboxComponent
{
private:
	//Variable
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	//Constrictor , Destructor
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height, sf::Color linecolor);
	virtual ~HitboxComponent();

	//Function
	bool checkIntersect(const sf::FloatRect& frect);

	void updateComponent();
	void renderComponent(sf::RenderTarget& target);
};

