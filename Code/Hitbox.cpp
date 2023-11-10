#pragma once
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include "GlobalVariablesForResources.h"
#include "GlobalConnsts.h"
#include "Hitbox.h"

// конструктор хітбоксу
Hitbox::Hitbox() {
	setSizePos(0, 0, 1, 1);
}

// конструктор хітбоксу з параметрами положення і розміру
Hitbox::Hitbox(float x, float y, float w, float h) {
	setSizePos(x, y, w, h);
}

// метод для встановлення положення і розмірів хітбоксу
void Hitbox::setSizePos(float x, float y, float w, float h) {
	hitbox.left = x;
	hitbox.top = y;
	hitbox.width = w;
	hitbox.height = h;
}

// метод для отримання з хітбоксу прямокутника
sf::FloatRect Hitbox::getRect() {
	return hitbox;
}

// перевірка перетину хітбоксів
bool Hitbox::collision(Hitbox& secondHitBox) {
	return hitbox.intersects(secondHitBox.getRect());
}

// метод для відображення хітбоксу
void Hitbox::draw(sf::RenderWindow& window) {
	if (!showHitbox) { return; }

	sf::RectangleShape rect;

	rect.setPosition(hitbox.left * sizeBlock + scrollX, hitbox.top * sizeBlock + scrollY);
	rect.setSize(sf::Vector2f(hitbox.width * sizeBlock, hitbox.height * sizeBlock));
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	rect.setOutlineColor(sf::Color(255, 0, 0, 180));
	rect.setOutlineThickness(1);
	window.draw(rect);
}
