#include "Item.h"

void Item::initVariable(std::string id)
{
	if (id == "1") {
		this->name = "Posion";
	}
	if (id == "2") {
		this->name = "BuffATK";
	}
	if (id == "3") {
		this->name = "BuffDEF";
	}
}

void Item::initStatus(std::string id)
{
	if (id == "1") {
		this->HPPoint = 25;
		this->ATKPoint = 0;
		this->DEFPoint = 0;
	}
	if (id == "2") {
		this->HPPoint = 0;
		this->ATKPoint = 10;
		this->DEFPoint = 0;
	}
	if (id == "3") {
		this->HPPoint = 0;
		this->ATKPoint = 0;
		this->DEFPoint = 10;
	}
}

void Item::initTexture(std::string id)
{
	if (id == "1") {
		if (!this->textureSheet.loadFromFile("src/Resource/Item/Posion/Posion.png")) {
			throw("..ERROR.. Could't load item texture sheet");
		}
	}
	if (id == "2") {
		if (!this->textureSheet.loadFromFile("src/Resource/Item/BuffATK/BuffATK.png")) {
			throw("..ERROR.. Could't load item texture sheet");
		}
	}
	if (id == "3") {
		if (!this->textureSheet.loadFromFile("src/Resource/Item/BuffDEF/BuffDEF.png")) {
			throw("..ERROR.. Could't load item texture sheet");
		}
	}
}

void Item::initSound(std::string id)
{
	if (id == "1") {
		this->soundComponent->addSound("GET", "src/Resource/SoundFX/Item/getPosion.ogg");
	}
	if (id == "2") {
		this->soundComponent->addSound("GET", "src/Resource/SoundFX/Item/getBuff.ogg");
	}
	if (id == "3") {
		this->soundComponent->addSound("GET", "src/Resource/SoundFX/Item/getBuff.ogg");
	}
}

//Constructor , Destructor
Item::Item(float x, float y, std::string id)
{
	this->initVariable(id);
	this->initStatus(id);
	this->initTexture(id);

	this->setPosition(x, y);

	//create animation component
	this->createAnimationComponent(this->textureSheet);
	this->animationComponent->addAnimation("IDLE", 10.0f, 0, 0, 0, 0, 16, 16);

	//create hitbox component
	this->createHitboxComponent(10.0f, 10.0f, this->sprite.getGlobalBounds().width - 20, this->sprite.getGlobalBounds().height - 20, sf::Color::Cyan);
	
	//create movement component
	this->createMovementComponent(200.0f, 30.0f, 10.0f, 50.0f, 35.0f);

	//create sound component
	this->createSoundComponent();
	this->initSound(id);
}

Item::~Item()
{
}

//Accessor
sf::Vector2f Item::getCenter()
{
	if (this->hitboxComponent) {
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x + this->hitboxComponent->getGlobalBounds().width / 2.0f,
			this->hitboxComponent->getPosition().y + this->hitboxComponent->getGlobalBounds().height / 2.0f
		);
	}

	return sf::Vector2f(
		this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2.0f,
		this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2.0f
	);
}

//Function
void Item::buffPlayer(Player * player)
{
	player->increaseHP(this->HPPoint);
	player->increaseATK(this->ATKPoint);
	player->increaseDEF(this->DEFPoint);
}

const bool Item::checkPlayerCollision(Player * player)
{
	if (this->hitboxComponent) {
		if (this->hitboxComponent->checkIntersect(player->getGlobalBounds())) {
			this->soundComponent->play("GET");
			return true;
		}
		return false;
	}

	return false;
}

void Item::updateEntity(const float & dt, sf::RenderWindow & window)
{
	//Update movement
	if (this->movementComponent) {
		this->movementComponent->updateComponent(dt);
	}

	this->updateAnimation(dt);

	//Update hitboxComponent
	if (this->hitboxComponent) {
		this->hitboxComponent->updateComponent();
	}

	//update collision
	this->updateCollisionFrame(window, 1);
}

void Item::updateAnimation(const float & dt)
{
	this->animationComponent->play("IDLE", dt);
}

void Item::renderEntity(sf::RenderTarget & target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent) {
		this->hitboxComponent->renderComponent(target);
	}
}
