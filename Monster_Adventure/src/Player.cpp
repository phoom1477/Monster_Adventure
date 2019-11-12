#include "Player.h"

//Initialization
void Player::initVariable()
{
	this->name = "Unknow";
	this->attacking = false;
	this->attackStyle = ATTACK_NONE;
	this->jumpping = false;
	this->attackHitbox = NULL;
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
	this->animationComponent->addAnimation("JUMP", 8.0f, 9, 1, 14, 1, 32, 32);
	this->animationComponent->addAnimation("ATTACK_1", 8.0f, 0, 3, 3, 3, 32, 32);
	this->animationComponent->addAnimation("ATTACK_2", 8.0f, 6, 5, 12, 5, 32, 32);
	
	//create hitbox component
	this->createHitboxComponent(16.0f, 16.0f, this->sprite.getGlobalBounds().width-40, this->sprite.getGlobalBounds().height-20, sf::Color::Green);
	
	//create movement component
	this->createMovementComponent(400.0f, 30.0f, 10.0f, 50.0f, 35.0f);
}

Player::~Player()
{
	delete this->attackHitbox;
}

//Accessor
bool & Player::getAttacking()
{
	return this->attacking;
}

bool & Player::getJumpping()
{
	return this->jumpping;
}

const sf::Vector2f & Player::getHitBoxPosition()
{
	return this->hitboxComponent->getPosition();
}

//Function
void Player::attack(short unsigned attack_style)
{
	this->attacking = true;
	this->attackStyle = attack_style;
}

void Player::jump()
{
	this->jumpping = true;
	this->movementComponent->jump();
}

void Player::checkHitCollision(std::vector<Entity> entity)
{
	for (int i = 0; i < entity.size(); i++) {
		if (this->attackHitbox->checkIntersect(entity[i].getHitBoxGlobalBounds())) {
			/* action*/
			std::cout << "Hit";
		}
	}
}

void Player::updateEntity(const float & dt)
{
	//Update movement
	if (this->movementComponent) {
		this->movementComponent->updateComponent(dt);
	}
	
	this->updateAttackHitbox();
	this->updateAnimation(dt);
	
	//Update hitboxComponent
	if (this->hitboxComponent) {
		this->hitboxComponent->updateComponent();
	}

	//Update Add on component
	if (this->attackHitbox) {
		this->attackHitbox->updateComponent();
	}
}

void Player::updateAttackHitbox()
{
	//delete attackHitbox if not NULL
	if (this->attackHitbox) {
		delete this->attackHitbox;
		this->attackHitbox = NULL;
	}
	//create new attackHitbox
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

void Player::renderEntity(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent) {
		this->hitboxComponent->renderComponent(target);
	}
	if (this->attackHitbox) {
		this->attackHitbox->renderComponent(target);
	}
}





