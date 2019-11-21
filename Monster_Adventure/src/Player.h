#pragma once

#include "Entity.h"
#include "Enemy.h"

//forward declarations
class Enemy;

class Player : public Entity
{
private:
	//Identification
	std::string name;
	int score;

	//Status
	float ATK;
	float DEF;
	float MSPD;
	float currHP;
	float maxHP;

	//Action
	bool hurting;
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
	enum attackstyle{ ATTACK_NONE = 0, ATTACK_ONCE, ATTACK_DOUBLE};

	//Constructor , Destructor
	Player(float x, float y, sf::Texture& texture_sheet, std::string name);
	virtual ~Player();

	//Accessor
	sf::Vector2f getCenter();

	const bool& getAttacking();
	const bool& getJumpping();
	const bool& getDied();
	const bool& getHurting();

	const std::string& getName();
	const float& getATK();
	const float& getDEF();

	const float& getCurrHP();
	const float& getMaxHP();
	const int& getScore();

	//Function
	void increaseATK(const float atk_point);
	void increaseDEF(const float def_point);
	void increaseHP(const float heal_point);

	void decreaseHP(const float& dt, const float ATK, sf::Vector2f attacker_center);
	void increaseScore(const int point);

	void attack(const float& dt, short unsigned attack_style, Enemy* enemy);
	void createAttackHitbox();
	const bool checkHitCollision(Enemy* enemy);
	void clearAttackHitbox();

	void jump();
	
	//update
	void updateEntity(const float &dt, sf::RenderWindow& window);
	void updateAnimation(const float &dt);

	//render
	virtual void renderEntity(sf::RenderTarget& target);
};

