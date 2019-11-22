#include "UIAnimation.h"

//Constructor , Destructor
UIAnimation::UIAnimation(float x, float y, sf::Texture & texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
	this->animationComponent->addAnimation("IDLE",2500.0f,0,0,5,0,16,16);

	this->sprite.setPosition(x, y);
}

UIAnimation::~UIAnimation()
{
	delete this->animationComponent;
}

//Function
void UIAnimation::setScale(const float x, const float y)
{
	this->sprite.setScale(x, y);
}

void UIAnimation::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void UIAnimation::updateEntity(const float & dt)
{
	this->animationComponent->play("IDLE",true);
}

void UIAnimation::renderUIAnimation(sf::RenderTarget & target)
{
	target.draw(this->sprite);
}
