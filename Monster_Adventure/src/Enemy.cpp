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
	this->name = "Unknow";
	this->ATK = 0;
	this->DEF = 0;
	this->MSPD = 0;
	this->maxHP = 0;

	//getdata from file
	while(getdata.is_open()) {
		std::string buff;
		std::string subbuff;
		getdata >> buff;
		if (buff == "ID") {
			while (getdata.is_open()) {
				getdata >> subbuff;
				if (subbuff == "NAME") {
					getline(getdata, this->name);
				}
				if (subbuff == "ATK") {
					getdata >> this->ATK;
				}
				if (subbuff == "DEF") {
					getdata >> this->DEF;
				}
				if (subbuff == "MSPD") {
					getdata >> this->MSPD;
				}
				if (subbuff == "maxHP") {
					getdata >> this->maxHP;
				}
				if (subbuff == "spritePath") {
					getdata >> this->spritePath;
				}

				if (subbuff == "ID") {
					getdata.close();
				}
			}
		}
	}
	
}

//Constructor , Destructor
Enemy::Enemy(float x, float y, std::string id)
{
	this->initVariable();
	this->initStatus(id);

	this->setPosition(x, y);

	/*//create animation component
	this->createAnimationComponent(texture_sheet);
	
	//create hitbox component
	this->createHitboxComponent();

	//create movement component
	this->createMovementComponent();*/
}

Enemy::~Enemy()
{
	delete this->attackHitbox;
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

void Enemy::checkHitCollision(std::vector<Entity> entity)
{
	for (int i = 0; i < entity.size(); i++) {
		if (this->attackHitbox->checkIntersect(entity[i].getHitBoxGlobalBounds())) {
			/* action*/
			std::cout << "Hit";
		}
	}
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
