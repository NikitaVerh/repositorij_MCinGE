#pragma once
#include "SFML/System.hpp"

class Task {
private:
	sf::String instance;
	sf::String answer1;
	sf::String answer2;
	sf::String answer3;
	sf::String answer4;
public:
	Task() {
		instance = "Instance";
		answer1 = "Answer1";
		answer2 = "Answer2";
		answer3 = "Answer3";
		answer4 = "Answer4";
	}
	void setTask(sf::String Instance, sf::String Answer1, sf::String Answer2, sf::String Answer3, sf::String Answer4) {
		instance = Instance;
		answer1 = Answer1;
		answer2 = Answer2;
		answer3 = Answer3;
		answer4 = Answer4;
	}

	sf::String getInstance() { return instance; }
	sf::String getanswer1() { return answer1; }
	sf::String getanswer2() { return answer2; }
	sf::String getanswer3() { return answer3; }
	sf::String getanswer4() { return answer4; }
};

Task getTask(int theme);