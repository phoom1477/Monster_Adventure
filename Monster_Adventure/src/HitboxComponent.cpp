#include "HitboxComponent.h"

//Constructor , Destructor
HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
	:sprite(sprite) ,offsetX(offset_x) ,offsetY(offset_y)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x , this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.0f);
	this->hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{
}

//Function
bool HitboxComponent::checkIntersect(const sf::FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::updateComponent()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offsetX, this->sprite.getPosition().y + offsetY);
}

void HitboxComponent::renderComponent(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
