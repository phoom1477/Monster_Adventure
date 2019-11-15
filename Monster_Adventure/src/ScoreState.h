//////////////////////////////////////////////////
//	Object list that used by dynamic allocated  //
//		- buttons								//
//////////////////////////////////////////////////

#pragma once

#include "State.h"
#include "Gui.h"

#include <algorithm>

class ScoreState : public State
{

private:
	//Variable
	std::vector<std::pair<std::string, int>> getScore;

	//Resource
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::RectangleShape container;

	sf::Font font;
	std::map<std::string, gui::Button*> buttons;

	sf::Text descriptText;
	sf::Text rankNameText;
	sf::Text rankScoreText;
	
	//Initialization
	void initKeybinds();
	void initFonts();

	void initScore();

	void initBackground();
	void initContainer();
	void initDescriptText();
	void initRankText();

	void initButtons();

	//Function
	void bubbleSortScore();
	void swap(std::pair<std::string, int>* pair_x, std::pair<std::string, int>* pair_y);

public:
	//Constructor , Destructor
	ScoreState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~ScoreState();

	//update
	void updateState(const float &dt);
	void updateInput(const float &dt);
	void updateButton();

	//render
	void renderState(sf::RenderTarget* target = NULL);
	void renderButton(sf::RenderTarget& target);
};

