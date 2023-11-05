/*
В цьому файлі йде реалізація головних методів
*/

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GlobalVariablesForResources.h"
#include "GlobalVariablesOfClasses.h"
#include "taskProecess.h"

//тимчасові бібліотеки
#include <iostream>



// метод що виконується один раз при старті програми
void startProgram() {
	if (!texture_block_wall.loadFromFile("Resources/textures/blocks/texture_wall.png")); //колян
	if (!texture_block_door.loadFromFile("Resources/textures/blocks/texture_door.png")); //колян
	if (!texture_block_ladder.loadFromFile("Resources/textures/blocks/texture_ladder.png")); //колян
	if (!texture_wall_left.loadFromFile("Resources/textures/blocks/texture_wall_left.png")); //колян
	if (!texture_wall_right.loadFromFile("Resources/textures/blocks/texture_wall_right.png")); //колян
	if (!texture_window.loadFromFile("Resources/textures/interface/background.png")); //колян
	if (!texture_window3.loadFromFile("Resources/textures/interface/background3.png")); //колян


	master_font.loadFromFile("Resources/fonts/testFont.ttf");//колян

	ButtonTest->setPosSize(0.49, 0.3, 0.2, 0.05);

	ButtonTest->setStyle(L"Почати", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonTest2->setStyle(L"Назад", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));

	ButtonTest2->setPosSize(0.1, 0.5, 0.2, 0.05);


	ButtonF3->setPosSize(0.2, 0.2, 0.6, 0.05);
	ButtonF3_1->setPosSize(0.2, 0.4, 0.1, 0.05);
	ButtonF3_2->setPosSize(0.35, 0.4, 0.1, 0.05);
	ButtonF3_3->setPosSize(0.5, 0.4, 0.1, 0.05);
	ButtonF3_4->setPosSize(0.65, 0.4, 0.1, 0.05);

	ButtonF3->setStyle(L"Приклад", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonF3_1->setStyle(L"Відповідь 1", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonF3_2->setStyle(L"Відповідь 2", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonF3_3->setStyle(L"Відповідь 3", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonF3_4->setStyle(L"Відповідь 4", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));


	Form1.addInterfaceObj(ButtonTest);
	Form2.addInterfaceObj(ButtonTest2);
	Form1.initializeBackground(texture_window);
	Form3.initializeBackground(texture_window3);

	Form3.addInterfaceObj(ButtonF3);
	Form3.addInterfaceObj(ButtonF3_1);
	Form3.addInterfaceObj(ButtonF3_2);
	Form3.addInterfaceObj(ButtonF3_3);
	Form3.addInterfaceObj(ButtonF3_4);

	GameMap = Map(); // створюватися ця змінна повинна після загрузки текстр
	GameMap.generateLabyrinth();
}

// метод що виконується один раз перед закриттям программи
void stopProgram(sf::RenderWindow& window) {

	window.close();
}



sf::String answerF3_1;
sf::String answerF3_2;
sf::String answerF3_3;
sf::String answerF3_4;
sf::String correctAnswer;

int correctAnswersCount = 0; // Количество правильных ответов на текущем уровне
int playerLives = 3; // Количество жизней игрока

// тимчасово
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
// метод для обробки подій вікна

void windowEventHandling(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {

		if (sf::Event::Closed == event.type) { stopProgram(window); }
		if (sf::Event::KeyReleased == event.type) {
			if (event.key.code == sf::Keyboard::Key::Num1) { Menu = menu_main; std::cout << "Menu: " << Menu << std::endl; }
			if (event.key.code == sf::Keyboard::Key::Num2) { Menu = menu_game;  std::cout << "Menu: " << Menu << std::endl; }
			if (event.key.code == sf::Keyboard::Key::Num3) {
				Menu = menu_test;  std::cout << "Menu: " << Menu << std::endl;
				//stopTest(); 
				//runEntireGame(tasks);
				SetTask("Resources/json/task.json", "Вища Математика", currentDifficulty);
			}
		}
	}


	switch (Menu) {

	case menu_main:
		if (ButtonTest->Released()) { std::cout << "released" << std::endl; Menu = menu_game; }
		break;
	case menu_game:
		if (ButtonTest2->Released()) { std::cout << "released" << std::endl;/* Menu = menu_main; */GameMap.generateLabyrinth(); }
		break;
	case menu_test:
		if (ButtonF3->Released()) { std::cout << "F" << std::endl; }
		if (ButtonF3_1->Released())
		{
			CheckAnswer(answerF3_1);
			SetTask("Resources/json/task.json", "Вища Математика", currentDifficulty);
			std::cout << "F1" << std::endl;
		}
		if (ButtonF3_2->Released())
		{
			CheckAnswer(answerF3_2);
			SetTask("Resources/json/task.json", "Вища Математика", currentDifficulty);
			std::cout << "F2" << std::endl;
		}
		if (ButtonF3_3->Released())
		{
			CheckAnswer(answerF3_3);
			SetTask("Resources/json/task.json", "Вища Математика", currentDifficulty);
			std::cout << "F3" << std::endl;
		}
		if (ButtonF3_4->Released())
		{
			CheckAnswer(answerF3_4);
			SetTask("Resources/json/task.json", "Вища Математика", currentDifficulty);
			std::cout << "F4" << std::endl;
		}
		break;
	default:
		break;
	}
}

// метод для оновлення інтерфейсу
void UpdateGraphic(sf::RenderWindow& window) {
	window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));

	sizeBlock = window.getSize().y / float(mapHeight);
	Form1.updateForm(window);
	Form2.updateForm(window);
	Form3.updateForm(window);

}

// метод для відображення графіки
void GraphicRender(sf::RenderWindow& window) {

	window.clear();
	if (Menu == menu_main) {
		Form1.drawBackground(window);
		Form1.draw(window);
	}
	if (Menu == menu_game) {
		GameMap.draw(window);
		Form2.draw(window);
	}
	if (Menu == menu_test) {
		Form3.drawBackground(window);
		Form3.draw(window);
	}
	window.display();
}