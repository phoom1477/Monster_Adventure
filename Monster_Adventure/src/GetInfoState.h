//////////////////////////////////////////////////
//	Object list that used by dynamic allocated  //
//		- buttons								//
//////////////////////////////////////////////////

#pragma once

#include "State.h"
#include "GameState.h"
#include "Gui.h"

class GetInfoState : public State
{
private:
	//Variable
	std::string playerName;
	short unsigned playerIndex;

	//Resource
	std::map<std::string, sf::Texture> textures;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	sf::Text descriptText;
	sf::Text previewName;
	std::vector <sf::RectangleShape> previewPlayer;

	sf::Font font;
	sf::Font temporaryFont;
	std::map<std::string, gui::Button*> buttons;

	sf::Event eventType;
	sf::Clock timer;
	bool showCursor;

	//Initialization
	void initVariable();

	void initKeybinds();
	void initFonts();

	void initBackground();
	void initDescriptText();

	void initPreviewName();
	void initPreviewPlayer();

	void initButton();
		
public:
	//Constructor , Destructor
	GetInfoState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GetInfoState();

	//update
	void updateState(const float &dt);
	void updateInput(const float &dt);

	void updateButton();

	void updateName();
	void updatePreviewName(const std::string name); 
	void updatePreviewPlayer();

	//render
	void renderState(sf::RenderTarget* target = NULL);
	void renderButton(sf::RenderTarget& target);
};

