//////////////////////////////////////////////////
//	Object list that used by dynamic allocated  //
//		- animationComponent					//
//////////////////////////////////////////////////

#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "AnimationComponent.h"

class UIAnimation
{
private:
	//Resource
	sf::Sprite sprite;

	AnimationComponent* animationComponent;

public:
	//Constructor , Destructor
	UIAnimation(float x, float y, sf::Texture& texture_sheet);
	virtual ~UIAnimation();

	//Function
	void setScale(const float x, const float y);
	void setPosition(const float x, const float y);

	//update
	void updateEntity(const float &dt);

	//render
	void renderUIAnimation(sf::RenderTarget& target);
};

