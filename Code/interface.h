#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Exceptions.h"
class interfaceObj {
protected:
	float indentLeft, indentTop; // значення від 0 до 1
	float width, height;  // значення від 0 до 1
	bool visible;
	bool snapToBackground;
public:
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void Update(float windowWidth, float windowHeight, float posX, float posY) = 0;
	virtual void setPosSize(float indent_left, float indent_top, float W, float H) = 0;
	virtual void updatePressed(sf::RenderWindow& window) = 0;
	void setVisible(bool value) { visible = value; }
	void setSnapToBackground(bool value) { snapToBackground = value; }
	bool getSnapToBackground() { return snapToBackground;}
};

class Slider : public interfaceObj {
private:
	sf::RectangleShape Area;
	sf::RectangleShape Track;
	sf::RectangleShape Pic;
	float value;
public:
	Slider();
	void draw(sf::RenderWindow& window) override;
	void Update(float windowWidth, float windowHeight, float posX, float posY) override;
	void setPosSize(float indent_left, float indent_top, float W, float H) override;
	void updatePressed(sf::RenderWindow& window) override;
};

class TextCanvas : public interfaceObj{
private:
	sf::Color colorText;
	sf::String strText;
	std::vector<sf::String> words;
	float sizeText;
	sf::Text text;
	sf::RectangleShape reg;
public:
	TextCanvas();
	void draw(sf::RenderWindow& window) override;
	void Update(float windowWidth, float windowHeight, float posX, float posY) override;
	void setPosSize(float indent_left, float indent_top, float W, float H) override;
	void updatePressed(sf::RenderWindow& window) override;

	void setText(sf::String value);
	void setSize(float value) { sizeText = value; }
	void setColorFill(sf::Color color) { colorText = color; }
};

class Button : public interfaceObj {
private:
	sf::RectangleShape Area;

	sf::Color color_fill;
	sf::Color color_line;
	sf::Color color_fill_pressed;
	sf::Color color_line_pressed;
	sf::Color color_fill_hovered;
	sf::Color color_line_hovered;

	sf::Text text_button;
	sf::Color color_text;
	float size_text;

	bool pressed = false;
	bool hover = false;
	bool released = false;

public:
	Button();
	void draw(sf::RenderWindow& window) override;
	void Update(float windowWidth, float windowHeight, float posX, float posY) override;
	void setPosSize(float indent_left, float indent_top, float W, float H) override;
	void updatePressed(sf::RenderWindow& window) override;

	//тимчасовий
	void setStyle(sf::String str, float textSize, sf::Color colorFill, sf::Color colorLine, sf::Color colorFillPressed, sf::Color colorLinePressed, sf::Color colorText);

	void setStyleText(float textSize, sf::Color colorText);
	void setColorButton(sf::Color fill, sf::Color line);
	void setColorPressed(sf::Color fill, sf::Color line);
	void setColorHover(sf::Color fill, sf::Color line);
	void setFont(sf::Font & font);

	void setText(sf::String str);
	bool Pressed();
	bool Released();
	bool Hovered();
};

class Form {
private:
	std::vector<interfaceObj*> elements;
	sf::RectangleShape background;
	bool bgr = false;

	void update(sf::RenderWindow& window);
	void updateBackground(sf::RenderWindow& window);
	void updatePressed(sf::RenderWindow& window);
public:
	Form();
	void addInterfaceObj(interfaceObj* Object);
	void draw(sf::RenderWindow& window);
	void updateForm(sf::RenderWindow& window);
	void initializeBackground(sf::Texture& texture);
	void drawBackground(sf::RenderWindow& window);
	
	//void setBackgroundIndent();
};

