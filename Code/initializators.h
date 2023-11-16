#pragma once
#include "GlobalVariablesForResources.h"
#include "GlobalVariablesOfClasses.h"
#include "taskProcess.h"
#include "ResourceLoadException.h"

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
	if (!texture_window.loadFromFile("Resources/textures/interface/old_background.png")) 
		throw ResourceLoadException("Resources/textures/interface/old_background.png"); 
	if (!texture_window3.loadFromFile("Resources/textures/interface/background3.png"))
		throw ResourceLoadException("Resources/textures/interface/background3.png");  
	if (!texture_person.loadFromFile("Resources/textures/pers.png"))
		throw ResourceLoadException("Resources/textures/pers.png");  
	if (!master_font.loadFromFile("Resources/fonts/testFont.ttf")) 
		throw ResourceLoadException("Resources/fonts/testFont.ttf");  
}

void initializeVariables() {
	playerHeight = 0.6;
	playerWidth = playerHeight * texture_person.getSize().x / texture_person.getSize().y;
	GameMap = Map(); // створюватися ця змінна повинна після загрузки текстр
	GameMap.generateLabyrinth();
}

void initializeInterface() {
	ButtonTest->setPosSize(0.49, 0.3, 0.2, 0.05);

	ButtonTest->setStyle(L"Почати", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonTest2->setStyle(L"Назад", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));

	ButtonTest2->setPosSize(0.1, 0.5, 0.2, 0.05);

	double a = 87 / 271.0 / 4.0 - 0.004;
	double b = a - 87 / 271.0 / 5.0;
	ButtonF3->setPosSize(0.425, 0.25, 0.15, 0.1);
	ButtonF3_1->setPosSize(0.5-2*a + b/2.0, 0.475, a - b, 0.04);
	ButtonF3_2->setPosSize(0.5 - a + b / 2.0, 0.475, a - b, 0.04);
	ButtonF3_3->setPosSize(0.5 + b / 2.0, 0.475, a - b, 0.04);
	ButtonF3_4->setPosSize(0.5 + a + b / 2.0, 0.475, a - b, 0.04);

	ButtonF3->setStyle(L"Приклад", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonF3_1->setStyle(L"Відповідь 1", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonF3_2->setStyle(L"Відповідь 2", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonF3_3->setStyle(L"Відповідь 3", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));
	ButtonF3_4->setStyle(L"Відповідь 4", 0.7, sf::Color(255, 160, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(200, 110, 0, 150), sf::Color(180, 80, 0, 150), sf::Color(50, 20, 0, 255));


	Form1.addInterfaceObj(ButtonTest);
	Form2.addInterfaceObj(ButtonTest2);
	Form1.initializeBackground(texture_window);
	Form3.initializeBackground(texture_window3);
	Form4.initializeBackground(texture_window3);

	Form3.addInterfaceObj(ButtonF3);
	Form3.addInterfaceObj(ButtonF3_1);
	Form3.addInterfaceObj(ButtonF3_2);
	Form3.addInterfaceObj(ButtonF3_3);
	Form3.addInterfaceObj(ButtonF3_4);
}