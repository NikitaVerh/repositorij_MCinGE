#pragma once
#include "GlobalVariablesForResources.h"
#include "GlobalVariablesOfClasses.h"
#include "Exceptions.h"

//виняткові ситуації враховані

void loadResources() {
	if (!texture_block_wall.loadFromFile("Resources/textures/blocks/texture_wall.png"))
		throw ResourceLoadException("Resources/textures/blocks/texture_wall.png");  
	if (!texture_block_door.loadFromFile("Resources/textures/blocks/texture_door.png"))  
		throw ResourceLoadException("Resources/textures/blocks/texture_door.png"); 
	if (!texture_block_ladder.loadFromFile("Resources/textures/blocks/texture_ladder.png"))
		throw ResourceLoadException("Resources/textures/blocks/texture_ladder.png");  
	if (!texture_wall_left.loadFromFile("Resources/textures/blocks/texture_wall_left.png")) 
		throw ResourceLoadException("Resources/textures/blocks/texture_wall_left.png");  
	if (!texture_wall_right.loadFromFile("Resources/textures/blocks/texture_wall_right.png")) 
		throw ResourceLoadException("Resources/textures/blocks/texture_wall_right.png");  
	if (!texture_window.loadFromFile("Resources/textures/interface/background.png")) 
		throw ResourceLoadException("Resources/textures/interface/background.png"); 
	if (!texture_window3.loadFromFile("Resources/textures/interface/background3.png"))
		throw ResourceLoadException("Resources/textures/interface/background3.png");  
	if (!texture_person.loadFromFile("Resources/textures/player-sprite.png"))
		throw ResourceLoadException("Resources/textures/player-sprite.png");
	if (!texture_person_left.loadFromFile("Resources/textures/player-sprite-left.png"))
		throw ResourceLoadException("Resources/textures/player-sprite-left.png");
	if (!master_font.loadFromFile("Resources/fonts/master_font.ttf")) 
		throw ResourceLoadException("Resources/fonts/master_font+.ttf");  
}

void initializeVariables() {
	playerHeight = 0.6;
	playerWidth = playerHeight * (texture_person.getSize().x/8.0) / texture_person.getSize().y;
	GameMap = Map(); // створюватися ця змінна повинна після загрузки текстр
	exam.load_tasks();
	GameMap.generateLabyrinth();
}

void initializeInterface() {
	ButtonF1_1->setPosSize(0.49, 0.3, 0.2, 0.05);
	ButtonF1_1->setStyle(L"Нова гра", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));

	ButtonF1_2->setPosSize(0.49, 0.4, 0.2, 0.05);
	ButtonF1_2->setStyle(L"Статистика", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	
	ButtonF1_3->setPosSize(0.49, 0.5, 0.2, 0.05);
	ButtonF1_3->setStyle(L"Інформація", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));

	ButtonF2_easy->setStyle(L"Легко", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonF2_easy->setPosSize(0.1, 0.4, 0.2, 0.05);

	ButtonF2_back->setStyle(L"Назад", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonF2_back->setPosSize(0.1, 0.8, 0.2, 0.05);

	ButtonF3->setStyle(L"Назад", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonF3->setPosSize(0.1, 0.5, 0.2, 0.05);

	ButtonF5_back->setPosSize(0.49, 0.3, 0.2, 0.05);
	ButtonF5_back->setStyle(L"Назад", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));

	ButtonF6_back->setPosSize(0.49, 0.3, 0.2, 0.05);
	ButtonF6_back->setStyle(L"Назад", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));

	double a = 87 / 271.0 / 4.0 - 0.004;
	double b = a - 87 / 271.0 / 5.0;
	ButtonF4->setPosSize(0.425, 0.25, 0.15, 0.1);
	ButtonF4_1->setPosSize(0.5-2*a + b/2.0, 0.475, a - b, 0.04);
	ButtonF4_2->setPosSize(0.5 - a + b / 2.0, 0.475, a - b, 0.04);
	ButtonF4_3->setPosSize(0.5 + b / 2.0, 0.475, a - b, 0.04);
	ButtonF4_4->setPosSize(0.5 + a + b / 2.0, 0.475, a - b, 0.04);
	ButtonF4_back->setPosSize(0.6, 0.7, 0.2, 0.05);
	ButtonF4_back->setStyle(L"Назад", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));

	ButtonF4->setStyle(L"Приклад", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonF4_1->setStyle(L"Відповідь 1", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonF4_2->setStyle(L"Відповідь 2", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonF4_3->setStyle(L"Відповідь 3", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonF4_4->setStyle(L"Відповідь 4", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));


	ButtonF4->setSnapToBackground(true);
	ButtonF4_1->setSnapToBackground(true);
	ButtonF4_2->setSnapToBackground(true);
	ButtonF4_3->setSnapToBackground(true);
	ButtonF4_4->setSnapToBackground(true);
	ButtonF1_1->setSnapToBackground(true);
	ButtonF1_2->setSnapToBackground(true);
	ButtonF1_3->setSnapToBackground(true);

	TextBlackboard->setPosSize(0.341,0.12,0.32,0.3275);
	TextBlackboard->setSnapToBackground(true);
	TextBlackboard->setColorFill(sf::Color::Black);
	TextBlackboard->setSize(1 / 30.0);
	TextBlackboard->setText(L"Стрілець робить постріл по мішені один раз. У випадку промаху стрілець робить другий постріл по тій самій мішені. Імовірність влучання в мішень при одному пострілі дорівнює 0,7. Знайдіть імовірність того, що мішень буде уражена.");

	Form1.addInterfaceObj(ButtonF1_1);
	Form1.addInterfaceObj(ButtonF1_2);
	Form1.addInterfaceObj(ButtonF1_3);
	Form2.addInterfaceObj(ButtonF2_back);
	Form2.addInterfaceObj(ButtonF2_easy);
	Form3.addInterfaceObj(ButtonF3);
	//Form4.addInterfaceObj(ButtonF4);
	Form4.addInterfaceObj(ButtonF4_back);
	Form5.addInterfaceObj(ButtonF5_back);
	Form6.addInterfaceObj(ButtonF6_back);

	Form1.initializeBackground(texture_window);
	Form2.initializeBackground(texture_window3);
	Form4.initializeBackground(texture_window3);
	Form5.initializeBackground(texture_window);
	Form6.initializeBackground(texture_window);

	Form4.addInterfaceObj(ButtonF4_1);
	Form4.addInterfaceObj(ButtonF4_2);
	Form4.addInterfaceObj(ButtonF4_3);
	Form4.addInterfaceObj(ButtonF4_4);
	Form4.addInterfaceObj(TextBlackboard);

}