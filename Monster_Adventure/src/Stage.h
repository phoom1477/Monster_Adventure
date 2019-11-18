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

class Stage
{
private:
	//Variable1
	bool clear;

	//Variable2
	sf::RenderWindow *window;

	//Resource1
	Player *player;
	std::vector<Enemy*> enemy;
	
	//Resource2
	sf::Texture background_texture;
	std::vector<sf::RectangleShape> background;

	//Initialization
	void initVariable();

public:
	//Contructor , Destructor
	Stage(sf::RenderWindow* window, Player *player);
	virtual ~Stage();

	//Accessor
	const bool& getClear();
	std::vector<Enemy*>& getEnemy();

	const sf::Vector2f getStageSize();

	//Function
	void addBackground(short unsigned background_id);
	void addEnemy(const float x, const float y, sf::Texture& texture_sheet, std::string id);

	//update
	void updateStage(const float& dt);
	void updateEnemy(const float &dt);
	void updateEnemyControl(const float& dt);

	//render
	void renderStage(sf::RenderTarget* target = NULL);
};

