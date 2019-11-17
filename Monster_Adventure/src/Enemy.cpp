#include "Enemy.h"

//Initialization
void Enemy::initVariable()
{
	this->hurting = false;

	this->attacking = false;
	this->attackStyle = ATTACK_NONE;
	this->attackHitbox = NULL;
}

void Enemy::initStatus(std::string id)
{
	//Load data from EnemyData.data
	std::ifstream getdata("src/Config/Data/EnemyData.data");

	//Set defalult if can,t read file
	this->enemyId = id;
	this->name = "Error Enemy";
	this->ATK = 100;
	this->DEF = 10;
	this->MSPD = 10;
	this->maxHP = 1000;
	this->currHP = this->maxHP;
	this->point = 100;
	
	//getdata from file
	while(getdata.is_open()) {
		std::string buff;
		getdata >> buff;
		if (buff == "ID" + this->enemyId + ":" + "NAME") {
			getline(getdata, this->name);
		}
		if (buff == "ID" + this->enemyId + ":" + "ATK") {
			getdata >> this->ATK;
		}
		if (buff == "ID" + this->enemyId + ":" + "DEF") {
			getdata >> this->DEF;
		}
		if (buff == "ID" + this->enemyId + ":" + "MSPD") {
			getdata >> this->MSPD;
		}
		if (buff == "ID" + this->enemyId + ":" + "maxHP") {
			getdata >> this->maxHP;
		}
		if (buff == "ID" + this->enemyId + ":" + "point") {
			getdata >> this->point;
		}

		if (buff == "") {
			getdata.close();
		}
	}
}

//Constructor , Destructor
Enemy::Enemy(float x, float y, sf::Texture& texture_sheet, std::string id)
{
	this->initVariable();
	this->initStatus(id);
	this->setPosition(x, y);

	//create animation component
	this->createAnimationComponent(texture_sheet);
	this->animationComponent->addAnimation("IDLE", 10.0f, 0, 0, 10, 0, 43, 37);
	this->animationComponent->addAnimation("WALK", 8.0f, 0, 1, 12, 1, 43, 37);
	this->animationComponent->addAnimation("ATTACK", 8.0f, 0, 2, 17, 2, 43, 37);
	this->animationComponent->addAnimation("DEAD", 13.0f, 0, 3, 14, 3, 43, 37);
	this->animationComponent->addAnimation("HURT", 13.0f, 0, 4, 7, 4, 43, 37);

	//create hitbox component
	this->createHitboxComponent(0.0f, 22.0f, this->sprite.getGlobalBounds().width - 80, this->sprite.getGlobalBounds().height - 20, sf::Color::Yellow);

	//create movement component
	this->createMovementComponent(40.0f * this->MSPD, 30.0f, 10.0f, 50.0f, 35.0f);
}

Enemy::~Enemy()
{
	if (this->attackHitbox) {
		delete this->attackHitbox;
	}
}

sf::Vector2f Enemy::getCenter()
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

//Accessor
const bool & Enemy::getAttacking()
{
	return this->attacking;
}

const bool & Enemy::getDied()
{
	return this->died;
}

const bool & Enemy::getHurting()
{
	return this->hurting;
}

const float& Enemy::getCurrHP()
{
	return this->currHP;
}

const int & Enemy::getPoint()
{
	return this->point;
}

//Function
void Enemy::decreaseHP(const float& dt, const float ATK, sf::Vector2f attacker_center)
{
	srand(int(time(NULL)));

	float damage = (ATK * 1.25f) - (this->DEF / 100.0f);

	if (rand() % 100 <= 5) {
		//miss attack
		this->currHP = this->currHP - 0.0f;
	}
	else {
		//hit attack
		this->currHP = this->currHP - ((rand() % 50 + damage));
		this->hurting = true;

		//if on the floor
		if (this->movementComponent->getVelocity().y >= 0.0f) {
			if (this->getCenter().x < attacker_center.x) {
				this->moveEntity(-5.0f, -20.0f, dt);
			}
			if (this->getCenter().x > attacker_center.x) {
				this->moveEntity(5.0f, -20.0f, dt);
			}
		}
	}
}

void Enemy::attack(const float& dt, short unsigned attack_style, Entity* player)
{
	attacking = true;
	std::cout << this->attacking << " ";
	this->attackStyle = attack_style;
	this->createAttackHitbox();
	if (this->checkHitCollision(player)) {
		if (this->attackStyle == ATTACK_ONCE) {
			player->decreaseHP(dt, this->ATK, this->getCenter());
		}
	}
	//this->clearAttackHitbox();
}

void Enemy::createAttackHitbox()
{
	//create new attackHitbox
	if (this->attacking) {
		if (this->sprite.getScale().x > 0.0f) {
			if (this->attackStyle == ATTACK_ONCE) {
				this->attackHitbox = new HitboxComponent(this->sprite, 65, 50, 30, 20, sf::Color::Red);
			}
		}
		else {
			if (this->attackStyle == ATTACK_ONCE) {
				this->attackHitbox = new HitboxComponent(this->sprite, -6, 50, 30, 20, sf::Color::Red);
			}
		}
	}
}

const bool Enemy::checkHitCollision(Entity* player)
{
	if (this->attacking) {
		if (this->attackHitbox->checkIntersect(player->getGlobalBounds())) {
			return true;
		}
	}
	return false;
}

void Enemy::clearAttackHitbox()
{
	//delete attackHitbox if not NULL
	if (this->attackHitbox) {
		delete this->attackHitbox;
		this->attackHitbox = NULL;
	}
}

void Enemy::updateEntity(const float & dt, sf::RenderWindow& window)
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

	//update collision
	this->updateCollisionFrame(window);
}

void Enemy::updateAnimation(const float & dt)
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
		if (this->hurting) {
			if (this->animationComponent->play("HURT", dt, true)) {
				this->hurting = false;
			}
		}
		else {
			if (this->attacking) {
				if (this->attackStyle == ATTACK_ONCE && this->animationComponent->play("ATTACK", dt, true)) {
					this->attacking = false;
					this->attackStyle = ATTACK_NONE;
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
					this->sprite.setOrigin(17.0f, 0.0f);
					this->sprite.setScale(-3.0f, 3.0f);
				}

				this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
			}
		}
	}
}

void Enemy::renderEntity(sf::RenderTarget & target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent) {
		this->hitboxComponent->renderComponent(target);
	}
	//---------------------- for debug
	if (this->attackHitbox) {
		this->attackHitbox->renderComponent(target);
	}
	//-----------------------
}
