#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Game.h"
#include "general.cpp"

Game::Game():GameWindow(GameWindowSize, GameWindowTitle) {
}

void Game::HandleInput() {
	windowEventHandling(GameWindow);
}

void Game::Update() {

}

void Game::Render() {

}

void Game::Run() {
	while (GameWindow.isOpen()) {
		HandleInput();
		Update();
		Render();
	}
}
