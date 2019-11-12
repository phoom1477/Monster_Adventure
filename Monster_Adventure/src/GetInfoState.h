//////////////////////////////////////////////////
//	Object list that used by dynamic allocated  //
//		- buttons								//
//////////////////////////////////////////////////

#pragma once

#include "State.h"
#include "GameState.h"
#include "Gui.h"
#include <sstream>

class GetInfoState : public State
{
private:
	//Variable
	std::string inputName;
	short unsigned previewIndex;

	//Resource
	std::vector <sf::RectangleShape> previewPlayer;
	sf::Text previewName;


	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	sf::Font font;
	sf::Font temporaryFont;
	std::map<std::string, gui::Button*> buttons;

	sf::Event event;
	sf::Clock timer;
	bool cursor;

	//Initialization
	void initVariable();
	void initFonts();
	void initKeybinds();
	void initPreviewName();
	void initPreviewPlayer();
	void initButton();
	void initBackground();
		
public:
	GetInfoState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GetInfoState();

	//update
	void updateState(const float &dt);
	void updateInput(const float &dt);
	void updateButton();
	void updatePreviewName(const std::string name);
	void updateName();
	void updatePreviewPlayer();
	
	//render
	void renderState(sf::RenderTarget* target = NULL);
	void renderButton(sf::RenderTarget& target);
};

