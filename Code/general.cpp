/*
В цьому файлі йде реалізація головних методів
*/

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GlobalVariablesForResources.h"
#include "GlobalVariablesOfClasses.h"


//тимчасові бібліотеки
#include <iostream>



// метод що виконується один раз при старті програми
void startProgram() {
	Form1.addInterfaceObj(ButtonTest);

	if (!texture_block_wall.loadFromFile("Resources/textures/blocks/texture_wall.png")); //колян
	if (!texture_block_door.loadFromFile("Resources/textures/blocks/texture_door.png")); //колян
	if (!texture_block_ladder.loadFromFile("Resources/textures/blocks/texture_ladder.png")); //колян

	if (!texture_window.loadFromFile("Resources/textures/interface/background.png")) std::cout << "d"; //колян
	background.setTexture(&texture_window);

	GameMap = Map(); // створюватися ця змінна повинна після загрузки текстр
	GameMap.generateLabyrinth();
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
	GameMap.draw(window);
	Form1.draw(window);
	window.display();
}