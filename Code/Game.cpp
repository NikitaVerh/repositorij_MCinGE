#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "general.h"
#include "GlobalVariablesForResources.h"

// тимчасові бібліотеки
#include <iostream>

// метод для обробки вікна
void HandleInput(sf::RenderWindow& window) {
	windowEventHandling(window);
}


// метод для обробки і оновлень всіх ігрових механік
void Update(sf::Time delta_time) {

}


// метод для рендеру графіки
void Render(sf::RenderWindow& window) {
	UpdateGraphic(window);
	GraphicRender(window);
}


// метод ігрового циклу
void Run(sf::RenderWindow& window, sf::Clock& delta_time_clock) {
    while (window.isOpen()) {
        sf::Time delta_time = delta_time_clock.restart(); // змінна що зберігає кількість часу за минулий кадр
        
        HandleInput(window); // метод для обробки вікна
        Update(delta_time);      // метод для обробки і оновлень всіх ігрових механік
        Render(window);      // метод для рендеру графіки
    }
}

