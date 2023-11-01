#pragma once
#include "GlobalConnsts.h"
#include "Block.h"


class Map {
private:
	bool WallLeft = false;
	bool WallRight = false;

	Block* map[mapWidth][mapHeight];
public:
	Map();
	void generateLabyrinth();

	void draw(sf::RenderWindow& window);

	void setBlock(int i, int j, Block* block);

	void setWallLeft(bool value);
	void setWallRight(bool value);
	Block& getMapBlock(int i, int j);
};