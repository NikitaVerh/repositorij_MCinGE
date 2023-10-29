#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

class Game {
private:
	VideoMode GameWindowSize = { 800,500 }; // змінна що відповідає за відео режим вікна
	String GameWindowTitle = L"Математичні концепції в ігровому середовищі"; // підпис вікна (caption)
	RenderWindow GameWindow; // основне вікно програми
	

	void HandleInput(); // метод для обробки вікна
	void Update();      // метод для обробки і оновлень всіх ігрових механік
	void Render();      // метод для рендеру графіки
public:
	Game(); // конструктор

	void Run();         // метод ігрового циклу
};

