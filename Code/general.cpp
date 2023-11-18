/*
В цьому файлі йде реалізація головних методів
*/

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GlobalVariablesForResources.h"
#include "GlobalVariablesOfClasses.h"
#include "initializators.h"

//тимчасові бібліотеки
#include <iostream>


//обробка виняткових ситуацій врахована
// 
// метод що виконується один раз при старті програми
void startProgram() {
	try {
		loadResources();
		initializeVariables();
		initializeInterface();
	}
	catch (const ResourceLoadException& e) {
		std::cerr << "Помилка: " << e.what() << '\n';
	}
}

// метод що виконується один раз перед закриттям программи
void stopProgram(sf::RenderWindow& window) {

	window.close();
}

void updateMehanics(sf::Time delta_time) {
	player.set_time(delta_time);
	player.Update();
}

void setMenu(int menu) {
	Menu = menu;
}

// тимчасово ці змінні тут
bool button_left = false;
bool button_right = false;
bool button_up = false;
bool button_down = false;
bool button_interact = false;


// метод для обробки подій вікна
void windowEventHandling(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {

		if (sf::Event::Closed == event.type) { stopProgram(window); }
		if (sf::Event::KeyReleased == event.type) {
			if (event.key.code == sf::Keyboard::Key::Num1) { setMenu(menu_main); std::cout << "Menu: " << Menu << std::endl; }
			if (event.key.code == sf::Keyboard::Key::Num2) { setMenu(menu_lobby);  std::cout << "Menu: " << Menu << std::endl; }
			if (event.key.code == sf::Keyboard::Key::Num3) { setMenu(menu_game);  std::cout << "Menu: " << Menu << std::endl; }
			if (event.key.code == sf::Keyboard::Key::Num4) { setMenu(menu_test);  std::cout << "Menu: " << Menu << std::endl; }
			if (event.key.code == sf::Keyboard::Key::Num5) { setMenu(menu_stat);  std::cout << "Menu: " << Menu << std::endl; }
			if (event.key.code == sf::Keyboard::Key::Num6) { setMenu(menu_inf);  std::cout << "Menu: " << Menu << std::endl; }
		}

		if (sf::Event::KeyReleased == event.type) {
			if ((event.key.code == sf::Keyboard::Key::W) || (event.key.code == sf::Keyboard::Key::Space) || (event.key.code == sf::Keyboard::Key::Up)) { button_up = false; }
			if ((event.key.code == sf::Keyboard::Key::S) || (event.key.code == sf::Keyboard::Key::LShift) || (event.key.code == sf::Keyboard::Key::Down)) { button_down = false; }
			if ((event.key.code == sf::Keyboard::Key::A) || (event.key.code == sf::Keyboard::Key::Left)) { button_left = false; }
			if ((event.key.code == sf::Keyboard::Key::D) || (event.key.code == sf::Keyboard::Key::Right)) { button_right = false; }
			if ((event.key.code == sf::Keyboard::Key::E) || (event.key.code == sf::Keyboard::Key::RControl)) { button_interact = false; }
		}

		if (sf::Event::KeyPressed == event.type) {
			if ((event.key.code == sf::Keyboard::Key::W) || (event.key.code == sf::Keyboard::Key::Space) || (event.key.code == sf::Keyboard::Key::Up)) { button_up = true; }
			if ((event.key.code == sf::Keyboard::Key::S) || (event.key.code == sf::Keyboard::Key::LShift) || (event.key.code == sf::Keyboard::Key::Down)) { button_down = true; }
			if ((event.key.code == sf::Keyboard::Key::A) || (event.key.code == sf::Keyboard::Key::Left)) { button_left = true; }
			if ((event.key.code == sf::Keyboard::Key::D) || (event.key.code == sf::Keyboard::Key::Right)) { button_right = true; }
			if ((event.key.code == sf::Keyboard::Key::E) || (event.key.code == sf::Keyboard::Key::RControl)) { button_interact = true; }
		}
	}
	if (Menu == menu_game) {
		if (button_left) { player.move(-1, 0); }
		if (button_right) { player.move(1, 0); }
		if (button_up) { player.move(0, -1); }
		if (button_down) { player.move(0, 1); }
		if (button_interact) { player.openDoor(); }
	}
	


	switch (Menu) {

	case menu_main:
		if (ButtonF1_1->Released()) { std::cout << "released" << std::endl; Menu = menu_lobby; }
		if (ButtonF1_2->Released()) { std::cout << "released" << std::endl; Menu = menu_stat; }
		if (ButtonF1_3->Released()) { std::cout << "released" << std::endl; Menu = menu_inf; }
		break;
	case menu_game:
		if (ButtonF3->Released()) { std::cout << "released" << std::endl;/* Menu = menu_main; */GameMap.generateLabyrinth(); player.Player_set_source(); }
		break;
	case menu_lobby:
		if (ButtonF2_back->Released()) { std::cout << "released" << std::endl; Menu = menu_main; }
		if (ButtonF2_easy->Released()) { std::cout << "released" << std::endl; Menu = menu_game; }
		break;
	case menu_test:
		if (ButtonF4->Released()) { std::cout << "F" << std::endl; }
		if (ButtonF4_back->Released()) { std::cout << "released" << std::endl; Menu = menu_game; }
		if (ButtonF4_1->Released()) {
			std::cout << "F1" << std::endl;
		}
		
		if (ButtonF4_2->Released())
		{
			std::cout << "F2" << std::endl;
		}
		if (ButtonF4_3->Released())
		{
			std::cout << "F3" << std::endl;
		}
		if (ButtonF4_4->Released())
		{
			std::cout << "F4" << std::endl;
		}
		break;
	case menu_stat:
		if (ButtonF5_back->Released()) { std::cout << "released" << std::endl; Menu = menu_main; }
		break;
	case menu_inf:
		if (ButtonF6_back->Released()) { std::cout << "released" << std::endl; Menu = menu_main; }
		break;
	default:
		break;
	}
}

// метод для оновлення інтерфейсу
void UpdateGraphic(sf::RenderWindow& window) {
	window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));

	sizeBlock = window.getSize().y / float(1.3);
	Form1.updateForm(window);
	Form2.updateForm(window);
	Form3.updateForm(window);
	Form4.updateForm(window);
	Form5.updateForm(window);
	Form6.updateForm(window);

}

// метод для відображення графіки
void GraphicRender(sf::RenderWindow& window) {

	window.clear();
	if (Menu == menu_main) {
		Form1.drawBackground(window);
		Form1.draw(window);
	}
	if (Menu == menu_lobby) {
		Form2.drawBackground(window);
		Form2.draw(window);
	}
	if (Menu == menu_game) {
		GameMap.draw(window);
		player.drawPlayer(window);
		Form3.draw(window);
	}
	if (Menu == menu_test) {
		Form4.drawBackground(window);
		Form4.draw(window);
	}
    if (Menu == menu_stat) {
		Form5.drawBackground(window);
		Form5.draw(window);
	}
	if (Menu == menu_inf) {
		Form6.drawBackground(window);
		Form6.draw(window);
	}
	window.display();
}