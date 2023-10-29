#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Game.h"
#include "general.h"

 
// конструктор 
Game::Game():GameWindow(GameWindowSize, GameWindowTitle) {}

// метод для обробки вікна
void Game::HandleInput() {
	windowEventHandling(GameWindow);
}

// метод для обробки і оновлень всіх ігрових механік
void Game::Update() {

}

// метод для рендеру графіки
void Game::Render() {

}

// метод ігрового циклу
void Game::Run() {
	while (GameWindow.isOpen()) {
		HandleInput();
		Update();
		Render();
	}
}

