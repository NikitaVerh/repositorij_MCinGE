#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "interface.h"
#include "GlobalVariablesForResources.h"
#include <iostream>

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
//||||||||||||||||||||||||||||||||||   Button   ||||||||||||||||||||||||||||||||||\\

//виняткові ситуації враховані
Button::Button() {
	visible = true;
	hover = false;
	text_button.setFont(master_font);
	snapToBackground = false;
	Area.setSize(sf::Vector2f(100.0, 50.0));
	Area.setPosition(sf::Vector2f(100.0, 50.0));
	Area.setOutlineThickness(5);
	Area.setFillColor(sf::Color(255, 160, 0, 100));
	Area.setOutlineColor(sf::Color(255, 120, 0));
}

void Button::draw(sf::RenderWindow& window) {
	if (!visible)return;
	if (!pressed) {
		Area.setFillColor(color_fill);
		Area.setOutlineColor(color_line);
	}
	if (hover) {
		Area.setFillColor(color_fill_hovered);
		Area.setOutlineColor(color_line_hovered);
	}
	if (pressed) {
		Area.setFillColor(color_fill_pressed);
		Area.setOutlineColor(color_line_pressed);
	}
	
	

	sf::FloatRect textBounds = text_button.getGlobalBounds();

	float scaleY = Area.getSize().y / text_button.getCharacterSize();

	float newSize = (scaleY * text_button.getCharacterSize())*size_text;
	if (newSize <= 0) { newSize = 1; }
	text_button.setCharacterSize(newSize);

	while (text_button.getLocalBounds().width > Area.getSize().x) {
		text_button.setCharacterSize(newSize--);
	}

	float x = Area.getPosition().x + (Area.getSize().x / 2);
	float y = Area.getPosition().y + (Area.getSize().y / 3);

	text_button.setOrigin(text_button.getGlobalBounds().width / 2, newSize / 2);
	
	text_button.setPosition(x, y);
	text_button.setFillColor(color_text);

	window.draw(Area);
	window.draw(text_button);
}

void Button::updatePressed(sf::RenderWindow& window) {
	if (!visible) {
		pressed = false;
		released = false;
		return;
	}

	bool MouseHover = Area.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

	if (pressed == false) { released = false; }
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && MouseHover) {
		pressed = true;
	}
	else {
		if (pressed && MouseHover) released = true;
		pressed = false;
	}
	if (MouseHover) {
		hover = true; 
	} else { hover = false; }

}

void Button::Update(float windowWidth, float windowHeight, float posX, float posY){
	Area.setPosition(sf::Vector2f(windowWidth * indentLeft + posX, windowHeight * indentTop + posY));
	Area.setSize(sf::Vector2f(windowWidth * width, windowHeight * height));
}

void Button::setPosSize(float indent_left, float indent_top, float W, float H){
	indentLeft = indent_left;
	indentTop = indent_top;
	width = W;
	height = H;
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
	color_fill_hovered = sf::Color(255, 255, 255, 50);
	color_line_hovered = sf::Color(150, 70, 30, 50);
}

void Button::setText(sf::String str) {
	text_button.setString(str);
}

void Button::setStyleText(float textSize, sf::Color colorText) {
	size_text = textSize;
	color_text = colorText;
}

void Button::setColorButton(sf::Color fill, sf::Color line) {
	color_fill = fill;
	color_line = line;
}

void Button::setColorPressed(sf::Color fill, sf::Color line) {
	color_fill_pressed = fill;
	color_line_pressed = line;
}

void Button::setColorHover(sf::Color fill, sf::Color line) {
	color_fill_hovered = fill;
	color_line_hovered = line;
}

void Button::setFont(sf::Font& font) {
	text_button.setFont(font);
}

bool Button::Pressed(){	return pressed;}

bool Button::Released() { return released; }

bool Button::Hovered() { return hover; }

void Form::addInterfaceObj(interfaceObj* Object) {
	elements.push_back(Object);
}


//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
//||||||||||||||||||||||||||||||||||    Form    ||||||||||||||||||||||||||||||||||\\



Form::Form() {}

void Form::draw(sf::RenderWindow& window) {
	for (const auto& element : elements) {
		element->draw(window);
	}
}

void Form::updateForm(sf::RenderWindow& window){
	updatePressed(window);
	updateBackground(window);
	update(window);
}

void Form::update(sf::RenderWindow& window){
	for (const auto& element : elements) {
		if (element->getSnapToBackground()) {
			element->Update(background.getSize().x, background.getSize().y, background.getPosition().x, background.getPosition().y);
		}
		else {
			element->Update(window.getSize().x, window.getSize().y, 0, 0);

		}
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


//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
//|||||||||||||||||||||||||||||||||  TextCanvas  |||||||||||||||||||||||||||||||||\\

TextCanvas::TextCanvas() {
	strText = "";
	sizeText = 1;
	visible = true;
	snapToBackground = false;
}

void TextCanvas::draw(sf::RenderWindow& window) {
	if (!visible)return;

	text.setFillColor(colorText);
	window.draw(text);
	window.draw(reg);///    reg
}

using namespace std;

void TextCanvas::Update(float windowWidth, float windowHeight, float posX, float posY) {
	
	float size = windowHeight * sizeText;
	text.setCharacterSize(size);
	
	float w = width * windowWidth;
	float h = height * windowHeight;

	sf::String str = "";
	sf::String strT = "";

	for (int i = 0; i < words.size(); i++) {
		text.setString(str + words[i]);
		if (text.getLocalBounds().width < w) {
			str += words[i] + " ";
			strT += words[i] + " ";
		}
		else {
			str = words[i] + " ";
			strT += "\n" + words[i] + " ";
		}
	}
	text.setString(strT);

	text.setPosition(windowWidth * indentLeft + posX, windowHeight * indentTop + posY);

	///////////тимчасовий код
	reg.setFillColor(sf::Color(0, 0, 0, 0));
	reg.setOutlineColor(sf::Color(255, 0, 0));
	reg.setOutlineThickness(1);
	reg.setPosition(sf::Vector2f(windowWidth * indentLeft + posX, windowHeight * indentTop + posY));
	reg.setSize(sf::Vector2f(windowWidth * width, windowHeight * height));

}


void TextCanvas::setPosSize(float indent_left, float indent_top, float W, float H) {
	indentLeft = indent_left;
	indentTop = indent_top;
	width = W;
	height = H;
}

void TextCanvas::updatePressed(sf::RenderWindow& window) {}


std::vector<sf::String> getWords(sf::String str) {
	std::vector<sf::String> words;
	while (!str.isEmpty()) {
		int pos = str.find(" ");
		if (pos == -1) {
			words.push_back(str);
			break;
		}
		words.push_back(str.substring(0, pos));
		str.erase(0, pos + 1);
	}
	return words;
}


void TextCanvas::setText(sf::String value) {
	strText = value; 
	words = getWords(value);
	text.setFont(master_font);
	text.setLineSpacing(1.2);
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
//||||||||||||||||||||||||||||||||||   Slider   ||||||||||||||||||||||||||||||||||\\

Slider::Slider() {
	value = 1;
}

void Slider::draw(sf::RenderWindow& window) {

}

void Slider::Update(float windowWidth, float windowHeight, float posX, float posY) {

}

void Slider::setPosSize(float indent_left, float indent_top, float W, float H) {

}

void Slider::updatePressed(sf::RenderWindow& window) {

}

