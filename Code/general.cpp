#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "GlobalVariables.h"
//#include "fileForIlla.cpp"
//#include "fileForAlisa.cpp"
//#include "fileForNikolai.cpp"
//#include "fileForNikita.cpp"

// метод що виконується один раз при старті програми

void startProgram() {
	if (!texture_window.loadFromFile("Resources/textures/interface/background.png")) std::cout << "d"; //колян
	background.setTexture(&texture_window);
}

// метод для обробки подій вікна
void windowEventHandling(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		
	}
}
void GraphicRender(sf::RenderWindow& window) {
	window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));
	background.setSize(sf::Vector2f((45 * window.getSize().y) / 19.0, window.getSize().y));
	background.setPosition((window.getSize().x - background.getSize().x) / 6.0, 0);
	window.clear();
	window.draw(background);
	window.display();
}