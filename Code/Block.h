#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalVariablesForResources.h"
#include <string>


class Block {
protected:
    std::string theme;
    bool WallLeft = false;
    bool WallRight = false;
    sf::RectangleShape Area;
    int idTexture = 0;
public:
    virtual sf::RectangleShape getBlockForDraw() = 0;
    virtual int getTypeBlock() = 0;

    std::string getTheme() {
        return theme;
    }

    void setIdTexture(int value) { idTexture = value; }
    int getIdTexture() { return idTexture; }

   
 void setTheme(std::string chsn_theme) {
        theme = chsn_theme;
    }

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
        idTexture = rand() % maxIdTextres;
        Area.setTexture(&texture_block_wall[idTexture]);
    }
    sf::RectangleShape getBlockForDraw() override {
        return Area;
    }

    int getTypeBlock() override { return type_block_wall; }
};



class BlockDoor : public Block {
public:
    BlockDoor() {
        theme = "";
        idTexture = rand() % maxIdTextres;
        Area.setTexture(&texture_block_door[idTexture]);
    }
    sf::RectangleShape getBlockForDraw() override {
        return Area;
    }
    int getTypeBlock() override { return type_block_door; }
    
};



class BlockLadder : public Block {
public:
    BlockLadder() {
        idTexture = rand() % maxIdTextres;
        Area.setTexture(&texture_block_ladder[idTexture]);
    }
    sf::RectangleShape getBlockForDraw() override {
        return Area;
    }

    int getTypeBlock() override { return type_block_ladder; }
};