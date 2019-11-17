#pragma once

#include "Entity.h"
#include "Player.h"
#include <time.h>

class Enemy : public Entity
{
private:
	//Identification
	std::string enemyId;
	std::string name;

	//Resource

	//Status
	short unsigned ATK;
	short unsigned DEF;
	short unsigned MSPD;
	float currHP;
	float maxHP;
	int point;

	//Action
	bool hurting;
	bool attacking;
	short unsigned attackStyle;
	bool died;

	//Add on Component
	HitboxComponent *attackHitbox;

	//Initialization
	void initVariable();
	void initStatus(std::string id);

public:
	//Public enum
	enum attackstyle { ATTACK_NONE = 0, ATTACK_ONCE };

	//Constructor , Destructor
	Enemy(float x, float y, sf::Texture& texture_sheet, std::string id);
	virtual ~Enemy();

	//Accessor
	sf::Vector2f getCenter();

	const bool& getAttacking();
	const bool& getDied();
	const bool& getHurting();

	const float& getCurrHP();
	const int& getPoint();

	//Function
	void decreaseHP(const float& dt, const float ATK, sf::Vector2f attacker_center);

	void attack(const float& dt, short unsigned attack_style, Entity* player);
	void createAttackHitbox();
	const bool checkHitCollision(Entity* player);
	void clearAttackHitbox();
	
	//update
	void updateEntity(const float &dt, sf::RenderWindow& window);
	void updateAnimation(const float &dt);

	//render
	virtual void renderEntity(sf::RenderTarget& target);
};

