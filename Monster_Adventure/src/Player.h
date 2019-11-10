#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
	//Variable
	bool attacking;

	//Initialization
	void initVariable();

public:
	//Constructor , Destructor
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	//Function
	
	//update
	void updateEntity(const float &dt);
	void updateAttack(const float &dt);
	void updateAnimation(const float &dt);
	
	//render
	
};

