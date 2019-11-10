//////////////////////////////////////////////////
//	Object list that used by dynamic allocated  //
//		- buttons								//
//		- dropdownbox							//
//////////////////////////////////////////////////

#pragma once

#include "State.h"
#include "Gui.h"

class SettingState :
	public State
{
private:
	//Variable
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	sf::Font font;
	std::map<std::string, gui::Button*> buttons;
	/*std::map<std::string, gui::DropDownBox*> dropDownBoxs;*/

	/*sf::Text optionText;
	std::vector<sf::VideoMode> videoModes;*/
	//Initialization
	void initVariable();
	void initFonts();
	void initKeybinds();
	void initGui();
	void initBackground();
	void InitText();

public:
	//Constructor , Destructor
	SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~SettingState();

	//Accessor

	//Function

	//update
	void updateState(const float &dt);
	void updateInput(const float &dt);
	void updateGui(const float &dt);

	//render
	void renderState(sf::RenderTarget* target = NULL);
	void renderGui(sf::RenderTarget& target);
};

