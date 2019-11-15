#include "Player.h"

//Initialization
void Player::initVariable()
{
	this->attacking = false;
	this->attackStyle = ATTACK_NONE;
	this->jumpping = false;
	this->attackHitbox = NULL;
}

void Player::initStatus()
{
	this->ATK = 100;
	this->DEF = 10;
	this->MSPD = 10;
	this->maxHP = 1000;
	this->currHP = this->maxHP;
}

//Constructor , Destructor
Player::Player(float x, float y, sf::Texture& texture_sheet ,std::string name)
{
	this->name = name;
	this->initVariable();
	this->initStatus();

	this->setPosition(x, y);
	
	//create animation component
	this->createAnimationComponent(texture_sheet);
	this->animationComponent->addAnimation("IDLE", 10.0f, 0, 5, 3, 5, 32, 32);
	this->animationComponent->addAnimation("WALK", 8.0f, 0, 1, 5, 1, 32, 32);
	this->animationComponent->addAnimation("JUMP", 10.0f, 9, 1, 14, 1, 32, 32);
	this->animationComponent->addAnimation("ATTACK_1", 8.0f, 0, 3, 3, 3, 32, 32);
	this->animationComponent->addAnimation("ATTACK_2", 8.0f, 6, 5, 12, 5, 32, 32);
	
	//create hitbox component
	this->createHitboxComponent(16.0f, 16.0f, this->sprite.getGlobalBounds().width-40, this->sprite.getGlobalBounds().height-20, sf::Color::Green);
	
	//create movement component
	this->createMovementComponent(40.0f * this->MSPD, 30.0f, 10.0f, 50.0f, 35.0f);
}

Player::~Player()
{
	if (this->attackHitbox) {
		delete this->attackHitbox;
	}
}

//Accessor
sf::Vector2f Player::getCenter()
{
	if (this->hitboxComponent) {
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x + this->hitboxComponent->getGlobalBounds().width / 2.0f,
			this->hitboxComponent->getPosition().y + this->hitboxComponent->getGlobalBounds().height / 2.0f
		);
	}

	return sf::Vector2f(
		this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2.0f,
		this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2.0f
	);
}

const bool & Player::getAttacking()
{
	return this->attacking;
}

const bool & Player::getJumpping()
{
	return this->jumpping;
}

//Function
void Player::attack(short unsigned attack_style, Entity* enemy)
{
	this->attacking = true;
	this->attackStyle = attack_style;

	this->createAttackHitbox();
	if (this->checkHitCollision(enemy)) {
		if (this->attackStyle == ATTACK_MELEE) {
			enemy->decreaseHP(this->ATK);
		}
		if (this->attackStyle == ATTACK_RANGE) {
			enemy->decreaseHP(this->ATK);
			enemy->decreaseHP(this->ATK);
		}
	}
	//this->clearAttackHitbox();
}

void Player::createAttackHitbox()
{
	//create new attackHitbox
	if (this->attacking) {
		if (this->sprite.getScale().x > 0.0f) {
			if (this->attackStyle == ATTACK_MELEE) {
				this->attackHitbox = new HitboxComponent(this->sprite, 65, 50, 30, 20, sf::Color::Red);
			}
			if (this->attackStyle == ATTACK_RANGE) {
				this->attackHitbox = new HitboxComponent(this->sprite, 65, 50, 30, 20, sf::Color::Blue);
			}
			if (this->attackStyle == ATTACK_SKILL) {
				this->attackHitbox = new HitboxComponent(this->sprite, 65, 50, 30, 20, sf::Color::Yellow);
			}
		}
		else {
			if (this->attackStyle == ATTACK_MELEE) {
				this->attackHitbox = new HitboxComponent(this->sprite, -6, 50, 30, 20, sf::Color::Red);
			}
			if (this->attackStyle == ATTACK_RANGE) {
				this->attackHitbox = new HitboxComponent(this->sprite, -6, 50, 30, 20, sf::Color::Blue);
			}
			if (this->attackStyle == ATTACK_SKILL) {
				this->attackHitbox = new HitboxComponent(this->sprite, -6, 50, 30, 20, sf::Color::Yellow);
			}
		}
	}
}

const bool Player::checkHitCollision(Entity* enemy)
{
	if (this->attacking) {
		if (this->attackHitbox->checkIntersect(enemy->getGlobalBounds())) {
			return true;
		}
	}
	return false;
}

void Player::clearAttackHitbox()
{
	//delete attackHitbox if not NULL
	if (this->attackHitbox) {
		delete this->attackHitbox;
		this->attackHitbox = NULL;
	}
}

void Player::decreaseHP(const float ATK)
{
	float damage = ATK * 2;

	srand(int(time(NULL)));
	this->currHP = this->currHP - ((rand() % 50 + damage) - (rand() % 20 + this->DEF));
}

void Player::jump()
{
	this->jumpping = true;
	this->movementComponent->jump();
}

void Player::updateEntity(const float & dt, sf::RenderWindow& window)
{
	//Update movement
	if (this->movementComponent) {
		this->movementComponent->updateComponent(dt);
	}

	this->updateAnimation(dt);
	
	//Update hitboxComponent
	if (this->hitboxComponent) {
		this->hitboxComponent->updateComponent();
	}

	//update collision
	this->updateCollisionFrame(window);
}

void Player::updateAnimation(const float & dt)
{
	//Animate and check for animation end
	if (this->attacking) {
		if (this->attackStyle == ATTACK_MELEE && this->animationComponent->play("ATTACK_1", dt, true)) {
			this->attacking = false;
			this->attackStyle = ATTACK_NONE;
		}
		if (this->attackStyle == ATTACK_RANGE && this->animationComponent->play("ATTACK_2", dt, true)) {
			this->attacking = false;
			this->attackStyle = ATTACK_NONE;
		}
		if (this->attackStyle == ATTACK_SKILL && this->animationComponent->play("IDLE", dt, true)) {
			this->attacking = false;
			this->attackStyle = ATTACK_NONE;
		}
	}
	if (this->jumpping) {
		if (this->animationComponent->play("JUMP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getJumpVelocity(), true)) {
			this->jumpping = false;
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
			this->sprite.setOrigin(29.0f, 0.0f);
			this->sprite.setScale(-3.0f, 3.0f);
		}

		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
}

void Player::updateCollisionEntity(Entity * entity)
{
	if (this->hitboxComponent->checkIntersect(entity->getGlobalBounds())) {
		this->stopEntityX();
		this->stopEntityY();
		this->setPosition(this->getPosition().x, this->getPosition().y);
	}
}

void Player::renderEntity(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent) {
		this->hitboxComponent->renderComponent(target);
	}
	//---------------------- for debug
	if (this->attackHitbox) {
		this->attackHitbox->renderComponent(target);
	}
	//--------------------
}





