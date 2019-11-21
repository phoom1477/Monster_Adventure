//////////////////////////////////////////////////
//	Object list that used by dynamic allocated  //
//		-enemy									//
//////////////////////////////////////////////////

#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <vector>

#include "Player.h"
#include "Enemy.h"
#include "Item.h"

class Stage
{
private:
	//Window
	sf::RenderWindow *window;
	sf::Font& font;

	//Variable
	bool clear;

	//Resource
	Player *player;
	std::vector<Enemy*> enemy;
	std::vector<Item*> item;

	sf::Texture background_texture;
	std::vector<sf::RectangleShape> background;

	//Initialization
	void initVariable();

public:
	//Contructor , Destructor
	Stage(sf::RenderWindow* window,sf::Font& font, Player *player);
	virtual ~Stage();

	//Accessor
	const sf::Vector2f getStageSize();

	const bool& getClear();
	std::vector<Enemy*>& getEnemy();

	//Function
	void addBackground(std::string background_id);
	void addEnemy(const float x, const float y, sf::Texture& texture_sheet, std::string id);

	//update
	void updateStage(const float& dt);
	void updateEnemy(const float &dt);
	void updateEnemyControl(const float& dt);
	void updateItem(const float& dt);
	void updateItemControl(const float& dt);

	//render
	void renderStage(sf::RenderTarget* target = NULL);
};

