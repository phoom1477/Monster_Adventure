#include "Enemy.h"

//Initialization
void Enemy::initVariable()
{
	this->hurting = false;

	this->attacking = false;
	this->attackStyle = ATTACK_NONE;
	this->attackHitbox = NULL;
}

void Enemy::initData(std::string id)
{
	//Set defalult if can,t read file
	this->enemyId = id;
	this->name = "Error Enemy";
	this->ATK = 100.0f;
	this->DEF = 10.0f;
	this->MSPD = 10.0f;
	this->maxHP = 1000.0f;
	this->currHP = this->maxHP;
	this->point = 100;

	this->faceRightOrigin = sf::Vector2f(0, 0);
	this->faceLeftOrigin = sf::Vector2f(0, 0);
}

//Constructor , Destructor
Enemy::Enemy(float x, float y, sf::Texture& texture_sheet, std::string id)
{
	this->initVariable();
	this->initData(id);
	this->setPosition(x, y);

	//Getdata Variable -------------------
	
	//animation
	sf::Vector2i sprite_size;
	
	float idle_time;
	sf::Vector2i idle_start;
	sf::Vector2i idle_end;

	float walk_time;
	sf::Vector2i walk_start;
	sf::Vector2i walk_end;

	float attack_time;
	sf::Vector2i attack_start;
	sf::Vector2i attack_end;

	float dead_time;
	sf::Vector2i dead_start;
	sf::Vector2i dead_end;

	float hurt_time;
	sf::Vector2i hurt_start;
	sf::Vector2i hurt_end;
	
	//hitbox
	sf::Vector2f offset;
	sf::Vector2f minus_size;
	
	//sound
	std::string attack_sound_path;
	
	//------------------------------------

	//Load data from EnemyData.data
	std::string data_path = "src/Config/Data/EnemyData";
	data_path = data_path + id + ".data";
	std::ifstream getdata(data_path);

	//getdata from file
	while (getdata.is_open()) {
		std::string buff;
		getdata >> buff;
		//get status
		if (buff == "NAME") {
			getline(getdata, this->name);
			//trim [this->name]
			this->name.erase(std::remove_if(this->name.begin(), this->name.end(), isspace), this->name.end());
		}
		if (buff == "ATK") {
			getdata >> this->ATK;
		}
		if (buff == "DEF") {
			getdata >> this->DEF;
		}
		if (buff == "MSPD") {
			getdata >> this->MSPD;
		}
		if (buff == "maxHP") {
			getdata >> this->maxHP;
			this->currHP = this->maxHP;
		}
		if (buff == "point") {
			getdata >> this->point;
		}

		//getdata to class varible for animation
		if (buff == "face_right_origin") {
			getdata >> this->faceRightOrigin.x >> this->faceRightOrigin.y;
		}
		if (buff == "face_left_origin") {
			getdata >> this->faceLeftOrigin.x >> this->faceLeftOrigin.y;
		}

		//getdata animation component
		if (buff == "sprite_size") {
			getdata >> sprite_size.x >> sprite_size.y;
		}
		if (buff == "idle") {
			getdata >> idle_time >> idle_start.x >> idle_start.y >> idle_end.x >> idle_end.y;
		}
		if (buff == "walk") {
			getdata >> walk_time >> walk_start.x >> walk_start.y >> walk_end.x >> walk_end.y;
		}
		if (buff == "attack") {
			getdata >> attack_time >> attack_start.x >> attack_start.y >> attack_end.x >> attack_end.y;
		}
		if (buff == "dead") {
			getdata >> dead_time >> dead_start.x >> dead_start.y >> dead_end.x >> dead_end.y;
		}
		if (buff == "hurt") {
			getdata >> hurt_time >> hurt_start.x >> hurt_start.y >> hurt_end.x >> hurt_end.y;
		}

		//getdata hitbox component
		if (buff == "offset") {
			getdata >> offset.x >> offset.y;
		}
		if (buff == "minus_size") {
			getdata >> minus_size.x >> minus_size.y;
		}
		if (buff == "attackSoundPath") {
			getline(getdata, attack_sound_path);
			attack_sound_path.erase(std::remove_if(attack_sound_path.begin(), attack_sound_path.end(), isspace), attack_sound_path.end());
		}

		//close file
		if (buff == "") {
			getdata.close();
		}

	}

	//create animation component
	this->createAnimationComponent(texture_sheet);
	this->animationComponent->addAnimation("IDLE", idle_time, idle_start.x, idle_start.y, idle_end.x, idle_end.y, sprite_size.x, sprite_size.y);
	this->animationComponent->addAnimation("WALK", walk_time, walk_start.x, walk_start.y, walk_end.x, walk_end.y, sprite_size.x, sprite_size.y);
	this->animationComponent->addAnimation("ATTACK", attack_time, attack_start.x, attack_start.y, attack_end.x, attack_end.y, sprite_size.x, sprite_size.y);
	this->animationComponent->addAnimation("DEAD", dead_time, dead_start.x, dead_start.y, dead_end.x, dead_end.y, sprite_size.x, sprite_size.y);
	this->animationComponent->addAnimation("HURT", hurt_time, hurt_start.x, hurt_start.y, hurt_end.x, hurt_end.y, sprite_size.x, sprite_size.y);

	//create hitbox component
	this->createHitboxComponent(offset.x, offset.y, this->sprite.getGlobalBounds().width - minus_size.x, this->sprite.getGlobalBounds().height - minus_size.y, sf::Color::Yellow);

	//create movement component
	this->createMovementComponent(40.0f * this->MSPD, 30.0f, 10.0f, 0.0f, 35.0f);

	//create sound component
	this->createSoundComponent();
	this->soundComponent->addSound("ATTACK", attack_sound_path);
}

Enemy::~Enemy()
{
	if (this->attackHitbox) {
		delete this->attackHitbox;
	}
}

//Accessor
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

	std::cout << this->currHP << "/" << this->maxHP << '\n';
}

void Enemy::attack(const float& dt, short unsigned attack_style, Entity* player)
{
	//play sound effect
	this->soundComponent->play("ATTACK");

	attacking = true;
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
	this->updateCollisionFrame(window, 2);
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
					this->sprite.setOrigin(this->faceRightOrigin.x, this->faceRightOrigin.y);
					this->sprite.setScale(3.0f, 3.0f);
				}

				this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
			}
			else if (this->movementComponent->getState(MOVING_LEFT)) {
				if (this->sprite.getScale().x > 0.0f) {
					this->sprite.setOrigin(this->faceLeftOrigin.x, this->faceLeftOrigin.y);
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
