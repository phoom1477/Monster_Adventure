#pragma once

#include "Entity.h"

class Enemy : public Entity
{
private:
	//Identification
	std::string enemyId;
	std::string name;

	//Status
	short unsigned ATK;
	short unsigned DEF;
	short unsigned MSPD;
	short unsigned currHP;
	short unsigned maxHP;

	//Resource
	std::string spritePath;

	//Action
	bool attacking;
	short unsigned attackStyle;

	//Add on Component
	HitboxComponent *attackHitbox;

	//Initialization
	void initVariable();
	void initStatus(std::string id);

public:
	//Public enum
	enum attackstyle { ATTACK_NONE = 0, ATTACK_MELEE, ATTACK_RANGE, ATTACK_SKILL };

	//Constructor , Destructor
	Enemy(float x, float y, std::string id);
	virtual ~Enemy();

	//Accessor
	bool& getAttacking();


	//Function
	void attack(short unsigned attack_style);
	void checkHitCollision(std::vector<Entity> entity);

	//update
	void updateEntity(const float &dt);
	void updateAttackHitbox();
	void updateAnimation(const float &dt);

	//render
	virtual void renderEntity(sf::RenderTarget& target);
};

