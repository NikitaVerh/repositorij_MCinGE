#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


// метод для обробки подій вікна
void windowEventHandling(sf::RenderWindow& window);

void GraphicRender(sf::RenderWindow& window);

// метод що виконується один раз при старті програми
void startProgram();
