#pragma once
#include <SFML/Graphics.hpp>
#include "interfaceObj.h"

const int mapWidth = 7;
const int mapHeight = 5;


sf::RectangleShape background(sf::Vector2f(800, 500));
sf::Texture texture_window;

Form Form1;
Button* ButtonTest = new Button();