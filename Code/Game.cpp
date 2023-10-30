/*
В цьому файлі йде реалізація методів класу Game
*/

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Game.h"
#include "general.h"

// тимчасові бібліотеки
#include <iostream>

 
// конструктор + тут створюється ігрове вікно
Game::Game():GameWindow(GameWindowSize, GameWindowTitle) {}


// метод для обробки вікна
void Game::HandleInput() {
	windowEventHandling(GameWindow);
}


// метод для обробки і оновлень всіх ігрових механік
void Game::Update(sf::Time delta_time) {

}


// метод для рендеру графіки
void Game::Render() {
	UpdateGraphic(GameWindow);
	GraphicRender(GameWindow);
}


// метод ігрового циклу
void Game::Run() {
	while (GameWindow.isOpen()) {
		sf::Time delta_time = delta_time_clock.restart(); // змінна що зберігає кількість часу за минулий кадр
		
		HandleInput();
		Update(delta_time);
		Render();
	}
}

