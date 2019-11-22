#include "Player.h"

//Initialization
void Player::initVariable()
{
	this->hurting = false;

	this->attacking = false;
	this->attackStyle = ATTACK_NONE;
	this->attackHitbox = NULL;
	
	this->jumpping = false;
	this->died = false;
}

void Player::initStatus()
{
	this->ATK = 100.0f;
	this->DEF = 10.0f;
	this->MSPD = 10.0f;
	this->maxHP = 1000.0f;
	this->currHP = this->maxHP;
}

//Constructor , Destructor
Player::Player(float x, float y, sf::Texture& texture_sheet ,std::string name)
{
	this->name = name;
	this->score = 0;
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
	this->animationComponent->addAnimation("DEAD", 13.0f, 6, 4, 13, 4, 32, 32);
	this->animationComponent->addAnimation("HURT", 13.0f, 6, 3, 9, 3, 32, 32);

	//create hitbox component
	this->createHitboxComponent(16.0f, 16.0f, this->sprite.getGlobalBounds().width-40, this->sprite.getGlobalBounds().height-20, sf::Color::Transparent);
	
	//create movement component
	this->createMovementComponent(40.0f * this->MSPD, 30.0f, 10.0f, 50.0f, 35.0f);

	//create sound component
	this->createSoundComponent();
	this->soundComponent->addSound("JUMP", "src/Resource/SoundFX/Player/jump.ogg");
	this->soundComponent->addSound("ATTACK", "src/Resource/SoundFX/Player/attack_punch.ogg");
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

const bool & Player::getDied()
{
	return this->died;
}

const bool & Player::getHurting()
{
	return this->hurting;
}

const std::string & Player::getName()
{
	return this->name;
}

const float & Player::getATK()
{
	return this->ATK;
}

const float & Player::getDEF()
{
	return this->DEF;
}

const float & Player::getCurrHP()
{
	return this->currHP;
}

const float & Player::getMaxHP()
{
	return this->maxHP;
}

const int & Player::getScore()
{
	return this->score;
}

//Function
void Player::increaseATK(const float atk_point)
{
	this->ATK += atk_point;
}

void Player::increaseDEF(const float def_point)
{
	this->DEF += def_point;
}

void Player::increaseHP(const float heal_point)
{
	//increase hp with % point
	this->currHP += (heal_point / 100.0f) * this->maxHP;
	
	//limit HP with max
	if (this->currHP >= this->maxHP) {
		this->currHP = this->maxHP;
	}
}

void Player::decreaseHP(const float& dt, const float ATK, sf::Vector2f attacker_center)
{
	srand(int(time(NULL)));

	float damage = (ATK * 1.25f) - (this->DEF / 100.0f);

	if (rand() % 101 <= 10) {
		//miss attack [ 1% chance to miss ]
		this->currHP = this->currHP - 0.0f;
	}
	else {
		//hit attack
		this->currHP = this->currHP - ((rand() % 50 + damage));
		this->hurting = true;
	}
}

void Player::increaseScore(const int point)
{
	this->score += point;
}

void Player::attack(const float& dt, short unsigned attack_style, Enemy* enemy)
{
	//play sound effect
	this->soundComponent->play("ATTACK");

	this->attacking = true;
	this->attackStyle = attack_style;
	
	this->createAttackHitbox();
	if (this->checkHitCollision(enemy)) {
		if (this->attackStyle == ATTACK_ONCE) {
			enemy->decreaseHP(dt, this->ATK, this->getCenter());
		}
		if (this->attackStyle == ATTACK_DOUBLE) {
			enemy->decreaseHP(dt, this->ATK, this->getCenter());
			enemy->decreaseHP(dt, this->ATK, this->getCenter());
		}
	}
	this->clearAttackHitbox();
}

void Player::createAttackHitbox()
{
	//create new attackHitbox
	if (this->attacking) {
		if (this->sprite.getScale().x > 0.0f) {
			if (this->attackStyle == ATTACK_ONCE) {
				this->attackHitbox = new HitboxComponent(this->sprite, 45, 50, 50, 30, sf::Color::Transparent);
			}
			if (this->attackStyle == ATTACK_DOUBLE) {
				this->attackHitbox = new HitboxComponent(this->sprite, 45, 50, 50, 30, sf::Color::Transparent);
			}
		}
		else {
			if (this->attackStyle == ATTACK_ONCE) {
				this->attackHitbox = new HitboxComponent(this->sprite, -10, 50, 50, 30, sf::Color::Transparent);
			}
			if (this->attackStyle == ATTACK_DOUBLE) {
				this->attackHitbox = new HitboxComponent(this->sprite, -10, 50, 50, 30, sf::Color::Transparent);
			}
		}
	}
}

const bool Player::checkHitCollision(Enemy* enemy)
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

void Player::jump()
{
	//play sound effect
	this->soundComponent->play("JUMP");

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
	this->updateCollisionFrame(window, 2);

	//god mode on ---------------------------------------------
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Insert)) {
		this->ATK = 10000;
		this->DEF = 10000;
		this->currHP = 10000;
		this->maxHP = 10000;
		this->sprite.setColor(sf::Color::Red);
	}
	//god mode on ---------------------------------------------
}

void Player::updateAnimation(const float & dt)
{
	//Animate and check for animation end
	if (this->currHP <= 0.0f) {
		this->movementComponent->stopVelocityX();
		this->movementComponent->stopVelocityY();

		if (this->animationComponent->play("DEAD", dt, true)) {
			this->died = true;
		}
	}
	else {
		if (this->hurting && !this->jumpping && !this->attacking) {
			if (this->animationComponent->play("HURT", dt)) {
				this->hurting = false;
			}
		}
		else {
			if (this->attacking) {
				if (this->attackStyle == ATTACK_ONCE && this->animationComponent->play("ATTACK_1", dt, true)) {
					this->attacking = false;
					this->attackStyle = ATTACK_NONE;
				}
				if (this->attackStyle == ATTACK_DOUBLE && this->animationComponent->play("ATTACK_2", dt, true)) {
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
	}
}

void Player::renderEntity(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent) {
		this->hitboxComponent->renderComponent(target);
	}
	//---------------------- for debug
	/*if (this->attackHitbox) {
		this->attackHitbox->renderComponent(target);
	}*/
	//--------------------
}





