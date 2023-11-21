#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalVariablesForResources.h"

sf::Cursor cursor;
sf::Image imageCursor;

json tasks;

sf::Texture texture_window;
sf::Texture texture_window2;
sf::Texture texture_window3;
sf::Texture texture_window4;
sf::Texture texture_window5;


sf::Texture texture_block_wall[maxIdTextres];
sf::Texture texture_block_door[maxIdTextres];
sf::Texture texture_block_ladder[maxIdTextres];

sf::Texture texture_wall_left;
sf::Texture texture_wall_right;
sf::Texture texture_person;
sf::Texture texture_person_left;

sf::Texture texture_slider_pic_music;
sf::Texture texture_slider_pic_sound;
sf::Texture texture_slider;
sf::Texture texture_slider_track;

sf::Texture texture_cursor;

sf::Font master_font;

int Menu = menu_main;

int sizeBlock = 50;

float playerHeight;
float playerWidth;
float speed_player = 0.5;
int Y_start_climbing = -1;


float scrollX = 0;
float scrollY = 0;

sf::Color ColorForButton(255, 161, 109, 150);
sf::Color ColorForButtonLine(227, 136, 86, 150);
sf::Color ColorForHoverButton(248, 132, 89, 150);
sf::Color ColorForHoverButtonLine(220, 107, 55, 150);
sf::Color ColorForPressedButton(243, 110, 55, 150);
sf::Color ColorForPressedButtonLine(215, 85, 32, 150);

sf::Color ColorForButtonDesk(62, 130, 63, 255);
sf::Color ColorForButtonDeskLine(20, 87, 21, 255);
sf::Color ColorForHoverButtonDesk(102, 163, 103, 255);
sf::Color ColorForHoverButtonDeskLine(62, 130, 63, 255);
sf::Color ColorForPressedButtonDesk(20, 87, 21);
sf::Color ColorForPressedButtonDeskLine(10, 76, 11, 255);

sf::Color color_door_title(255,255,255);

int test_amnt = 0;
std::vector<rslt_pair> easy_best_marks;
std::vector<rslt_pair> normal_best_marks;
std::vector<rslt_pair> hard_best_marks;
std::vector<rslt_pair> last_marks;
std::vector<rslt_pair> curr_marks;  
std::string last_difficulty = "";
int game_sessions = 0;

bool isReadedGood = true;


