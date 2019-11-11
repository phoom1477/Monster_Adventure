#include "MovementComponent.h"

//Constructor , Destructor
MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration, float jumpForce, float gravity)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration), jumpForce(-jumpForce), gravity(gravity)
{
}

MovementComponent::~MovementComponent()
{
}

//Accessor
const sf::Vector2f& MovementComponent::getVelocity()
{
	return this->velocity;
}

const float & MovementComponent::getJumpVelocity()
{
	return this->acceleration * this->jumpForce;
}

const float & MovementComponent::getMaxVelocity()
{
	return this->maxVelocity;
}

const bool MovementComponent::getState(const short unsigned state)
{
	if (state == IDLE && this->velocity.x == 0.0f && this->velocity.y >= 0.0f) {
		return true;
	}
	else if (state == MOVING && this->velocity.x != 0.0f && this->velocity.y != 0.0f) {
		return true;
	}
	else if (state == MOVING_LEFT && this->velocity.x < 0.0f) {
		return true;
	}
	else if (state == MOVING_RIGHT && this->velocity.x > 0.0f) {
		return true;
	}
	else if (state == MOVING_JUMP && this->velocity.y != 0.0f) {
		return true;
	}
	else {
		return false;
	}
}

//Modifier
void MovementComponent::stopVelocityX()
{
	this->velocity.x = 0.0f;
}

void MovementComponent::stopVelocityY()
{
	this->velocity.y = 0.0f;
}

//Function
void MovementComponent::move(const float direction_x, const float &dt)
{
	//acceleration increase to reaches maxVelocity
	this->velocity.x += this->acceleration * direction_x;
}

void MovementComponent::jump()
{
	this->velocity.y += this->acceleration * this->jumpForce;
}

void MovementComponent::updateComponent(const float &dt)
{
	std::cout << this->velocity.x << " " << this->velocity.y << '\n';
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

	this->velocity.y += this->gravity;

	/*Move the sprite*/
	this->sprite.move(this->velocity * dt);					//Final move 
}
