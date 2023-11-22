#pragma once
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include <SFML/System.hpp>
#include "GlobalVariablesForResources.h"
#include "GlobalConnsts.h"
#include "Hitbox.h"
#include "timer.h"

class Player {
private:
	sf::RectangleShape player_pers;
	float x, y;  
	Hitbox hitbox;
	sf::Time delta_time;
	int frame;
	Timer interval_standing;
	Timer interval_walking;
	Timer interval_walking_sound;
	bool mov_flag = false;
	int state = 0;
	int prev_state = 0;
	bool rotate = false;
	bool checkColision(float dx);
public:
	float getX() { return x; }
	float getY() { return y; }
	void setX(float value) { x = value; }
	void setY(float value) { y = value; }
	// конструктор класа гравц€
	Player();

	// встановленн€ поатковоњ позиц≥њ гравц€
	void Player_set_source();

	// встановленн€ х≥тбоксу гравц€ в≥дносно гравц€
	void set_pos_hitbox_player();

	// метод дл€ отриманн€ часу останнього кадру
	void set_time(sf::Time delta_time);

	// оновленн€ гравц€
	void Update();

	// метод дл€ руху гравц€
	void move(float dx, float dy);

	// метод дл€ в≥дкритт€ дверей гравцем
	void openDoor();

	// метод дл€ рендеру гравц€ на в≥кн≥
	void drawPlayer(sf::RenderWindow& window);

	void skipFrame();
};
