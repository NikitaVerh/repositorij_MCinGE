#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalVariablesForResources.h"

json tasks;

sf::Texture texture_window;
sf::Texture texture_window3;


sf::Texture texture_block_wall;
sf::Texture texture_block_door;
sf::Texture texture_block_ladder;

sf::Texture texture_wall_left;
sf::Texture texture_wall_right;

sf::Font master_font;

int Menu = menu_main;

int sizeBlock = 50;
std::string currentDifficulty = "easy"; // Текущий уровень сложности