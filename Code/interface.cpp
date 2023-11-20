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
	size_text = 1;
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
	if (!visible || !window.hasFocus()) {
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
	text_button.setString(sf::String::fromUtf8(str.begin(), str.end()));
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



Form::Form() {
	coefficient = 2.0;
}

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
		background.setPosition((window.getSize().x - background.getSize().x) / coefficient, 0);
	}
	else {
		background.setSize(sf::Vector2f(window.getSize().x , window.getSize().y));
		background.setPosition(0, 0);
	}
}

void Form::drawBackground(sf::RenderWindow& window){
	window.draw(background);
}

void Form::setBackgroundCoefficient(float value) {
	coefficient = value;
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

//using namespace std;

void TextCanvas::Update(float windowWidth, float windowHeight, float posX, float posY) {
	
	float size = windowHeight * sizeText;
	text.setCharacterSize(size);
	
	float w = width * windowWidth;
	float h = height * windowHeight;

	sf::String str = "";
	sf::String strT = "";

	if (needUpdateWords) {
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
	}
	else {
		text.setString(strText);
	}
	//sf::String strT32 = sf::String::fromUtf8(strT.begin(), strT.end());
	

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
			words.push_back(sf::String::fromUtf8(str.begin(), str.end()));
			break;
		}
		sf::String a = str.substring(0, pos);
		words.push_back(sf::String::fromUtf8(a.begin(), a.end()));
		str.erase(0, pos + 1);
	}
	return words;
}


void TextCanvas::setText(sf::String value) {
	strText = sf::String::fromUtf8(value.begin(), value.end());
	words = getWords(value);
	text.setFont(master_font);
	text.setLineSpacing(1.2);
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\\
//||||||||||||||||||||||||||||||||||   Slider   ||||||||||||||||||||||||||||||||||\\


Slider::Slider() {
	value = 1.0;
	visible = true;
	snapToBackground = false;
}

void Slider::draw(sf::RenderWindow& window) {
	if (!visible)return;
	window.draw(Pic);
	window.draw(Track);
	window.draw(Area);
}

void Slider::Update(float windowWidth, float windowHeight, float posX, float posY) {
	Pic.setTexture(&texturePic);
	Area.setTexture(&texture_slider);
	Track.setTexture(&texture_slider_track);

	Pic.setPosition(windowWidth*indentLeft + posX,windowHeight*indentTop + posY);
	Pic.setSize(sf::Vector2f(windowHeight*height, windowHeight*height));

	Track.setPosition(windowWidth * indentLeft + windowHeight * height + posX, windowHeight * indentTop + posY);
	Track.setSize(sf::Vector2f(windowHeight * height * 4, windowHeight * height));

	Area.setPosition(windowWidth * indentLeft + windowHeight * height + value* windowHeight * height * 3 + posX, windowHeight * indentTop + posY);
	Area.setSize(sf::Vector2f(windowHeight * height, windowHeight * height));

}

void Slider::setPosSize(float indent_left, float indent_top, float W, float H) {
	indentLeft = indent_left;
	indentTop = indent_top;
	height = H;
}

void Slider::setCanUpdatePresed(bool can) {
	canUpdatePressed = can;
}

void Slider::updatePressed(sf::RenderWindow& window) {
	if (!visible || !canUpdatePressed) {
		pressed = false;
		released = false;
		return;
	}
	bool MouseHover = Pic.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) ||
		Track.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

	if (pressed == false) { released = false; }
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && MouseHover) {
		pressed = true;
	}
	else {
		if (pressed && MouseHover) released = true;
		pressed = false;
	}

	MouseHover = Pic.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	if (released && MouseHover) {
		if (value != 0) { value = 0; }
		else { value = 1; }
	}

	MouseHover = Track.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	if (pressed && MouseHover) {
		float xTrack = Track.getPosition().x;
		float wTrack = Track.getSize().x;

		float mouseX = sf::Mouse::getPosition(window).x - Track.getSize().y/2.0;

		value = (mouseX - xTrack) / (wTrack * 3 / 4.0);

		if (value > 1) { value = 1; }
		if (value < 0) { value = 0; }
		std::cout << value << std::endl;
	}
	canUpdatePressed = false;
}

void Slider::setTexturePic(sf::Texture& textureForPic) {
	texturePic = textureForPic;
}

float Slider::getValue() {
	return value;
}