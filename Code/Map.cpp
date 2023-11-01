#pragma once
#include "map.h"
#include "GlobalVariablesForResources.h"

void Map::generateLabyrinth() {
	for (int i = 0; i < mapWidth; i++) {
		for (int j = 0; j < mapHeight; j++) {
			map[i][j] = new BlockWall();
		}
	}
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
			map[i][j] = new BlockWall();
		}
	}
}