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

enum movement_state { IDLE = 0 ,MOVING ,MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class MovementComponent
{
private:
	//Variable
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

public:
	//Constructor , Destructor
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessor
	const sf::Vector2f& getVelocity();
	const float& getMaxVelocity();

	//Function
	const bool getState(const short unsigned state);

	void move(const float direction_x, const float direction_y, const float &dt);
	void updateComponent(const float &dt);
};

