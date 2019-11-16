#include "Enemy.h"

//Initialization
void Enemy::initVariable()
{
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
	this->animationComponent->addAnimation("IDLE", 10.0f, 0, 0, 10, 0, 24, 32);

	//create hitbox component
	this->createHitboxComponent(0.0f, 22.0f, this->sprite.getGlobalBounds().width - 20, this->sprite.getGlobalBounds().height - 20, sf::Color::Green);

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
bool & Enemy::getAttacking()
{
	return this->attacking;
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
void Enemy::decreaseHP(const float ATK)
{
	srand(int(time(NULL)));

	float damage = (ATK * 2) - (this->DEF / 100.0f);

	if (rand() % 100 <= 5) {
		//miss attack
		this->currHP = this->currHP - 0.0f;
	}
	else {
		//hit attack
		this->currHP = this->currHP - ((rand() % 50 + damage));
	}
}

void Enemy::attack(short unsigned attack_style, Entity* player)
{
	attacking = true;
	std::cout << this->attacking << " ";
	this->attackStyle = attack_style;
	this->createAttackHitbox();
	if (this->checkHitCollision(player)) {
		if (this->attackStyle == ATTACK_MELEE) {
			player->decreaseHP(this->ATK);
		}
		if (this->attackStyle == ATTACK_RANGE) {
			player->decreaseHP(this->ATK);
			player->decreaseHP(this->ATK);
		}
	}
	//this->clearAttackHitbox();
}

void Enemy::createAttackHitbox()
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
	if (this->attacking) {
		if (this->attackStyle == ATTACK_MELEE && this->animationComponent->play("IDLE", dt, true)) {
		//if (this->attackStyle == ATTACK_MELEE && this->animationComponent->play("ATTACK_1", dt, true)) {
			this->attacking = false;
			this->attackStyle = ATTACK_NONE;
		}
		if (this->attackStyle == ATTACK_RANGE && this->animationComponent->play("IDLE", dt, true)) {
		//if (this->attackStyle == ATTACK_MELEE && this->animationComponent->play("ATTACK_2", dt, true)) {
			this->attacking = false;
			this->attackStyle = ATTACK_NONE;
		}
		if (this->attackStyle == ATTACK_SKILL && this->animationComponent->play("IDLE", dt, true)) {
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

		this->animationComponent->play("IDLE", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT)) {
		if (this->sprite.getScale().x > 0.0f) {
			this->sprite.setOrigin(17.0f, 0.0f);
			this->sprite.setScale(-3.0f, 3.0f);
		}

		this->animationComponent->play("IDLE", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
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
