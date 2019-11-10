#include "Player.h"

//Initialization
void Player::initVariable()
{
	this->attacking = false;
}

//Constructor , Destructor
Player::Player(float x, float y, sf::Texture& texture_sheet )
{
	this->initVariable();

	this->setPosition(x, y);
	
	//create animation component
	this->createAnimationComponent(texture_sheet);
	this->animationComponent->addAnimation("IDLE", 10.0f, 0, 5, 3, 5, 32, 32);
	this->animationComponent->addAnimation("WALK", 8.0f, 0, 1, 5, 1, 32, 32);
	this->animationComponent->addAnimation("ATTACK", 8.0f, 0, 3, 3, 3, 32, 32);
	
	//create hitbox component
	this->createHitboxComponent(20.0f, 20.0f, this->sprite.getGlobalBounds().width-40, this->sprite.getGlobalBounds().height-20);
	
	//create movement component
	this->createMovementComponent(400.0f, 30.0f, 10.0f);
}

Player::~Player()
{
}

//Function
void Player::updateEntity(const float & dt)
{
	this->movementComponent->updateComponent(dt);
	
	this->updateAttack(dt);
	this->updateAnimation(dt);

	this->hitboxComponent->updateComponent();
}

void Player::updateAttack(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {					// <<---add for test
		this->attacking = true;
	}
}

void Player::updateAnimation(const float & dt)
{
	if (this->attacking) {
		//Set origin depending on direction
		if (this->sprite.getScale().x > 0.0f) { //Facing right
			this->sprite.setOrigin(0.0f, 0.0f);
			this->sprite.setScale(3.0f, 3.0f);
		}
		else {									//Facing left
			this->sprite.setOrigin(32.0f, 0.0f);
			this->sprite.setScale(-3.0f, 3.0f);
		}
		//Animate and check for animation end
		if (this->animationComponent->play("ATTACK", dt, true)) {
			this->attacking = false;
			if (this->sprite.getScale().x > 0.0f) { //Facing right
				this->sprite.setOrigin(0.0f, 0.0f);
				this->sprite.setScale(3.0f, 3.0f);
			}
			else {									//Facing left
				this->sprite.setOrigin(32.0f, 0.0f);
				this->sprite.setScale(-3.0f, 3.0f);
			}
		}
	}

	if (this->movementComponent->getState(IDLE)) {
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT)) {
		if (this->sprite.getScale().x < 0.0f) {
			this->sprite.setOrigin(0.0f, 0.0f);
			this->sprite.setScale(3.0f, 3.0f);
		}

		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT)) {
		if (this->sprite.getScale().x > 0.0f) {
			this->sprite.setOrigin(32.0f, 0.0f);
			this->sprite.setScale(-3.0f, 3.0f);
		}

		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
}






