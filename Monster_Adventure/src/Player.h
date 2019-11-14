#pragma once

#include "Entity.h"
#include "Enemy.h"

class Player : public Entity
{
private:
	//Identification
	std::string name;

	//Status
	short unsigned ATK;
	short unsigned DEF;
	short unsigned MSPD;
	short unsigned currHP;
	short unsigned maxHP;

	//Action
	bool attacking;
	short unsigned attackStyle;
	bool jumpping;
	
	//Add on Component
	HitboxComponent *attackHitbox;

	//Initialization
	void initVariable();
	void initStatus();

public:
	//Public enum
	enum attackstyle{ ATTACK_NONE = 0, ATTACK_MELEE , ATTACK_RANGE, ATTACK_SKILL };

	//Constructor , Destructor
	Player(float x, float y, sf::Texture& texture_sheet, std::string name);
	virtual ~Player();

	//Accessor
	sf::Vector2f getCenter();

	const bool& getAttacking();
	const bool& getJumpping();
	const float getATK();


	//Function
	const bool checkHitCollision(Entity* enemy);
	void attack(short unsigned attack_style);
	void jump();
	
	//update
	void updateEntity(const float &dt);
	void updateAttackHitbox();
	void updateAnimation(const float &dt);

	//render
	virtual void renderEntity(sf::RenderTarget& target);
};

