#pragma once
#include "nlohmann/json.hpp"
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "GlobalConnsts.h"

extern sf::Cursor cursor;
extern sf::Image imageCursor;
extern sf::Image icon;

using json = nlohmann::json;

extern sf::Texture texture_window;
extern sf::Texture texture_window2;
extern sf::Texture texture_window3;
extern sf::Texture texture_window4;
extern sf::Texture texture_window5;

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

extern sf::Color ColorForButtonBoard;
extern sf::Color ColorForButtonBoardLine;
extern sf::Color ColorForHoverButtonBoard;
extern sf::Color ColorForHoverButtonBoardLine;
extern sf::Color ColorForPressedButtonBoard;
extern sf::Color ColorForPressedButtonBoardLine;

extern sf::Color ColorForButtonGame;
extern sf::Color ColorForButtonGameLine;
extern sf::Color ColorForHoverButtonGame;
extern sf::Color ColorForHoverButtonGameLine;
extern sf::Color ColorForPressedButtonGame;
extern sf::Color ColorForPressedButtonGameLine;

extern sf::Color color_door_title;

extern sf::Color color_button;
extern sf::Color color_menu;
extern sf::Color color_board;

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


extern bool isReadedGood;



extern sf::Sound SoundClick_in;
extern sf::Sound SoundClick_out;
extern sf::Sound SoundCorrect;
extern sf::Sound SoundWrong;
extern sf::Sound SoundDoor_open;
extern sf::Sound SoundStep[maxStepSounds];

extern sf::SoundBuffer sbclick_in;
extern sf::SoundBuffer sbclick_out;
extern sf::SoundBuffer sbcorrect;
extern sf::SoundBuffer sbwrong;
extern sf::SoundBuffer sbdoor_open;
extern sf::SoundBuffer sbstep[maxStepSounds];

extern sf::Music music[maxMusicTracks];