#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "interface.h"
#include "GlobalVariablesForResources.h"
#include <iostream>

//виняткові ситуації враховані
Button::Button() {
	Area.setSize(sf::Vector2f(100.0, 50.0));
	Area.setPosition(sf::Vector2f(100.0, 50.0));
	Area.setOutlineThickness(5);
	Area.setFillColor(sf::Color(255, 160, 0, 100));
	Area.setOutlineColor(sf::Color(255, 120, 0));
}

void Button::draw(sf::RenderWindow& window) {
	if (pressed) {
		Area.setFillColor(color_fill_pressed);
		Area.setOutlineColor(color_line_pressed);
	}
	else {
		Area.setFillColor(color_fill);
		Area.setOutlineColor(color_line);
	}

	sf::FloatRect textBounds = text_button.getGlobalBounds();

	float scaleY = Area.getSize().y / text_button.getCharacterSize();

	float newSize = (scaleY * text_button.getCharacterSize())*size_text;
	if (newSize <= 0) { newSize = 1; }
	text_button.setCharacterSize(newSize);

	float x = Area.getPosition().x + (Area.getSize().x / 2);
	float y = Area.getPosition().y + (Area.getSize().y / 3);
	
	text_button.setOrigin(text_button.getGlobalBounds().width / 2, newSize / 2);
	
	text_button.setPosition(x, y);
	text_button.setFillColor(color_text);

	window.draw(Area);
	window.draw(text_button);
}

void Button::updatePressed(sf::RenderWindow& window) {
	if (pressed == false) { released = false; }
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		Area.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
		pressed = true;
	}
	else {
		if (pressed) released = true;
		pressed = false;
	}
}

void Button::Update(float windowWidth, float windowHeight, float posX, float posY){
	Area.setPosition(sf::Vector2f(windowWidth*indentLeft+posX, windowHeight*indentTop+posY));
	Area.setSize(sf::Vector2f(windowWidth*width, windowHeight*height));
}

void Button::setPosSize(float indent_left, float indent_top, float W, float H){
	indentLeft = indent_left;
	indentTop = indent_top;
	width = W;
	height = H;
}

void Button::setText(sf::String str) {
	text_button.setString(str);
}

void Button::setStyle(sf::String str, float textSize, sf::Color colorFill, sf::Color colorLine, sf::Color colorFillPressed, sf::Color colorLinePressed, sf::Color colorText) {
	/*Area.setFillColor();
	Area.set*/
	//try catch should be added
	if (textSize <= 0) {
		throw UIException("Розмір тексту не може бути меншим або дорівнювати нулю.");
	}
	size_text = textSize;
	text_button.setFont(master_font);
	text_button.setString(str);
	color_fill = colorFill;
	color_fill_pressed = colorFillPressed;
	color_line = colorLine;
	color_line_pressed = colorLinePressed;
	color_text = colorText;
}

bool Button::Pressed(){	return pressed;}

bool Button::Released() { return released; }

void Form::addInterfaceObj(interfaceObj* Object) {
	elements.push_back(Object);
}

Form::Form() {}

void Form::draw(sf::RenderWindow& window) {
	for (const auto& element : elements) {
		element->draw(window);
	}
}

void Form::updateForm(sf::RenderWindow& window){
	updatePressed(window);
	updateBackground(window);
	update();
}

void Form::update(){
	for (const auto& element : elements) {
		element->Update(background.getSize().x, background.getSize().y, background.getPosition().x, background.getPosition().y);
	}
}

void Form::initializeBackground(sf::Texture & texture){
	bgr = true;
	background.setSize(sf::Vector2f(800, 500));
	background.setTexture(&texture);
}

void Form::updateBackground(sf::RenderWindow& window){
	if (bgr) {
		background.setSize(sf::Vector2f(window.getSize().y * background.getTexture()->getSize().x / background.getTexture()->getSize().y, window.getSize().y));
		background.setPosition((window.getSize().x - background.getSize().x) / 6.0, 0);
	}
	else {
		background.setSize(sf::Vector2f(window.getSize().x , window.getSize().y));
		background.setPosition(0, 0);
	}
}

void Form::drawBackground(sf::RenderWindow& window){
	window.draw(background);
}

void Form::updatePressed(sf::RenderWindow& window){
	for (const auto& element : elements) {
		element->updatePressed(window);
	}
}
