#pragma once
#include <SFML/Graphics.hpp>

extern sf::Texture texture_window;
extern sf::Texture texture_window3;

extern sf::Texture texture_block_wall;
extern sf::Texture texture_block_door;
extern sf::Texture texture_block_ladder;

extern sf::Texture texture_wall_left;
extern sf::Texture texture_wall_right;

extern int sizeBlock;

extern sf::Font master_font;

extern int Menu;

enum {
	type_block_wall,
	type_block_door,
	type_block_ladder
};

enum {
	menu_main,
	menu_game,
	menu_test
};

enum {
	theme_high_math

};