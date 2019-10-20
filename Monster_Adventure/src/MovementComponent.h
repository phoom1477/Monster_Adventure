#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <map>

class MovementComponent
{
private:
	//Variable
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;
	
	//Initialization

public:
	//Constructor , Destructor
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessor
	const sf::Vector2f& getVelocity();

	//Function
	void move(const float direction_x, const float direction_y, const float &dt);
	void updateComponent(const float &dt);
};

