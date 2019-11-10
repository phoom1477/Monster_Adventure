#include "Entity.h"

//Initialization
void Entity::initVariable()
{
	this->animationComponent = NULL;
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
}

//Constructor , Destructor
Entity::Entity()
{
	this->initVariable();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
    delete this->movementComponent;
	delete this->animationComponent;
}

//Component Function
/*void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}*/

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitboxComponent(const float offset_x, const float offset_y, const float width, const float height)
{
	this->hitboxComponent = new HitboxComponent(this->sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

//Function
void Entity::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Entity::moveEntity(float direction_x, float direction_y, const float &dt)
{
	if (this->movementComponent) {
		this->movementComponent->move(direction_x, direction_y ,dt);
	}
}

void Entity::renderEntity(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	
	if (this->hitboxComponent) {
		this->hitboxComponent->renderComponent(target);
	}
}



