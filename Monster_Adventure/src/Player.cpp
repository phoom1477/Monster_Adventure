#include "Player.h"

//Initialization
void Player::initVariable()
{
	
}

/*void Player::initComponent()
{
	
}*/

//Constructor , Destructor
Player::Player(float x, float y, sf::Texture& texture_sheet )
{
	this->initVariable();

	this->setPosition(x, y);

	this->createMovementComponent(300.0f, 30.0f, 5.0f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("PLAYER_IDLE_RIGHT", 100.0f, 0, 0, 3, 0, 32, 32);
}

Player::~Player()
{

}

//Function
void Player::updateEntity(const float & dt)
{
	Entity::updateEntity(dt);

	this->animationComponent->play("PLAYER_IDLE_RIGHT", dt);
}




