#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

class Game{
private:
	VideoMode GameWindowSize = { 800,500 };
	String GameWindowTitle = L"Математичні концепції в ігровому середовищі";
	RenderWindow GameWindow;


	void HandleInput();
	void Update();
	void Render();
public:
	Game();

	void Run();
};

