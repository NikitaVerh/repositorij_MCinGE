#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalVariablesForResources.h"


class Block {
protected:
    bool WallLeft = false;
    bool WallRight = false;
    sf::RectangleShape Area;
public:
    virtual sf::RectangleShape getBlockForDraw() = 0;

    void setWallLeft(bool value) {
        WallLeft = value;
    }

    void setWallRight(bool value) {
        WallRight = value;
    }

    bool getWallLeft() { return WallLeft; }
    bool getWallRight() { return WallRight; }
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
    BlockDoor() {
        Area.setTexture(&texture_block_door);
    }
    sf::RectangleShape getBlockForDraw() override {
        return Area;
    }
};

class BlockLadder : public Block {
public:
    BlockLadder() {
        Area.setTexture(&texture_block_ladder);
    }
    sf::RectangleShape getBlockForDraw() override {
        return Area;
    }
};