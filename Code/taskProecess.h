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
	Task() {
		instance = "Instance";
		answer1 = "Answer1";
		answer2 = "Answer2";
		answer3 = "Answer3";
		answer4 = "Answer4";
	}
	void setTask(sf::String Instance, sf::String Answer1, sf::String Answer2,
		sf::String Answer3, sf::String Answer4, sf::String correctAnswer) {
		instance = Instance;
		answer1 = Answer1;
		answer2 = Answer2;
		answer3 = Answer3;
		answer4 = Answer4;
		correct_answer = correctAnswer;
	}
	static std::vector<Task> loadTasksFromFile(const std::string& filename, const std::string& category, const std::string& difficulty) {
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
	static std::vector<Task> getRandomTasks(const std::vector<Task>& allTasks, size_t taskCount) {
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

	bool isCorrectAnswer(const sf::String& userAnswer) const {
		return userAnswer == correct_answer;  
	}

	static Task generateNewTask(const std::string& filename, const std::string& category, const std::string& difficulty) 
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
	sf::String getInstance() { return instance; }
	sf::String getanswer1() { return answer1; }
	sf::String getanswer2() { return answer2; }
	sf::String getanswer3() { return answer3; }
	sf::String getanswer4() { return answer4; }
	sf::String getCorrectAnswer() const { return correct_answer; }
};


//Task getTask(int theme);




//void stopTest(); 
//
////завантаження прикладів з файлу
//bool loadQuestions(const std::string& filename, json& tasks); //+++
//
////старт виконання програми
//bool runEntireGame(json& tasks);



//поки непотрібні 

//запуск гри, зчитка питань з файлу 
//void runTask(); //+++
//void startTest() {};