#pragma once
#include "GlobalVariablesForResources.h"
#include "GlobalVariablesOfClasses.h"
#include "Exceptions.h"

//виняткові ситуації враховані

void loadResources() {
	if (!imageCursor.loadFromFile("Resources/textures/interface/cursor.png"))
		throw ResourceLoadException("Resources/textures/interface/cursor.png");
	for (int i = 0; i < maxIdTextres; i++) {
		if (!texture_block_wall[i].loadFromFile("Resources/textures/blocks/texture_wall"+std::to_string(i)+".png"))
			throw ResourceLoadException("Resources/textures/blocks/texture_wall" + std::to_string(i) + ".png");
		if (!texture_block_door[i].loadFromFile("Resources/textures/blocks/texture_door" + std::to_string(i) + ".png"))
			throw ResourceLoadException("Resources/textures/blocks/texture_door" + std::to_string(i) + ".png");
		if (!texture_block_ladder[i].loadFromFile("Resources/textures/blocks/texture_ladder" + std::to_string(i) + ".png"))
			throw ResourceLoadException("Resources/textures/blocks/texture_ladder" + std::to_string(i) + ".png");
	}
	if (!texture_wall_left.loadFromFile("Resources/textures/blocks/texture_wall_left.png")) 
		throw ResourceLoadException("Resources/textures/blocks/texture_wall_left.png");  
	if (!texture_wall_right.loadFromFile("Resources/textures/blocks/texture_wall_right.png")) 
		throw ResourceLoadException("Resources/textures/blocks/texture_wall_right.png");  
	
	if (!texture_window.loadFromFile("Resources/textures/interface/background.png")) 
		throw ResourceLoadException("Resources/textures/interface/background.png"); 
	if (!texture_window2.loadFromFile("Resources/textures/interface/background_room.png"))
		throw ResourceLoadException("Resources/textures/interface/background_room.png");
	if (!texture_window3.loadFromFile("Resources/textures/interface/background_lobby.png"))
		throw ResourceLoadException("Resources/textures/interface/background_lobby.png");  
	if (!texture_window4.loadFromFile("Resources/textures/interface/background_static.png"))
		throw ResourceLoadException("Resources/textures/interface/background_static.png");
	if (!texture_window5.loadFromFile("Resources/textures/interface/background_inf.png"))
		throw ResourceLoadException("Resources/textures/interface/background_inf.png");

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
	GameMap.generateLabyrinth();
	player.Player_set_source();
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

void initializeInterface() { //метод для ініціалізації об'єктів

	ButtonMenuContinue->setPosSize(0.493, 0.28, 0.185, 0.065);
	ButtonMenuContinue->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonMenuContinue->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonMenuContinue->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonMenuContinue->setStyleText(0.6, color_menu);
	ButtonMenuContinue->setText("Продовжувати");

	ButtonMenuStart->setPosSize(0.493, 0.28 + 0.1, 0.185, 0.065);
	ButtonMenuStart->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonMenuStart->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonMenuStart->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonMenuStart->setStyleText(0.6, color_menu);
	ButtonMenuStart->setText("Нова гра");

	ButtonMenuStatic->setPosSize(0.493, 0.28 + 0.1 * 2, 0.185, 0.065);
	ButtonMenuStatic->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonMenuStatic->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonMenuStatic->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonMenuStatic->setStyleText(0.6, color_menu);
	ButtonMenuStatic->setText("Статистика");

	ButtonMenuInf->setPosSize(0.493, 0.28 + 0.1 * 3, 0.185, 0.065);
	ButtonMenuInf->setColorButton(ColorForButton, ColorForButtonLine);
	ButtonMenuInf->setColorHover(ColorForHoverButton, ColorForHoverButtonLine);
	ButtonMenuInf->setColorPressed(ColorForPressedButton, ColorForPressedButtonLine);
	ButtonMenuInf->setStyleText(0.6, color_menu);
	ButtonMenuInf->setText("Інформація");

	ButtonLobbyEasy->setPosSize(0.4, 0.2, 0.2, 0.05);
	ButtonLobbyEasy->setColorButton(ColorForButtonBoard, ColorForButtonBoardLine);
	ButtonLobbyEasy->setColorHover(ColorForHoverButtonBoard, ColorForHoverButtonBoardLine);
	ButtonLobbyEasy->setColorPressed(ColorForPressedButtonBoard, ColorForPressedButtonBoardLine);
	ButtonLobbyEasy->setStyleText(0.6, sf::Color(255, 255, 255, 255));
	ButtonLobbyEasy->setText("Легко");

	ButtonLobbyNormal->setPosSize(0.4, 0.3, 0.2, 0.05);
	ButtonLobbyNormal->setColorButton(ColorForButtonBoard, ColorForButtonBoardLine);
	ButtonLobbyNormal->setColorHover(ColorForHoverButtonBoard, ColorForHoverButtonBoardLine);
	ButtonLobbyNormal->setColorPressed(ColorForPressedButtonBoard, ColorForPressedButtonBoardLine);
	ButtonLobbyNormal->setStyleText(0.6, sf::Color(255, 255, 255, 255));
	ButtonLobbyNormal->setText("Нормально");

	ButtonLobbyHard->setPosSize(0.4, 0.4, 0.2, 0.05);
	ButtonLobbyHard->setColorButton(ColorForButtonBoard, ColorForButtonBoardLine);
	ButtonLobbyHard->setColorHover(ColorForHoverButtonBoard, ColorForHoverButtonBoardLine);
	ButtonLobbyHard->setColorPressed(ColorForPressedButtonBoard, ColorForPressedButtonBoardLine);
	ButtonLobbyHard->setStyleText(0.6, sf::Color(255, 255, 255, 255));
	ButtonLobbyHard->setText("Складно");

	ButtonLobbyBack->setPosSize(0.04, 0.88, 0.15, 0.05);
	ButtonLobbyBack->setColorButton(ColorForButtonGame, ColorForButtonGameLine);
	ButtonLobbyBack->setColorHover(ColorForHoverButtonGame, ColorForHoverButtonGameLine);
	ButtonLobbyBack->setColorPressed(ColorForPressedButtonGame, ColorForPressedButtonGameLine);
	ButtonLobbyBack->setStyleText(0.6, color_button);
	ButtonLobbyBack->setText("Назад");

	ButtonLabirintBack->setPosSize(0.04, 0.05, 0.15, 0.05);
	ButtonLabirintBack->setColorButton(ColorForButtonGame, ColorForButtonGameLine);
	ButtonLabirintBack->setColorHover(ColorForHoverButtonGame, ColorForHoverButtonGameLine);
	ButtonLabirintBack->setColorPressed(ColorForPressedButtonGame, ColorForPressedButtonGameLine);
	ButtonLabirintBack->setStyleText(0.6, color_button);
	ButtonLabirintBack->setText("Вийти");

	ButtonInfBack->setPosSize(0.278, 0.76, 0.05, 0.06);
	ButtonInfBack->setColorButton(ColorForButtonGame, ColorForButtonGameLine);
	ButtonInfBack->setColorHover(ColorForHoverButtonGame, ColorForHoverButtonGameLine);
	ButtonInfBack->setColorPressed(ColorForPressedButtonGame, ColorForPressedButtonGameLine);
	ButtonInfBack->setStyleText(0.6, color_button);
	ButtonInfBack->setText("Назад");

	ButtonStatBack->setPosSize(0.278, 0.76, 0.05, 0.06);
	ButtonStatBack->setColorButton(ColorForButtonGame, ColorForButtonGameLine);
	ButtonStatBack->setColorHover(ColorForHoverButtonGame, ColorForHoverButtonGameLine);
	ButtonStatBack->setColorPressed(ColorForPressedButtonGame, ColorForPressedButtonGameLine);
	ButtonStatBack->setStyleText(0.6, color_button);
	ButtonStatBack->setText("Назад");

	ButtonTest->setPosSize(0.425, 0.25, 0.15, 0.1);
	ButtonTest1->setPosSize(0.345, 0.7, 0.073, 0.06);
	ButtonTest1->setColorButton(ColorForButtonBoard, ColorForButtonBoardLine);
	ButtonTest1->setColorHover(ColorForHoverButtonBoard, ColorForHoverButtonBoardLine);
	ButtonTest1->setColorPressed(ColorForPressedButtonBoard, ColorForPressedButtonBoardLine);
	ButtonTest1->setStyleText(0.6, sf::Color(255, 255, 255, 255));
	ButtonTest1->setText("Відповідь 1");

	ButtonTest2->setPosSize(0.345 + 0.08, 0.7, 0.071, 0.06);
	ButtonTest2->setColorButton(ColorForButtonBoard, ColorForButtonBoardLine);
	ButtonTest2->setColorHover(ColorForHoverButtonBoard, ColorForHoverButtonBoardLine);
	ButtonTest2->setColorPressed(ColorForPressedButtonBoard, ColorForPressedButtonBoardLine);
	ButtonTest2->setStyleText(0.6, sf::Color(255, 255, 255, 255));
	ButtonTest2->setText("Відповідь 2");

	ButtonTest3->setPosSize(0.345 + 0.08*2, 0.7, 0.071, 0.06);
	ButtonTest3->setColorButton(ColorForButtonBoard, ColorForButtonBoardLine);
	ButtonTest3->setColorHover(ColorForHoverButtonBoard, ColorForHoverButtonBoardLine);
	ButtonTest3->setColorPressed(ColorForPressedButtonBoard, ColorForPressedButtonBoardLine);
	ButtonTest3->setStyleText(0.6, sf::Color(255, 255, 255, 255));
	ButtonTest3->setText("Відповідь 3");

	ButtonTest4->setPosSize(0.345 + 0.08*3, 0.7, 0.071, 0.06);
	ButtonTest4->setColorButton(ColorForButtonBoard, ColorForButtonBoardLine);
	ButtonTest4->setColorHover(ColorForHoverButtonBoard, ColorForHoverButtonBoardLine);
	ButtonTest4->setColorPressed(ColorForPressedButtonBoard, ColorForPressedButtonBoardLine);
	ButtonTest4->setStyleText(0.6, sf::Color(255, 255, 255, 255));
	ButtonTest4->setText("Відповідь 4");

	ButtonTestBack->setPosSize(0.47, 0.7, 0.05, 0.08);
	ButtonTestBack->setColorButton(ColorForButtonGame, ColorForButtonGameLine);
	ButtonTestBack->setColorHover(ColorForHoverButtonGame, ColorForHoverButtonGameLine);
	ButtonTestBack->setColorPressed(ColorForPressedButtonGame, ColorForPressedButtonGameLine);
	ButtonTestBack->setStyleText(0.6, color_button);
	ButtonTestBack->setText("Назад");

	ButtonTestFinish->setPosSize(0.68, 0.77, 0.06, 0.07);
	ButtonTestFinish->setColorButton(ColorForButtonGame, ColorForButtonGameLine);
	ButtonTestFinish->setColorHover(ColorForHoverButtonGame, ColorForHoverButtonGameLine);
	ButtonTestFinish->setColorPressed(ColorForPressedButtonGame, ColorForPressedButtonGameLine);
	ButtonTestFinish->setStyleText(0.6, color_button);
	ButtonTestFinish->setText("Завершити");

	ButtonTest->setSnapToBackground(true);
	ButtonTest1->setSnapToBackground(true);
	ButtonTest2->setSnapToBackground(true);
	ButtonTest3->setSnapToBackground(true);
	ButtonTest4->setSnapToBackground(true);
	ButtonTestBack->setSnapToBackground(true);
	ButtonTestFinish->setSnapToBackground(true);
	ButtonMenuStart->setSnapToBackground(true);
	ButtonMenuContinue->setSnapToBackground(true);
	ButtonMenuStatic->setSnapToBackground(true);
	ButtonMenuInf->setSnapToBackground(true);
	ButtonLobbyEasy->setSnapToBackground(true);
	ButtonLobbyNormal->setSnapToBackground(true);
	ButtonLobbyHard->setSnapToBackground(true);
	ButtonLobbyBack->setSnapToBackground(false);
	ButtonLabirintBack->setSnapToBackground(false);
	ButtonInfBack->setSnapToBackground(true);
	ButtonStatBack->setSnapToBackground(true);

	TextBlackboard->setPosSize(0.36,0.15,0.28,0.5);
	TextBlackboard->setSnapToBackground(true);
	TextBlackboard->setNeedUpdateWords(true);
	TextBlackboard->setColorFill(sf::Color::White);
	TextBlackboard->setSize(1 / 20.0);

	TextStatistics->setPosSize(0.35, 0.14, 0.3, 0.65);
	TextStatistics->setSnapToBackground(true);
	TextStatistics->setColorFill(sf::Color::White);
	TextStatistics->setSize(1 / 39.0);

	SliderMusic->setPosSize(0, 0, 0, 0.065);
	SliderSound->setPosSize(0, 0.065 + 0.005, 0, 0.065);

	SliderMusic->setTexturePic(texture_slider_pic_music);
	SliderSound->setTexturePic(texture_slider_pic_sound);

	SliderMusic->setSnapToBackground(false);
	SliderSound->setSnapToBackground(false);

	particles->setPosSize(0, 0, 0, 1 / float(texture_window.getSize().y));

	Form_menu.addInterfaceObj(particles);
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
	Form_stat.initializeBackground(texture_window4);
	Form_inf.initializeBackground(texture_window5);

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
