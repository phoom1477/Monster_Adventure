#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
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

public:
	//Public enum
	enum { ATTACK_NONE = 0, ATTACK_MELEE , ATTACK_RANGE, ATTACK_SKILL };

	//Constructor , Destructor
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	//Accessor
	bool& getAttacking();
	virtual const sf::Vector2f& getHitBoxPosition();


	//Function
	void attack(short unsigned attack_style);

	//update
	void updateEntity(const float &dt);
	void updateAttackHitbox();
	void updateAnimation(const float &dt);

	//render
	virtual void renderEntity(sf::RenderTarget& target);
};
