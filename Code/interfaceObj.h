#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

class interfaceObj {
public:
	virtual void draw(sf::RenderWindow& window) = 0;
};

class Button : public interfaceObj {
private:
	sf::RectangleShape Area;
public:
	Button();
	void draw(sf::RenderWindow& window) override;

};

class Form {
private:
	std::vector<interfaceObj*> elements;
public:
	Form() {}
	void addInterfaceObj(interfaceObj* Object);
	void draw(sf::RenderWindow& window);
};

