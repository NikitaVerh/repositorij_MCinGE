#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalVariablesForResources.h"


class Block {
protected:
	sf::RectangleShape Area;	
public:
	virtual sf::RectangleShape getBlockForDraw() = 0;
};

class BlockWall : public Block {
public:
	BlockWall() {
		//Area.setTextureRect(sf::IntRect(0, 0, texture_block_wall.getSize().x, texture_block_wall.getSize().y));
		Area.setTexture(&texture_block_wall);
	}
	sf::RectangleShape getBlockForDraw() override {
		return Area;
	}
};

class BlockDoor : public Block {
public:
	BlockDoor() {}
	sf::RectangleShape getBlockForDraw() override {}
};

class BlockLadder : public Block {
public:
	BlockLadder() {}
	sf::RectangleShape getBlockForDraw() override {}
};

