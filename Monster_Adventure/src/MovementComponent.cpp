#include "MovementComponent.h"

//Constructor , Destructor
MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
}

MovementComponent::~MovementComponent()
{
}

const sf::Vector2f& MovementComponent::getVelocity()
{
	return this->velocity;
}

//Function
void MovementComponent::move(const float direction_x, const float direction_y, const float &dt)
{
	//acceleration increase to reaches maxVelocity
	this->velocity.x += this->acceleration * direction_x;
	this->velocity.y += this->acceleration * direction_y;
}

void MovementComponent::updateComponent(const float &dt)
{
	/*Deceleration the sprite and control the maximum velocity*/
	
	if (this->velocity.x > 0.0f) {							//Check for positive x
		//Max velocity check positive
		if (this->velocity.x > this->maxVelocity) {
			this->velocity.x = this->maxVelocity;
		}

		//Deceleration x positive
		this->velocity.x -= this->deceleration;
		if (this->velocity.x < 0.0f) {
			this->velocity.x = 0.0f;
		}
	}
	else if (this->velocity.x < 0.0f) {						//Check for negative x
		//Max velocity check negative
		if (this->velocity.x < -this->maxVelocity) {
			this->velocity.x = -this->maxVelocity;
		}

		//Deceleration x negative
		this->velocity.x += this->deceleration;
		if (this->velocity.x > 0.0f) {
			this->velocity.x = 0.0f;
		}
	}

	if (this->velocity.y > 0.0f) {							//Check for positive y
		//Max velocity check positive
		if (this->velocity.y > this->maxVelocity) {
			this->velocity.y = this->maxVelocity;
		}

		//Deceleration y positive
		this->velocity.y -= this->deceleration;
		if (this->velocity.y < 0.0f) {
			this->velocity.y = 0.0f;
		}
	}
	else if (this->velocity.y < 0.0f) {						//Check for negative y
		//Max velocity check negative
		if (this->velocity.y < -this->maxVelocity) {		
			this->velocity.y = -this->maxVelocity;
		}

		//Deceleration y negative
		this->velocity.y += this->deceleration;
		if (this->velocity.y > 0.0f) {
			this->velocity.y = 0.0f;
		}
	}

	/*Move the sprite*/

	this->sprite.move(this->velocity * dt);					//Final move 
}
