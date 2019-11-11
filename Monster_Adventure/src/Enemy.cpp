/*#include "Enemy.h"

//Constructor , Destructor
Enemy::Enemy(float x, float y, sf::Texture& texture_sheet)
{
	this->setPosition(x, y);

	//create animation component
	this->createAnimationComponent(texture_sheet);
	
	//create hitbox component
	this->createHitboxComponent();

	//create movement component
	this->createMovementComponent();
}

Enemy::~Enemy()
{
}

//Function
void Enemy::updateEntity(const float & dt)
{
	//Update movement
	if (this->movementComponent) {
		this->movementComponent->updateComponent(dt);
	}

	this->updateAnimation(dt);

	//update hitboxComponent
	if (this->hitboxComponent) {
		this->hitboxComponent->updateComponent();
	}
}

void Enemy::updateAnimation(const float & dt)
{
}

void Enemy::renderEntity(sf::RenderTarget & target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent) {
		this->hitboxComponent->renderComponent();
	}
}*/
