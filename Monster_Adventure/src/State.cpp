#include "State.h"

//Initialization
void State::initVariable()
{
	this->quit = false;
	this->paused = false;
	this->gameover = false;
	this->gamewin = false;
	this->keyTime = 0.0f;
	this->keyTimeMax = 10.0f;
}

//Constructor , Destructor
State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, std::map<std::string, sf::Sound>* musicList)
	:window(window), supportedKeys(supportedKeys), states(states), musicList(musicList)
{
	this->initVariable();
}

State::~State()
{
}

//Accessor
const bool& State::getQuit()
{
	return this->quit;
}

const bool State::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax) {
		this->keyTime = 0.0f;
		return true;
	}
	else {
		return false;
	}
}

//Function
void State::pausedState()
{
	this->paused = true;
	std::cout << "[ Paused State ]" << std::endl;
}

void State::unpausedState()
{
	this->paused = false;
	std::cout << "[ Unpaused State ]" << std::endl;
}

void State::gameOverState()
{
	this->gameover = true;
	std::cout << "[ Game Over ]" << std::endl;
}

void State::gameWinState()
{
	this->gamewin = true;
	std::cout << "[ Win ]" << std::endl;
}

void State::endState()
{
	this->quit = true;
	std::cout << "[ Quit State ]" << std::endl;
}

void State::updateKeyTime(const float &dt)
{
	if (this->keyTime < this->keyTimeMax) {
		this->keyTime += 50.f * dt;
	}
}

void State::updateMousePosition()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}







