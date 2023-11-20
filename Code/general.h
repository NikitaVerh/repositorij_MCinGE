/*
В цьому файлі ініціалізуються головні методи
*/


#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


// метод для обробки подій вікна
void windowEventHandling(sf::RenderWindow& window);

// метод що виконується один раз перед закриттям программи
void stopProgram(sf::RenderWindow& window);

void updateMehanics(sf::Time delta_time);

void setMenu(int menu);

// метод для відображення графіки
void GraphicRender(sf::RenderWindow& window);

// метод для оновлення інтерфейсу
void UpdateGraphic(sf::RenderWindow& window);

// метод що виконується один раз при старті програми
void startProgram();

void restart_all();

void update_statistics();

void setMenu(int menu);