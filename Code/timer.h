#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/System.hpp>

//обробка виняткових ситуацій не потрібна 
class Timer {
private:
	sf::Clock cl;
	float interval;
	bool value = false;
public:
	Timer() {}
	void update() {
		value = false;
		if (cl.getElapsedTime().asMilliseconds() > interval) {
			cl.restart();
			value = true;
		}
	}
	bool getValue() {return value;}
	void setInterval(float interv) {interval = interv;}
	void restart() {cl.restart();}
};