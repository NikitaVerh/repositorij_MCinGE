#pragma once
#pragma execution_character_set("utf-8")
#include "SFML/System.hpp"
#include "GlobalVariablesForResources.h"
#include "GlobalVariablesOfClasses.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <nlohmann/json.hpp>
#include <random>
#include "taskProcess.h"

using json = nlohmann::json;

//обробка виняткових ситуацій є
Task::Task() {
	instance = "Instance";
	answer1 = "Answer1";
	answer2 = "Answer2";
	answer3 = "Answer3";
	answer4 = "Answer4";
}
void Task::setTask(sf::String Instance, sf::String Answer1, sf::String Answer2,
	sf::String Answer3, sf::String Answer4, sf::String correctAnswer) {
	instance = Instance;
	answer1 = Answer1;
	answer2 = Answer2;
	answer3 = Answer3;
	answer4 = Answer4;
	correct_answer = correctAnswer;
}
std::vector<Task> Task::loadTasksFromFile(const std::string& filename, const std::string& category, const std::string& difficulty) {
	std::vector<Task> tasks;

	//try catch
	std::ifstream file(filename);
	if (!file.is_open()) {
		char error_message[1024];
		strerror_s(error_message, sizeof(error_message), errno); // Використання strerror_s
		std::string errMsg = "Не вдалось відкрити файл " + filename + ". Помилка: " + error_message;
		throw TaskLoadException(filename, errMsg);
	}
	//if (file.peek() == std::ifstream::traits_type::eof()) {
	//	std::cerr << "Файл пуст: " << filename << std::endl;
	//	return tasks;
	//}

	json j;
	file >> j;
	for (const auto& item : j[category][difficulty]) {
		Task task;
		sf::String problem(item["problem"].get<std::string>());
		sf::String answer(item["answer"].get<std::string>());

		std::vector<sf::String> options;
		for (const auto& opt : item["options"]) {
			options.push_back(sf::String(opt.get<std::string>()));
		}


		options.push_back(answer);
		std::shuffle(options.begin(), options.end(), std::mt19937(std::random_device()()));

		if (options.size() >= 4) {
			task.setTask(problem, options[0], options[1], options[2], options[3], answer);
			tasks.push_back(task);
		}
		//try catch
		else {
			throw TaskParseException("Недостатньо варіантів відповідей для задачі: " + problem.toAnsiString());
		}
	}

	file.close();
	return tasks;

}
#pragma region getRandomTasks
std::vector<Task> Task::getRandomTasks(const std::vector<Task>& allTasks, size_t taskCount) {
	std::vector<Task> randomTasks = allTasks;
	std::random_device rd;
	std::mt19937 g(rd());


	std::shuffle(randomTasks.begin(), randomTasks.end(), g);

	if (randomTasks.size() < taskCount) {
		return randomTasks;
	}

	randomTasks.resize(taskCount);

	return randomTasks;
}
#pragma endregion 

bool Task::isCorrectAnswer(const sf::String& userAnswer) const {
	return userAnswer == correct_answer;
}

Task Task::generateNewTask(const std::string& filename, const std::string& category, const std::string& difficulty) {
	static std::vector<Task> recentTasks; // Статична змінна для зберігання історії
	const size_t maxRecentTasks = 5; // Максимальна кількість останніх завдань для зберігання

	std::vector<Task> tasks;
	try {
		tasks = loadTasksFromFile("Resources/json/task.json", "Лінійна Алгебра", currentDifficulty);
	}
	catch (const TaskLoadException& e) {
		std::cerr << "Помилка завантаження завдання: " << e.what() << std::endl;
		throw;
	}

	if (tasks.empty()) {
		throw std::runtime_error("No tasks available for the chosen category and difficulty.");
	}

	std::random_device rd;
	std::mt19937 g(rd());
	Task randomTask;
	bool isUnique;

	do {
		std::shuffle(tasks.begin(), tasks.end(), g);
		randomTask = tasks.front();
		isUnique = std::find(recentTasks.begin(), recentTasks.end(), randomTask) == recentTasks.end();
	} while (!isUnique);

	// Оновлення історії останніх завдань
	recentTasks.push_back(randomTask);
	if (recentTasks.size() > maxRecentTasks) {
		recentTasks.erase(recentTasks.begin()); // Видаляємо найстаріше завдання
	}

	return randomTask;
}
sf::String Task::getInstance() { return instance; }
sf::String Task::getanswer1() { return answer1; }
sf::String Task::getanswer2() { return answer2; }
sf::String Task::getanswer3() { return answer3; }
sf::String Task::getanswer4() { return answer4; }
sf::String Task::getCorrectAnswer() const { return correct_answer; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// тимчасово, код далі був перенесений з general

sf::String answerF4_1;
sf::String answerF4_2;
sf::String answerF4_3;
sf::String answerF4_4;
sf::String correctAnswer;

int correctAnswersCount = 0; // Количество правильных ответов на текущем уровне
int playerLives = 3; // Количество жизней игрока

void SetTask(const std::string& filename, const std::string& category, const std::string& difficulty) {

	// Попытка сгенерировать новую задачу
	Task newTask;

	try {
		newTask = Task::generateNewTask(filename, category, currentDifficulty);
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Ошибка: " << e.what() << std::endl;
		return;
	}
	answerF4_1 = newTask.getanswer1();
	answerF4_2 = newTask.getanswer2();
	answerF4_3 = newTask.getanswer3();
	answerF4_4 = newTask.getanswer4();
	// Если нет исключения, и задача создана успешно, установим текст для кнопок
	ButtonF4->setText(newTask.getInstance());
	ButtonF4_1->setText(newTask.getanswer1());
	ButtonF4_2->setText(newTask.getanswer2());
	ButtonF4_3->setText(newTask.getanswer3());
	ButtonF4_4->setText(newTask.getanswer4());
	correctAnswer = newTask.getCorrectAnswer();
	std::cout << "Правильный ответ: " << correctAnswer.toAnsiString() << std::endl;
	/*std::cout << "answerF3_1.toAnsiString(): " << answerF3_1.toAnsiString() << std::endl;
	std::cout << "answerF3_2.toAnsiString(): " << answerF3_2.toAnsiString() << std::endl;
	std::cout << "answerF3_3.toAnsiString(): " << answerF3_3.toAnsiString() << std::endl;
	std::cout << "answerF3_4.toAnsiString()" << answerF3_4.toAnsiString() << std::endl;*/
}

void CheckAnswer(const sf::String& answer)
{
	if (answer.toAnsiString() == correctAnswer.toAnsiString()) {
		std::cout << "Correct!" << std::endl;
		correctAnswersCount++;
		// Проверка на смену уровня сложности
		if (correctAnswersCount == 5) {
			if (currentDifficulty == "easy") {
				currentDifficulty = "normal";
			}
			else if (currentDifficulty == "normal") {
				currentDifficulty = "hard";
			}
			else if (currentDifficulty == "hard") {
				std::cout << "You've completed the game!" << std::endl;
				// Сброс игры
				currentDifficulty = "easy";
				playerLives = 3;
			}
			correctAnswersCount = 0; // Сброс счетчика для нового уровня
		}
		// Генерация нового вопроса на текущем уровне сложности
		SetTask("Resources/json/task.json", "Вища Математика", currentDifficulty);
	}
	else {
		std::cout << "Wrong!" << std::endl;
		playerLives--;
		// Проверка на конец игры
		if (playerLives <= 0) {
			std::cout << "Game Over! Starting again." << std::endl;
			// Сброс игры
			currentDifficulty = "easy";
			correctAnswersCount = 0;
			playerLives = 3;
			SetTask("Resources/json/task.json", "Вища Математика", currentDifficulty);
		}
	}
}

