#pragma once
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include "GlobalVariablesForResources.h"
#include "GlobalConnsts.h"

class Hitbox {
private:
	static bool showHitbox; // змінна для тестування і перевірки, показ всіх хітбоксів
	sf::FloatRect hitbox;
public:
	// конструктор хітбоксу
	Hitbox();
	
	// конструктор хітбоксу з параметрами положення і розміру
	Hitbox(float x, float y, float w, float h);
	
	// метод для встановлення положення і розмірів хітбоксу
	void setSizePos(float x, float y, float w, float h);
	
	// метод для отримання з хітбоксу прямокутника
	sf::FloatRect getRect();

	// перевірка перетину хітбоксів
	bool collision(Hitbox& secondHitBox);

	// метод для відображення хітбоксу
	void draw(sf::RenderWindow& window);
};