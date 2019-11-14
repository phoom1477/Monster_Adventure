#include "Gui.h"
//==================================================== Button ====================================================
//Initialization
void gui::Button::initPressedSound()
{
	if (!this->pressedSoundBuffer.loadFromFile("src/Resource/SoundFX/Button/click.ogg")) {
		throw("ERROR can't load pressedEffect");
	}
	this->pressedSound.setBuffer(this->pressedSoundBuffer);
}

//Constructor , Destructor
gui::Button::Button(float x, float y, float width, float height
	, sf::Font& font, std::string text, unsigned charector_size
	, sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color
	, sf::Color shape_idle_color, sf::Color shape_hover_color, sf::Color shape_active_color,
	short unsigned id) 
	: font(font)
{
	this->initPressedSound();

	this->buttonState = BUTTON_IDLE;
	this->id = id;
	this->charectorSize = charector_size;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	
	this->font = font;
	this->text.setFont(this->font);
	this->text.setString(text);
	this->text.setCharacterSize(charector_size);
	this->text.setPosition(
		this->shape.getPosition().x - this->text.getGlobalBounds().width / 2.0f + this->shape.getGlobalBounds().width / 2.0f,
		this->shape.getPosition().y - this->text.getGlobalBounds().height / 2.0f + this->shape.getGlobalBounds().height / 2.0f - this->charectorSize * 0.3f
	);
	
	this->shapeIdleColor = shape_idle_color;
	this->shapeHoverColor = shape_hover_color;
	this->shapeActiveColor = shape_active_color;
	
	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->shape.setFillColor(this->shapeIdleColor);
	this->text.setFillColor(this->textIdleColor);
}

gui::Button::~Button()
{
}

//Accessor
const bool gui::Button::isPressed()
{
	if (this->buttonState == BUTTON_ACTIVE) {
		return true;
	}

	return false;
}

const std::string gui::Button::getText()
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId()
{
	return this->id;
}

sf::Vector2f gui::Button::getSize()
{
	return this->shape.getSize();
}

sf::Vector2f gui::Button::getPosition()
{
	return this->shape.getPosition();
}

//Modifier
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

void gui::Button::setPosition(const float position_x, const float position_y)
{
	this->shape.setPosition(position_x, position_y);
	this->text.setPosition(
		this->shape.getPosition().x - this->text.getGlobalBounds().width / 2.0f + this->shape.getGlobalBounds().width / 2.0f,
		this->shape.getPosition().y - this->text.getGlobalBounds().height / 2.0f + this->shape.getGlobalBounds().height / 2.0f - this->charectorSize * 0.3f
	);
}

//Function
void gui::Button::updateButton(const sf::Vector2f& mousePosition)
{
	/*Update the booleans for hover and pressed*/
	//Idle
	this->buttonState = BUTTON_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePosition) || this->text.getGlobalBounds().contains(mousePosition)) {
		this->buttonState = BUTTON_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = BUTTON_ACTIVE;
		}
	}

	//Update the button
	if (this->buttonState == BUTTON_IDLE) {
		//update color
		this->shape.setFillColor(this->shapeIdleColor);
		this->text.setFillColor(this->textIdleColor);
	}
	else if (this->buttonState == BUTTON_HOVER) {
		//update color
		this->shape.setFillColor(this->shapeHoverColor);
		this->text.setFillColor(this->textHoverColor);
	}
	else if (this->buttonState == BUTTON_ACTIVE) {
		//update color
		this->shape.setFillColor(this->shapeActiveColor);
		this->text.setFillColor(this->textActiveColor);

		//play click sound
		if (this->pressedSound.getStatus() != sf::Sound::Playing) {
			this->pressedSound.play();
		}
	}
}

void gui::Button::renderButton(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}



//==================================================== Drop Down Box ====================================================
//Constructor , Destructor
gui::DropDownBox::DropDownBox(float x, float y, float width, float height, 
	sf::Font& font, std::string list[], unsigned num_Elements, unsigned default_index)
	:font(font), showList(false), keyTimeMax(10.0f), keyTime(0.0f)
{
	this->activeElement = new gui::Button(
		x, y, width, height,
		this->font, list[default_index], 25,
		sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255), sf::Color(0, 0, 0, 255),
		sf::Color(255, 255, 255, 200), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255),
		default_index
	);

	for (size_t i = 0; i < num_Elements; i++) {
		std::cout << i << std::endl;
		this->list.push_back(
			new gui::Button(
				x, y + ((i + 1) * height), width, height,
				this->font, list[i], 25,
				sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 255), sf::Color(0, 0, 0, 255),
				sf::Color(255, 255, 255, 200), sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255),
				i
			)
		);
	}
}

gui::DropDownBox::~DropDownBox()
{
	delete this->activeElement;
	
	for (size_t i = 0; i < this->list.size(); i++) {
		delete this->list[i];
	}
}

//Accessor
const bool gui::DropDownBox::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax) {
		this->keyTime = 0.0f;
		return true;
	}
	else {
		return false;
	}
}

const unsigned short & gui::DropDownBox::getActiveElementId()
{
	return this->activeElement->getId();
}

//Function
void gui::DropDownBox::updateDropDownBox(const float &dt, const sf::Vector2f & mousePosition)
{
	this->updateKeyTime(dt);

	this->activeElement->updateButton(mousePosition);
	
	//Show and hide the list
	if (this->activeElement->isPressed() && this->getKeyTime()) {
		if (this->showList) {
			this->showList = false;
		}
		else {
			this->showList = true;
		}
	}

	if (this->showList) {
		for (auto &i : this->list) {
			i->updateButton(mousePosition);

			if (i->isPressed() && this->getKeyTime()) {
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}
}

void gui::DropDownBox::updateKeyTime(const float &dt)
{
	if (this->keyTime < this->keyTimeMax) {
		this->keyTime += 50.0f * dt;
	}
}

void gui::DropDownBox::renderDropDownBox(sf::RenderTarget & target)
{
	this->activeElement->renderButton(target);
	
	if (this->showList) {
		for (auto &i : this->list) {
			i->renderButton(target);
		}
	}
}
