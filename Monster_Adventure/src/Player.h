#pragma once

#include "Entity.h"
#include "Enemy.h"

class Player : public Entity
{
private:
	//Identification
	std::string name;
	int score;

	//Status
	short unsigned ATK;
	short unsigned DEF;
	short unsigned MSPD;
	float currHP;
	float maxHP;

	//Action
	bool attacking;
	short unsigned attackStyle;
	bool jumpping;
	bool died;
	
	//Add on Component
	HitboxComponent *attackHitbox;

	//Initialization
	void initVariable();
	void initStatus();

public:
	//Public enum
	enum attackstyle{ ATTACK_NONE = 0, ATTACK_ONCE, ATTACK_DOUBLE, ATTACK_SKILL };

	//Constructor , Destructor
	Player(float x, float y, sf::Texture& texture_sheet, std::string name);
	virtual ~Player();

	//Accessor
	sf::Vector2f getCenter();

	const bool& getAttacking();
	const bool& getJumpping();
	const bool& getDied();

	const std::string& getName();
	const float& getCurrHP();
	const float& getMaxHP();
	const int& getScore();

	//Function
	void decreaseHP(const float& dt, const float ATK, sf::Vector2f attacker_center);
	void increaseScore(const int point);

	void attack(const float& dt, short unsigned attack_style, Entity* enemy);
	void createAttackHitbox();
	const bool checkHitCollision(Entity* enemy);
	void clearAttackHitbox();

	void jump();
	
	//update
	void updateEntity(const float &dt, sf::RenderWindow& window);
	void updateAnimation(const float &dt);

	//render
	virtual void renderEntity(sf::RenderTarget& target);
};

