#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
	//Variable

	//Initialization
	void initVariable();
	/*void initComponent();*/

public:
	//Constructor , Destructor
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	//Function
	
	//update
	void updateEntity(const float &dt);
	//render
	
};

