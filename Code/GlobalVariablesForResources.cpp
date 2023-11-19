#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalVariablesForResources.h"

json tasks;

sf::Texture texture_window;
sf::Texture texture_window2;
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


sf::Color ColorForButton(187, 157, 141, 255);
sf::Color ColorForButtonLine(156, 119, 107, 255);
sf::Color ColorForHoverButton(204, 180, 167, 255);
sf::Color ColorForHoverButtonLine(169, 139, 129, 255);
sf::Color ColorForPressedButton(164, 134, 118, 255);
sf::Color ColorForPressedButtonLine(143, 106, 94, 255);

sf::Color ColorForButtonDesk(62, 130, 63, 255);
sf::Color ColorForButtonDeskLine(20, 87, 21, 255);
sf::Color ColorForHoverButtonDesk(102, 163, 103, 255);
sf::Color ColorForHoverButtonDeskLine(62, 130, 63, 255);
sf::Color ColorForPressedButtonDesk(20, 87, 21);
sf::Color ColorForPressedButtonDeskLine(10, 76, 11, 255);