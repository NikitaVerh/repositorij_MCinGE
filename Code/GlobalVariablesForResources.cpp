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
sf::Texture texture_person;

sf::Font master_font;

int Menu = menu_main;

int sizeBlock = 50;

float playerHeight;
float playerWidth;
float speed_player = 0.5;
int Y_start_climbing = -1;
bool moving_flag = false;
std::string currentDifficulty = "easy"; // Текущий уровень сложности


float scrollX = 0;
float scrollY = 0;

sf::Color color_door_title(255,255,255);