#pragma once
#include "GlobalVariables.h"
#include "Block.h"


class Map {
private:
	Block * map[mapWidth][mapHeight];
public:

	void generateLabyrinth();
};