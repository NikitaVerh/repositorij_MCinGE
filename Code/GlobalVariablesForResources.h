#pragma once
#include <SFML/Graphics.hpp>

extern sf::RectangleShape background; // עטלקאסמגמ

extern sf::Texture texture_window;


extern sf::Texture texture_block_wall;
extern sf::Texture texture_block_door;
extern sf::Texture texture_block_ladder;

extern sf::Texture texture_wall_left;
extern sf::Texture texture_wall_right;

extern int sizeBlock;

enum {
	type_block_wall,
	type_block_door,
	type_block_ladder
};