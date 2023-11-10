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

	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Не вдалось відкрити файл " << filename << std::endl;
		char error_message[1024];
		strerror_s(error_message, sizeof(error_message), errno); // использование strerror_s
		std::cerr << "Ошибка при открытии файла. Проверьте путь и доступ к файлу: " << filename << std::endl;
		std::cerr << "Ошибка: " << error_message << std::endl;
		return tasks;
	}

	//if (file.peek() == std::ifstream::traits_type::eof()) {
	//	std::cerr << "Файл пуст: " << filename << std::endl;
	//	// Здесь также можно добавить дополнительные действия
	//	return tasks;
	//}

	json j;
	file >> j;
	for (const auto& item : j[category][difficulty]) {
		Task task;
		sf::String problem(item["problem"].get<std::string>()); // Преобразование в std::string, затем в sf::String
		sf::String answer(item["answer"].get<std::string>());

		std::vector<sf::String> options;
		for (const auto& opt : item["options"]) {
			options.push_back(sf::String(opt.get<std::string>()));
		}

		// Теперь у нас есть правильный ответ и варианты ответов в options, перемешаем их
		options.push_back(answer); // Добавляем правильный ответ в список опций
		std::shuffle(options.begin(), options.end(), std::mt19937(std::random_device()())); // Перемешиваем варианты ответа

		// Убедитесь, что у вас есть все 4 варианта ответа после перемешивания, прежде чем вызвать setTask
		if (options.size() >= 4) {
			task.setTask(problem, options[0], options[1], options[2], options[3], answer);
			tasks.push_back(task);
		}
		else {
			std::cerr << "Недостаточно вариантов ответов для задачи: " << problem.toAnsiString() << std::endl;
		}
	}

	file.close();
	return tasks;

}
#pragma region getRandomTasks
std::vector<Task> Task::getRandomTasks(const std::vector<Task>& allTasks, size_t taskCount) {
	std::vector<Task> randomTasks = allTasks; // Создаем копию всех задач
	std::random_device rd; // Получаем случайное начальное число
	std::mt19937 g(rd()); // Инициализируем генератор случайных чисел

	// Перемешиваем вектор задач
	std::shuffle(randomTasks.begin(), randomTasks.end(), g);

	// Если вектор задач меньше, чем запрошенное количество задач, возвращаем его целиком
	if (randomTasks.size() < taskCount) {
		return randomTasks;
	}

	// Урезаем вектор до заданного количества задач
	randomTasks.resize(taskCount);

	// Теперь в randomTasks находится taskCount случайно выбранных задач
	return randomTasks;
}
#pragma endregion 

bool Task::isCorrectAnswer(const sf::String& userAnswer) const {
	return userAnswer == correct_answer;
}

Task Task::generateNewTask(const std::string& filename, const std::string& category, const std::string& difficulty)
{
	// Загрузите все задачи из файла для заданной категории и сложности
	std::vector<Task> tasks = loadTasksFromFile("Resources/json/task.json", "Лінійна Алгебра", currentDifficulty);

	// Если нет задач, выбросите исключение
	if (tasks.empty()) {
		throw std::runtime_error("No tasks available for the chosen category and difficulty.");
	}

	// Получите случайную задачу из списка
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(tasks.begin(), tasks.end(), g);
	Task randomTask = tasks.front();

	// Верните выбранную задачу
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

sf::String answerF3_1;
sf::String answerF3_2;
sf::String answerF3_3;
sf::String answerF3_4;
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
	answerF3_1 = newTask.getanswer1();
	answerF3_2 = newTask.getanswer2();
	answerF3_3 = newTask.getanswer3();
	answerF3_4 = newTask.getanswer4();
	// Если нет исключения, и задача создана успешно, установим текст для кнопок
	ButtonF3->setText(newTask.getInstance());
	ButtonF3_1->setText(newTask.getanswer1());
	ButtonF3_2->setText(newTask.getanswer2());
	ButtonF3_3->setText(newTask.getanswer3());
	ButtonF3_4->setText(newTask.getanswer4());
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

