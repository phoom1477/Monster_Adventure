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

		if (buff == "") {
			getdata.close();
		}
	}
	std::cout << this->spritePath;
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
	this->createHitboxComponent(0.0f, 22.0f, this->sprite.getGlobalBounds().width - 20, this->sprite.getGlobalBounds().height - 20, sf::Color::Yellow);

	//create movement component
	this->createMovementComponent(40.0f * this->MSPD, 30.0f, 10.0f, 50.0f, 35.0f);
}

Enemy::~Enemy()
{
	if (this->attackHitbox) {
		delete this->attackHitbox;
	}
}

//Accessor
bool & Enemy::getAttacking()
{
	return this->attacking;
}

void Enemy::attack(short unsigned attack_style)
{
	attacking = true;
	this->attackStyle = attack_style;
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

//Function
void Enemy::updateEntity(const float & dt)
{
	//Update movement
	if (this->movementComponent) {
		this->movementComponent->updateComponent(dt);
	}

	this->updateAttackHitbox();
	this->updateAnimation(dt);

	//update hitboxComponent
	if (this->hitboxComponent) {
		this->hitboxComponent->updateComponent();
	}
}

void Enemy::updateAttackHitbox()
{
}

void Enemy::updateAnimation(const float & dt)
{
	if (this->movementComponent->getState(IDLE)) {
		this->animationComponent->play("IDLE", dt);
	}
}

void Enemy::renderEntity(sf::RenderTarget & target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent) {
		this->hitboxComponent->renderComponent(target);
	}
	if (this->attackHitbox) {
		this->attackHitbox->renderComponent(target);
	}
}
