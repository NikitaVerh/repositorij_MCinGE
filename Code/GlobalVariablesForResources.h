#pragma once
#include "nlohmann/json.hpp"
#include <SFML/Graphics.hpp>
#include "GlobalConnsts.h"

extern sf::Cursor cursor;
extern sf::Image imageCursor;

using json = nlohmann::json;

extern sf::Texture texture_window;
extern sf::Texture texture_window2;
extern sf::Texture texture_window3;

extern sf::Texture texture_block_wall[maxIdTextres];
extern sf::Texture texture_block_door[maxIdTextres];
extern sf::Texture texture_block_ladder[maxIdTextres];

extern sf::Texture texture_wall_left;
extern sf::Texture texture_wall_right;
extern sf::Texture texture_person;
extern sf::Texture texture_person_left;

extern sf::Texture texture_slider_pic_music;
extern sf::Texture texture_slider_pic_sound;
extern sf::Texture texture_slider;
extern sf::Texture texture_slider_track;


extern sf::Texture texture_cursor;

extern int sizeBlock;

extern sf::Font master_font;

extern int Menu;  

extern json tasks;

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

extern sf::Color color_door_title;

struct rslt_pair {
	int mark = 0;
	std::string theme = "";
	rslt_pair(int st_mrk, std::string st_thm) {
		mark = st_mrk;
		theme = st_thm;
	}
};
extern int test_amnt;
extern std::vector<rslt_pair> easy_best_marks;
extern std::vector<rslt_pair> normal_best_marks;
extern std::vector<rslt_pair> hard_best_marks;
extern std::vector<rslt_pair> last_marks;
extern std::vector<rslt_pair> curr_marks;
extern std::string last_difficulty;
extern int game_sessions;




