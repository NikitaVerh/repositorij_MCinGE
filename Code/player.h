#pragma once
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include <SFML/System.hpp>
#include "GlobalVariablesForResources.h"

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

		rect.setPosition(hitbox.left * sizeBlock, hitbox.top * sizeBlock);
		rect.setSize(sf::Vector2f(hitbox.width * sizeBlock, hitbox.height * sizeBlock));
		rect.setFillColor(sf::Color(0, 0, 0, 0));
		rect.setOutlineColor(sf::Color(255,0,0,180));
		rect.setOutlineThickness(1);
		window.draw(rect);
	}

};

class Player {
private:
	float x, y;
	Hitbox hitbox;
	
	bool checkColision();
public:
	void Update();
	void move(float dx, float dy);
	void openDoor();
	void drawPlayer(sf::RenderWindow& window);
};
