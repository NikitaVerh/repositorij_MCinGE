#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalVariablesForResources.h"

sf::Cursor cursor;
sf::Image imageCursor;

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

sf::Color ColorForButton(255, 161, 117, 255);
sf::Color ColorForButtonLine(240, 131, 80, 255);
sf::Color ColorForHoverButton(245, 145, 98, 255);
sf::Color ColorForHoverButtonLine(223, 110, 56, 255);
sf::Color ColorForPressedButton(164, 134, 118, 255);
sf::Color ColorForPressedButtonLine(143, 106, 94, 255);

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