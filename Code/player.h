#pragma once
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include <SFML/System.hpp>

class Player {
private:
	float x, y;
	
	bool checkColision() {};
public:
	void Update();
	void move(float dx, float dy);
	void openDoor();
};
