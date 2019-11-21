#pragma once

#include "Entity.h"
#include "Player.h"

class Item : public Entity
{
private:
	//Identification
	std::string name;

	//Status
	float HPPoint;
	float ATKPoint;
	float DEFPoint;

	//Resource
	sf::Texture textureSheet;

	//Initialization
	void initVariable(std::string id);
	void initStatus(std::string id);
	void initTexture(std::string id);
	void initSound(std::string id);

public:
	///Constructor , Destructor
	Item(float x, float y, std::string id);
	virtual ~Item();

	//Accessor
	sf::Vector2f getCenter();

	//Function
	void buffPlayer(Player* player);
	const bool checkPlayerCollision(Player* player);

	//update
	void updateEntity(const float &dt, sf::RenderWindow& window);
	void updateAnimation(const float &dt);

	//render
	virtual void renderEntity(sf::RenderTarget& target);


	//not use just define for inheritance
	virtual void decreaseHP(const float& dt, const float ATK, sf::Vector2f attacker_center);
};

