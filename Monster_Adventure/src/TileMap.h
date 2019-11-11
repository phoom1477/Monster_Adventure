#pragma once

#include "Tile.h"

class TileMap
{
private:
	//Resource
	std::vector<std::vector<std::vector<Tile>>> map;
	sf::Vector2u maxSize;
	unsigned layers;

	//Variable
	unsigned gridSizeU;

public:
	TileMap();
	virtual ~TileMap();
};

