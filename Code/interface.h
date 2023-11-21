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

class Particles : public interfaceObj {
private:
	struct particle	{
		float x, y;
		float dx, dy;
		float coefficientForAnimation, speed;
		int seed;
		sf::RectangleShape area;
		particle(float X, float Y, float W, float H) {
			srand((unsigned int)(time(0) * seed++));
			coefficientForAnimation = (rand()%7000)/1000.0-3;
			speed = 1 / float(rand());
			if (speed < 0.3) { speed = 0.3; }
			setRandomPositionInCircle(X,Y,W,H);
			area.setFillColor(sf::Color(240+rand()%15, 100+rand()%75, 7+rand()%15));
		}
		void move() {
			x += dx;
			y += dy;
		}
		void setDxDy(float DX, float DY, float DT) {
			dx = DX * DT / 10;
			dy = DY * DT / 10;
		}
		void setRandomPositionInCircle(float X, float Y, float W, float H) {
			srand((unsigned int)(time(0)*seed++));
			x = (rand() % int(W * 1000)) / 1000.0 + X;
			y = (rand() % int(H * 1000)) / 1000.0 + Y;
		}
	};
	struct spawn {
		float x, y, w, h;
		spawn(float X, float Y, float W, float H) { x = X; y = Y; w = W; h = H; }

		sf::RectangleShape area;
	};
	std::vector<particle> particles;
	std::vector<spawn> spawners;
	float DT;
public:
	Particles() { 
		snapToBackground = true; 
		visible = true;
		spawners.push_back(spawn(0.35, 0.21, 0.1, 0.4));
		spawners.push_back(spawn(0, 0.33, 0.09, 0.36));
		spawners.push_back(spawn(0.72, 0.4, 0.14, 0.34));
		spawners.push_back(spawn(0.86, 0.42, 0.14, 0.34));
		for (int i = 0; i < 100; i++) {
			int a = rand() % spawners.size();
			particles.push_back(particle(spawners[a].x, spawners[a].y, spawners[a].w, spawners[a].h ));
		}
	}
	void draw(sf::RenderWindow& window) override;
	void Update(float windowWidth, float windowHeight, float posX, float posY) override;
	void setPosSize(float indent_left, float indent_top, float W, float H) override;
	void updatePressed(sf::RenderWindow& window) override;
	void set_time(sf::Time delta_time);
};

class Slider : public interfaceObj {
private:
	sf::RectangleShape Area;
	sf::RectangleShape Track;
	sf::RectangleShape Pic;
	sf::Texture texturePic;
	float value;

	bool pressed;
	bool released;
	bool canUpdatePressed;
public:
	Slider();
	void draw(sf::RenderWindow& window) override;
	void Update(float windowWidth, float windowHeight, float posX, float posY) override;
	void setPosSize(float indent_left, float indent_top, float W, float H) override;
	void updatePressed(sf::RenderWindow& window) override;
	void setTexturePic(sf::Texture& textureForPic);
	float getValue();
	void setValue(float val);
	void setCanUpdatePresed(bool can);
};

class TextCanvas : public interfaceObj{
private:
	sf::Color colorText;
	sf::String strText;
	std::vector<sf::String> words;
	float sizeText;
	sf::Text text;
	sf::RectangleShape reg;
	bool needUpdateWords = false;
public:
	TextCanvas();
	void draw(sf::RenderWindow& window) override;
	void Update(float windowWidth, float windowHeight, float posX, float posY) override;
	void setPosSize(float indent_left, float indent_top, float W, float H) override;
	void updatePressed(sf::RenderWindow& window) override;

	void setText(sf::String value);
	void setSize(float value) { sizeText = value; }
	void setColorFill(sf::Color color) { colorText = color; }
	void setNeedUpdateWords(bool value) { needUpdateWords = value; }
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
	float coefficient;

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
	void setBackgroundCoefficient(float value);
	
	//void setBackgroundIndent();
};

std::vector<sf::String> getWords(sf::String str);