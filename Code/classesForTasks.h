#pragma once
#pragma execution_character_set("utf-8")
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <cstdlib> // для rand()
#include <ctime> // для time()
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace sf;
using namespace std;

// клас для задачі/завдання
class Task {
private:
	string exercise; // текст завдання
	string correct_answer; // правильна відповідь
	std::vector<string> answers; // додаткові відповіді
	bool used; // змінна для позначки використання прикладу
public:
	Task() : used(false), exercise("exercise"), correct_answer("correct_answer") {}

	Task(string ex, string cor_answ, std::vector<string> answ)
		: exercise(ex), correct_answer(cor_answ), answers(answ), used(false) {}

	// метод для встановлення завдання (змінних)
	void setTask(string ex, string cor_answ, std::vector<string> answ) {
		exercise = ex;
		correct_answer = cor_answ;
		answers = answ;
		used = false;
	}

	// метод для отримання правильної відповіді
	string getCorrectAnswer() { return correct_answer; };

	// метод для отримання всіх відповідей
	std::vector<string> getAnswers() { return answers; };

	// метод для отримання тексту завдання
	string getExercise() { return exercise; };

	// метод для отримання стану використання завдання
	bool getUsed() { return used; };

	// метод для скидання стану використання завдання
	void resetUsed() { used = false; };
	
	// метод для помітки що завдання було взяте
	void setUsed() { used = true; };  
};

// клас, для поєднання завдань у складність
class Difficult {
private:
	string value; // складність
	std::vector<Task> exercises; // масив задач для поточної складності
	int countUsed; // кількість використаних завдань 
public:
	Difficult(string val) : value(val), countUsed(0) {}

	// отримати задачу (рандомну з масиву, тут помічати що задача була взята)
	Task getExercise();

	// додати завдання до поточної складності (складність це цей клас, тобто просто додати у масив задачу)
	void addExercise(Task task);

	// отримати значення value
	string getDifficult() { return value; };

	// оновити всі завдання (встановити позначку не використано (resetUsed() для всього масиву))
	void resetAllTasks();
};

// клас тема, що об'єднує складності в один масив для однієї теми
class Theme {
private:
	string value; // значення теми
	std::vector<Difficult> difficults; // масив складностей
public:
	Theme(string val) : value(val) {}

	// додати нову складність
	void addDifficult(string value);

	// додати нове завдання по складності
	void addExercise(string difficult, Task task);

	// отримати рандомне завдання по складності
	Task getTask(string difficult); //+

	// отримати масив складностей
	std::vector<string> getDifficults(); //+

	// отримати назву теми
	string getTheme() { return value; }; //+

	// оновити всі завдання (встановити позначку не використано (resetUsed() для всього масиву))
	void resetAllTasks();//+
};

// основний клас для використання задач та контролю їх
class Union {
private:
	std::vector<Theme> themes; // масив тем
public:
	// додати тему
	void addTheme(string value);

	// додати завдання по складності (треба обирати тему вручну)
	void addTask(string theme, string difficult, Task task);

	// отримати рандомну задачу згідно теми та складності
	Task getTask(string theme, string difficult);

	// отримати масив тем
	std::vector<string> getThemes();

	// отримати масив складностей
	std::vector<string> getDifficults(string theme) {
		for (auto& t : themes) {
			if (t.getTheme() == theme) {
				return t.getDifficults();
			}
		}
		return std::vector<string>(); // повернути порожній вектор, якщо не знайдено
	}

	// оновити всі завдання (скидання поміток використання)
	void resetAllTasks();

	// метод що зчитує з файлу задачі та встановлює їх у всю систему
	void readTasksFromJson();

};
