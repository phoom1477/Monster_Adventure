#include "HitboxComponent.h"

//Constructor , Destructor
HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height, sf::Color line_color)
	:sprite(sprite), offsetX(offset_x), offsetY(offset_y), firstIntersact(false)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x , this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.0f);
	this->hitbox.setOutlineColor(line_color);
}

HitboxComponent::~HitboxComponent()
{
}

//Accessor
const sf::Vector2f &HitboxComponent::getPosition()
{
	return this->hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::getGlobalBounds()
{
	return this->hitbox.getGlobalBounds();
}

const sf::Vector2f HitboxComponent::getSize()
{
	return this->hitbox.getSize();
}

//Modifier
void HitboxComponent::setPosition(const sf::Vector2f & position)
{
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

void HitboxComponent::setPosition(const float x, const float y)
{
	this->hitbox.setPosition(x, y);
	this->sprite.setPosition(x - this->offsetX, y - this->offsetY);
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
