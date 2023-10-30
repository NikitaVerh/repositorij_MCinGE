/*
В цьому файлі йде реалізація головних методів
*/

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GlobalVariables.h"
#include "interfaceObj.h"

//тимчасові бібліотеки
#include <iostream>



// метод що виконується один раз при старті програми
void startProgram() {
	Form1.addInterfaceObj(ButtonTest);

	if (!texture_window.loadFromFile("Resources/textures/interface/background.png")) std::cout << "d"; //колян
	background.setTexture(&texture_window);
}

// метод що виконується один раз перед закриттям программи
void stopProgram(sf::RenderWindow& window) {

	window.close();
}

// метод для обробки подій вікна
void windowEventHandling(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (sf::Event::Closed == event.type) { stopProgram(window); }
		
	}
}

// метод для оновлення інтерфейсу
void UpdateGraphic(sf::RenderWindow& window) {
	window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));

	background.setSize(sf::Vector2f((45 * window.getSize().y) / 19.0, window.getSize().y));
	background.setPosition((window.getSize().x - background.getSize().x) / 6.0, 0);
}

// метод для відображення графіки
void GraphicRender(sf::RenderWindow& window) {
	window.clear();
	window.draw(background);
	Form1.draw(window);
	window.display();
}