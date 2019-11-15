////////////////////////////////////////////////
//   This class is Abstract class of Entity.  //
////////////////////////////////////////////////

//////////////////////////////////////////////////
//	Object list that used by dynamic allocated  //
//          - animationComponent				//
//			- hitboxComponent					//
//			- movementComponent					//
//////////////////////////////////////////////////

#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	//Intialization
	void initVariable();

protected:
	//Resource
	sf::Sprite sprite;
	
	//Builtin component
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;	
	MovementComponent* movementComponent;

public:
	//Constructor , Destructor
	Entity();
	virtual ~Entity();

	//Component function
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createHitboxComponent(const float offset_x, const float offset_y, const float width, const float height, sf::Color line_color);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration, const float jumpForce, const float gravity);
	
	//Accessor
	virtual sf::FloatRect getGlobalBounds();
	virtual const sf::Vector2f getPosition();

	//Function
	virtual void setPosition(const float x, const float y);
	virtual void moveEntity(float direction_x, const float &dt);
	virtual void stopEntityX();
	virtual void stopEntityY();
	
	virtual void decreaseHP(const float ATK) = 0;

	//update
	virtual void updateEntity(const float &dt, sf::RenderWindow& window) = 0;
	virtual void updateCollisionFrame(sf::RenderWindow& window);

	//render
	virtual void renderEntity(sf::RenderTarget& target) = 0;
};  

