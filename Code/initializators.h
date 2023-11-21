#pragma once
#include "GlobalVariablesForResources.h"
#include "GlobalVariablesOfClasses.h"
#include "Exceptions.h"

//виняткові ситуації враховані

void loadResources() {
	if (!imageCursor.loadFromFile("Resources/textures/interface/cursor.png"))
		throw ResourceLoadException("Resources/textures/interface/cursor.png");
	;
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

	if (!texture_slider_pic_music.loadFromFile("Resources/textures/interface/slider/pic_music.png"))
		throw ResourceLoadException("Resources/textures/interface/slider/pic_music.png");
	if (!texture_slider_pic_sound.loadFromFile("Resources/textures/interface/slider/pic_sound.png"))
		throw ResourceLoadException("Resources/textures/interface/slider/pic_sound.png");
	if (!texture_slider.loadFromFile("Resources/textures/interface/slider/slider.png"))
		throw ResourceLoadException("Resources/textures/interface/slider/slider.png");
	if (!texture_slider_track.loadFromFile("Resources/textures/interface/slider/slider_track.png"))
		throw ResourceLoadException("Resources/textures/interface/slider/slider_track.png");

	if (!texture_cursor.loadFromFile("Resources/textures/interface/cursor.png"))
		throw ResourceLoadException("Resources/textures/interface/cursor.png");

}

void initializeVariables() {
	playerHeight = 0.6;
	playerWidth = playerHeight * (texture_person.getSize().x/8.0) / texture_person.getSize().y;
	GameMap = Map(); // створюватися ця змінна повинна після загрузки текстр
	exam.load_tasks();
	std::vector<std::string> themes = task_union.getThemes();
	for (const std::string& single_theme : themes) {
		easy_best_marks.push_back(rslt_pair(0, single_theme));
		normal_best_marks.push_back(rslt_pair(0, single_theme));
		hard_best_marks.push_back(rslt_pair(0, single_theme));
		last_marks.push_back(rslt_pair(0, single_theme));
	}
	last_difficulty = "інформація відсутня";
}

void initializeInterface() {
	ButtonMenuStart->setPosSize(0.493, 0.28, 0.185, 0.065);
	ButtonMenuStart->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonMenuStart->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonMenuStart->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonMenuStart->setStyleText(0.6, sf::Color(95, 42, 21, 255));
	ButtonMenuStart->setText("Нова гра");

	ButtonMenuContinue->setPosSize(0.493, 0.28 + 0.1, 0.185, 0.065);
	ButtonMenuContinue->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonMenuContinue->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonMenuContinue->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonMenuContinue->setStyleText(0.6, sf::Color(95, 42, 21, 255));
	ButtonMenuContinue->setText("Продовжувати");

	ButtonMenuStatic->setPosSize(0.493, 0.28 + 0.1 * 2, 0.185, 0.065);
	ButtonMenuStatic->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonMenuStatic->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonMenuStatic->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonMenuStatic->setStyleText(0.6, sf::Color(95, 42, 21, 255));
	ButtonMenuStatic->setText("Статистика");

	ButtonMenuInf->setPosSize(0.493, 0.28 + 0.1 * 3, 0.185, 0.065);
	ButtonMenuInf->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonMenuInf->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonMenuInf->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonMenuInf->setStyleText(0.6, sf::Color(95, 42, 21, 255));
	ButtonMenuInf->setText("Інформація");

	ButtonLobbyEasy->setPosSize(0.4, 0.2, 0.2, 0.05);
	ButtonLobbyEasy->setColorButton(ColorForButtonDesk, ColorForButtonDeskLine);
	ButtonLobbyEasy->setColorHover(ColorForHoverButtonDesk, ColorForHoverButtonDeskLine);
	ButtonLobbyEasy->setColorPressed(ColorForPressedButtonDesk, ColorForPressedButtonDeskLine);
	ButtonLobbyEasy->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonLobbyEasy->setText("Легко");

	ButtonLobbyNormal->setPosSize(0.4, 0.3, 0.2, 0.05);
	ButtonLobbyNormal->setColorButton(ColorForButtonDesk, ColorForButtonDeskLine);
	ButtonLobbyNormal->setColorHover(ColorForHoverButtonDesk, ColorForHoverButtonDeskLine);
	ButtonLobbyNormal->setColorPressed(ColorForPressedButtonDesk, ColorForPressedButtonDeskLine);
	ButtonLobbyNormal->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonLobbyNormal->setText("Нормально");

	ButtonLobbyHard->setPosSize(0.4, 0.4, 0.2, 0.05);
	ButtonLobbyHard->setColorButton(ColorForButtonDesk, ColorForButtonDeskLine);
	ButtonLobbyHard->setColorHover(ColorForHoverButtonDesk, ColorForHoverButtonDeskLine);
	ButtonLobbyHard->setColorPressed(ColorForPressedButtonDesk, ColorForPressedButtonDeskLine);
	ButtonLobbyHard->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonLobbyHard->setText("Складно");

	ButtonLobbyBack->setPosSize(0.04, 0.88, 0.15, 0.05);
	ButtonLobbyBack->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonLobbyBack->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonLobbyBack->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonLobbyBack->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonLobbyBack->setText("Назад");

	ButtonLabirintBack->setPosSize(0.04, 0.07, 0.15, 0.05);
	ButtonLabirintBack->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonLabirintBack->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonLabirintBack->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonLabirintBack->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonLabirintBack->setText("Вийти");

	ButtonInfBack->setPosSize(0.04, 0.88, 0.15, 0.05);
	ButtonInfBack->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonInfBack->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonInfBack->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonInfBack->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonInfBack->setText("Назад");

	ButtonStatBack->setPosSize(0.04, 0.88, 0.15, 0.05);
	ButtonStatBack->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonStatBack->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonStatBack->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonStatBack->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonStatBack->setText("Назад");

	ButtonTest->setPosSize(0.425, 0.25, 0.15, 0.1);
	ButtonTest1->setPosSize(0.345, 0.7, 0.073, 0.06);
	ButtonTest1->setColorButton(ColorForButtonDesk, ColorForButtonDeskLine);
	ButtonTest1->setColorHover(ColorForHoverButtonDesk, ColorForHoverButtonDeskLine);
	ButtonTest1->setColorPressed(ColorForPressedButtonDesk, ColorForPressedButtonDeskLine);
	ButtonTest1->setStyleText(0.6, sf::Color(255, 255, 255, 255));
	ButtonTest1->setText("Відповідь 1");

	ButtonTest2->setPosSize(0.345 + 0.08, 0.7, 0.071, 0.06);
	ButtonTest2->setColorButton(ColorForButtonDesk, ColorForButtonDeskLine);
	ButtonTest2->setColorHover(ColorForHoverButtonDesk, ColorForHoverButtonDeskLine);
	ButtonTest2->setColorPressed(ColorForPressedButtonDesk, ColorForPressedButtonDeskLine);
	ButtonTest2->setStyleText(0.6, sf::Color(255, 255, 255, 255));
	ButtonTest2->setText("Відповідь 2");

	ButtonTest3->setPosSize(0.345 + 0.08*2, 0.7, 0.071, 0.06);
	ButtonTest3->setColorButton(ColorForButtonDesk, ColorForButtonDeskLine);
	ButtonTest3->setColorHover(ColorForHoverButtonDesk, ColorForHoverButtonDeskLine);
	ButtonTest3->setColorPressed(ColorForPressedButtonDesk, ColorForPressedButtonDeskLine);
	ButtonTest3->setStyleText(0.6, sf::Color(255, 255, 255, 255));
	ButtonTest3->setText("Відповідь 3");

	ButtonTest4->setPosSize(0.345 + 0.08*3, 0.7, 0.071, 0.06);
	ButtonTest4->setColorButton(ColorForButtonDesk, ColorForButtonDeskLine);
	ButtonTest4->setColorHover(ColorForHoverButtonDesk, ColorForHoverButtonDeskLine);
	ButtonTest4->setColorPressed(ColorForPressedButtonDesk, ColorForPressedButtonDeskLine);
	ButtonTest4->setStyleText(0.6, sf::Color(255, 255, 255, 255));
	ButtonTest4->setText("Відповідь 4");

	ButtonTestBack->setPosSize(0.04, 0.88, 0.15, 0.05);
	ButtonTestBack->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonTestBack->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonTestBack->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonTestBack->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonTestBack->setText("Назад");

	ButtonTestFinish->setPosSize(0.81, 0.88, 0.15, 0.05);
	ButtonTestFinish->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonTestFinish->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonTestFinish->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonTestFinish->setStyleText(0.6, sf::Color(0, 0, 0, 255));
	ButtonTestFinish->setText("Завершити");

	ButtonTest->setText("Приклад");
	ButtonTest1->setText("Відповідь 1");
	ButtonTest2->setText("Відповідь 2");
	ButtonTest3->setText("Відповідь 3");
	ButtonTest4->setText("Відповідь 4");


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
	TextBlackboard->setNeedUpdateWords(true);
	TextBlackboard->setColorFill(sf::Color::Black);
	TextBlackboard->setSize(1 / 20.0);
	TextBlackboard->setText("Стрілець робить постріл по мішені один раз. У випадку промаху стрілець робить другий постріл по тій самій мішені. Імовірність влучання в мішень при одному пострілі дорівнює 0,7. Знайдіть імовірність того, що мішень буде уражена.");

	TextStatistics->setPosSize(0.2, 0.1, 0.6, 0.5);
	TextStatistics->setSnapToBackground(true);
	TextStatistics->setColorFill(sf::Color::Black);
	TextStatistics->setSize(1 / 40.0);
	TextStatistics->setText("Стрілець робить постріл по мішені один раз. У випадку промаху стрілець робить другий постріл по тій самій мішені. Імовірність влучання в мішень при одному пострілі дорівнює 0,7. Знайдіть імовірність того, що мішень буде уражена.");

	SliderMusic->setPosSize(0, 0, 0, 0.05);
	SliderSound->setPosSize(0, 0.05, 0, 0.05);

	SliderMusic->setTexturePic(texture_slider_pic_music);
	SliderSound->setTexturePic(texture_slider_pic_sound);

	SliderMusic->setSnapToBackground(false);
	SliderSound->setSnapToBackground(false);

	Form_menu.addInterfaceObj(ButtonMenuStart);
	Form_menu.addInterfaceObj(ButtonMenuContinue);
	Form_menu.addInterfaceObj(ButtonMenuStatic);
	Form_menu.addInterfaceObj(ButtonMenuInf);

	Form_menu.addInterfaceObj(SliderMusic);
	Form_menu.addInterfaceObj(SliderSound);

	Form_lobby.addInterfaceObj(ButtonLobbyBack);
	Form_lobby.addInterfaceObj(ButtonLobbyEasy);
	Form_lobby.addInterfaceObj(ButtonLobbyNormal);
	Form_lobby.addInterfaceObj(ButtonLobbyHard);
	Form_labirint.addInterfaceObj(ButtonLabirintBack);
	// Form_test.addInterfaceObj(ButtonTest);
	Form_test.addInterfaceObj(ButtonTestBack);
	Form_test.addInterfaceObj(ButtonTestFinish);
	Form_stat.addInterfaceObj(ButtonStatBack);
	Form_stat.addInterfaceObj(TextStatistics);
	Form_inf.addInterfaceObj(ButtonInfBack);

	Form_menu.setBackgroundCoefficient(6.0);

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

void initializeCursorAndIcon(sf::RenderWindow& window) {
	sf::Vector2u clickSpot(0, 0);
	cursor.loadFromPixels(imageCursor.getPixelsPtr(), imageCursor.getSize(), clickSpot);
	
}
