#pragma once
#include "map.h"
#include "GlobalVariablesForResources.h"
#include "GlobalVariablesOfClasses.h"

void Map::generateLabyrinth() {
	for (int i = 0; i < mapWidth; i++) {
		for (int j = 0; j < mapHeight; j++) {
			setBlock(i, j, new BlockWall());

		}
	}

	setBlock(1, 0, new BlockLadder());
}

void Map::draw(sf::RenderWindow& window) {
	for (int i = 0; i < mapWidth; i++) {
		for (int j = 0; j < mapHeight; j++) {
			sf::RectangleShape block = map[i][j]->getBlockForDraw();
			block.setPosition(sf::Vector2f(i*sizeBlock,j*sizeBlock));
			block.setSize(sf::Vector2f(sizeBlock, sizeBlock));
			
			window.draw(block);
		}
	}
}

Map::Map() {
	for (int i = 0; i < mapWidth; i++) {
		for (int j = 0; j < mapHeight; j++) {
			map[i][j] = NULL;
		}
	}
}

void Map::setBlock(int i, int j, Block* block) {
	if (map[i][j] != NULL) { delete(map[i][j]); }
	map[i][j] = block;
}

Block& Map::getMapBlock(int i, int j) {
	if (i >= 0 && i < mapWidth && j >= 0 && j < mapHeight) {
		return *map[i][j];
	}
}