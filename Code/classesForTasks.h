#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

// клас для задачі/завдання
class Task {
private:
	String exercise; // текст завдання
	String correct_answer; // правильна відповідь
	std::vector<String> answers; // додаткові відповіді
	bool used; // змінна для позначки використання прикладу
public:
	Task() {
		used = false;
		exercise = "exercise";
		correct_answer = "correct_answer";
	}

	Task(String ex, String cor_answ, String answ[3]);

	// метод для встановлення завдання (змінних)
	void setTask(String ex, String cor_answ, String answ[3]); 

	// метод для отримання правильної відповіді
	String getCorrectAnswer();

	// метод для отримання всіх відповідей
	std::vector<String> getAnswers();

	// метод для отримання тексту завдання
	String getExercise();

	// метод для отримання стану використання завдання
	bool getUsed();

	// метод для скидання стану використання завдання
	void resetUsed();
	
	// метод для помітки що завдання було взяте
	void setUsed();
};

// клас, для поєднання завдань у складність
class Difficult {
private:
	String value; // складність
	std::vector<Task> exercise; // масив задач для поточної складності
	int countUsed; // кількість використаних завдань 
public:
	Difficult() {
		countUsed = 0;
	}
	// отримати задачу (рандомну з масиву, тут помічати що задача була взята)
	Task getExercise();

	// додати завдання до поточної складності (складність це цей клас, тобто просто додати у масив задачу)
	void addExercise(Task task);

	// отримати значення value
	String getDifficult();

	// оновити всі завдання (встановити позначку не використано (resetUsed() для всього масиву))
	void resetAllTasks();
};

// клас тема, що об'єднує складності в один масив для однієї теми
class Theme {
private:
	String value; // значення теми
	std::vector<Difficult> difficults; // масив складностей
public:
	// додати нову складність
	void addDifficult(String value);

	// додати нове завдання по складності
	void addExercise(String difficult, Task task);

	// отримати рандомне завдання по складності
	Task getTask(String difficult);

	// отримати масив складностей
	std::vector<String> getDifficults();

	// отримати назву теми
	String getTheme();

	// оновити всі завдання (встановити позначку не використано (resetUsed() для всього масиву))
	void resetAllTasks();
};

// основний клас для використання задач та контролю їх
class Union {
private:
	std::vector<Theme>  themes; // масив тем
public:
	// додати тему
	void addTheme(String value);

	// додати завдання по складності (треба обирати тему вручну)
	void addTask(String difficult, Task task);

	// отримати рандомну задачу згідно теми та складності
	Task getTask(String theme, String difficult);

	// отримати масив тем
	std::vector<String> getThemes();

	// отримати масив складностей
	std::vector<String> getDifficults();

	// оновити всі завдання (скидання поміток використання)
	void resetAllTasks();

	// метод що зчитує з файлу задачі та встановлює їх у всю систему
	void readTasksFromJson();
};
