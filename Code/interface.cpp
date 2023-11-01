#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "interface.h"

Button::Button() {
	Area.setSize(sf::Vector2f(100.0, 50.0));
	Area.setPosition(sf::Vector2f(100.0, 50.0));
	Area.setOutlineThickness(5);
	Area.setFillColor(sf::Color(255, 160, 0, 100));
	Area.setOutlineColor(sf::Color(255, 120, 0));
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(Area);
}

void Form::addInterfaceObj(interfaceObj* Object) {
	elements.push_back(Object);
}

Form::Form() {}

void Form::draw(sf::RenderWindow& window) {
	for (const auto& element : elements) {
		element->draw(window);
	}
}
