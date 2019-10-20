#include "Button.h"

//Constructor , Destructor
Button::Button(float x, float y, float width, float height
	, sf::Font& font, std::string text, unsigned charector_size
	, sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color
	, sf::Color shape_idle_color, sf::Color shape_hover_color, sf::Color shape_active_color) : font(font)
{
	/*Constructor with shape*/
	this->buttonState = BUTTON_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	
	this->font = font;
	this->text.setFont(this->font);
	this->text.setString(text);
	this->text.setCharacterSize(charector_size);
	this->text.setPosition(
		this->shape.getPosition().x - this->text.getGlobalBounds().width / 2.0f + this->shape.getGlobalBounds().width / 2.0f,
		this->shape.getPosition().y - this->text.getGlobalBounds().height / 2.0f + this->shape.getGlobalBounds().height / 2.0f - charector_size * 0.3f
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

Button::~Button()
{
}

//Accessor
const bool Button::isPressed()
{
	if (this->buttonState == BUTTON_ACTIVE) {
		return true;
	}

	return false;
}

//Function
void Button::updateButton(sf::Vector2f mousePosition)
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
		this->shape.setFillColor(this->shapeIdleColor);
		this->text.setFillColor(this->textIdleColor);
	}
	else if (this->buttonState == BUTTON_HOVER) {
		this->shape.setFillColor(this->shapeHoverColor);
		this->text.setFillColor(this->textHoverColor);
	}
	else if (this->buttonState == BUTTON_ACTIVE) {
		this->shape.setFillColor(this->shapeActiveColor);
		this->text.setFillColor(this->textActiveColor);
	}
}

void Button::renderButton(sf::RenderTarget * target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
