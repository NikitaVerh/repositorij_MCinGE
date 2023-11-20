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
	if (!texture_window2.loadFromFile("Resources/textures/interface/background2.png"))
		throw ResourceLoadException("Resources/textures/interface/background2.png");
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
	ButtonMenuStart->setPosSize(0.493, 0.28, 0.185, 0.065);
	ButtonMenuStart->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonMenuStart->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonMenuStart->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonMenuStart->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonMenuStart->setText(L"Нова гра");

	ButtonMenuContinue->setPosSize(0.493, 0.28 + 0.1, 0.185, 0.065);
	ButtonMenuContinue->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonMenuContinue->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonMenuContinue->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonMenuContinue->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonMenuContinue->setText(L"Продовжувати");

	ButtonMenuStatic->setPosSize(0.493, 0.28 + 0.1 * 2, 0.185, 0.065);
	ButtonMenuStatic->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonMenuStatic->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonMenuStatic->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonMenuStatic->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonMenuStatic->setText(L"Статистика");

	ButtonMenuInf->setPosSize(0.493, 0.28 + 0.1 * 3, 0.185, 0.065);
	ButtonMenuInf->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonMenuInf->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonMenuInf->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonMenuInf->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonMenuInf->setText(L"Інформація");

	ButtonLobbyEasy->setPosSize(0.4, 0.2, 0.2, 0.05);
	ButtonLobbyEasy->setColorButton(ColorForButtonDesk, ColorForButtonDeskLine);
	ButtonLobbyEasy->setColorHover(ColorForHoverButtonDesk, ColorForHoverButtonDeskLine);
	ButtonLobbyEasy->setColorPressed(ColorForPressedButtonDesk, ColorForPressedButtonDeskLine);
	ButtonLobbyEasy->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonLobbyEasy->setText(L"Легко");

	ButtonLobbyNormal->setPosSize(0.4, 0.3, 0.2, 0.05);
	ButtonLobbyNormal->setColorButton(ColorForButtonDesk, ColorForButtonDeskLine);
	ButtonLobbyNormal->setColorHover(ColorForHoverButtonDesk, ColorForHoverButtonDeskLine);
	ButtonLobbyNormal->setColorPressed(ColorForPressedButtonDesk, ColorForPressedButtonDeskLine);
	ButtonLobbyNormal->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonLobbyNormal->setText(L"Нормально");

	ButtonLobbyHard->setPosSize(0.4, 0.4, 0.2, 0.05);
	ButtonLobbyHard->setColorButton(ColorForButtonDesk, ColorForButtonDeskLine);
	ButtonLobbyHard->setColorHover(ColorForHoverButtonDesk, ColorForHoverButtonDeskLine);
	ButtonLobbyHard->setColorPressed(ColorForPressedButtonDesk, ColorForPressedButtonDeskLine);
	ButtonLobbyHard->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonLobbyHard->setText(L"Складно");

	ButtonLobbyBack->setPosSize(0.04, 0.88, 0.15, 0.05);
	ButtonLobbyBack->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonLobbyBack->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonLobbyBack->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonLobbyBack->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonLobbyBack->setText(L"Назад");

	ButtonLabirint->setPosSize(0.1, 0.1, 0.2, 0.05);
	ButtonLabirint->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonLabirint->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonLabirint->setText(L"обновить");

	ButtonLabirintBack->setPosSize(0.04, 0.88, 0.15, 0.05);
	ButtonLabirintBack->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonLabirintBack->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonLabirintBack->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonLabirintBack->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonLabirintBack->setText(L"Назад");

	ButtonInfBack->setPosSize(0.04, 0.88, 0.15, 0.05);
	ButtonInfBack->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonInfBack->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonInfBack->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonInfBack->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonInfBack->setText(L"Назад");

	ButtonStatBack->setPosSize(0.04, 0.88, 0.15, 0.05);
	ButtonStatBack->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonStatBack->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonStatBack->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonStatBack->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonStatBack->setText(L"Назад");

	ButtonTest->setPosSize(0.425, 0.25, 0.15, 0.1);
	ButtonTest1->setPosSize(0.345, 0.7, 0.073, 0.06);
	ButtonTest1->setColorButton(ColorForButtonDesk, ColorForButtonDeskLine);
	ButtonTest1->setColorHover(ColorForHoverButtonDesk, ColorForHoverButtonDeskLine);
	ButtonTest1->setColorPressed(ColorForPressedButtonDesk, ColorForPressedButtonDeskLine);
	ButtonTest1->setStyleText(0.6, sf::Color(255, 255, 255, 255));
	ButtonTest1->setText(L"Відповідь 1");

	ButtonTest2->setPosSize(0.345 + 0.08, 0.7, 0.071, 0.06);
	ButtonTest2->setColorButton(ColorForButtonDesk, ColorForButtonDeskLine);
	ButtonTest2->setColorHover(ColorForHoverButtonDesk, ColorForHoverButtonDeskLine);
	ButtonTest2->setColorPressed(ColorForPressedButtonDesk, ColorForPressedButtonDeskLine);
	ButtonTest2->setStyleText(0.6, sf::Color(255, 255, 255, 255));
	ButtonTest2->setText(L"Відповідь 2");

	ButtonTest3->setPosSize(0.345 + 0.08*2, 0.7, 0.071, 0.06);
	ButtonTest3->setColorButton(ColorForButtonDesk, ColorForButtonDeskLine);
	ButtonTest3->setColorHover(ColorForHoverButtonDesk, ColorForHoverButtonDeskLine);
	ButtonTest3->setColorPressed(ColorForPressedButtonDesk, ColorForPressedButtonDeskLine);
	ButtonTest3->setStyleText(0.6, sf::Color(255, 255, 255, 255));
	ButtonTest3->setText(L"Відповідь 3");

	ButtonTest4->setPosSize(0.345 + 0.08*3, 0.7, 0.071, 0.06);
	ButtonTest4->setColorButton(ColorForButtonDesk, ColorForButtonDeskLine);
	ButtonTest4->setColorHover(ColorForHoverButtonDesk, ColorForHoverButtonDeskLine);
	ButtonTest4->setColorPressed(ColorForPressedButtonDesk, ColorForPressedButtonDeskLine);
	ButtonTest4->setStyleText(0.6, sf::Color(255, 255, 255, 255));
	ButtonTest4->setText(L"Відповідь 4");

	ButtonTestBack->setPosSize(0.04, 0.88, 0.15, 0.05);
	ButtonTestBack->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonTestBack->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonTestBack->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonTestBack->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonTestBack->setText(L"Назад");

	ButtonTestFinish->setPosSize(0.81, 0.88, 0.15, 0.05);
	ButtonTestFinish->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonTestFinish->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonTestFinish->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonTestFinish->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonTestFinish->setText(L"Завершити");

	ButtonTest->setText(L"Приклад");
	ButtonTest1->setText(L"Відповідь 1");
	ButtonTest2->setText(L"Відповідь 2");
	ButtonTest3->setText(L"Відповідь 3");
	ButtonTest4->setText(L"Відповідь 4");


	ButtonTest->setSnapToBackground(true);
	ButtonTest1->setSnapToBackground(true);
	ButtonTest2->setSnapToBackground(true);
	ButtonTest3->setSnapToBackground(true);
	ButtonTest4->setSnapToBackground(true);
	ButtonTestBack->setSnapToBackground(false);
	ButtonTestFinish->setSnapToBackground(false);
	ButtonMenuStart->setSnapToBackground(true);
	ButtonMenuContinue->setSnapToBackground(true);
	ButtonMenuStatic->setSnapToBackground(true);
	ButtonMenuInf->setSnapToBackground(true);
	ButtonLobbyEasy->setSnapToBackground(true);
	ButtonLobbyNormal->setSnapToBackground(true);
	ButtonLobbyHard->setSnapToBackground(true);
	ButtonLobbyBack->setSnapToBackground(false);
	ButtonLabirintBack->setSnapToBackground(false);

	TextBlackboard->setPosSize(0.36,0.15,0.28,0.5);
	TextBlackboard->setSnapToBackground(true);
	TextBlackboard->setColorFill(sf::Color::Black);
	TextBlackboard->setSize(1 / 20.0);
	TextBlackboard->setText(L"Стрілець робить постріл по мішені один раз. У випадку промаху стрілець робить другий постріл по тій самій мішені. Імовірність влучання в мішень при одному пострілі дорівнює 0,7. Знайдіть імовірність того, що мішень буде уражена.");

	Form_menu.addInterfaceObj(ButtonMenuStart);
	Form_menu.addInterfaceObj(ButtonMenuContinue);
	Form_menu.addInterfaceObj(ButtonMenuStatic);
	Form_menu.addInterfaceObj(ButtonMenuInf);
	Form_lobby.addInterfaceObj(ButtonLobbyBack);
	Form_lobby.addInterfaceObj(ButtonLobbyEasy);
	Form_lobby.addInterfaceObj(ButtonLobbyNormal);
	Form_lobby.addInterfaceObj(ButtonLobbyHard);
	Form_labirint.addInterfaceObj(ButtonLabirint);
	Form_labirint.addInterfaceObj(ButtonLabirintBack);
	// Form_test.addInterfaceObj(ButtonTest);
	Form_test.addInterfaceObj(ButtonTestBack);
	Form_test.addInterfaceObj(ButtonTestFinish);
	Form_stat.addInterfaceObj(ButtonStatBack);
	Form_inf.addInterfaceObj(ButtonInfBack);

	Form_menu.initializeBackground(texture_window);
	Form_lobby.initializeBackground(texture_window3);
	Form_test.initializeBackground(texture_window2);
	Form_stat.initializeBackground(texture_window);
	Form_inf.initializeBackground(texture_window);

	Form_test.addInterfaceObj(ButtonTest1);
	Form_test.addInterfaceObj(ButtonTest2);
	Form_test.addInterfaceObj(ButtonTest3);
	Form_test.addInterfaceObj(ButtonTest4);
	Form_test.addInterfaceObj(TextBlackboard);

}