#pragma once

#include "Entity.h"
#include "Player.h"

class Enemy : public Entity
{
private:
	//Identification
	std::string enemyId;
	std::string name;

	//Resource
	std::string spritePath;

	//Status
	short unsigned ATK;
	short unsigned DEF;
	short unsigned MSPD;
	short unsigned currHP;
	short unsigned maxHP;

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
	Enemy(float x, float y, sf::Texture& texture_sheet, std::string id);
	virtual ~Enemy();

	//Accessor
	bool& getAttacking();


	//Function
	void attack(short unsigned attack_style);
	const bool checkHitCollision(Entity* player);

	//update
	void updateEntity(const float &dt);
	void updateAttackHitbox();
	void updateAnimation(const float &dt);

	//render
	virtual void renderEntity(sf::RenderTarget& target);
};

