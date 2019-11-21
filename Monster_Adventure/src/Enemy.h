#pragma once

#include "Entity.h"
#include "Player.h"

#include <time.h>

//forward declarations
class Player;

class Enemy : public Entity
{
private:
	//Identification
	std::string enemyId;
	std::string name;

	//Status
	float ATK;
	float DEF;
	float MSPD;
	float currHP;
	float maxHP;
	int point;

	//Getdata variable for animation
	sf::Vector2f faceRightOrigin;
	sf::Vector2f faceLeftOrigin;
	//Getdata variable for attack
	sf::Vector2f attackRightOffset;
	sf::Vector2f attackRightSize;
	sf::Vector2f attackLeftOffset;
	sf::Vector2f attackLeftSize;

	//Action
	bool hurting;
	bool attacking;
	short unsigned attackStyle;
	bool died;

	//Add on Component
	HitboxComponent *attackHitbox;

	//UI Resource
	sf::RectangleShape enemyShowHPBar;

	//Initialization
	void initVariable();
	void initData(std::string id);
	void initUI();

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
	const float& getMaxHP();
	const int& getPoint();

	//Function
	void decreaseHP(const float& dt, const float ATK, sf::Vector2f attacker_center);

	void attack(const float& dt, short unsigned attack_style, Player* player);
	void createAttackHitbox();
	const bool checkHitCollision(Player* player);
	void clearAttackHitbox();
	
	//update
	void updateEntity(const float &dt, sf::RenderWindow& window);
	void updateAnimation(const float &dt);
	void updateUI();

	//render
	virtual void renderEntity(sf::RenderTarget& target);
	void renderUI(sf::RenderTarget& target);
};

