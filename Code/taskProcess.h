#pragma once
#pragma execution_character_set("utf-8")
#include "SFML/System.hpp"
#include "GlobalVariablesForResources.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <nlohmann/json.hpp>
#include <random>

using json = nlohmann::json;

class Task {
private:
	sf::String instance;
	sf::String answer1;
	sf::String answer2;
	sf::String answer3;
	sf::String answer4;
	sf::String correct_answer;
public:
	Task();
	void setTask(sf::String Instance, sf::String Answer1, sf::String Answer2,
		sf::String Answer3, sf::String Answer4, sf::String correctAnswer);

	static std::vector<Task> loadTasksFromFile(const std::string& filename, const std::string& category, const std::string& difficulty);
	static std::vector<Task> getRandomTasks(const std::vector<Task>& allTasks, size_t taskCount);


	bool isCorrectAnswer(const sf::String& userAnswer) const;

	static Task generateNewTask(const std::string& filename, const std::string& category, const std::string& difficulty);
	sf::String getInstance();
	sf::String getanswer1();
	sf::String getanswer2();
	sf::String getanswer3();
	sf::String getanswer4();
	sf::String getCorrectAnswer() const;
};


/////////////////////////////////////////////////////////////////////////////////////////
// тимчасово

extern sf::String answerF3_1;
extern sf::String answerF3_2;
extern sf::String answerF3_3;
extern sf::String answerF3_4;
extern sf::String correctAnswer;

extern int correctAnswersCount; // Количество правильных ответов на текущем уровне
extern int playerLives; // Количество жизней игрока

void SetTask(const std::string& filename, const std::string& category, const std::string& difficulty);

void CheckAnswer(const sf::String& answer);


