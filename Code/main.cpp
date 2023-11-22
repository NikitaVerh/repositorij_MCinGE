/*
Головний файл де розпочинається програма
*/

#pragma once
#include "Game.h"
#include <Windows.h> // бібліотека для встановлення кодування для консолі

// тимчасові бібліотеки
#include <iostream>

sf::VideoMode GameWindowSize = { 1400,700 }; // змінна що відповідає за відео режим вікна
sf::String GameWindowTitle = L"Математичні концепції в ігровому середовищі"; // підпис вікна (caption)
sf::RenderWindow GameWindow(GameWindowSize, GameWindowTitle); // основне вікно програми
sf::Clock delta_time_clock; // змінна для підрахунку часу що йде на один кадр

int main() {
    SetConsoleCP(65001); // встановлення кодування Windows-65001 в  потік введення
    SetConsoleOutputCP(65001);// встановлення кодування Windows-65001 в  потік виведення


    startProgram(GameWindow);
    Run(GameWindow, delta_time_clock); // метод ігрового циклу
    stopProgram(GameWindow);
    return 0;
}