#pragma once
#include "nlohmann/json.hpp"
#include <SFML/Graphics.hpp>

using json = nlohmann::json;

extern sf::Texture texture_window;
extern sf::Texture texture_window2;
extern sf::Texture texture_window3;

extern sf::Texture texture_block_wall;
extern sf::Texture texture_block_door;
extern sf::Texture texture_block_ladder;

extern sf::Texture texture_wall_left;
extern sf::Texture texture_wall_right;
extern sf::Texture texture_person;

extern int sizeBlock;

extern sf::Font master_font;

extern int Menu;

extern json tasks;

extern std::string currentDifficulty; // Текущий уровень сложности

enum {
	type_block_wall,
	type_block_door,
	type_block_ladder
};

enum {
	menu_main,
	menu_lobby,
	menu_game,
	menu_test,
	menu_stat,
	menu_inf
};

enum {
	theme_high_math,
	theme_linear_algebra, 
	theme_probality_theory
};

extern float playerHeight;
extern float playerWidth;
extern float speed_player;
extern int Y_start_climbing;
extern bool moving_flag;



extern float scrollX;
extern float scrollY;

extern sf::Color ColorForButton;
extern sf::Color ColorForButtonLine;
extern sf::Color ColorForHoverButton;
extern sf::Color ColorForHoverButtonLine;
extern sf::Color ColorForPressedButton;
extern sf::Color ColorForPressedButtonLine;

extern sf::Color ColorForButtonDesk;
extern sf::Color ColorForButtonDeskLine;
extern sf::Color ColorForHoverButtonDesk;
extern sf::Color ColorForHoverButtonDeskLine;
extern sf::Color ColorForPressedButtonDesk;
extern sf::Color ColorForPressedButtonDeskLine;