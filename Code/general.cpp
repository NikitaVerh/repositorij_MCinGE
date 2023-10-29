#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

//#include <iostream>
//#include "fileForIlla.cpp"
//#include "fileForAlisa.cpp"
//#include "fileForNikolai.cpp"
//#include "fileForNikita.cpp"

// метод що виконується один раз при старті програми
void startProgram() {
	
}

// метод для обробки подій вікна
void windowEventHandling(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		
	}
}
void GraphicRender(sf::RenderWindow& window) {
	//вся графика
}