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
		if (ButtonMenuStart->Released()) { std::cout << "released" << std::endl; setMenu(menu_lobby); }
		if (ButtonMenuContinue->Released()) { std::cout << "released" << std::endl; setMenu(menu_game); }
		if (ButtonMenuStatic->Released()) { std::cout << "released" << std::endl; setMenu(menu_stat); }
		if (ButtonMenuInf->Released()) { std::cout << "released" << std::endl; setMenu(menu_inf); }
		break;
	case menu_game:
		if (ButtonLabirint->Released()) { std::cout << "released" << std::endl; /* Menu = menu_main; */ GameMap.generateLabyrinth(); player.Player_set_source(); }
		if (ButtonLabirintBack->Released()) { std::cout << "released" << std::endl; setMenu(menu_lobby); }
		break;
	case menu_lobby:
		if (ButtonLobbyBack->Released()) { std::cout << "released" << std::endl; Menu = menu_main; }
		if (ButtonLobbyEasy->Released()) { exam.set_difficulty(0); Menu = menu_game; }
		if (ButtonLobbyNormal->Released()) { exam.set_difficulty(1); Menu = menu_game; }
		if (ButtonLobbyHard->Released()) { exam.set_difficulty(2); Menu = menu_game; }
		break;
	case menu_test:
		if (ButtonTest->Released()) { std::cout << "F" << std::endl; }
		if (ButtonTestBack->Released()) { std::cout << "released" << std::endl; Menu = menu_game; }
		if (ButtonTest1->Released()) { exam.answer_chosen(0); }
		if (ButtonTest2->Released()) { exam.answer_chosen(1); }
		if (ButtonTest3->Released()) { exam.answer_chosen(2); }
		if (ButtonTest4->Released()) { exam.answer_chosen(3); }
		if (ButtonTestFinish->Released()) { exam.stop_test(); }
		break;
	case menu_stat:
		if (ButtonStatBack->Released()) { std::cout << "released" << std::endl; Menu = menu_main; }
		break;
	case menu_inf:
		if (ButtonInfBack->Released()) { std::cout << "released" << std::endl; Menu = menu_main; }
		break;
	default:
		break;
	}

}

// метод для оновлення інтерфейсу
void UpdateGraphic(sf::RenderWindow& window) {
	window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));

	sizeBlock = window.getSize().y / float(1.3);
	Form_menu.updateForm(window);
	Form_lobby.updateForm(window);
	Form_labirint.updateForm(window);
	Form_test.updateForm(window);
	Form_stat.updateForm(window);
	Form_inf.updateForm(window);

}

// метод для відображення графіки
void GraphicRender(sf::RenderWindow& window) {

	window.clear();
	if (Menu == menu_main) {
		Form_menu.drawBackground(window);
		Form_menu.draw(window);
	}
	if (Menu == menu_lobby) {
		Form_lobby.drawBackground(window);
		Form_lobby.draw(window);
	}
	if (Menu == menu_game) {
		GameMap.draw(window);
		player.drawPlayer(window);
		Form_labirint.draw(window);
	}
	if (Menu == menu_test) {
		Form_test.drawBackground(window);
		Form_test.draw(window);
	}
    if (Menu == menu_stat) {
		Form_stat.drawBackground(window);
		Form_stat.draw(window);
	}
	if (Menu == menu_inf) {
		Form_inf.drawBackground(window);
		Form_inf.draw(window);
	}
	window.display();
}