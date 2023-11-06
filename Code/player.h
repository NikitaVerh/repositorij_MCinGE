#pragma once
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include <SFML/System.hpp>
#include "GlobalVariablesForResources.h"
#include "GlobalConnsts.h"

class Hitbox {
private:
	static bool showHitbox; // змінна для тестування і перевірки, показ всіх хітбоксів
	sf::FloatRect hitbox;
public:

	Hitbox() {
		setSizePos(0, 0, 1, 1);
	}

	Hitbox(float x, float y, float w, float h) { 
		setSizePos(x, y, w, h); 
	}

	void setSizePos(float x, float y, float w, float h) {
		hitbox.left = x;
		hitbox.top = y;
		hitbox.width = w;
		hitbox.height = h;
	}

	sf::FloatRect getRect() {
		return hitbox;
	}

	bool collision(Hitbox& secondHitBox) {
		return hitbox.intersects(secondHitBox.getRect());
	}

	void draw(sf::RenderWindow& window) {
		if (!showHitbox) { return; }

		sf::RectangleShape rect;

		rect.setPosition(hitbox.left * sizeBlock + scrollX, hitbox.top * sizeBlock + scrollY);
		rect.setSize(sf::Vector2f(hitbox.width * sizeBlock, hitbox.height * sizeBlock));
		rect.setFillColor(sf::Color(0, 0, 0, 0));
		rect.setOutlineColor(sf::Color(255,0,0,180));
		rect.setOutlineThickness(1);
		window.draw(rect);
	}

};

class Player {
private:
	sf::RectangleShape player_pers;
	float x, y;
	Hitbox hitbox;
	bool checkColision(float dx);
	sf::Time delta_time;
public:
	Player() {
		Player_set_source();	
	}
	void Player_set_source() {
		x = 0.3;
		y = mapHeight - 0.01;
	}
	void set_pos_hitbox_player();
	void set_time(sf::Time delta_time);
	void Update();
	void move(float dx, float dy);
	void openDoor();
	void drawPlayer(sf::RenderWindow& window);
};
