#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "general.h"

void Run(sf::RenderWindow& window, sf::Clock& delta_time_clock);

void HandleInput(sf::RenderWindow& window);
void Update(sf::Time delta_time);
void Render(sf::RenderWindow& window);

