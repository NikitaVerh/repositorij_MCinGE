#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "interfaceObj.h"

Button::Button() {
	Area.setSize(sf::Vector2f(100.0,50.0));
	Area.setPosition(sf::Vector2f(100.0,50.0));
	Area.setOutlineThickness(5);
	Area.setOutlineColor(sf::Color(0,0,0));
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(Area);
}

void Form::addInterfaceObj(interfaceObj* Object) {
	elements.push_back(Object);
}

void Form::draw(sf::RenderWindow& window) {
	for (const auto& element : elements) {
		element->draw(window);
	}
}
