#include "State.h"

//Initialization
void State::initVariable()
{
	this->quit = false;
}

//Constructor , Destructor
State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	this->initVariable();

	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
}

State::~State()
{

}

//Accessor
const bool& State::getQuit()
{
	return this->quit;
}

//Function
void State::updateMousePosition()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}


