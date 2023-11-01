#pragma once
#include "GlobalConnsts.h"
#include "Block.h"


class Map {
private:
	Block* map[mapWidth][mapHeight];
public:
	Map();
	void generateLabyrinth();

	void draw(sf::RenderWindow& window);

	void setBlock(int i, int j, Block* block);

	
	Block& getMapBlock(int i, int j);
};