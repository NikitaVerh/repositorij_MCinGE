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
	if (!texture_block_wall.loadFromFile("Resources/textures/blocks/texture_wall.png")); //колян
	if (!texture_block_door.loadFromFile("Resources/textures/blocks/texture_door.png")); //колян
	if (!texture_block_ladder.loadFromFile("Resources/textures/blocks/texture_ladder.png")); //колян
	if (!texture_wall_left.loadFromFile("Resources/textures/blocks/texture_wall_left.png")); //колян
	if (!texture_wall_right.loadFromFile("Resources/textures/blocks/texture_wall_right.png")); //колян
	if (!texture_window.loadFromFile("Resources/textures/interface/background.png")); //колян

	master_font.loadFromFile("Resources/fonts/testFont.ttf");//колян

	ButtonTest->setPosSize(0.49, 0.3, 0.2, 0.05);

	ButtonTest->setStyle(L"Почати", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonTest2->setStyle(L"Назад", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));

	ButtonTest2->setPosSize(0.1, 0.5, 0.2, 0.05);

	Form1.addInterfaceObj(ButtonTest);
	Form2.addInterfaceObj(ButtonTest2);
	Form1.initializeBackground(texture_window);

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


	switch (Menu){
	case menu_main:
		if (ButtonTest->Pressed()) { std::cout << "pressed" << std::endl; }
		if (ButtonTest->Released()) { std::cout << "released" << std::endl; Menu = menu_game; }
		break;
	case menu_game:
		if (ButtonTest2->Released()) { std::cout << "released" << std::endl; Menu = menu_main; GameMap.generateLabyrinth(); }
		break;
	default:
		break;
	}
}

// метод для оновлення інтерфейсу
void UpdateGraphic(sf::RenderWindow& window) {
	window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));

	sizeBlock = window.getSize().y / float(mapHeight);
	Form1.updateForm(window);
	Form2.updateForm(window);

}

// метод для відображення графіки
void GraphicRender(sf::RenderWindow& window) {

	window.clear();
	if (Menu == menu_main) {
		Form1.drawBackground(window);
		Form1.draw(window);
	}
	if (Menu == menu_game) {
		GameMap.draw(window);
		Form2.draw(window);
	}
	window.display();
}