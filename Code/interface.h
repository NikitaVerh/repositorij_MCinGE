#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

class interfaceObj {
public:
	float indentLeft, indentTop; // значення від 0 до 1
	float width, height;  // значення від 0 до 1

	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void Update(float windowWidth, float windowHeight, float posX, float posY) = 0;
	virtual void setPosSize(float indent_left, float indent_right, float W, float H) = 0;
	virtual void updatePressed(sf::RenderWindow& window) = 0;
};

class Button : public interfaceObj {
private:
	sf::RectangleShape Area;
	sf::Color color_fill;
	sf::Color color_fill_pressed;
	sf::Color color_line;
	sf::Color color_line_pressed;
	sf::Color color_text;
	sf::Text text_button;

	float size_text;

	bool pressed = false;
	bool released = false;

public:
	Button();
	void draw(sf::RenderWindow& window) override;
	void Update(float windowWidth, float windowHeight, float posX, float posY) override;
	void setPosSize(float indent_left, float indent_top, float W, float H) override;
	void updatePressed(sf::RenderWindow& window) override;

	void setStyle(sf::String str, float textSize, sf::Color colorFill, sf::Color colorLine, sf::Color colorFillPressed, sf::Color colorLinePressed, sf::Color colorText);
	bool Pressed();
	bool Released();
};

class Form {
private:
	std::vector<interfaceObj*> elements;
	sf::RectangleShape background;
	bool bgr = false;

	void update();
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

