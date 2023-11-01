#pragma once
#include "GlobalConnsts.h"
#include "Block.h"


class Map {
private:
	Block * map[mapWidth][mapHeight];
public:
	Map();
	void generateLabyrinth();

	void draw(sf::RenderWindow& window);
};