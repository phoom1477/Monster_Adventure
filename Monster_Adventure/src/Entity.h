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
	sf::Sprite sprite;
	
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;	
	MovementComponent* movementComponent;

public:
	//Constructor , Destructor
	Entity();
	virtual ~Entity();

	//Component function
	/*void setTexture(sf::Texture& texture);*/
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createHitboxComponent(const float offset_x, const float offset_y, const float width, const float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	
	//Function
	virtual void setPosition(const float x, const float y);
	virtual void moveEntity(float direction_x, float direction_y, const float &dt);
	
	//update
	virtual void updateEntity(const float &dt) = 0;

	//render
	virtual void renderEntity(sf::RenderTarget& target);

};  

