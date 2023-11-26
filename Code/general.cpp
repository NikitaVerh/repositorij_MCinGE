/*
В цьому файлі йде реалізація головних методів
*/

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GlobalVariablesForResources.h"
#include "GlobalVariablesOfClasses.h"
#include "initializators.h"
#include "save.h"

void restart_all() {
	GameMap.generateLabyrinth();
	player.Player_set_source();
	std::vector<std::string> themes = task_union.getThemes();
	curr_marks.clear();
	for (const std::string& single_theme : themes) {
		curr_marks.push_back(rslt_pair(0, single_theme));
	}
}
void saveAllData() {
	saveStatistics("Resources/data/statistics.csv");
	saveLabyrinth("Resources/data/labyrinth.sld", GameMap);
	savePlayerPosition("Resources/data/playerPos.spp");
	saveMarks("Resources/data/marks.smd");
	saveExamData("Resources/data/exam.sed");
	saveSliderData("Resources/data/slider.ssd");
}

void loadAllData() {
	loadStatistics("Resources/data/statistics.csv");
	loadLabyrinth("Resources/data/labyrinth.sld", GameMap);
	loadPlayerPosition("Resources/data/playerPos.spp");
	loadMarks("Resources/data/marks.smd");
	loadExamData("Resources/data/exam.sed");
	loadSliderData("Resources/data/slider.ssd");
}

//обробка виняткових ситуацій врахована
// 
// метод що виконується один раз при старті програми
void startProgram(sf::RenderWindow& window) {
	try {
		loadResources();
		initializeVariables();
		initializeInterface();
		initializeCursorAndIcon(window);
		loadAllData();
	}
	catch (const ResourceLoadException& e) {
		std::cerr << "Помилка: " << e.what() << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << "Помилка при завантаженні статистики: " << e.what() << '\n';
	}
	ButtonMenuContinue->setVisible(InProgress);
	if (!isReadedGood) { restart_all(); }
	
}

// метод що виконується один раз перед закриттям программи
void stopProgram(sf::RenderWindow& window) {
	saveAllData();
	window.close();
}

void updateMehanics(sf::Time delta_time) {
	player.set_time(delta_time);
	player.Update();
	particles->set_time(delta_time);
}

void setMenu(int menu) {
	Menu = menu;
	saveAllData();
}

// тимчасово ці змінні тут
bool button_left = false;
bool button_right = false;
bool button_up = false;
bool button_down = false;
bool button_interact = false;






void update_statistics() {
	sf::String str;
	str = "Усього тестів пройдено: " + std::to_string(test_amnt) + "\n" + "Усього сесій гри завершено: " + std::to_string(game_sessions) + "\n" + "\n" + "Найвищі отримані оцінки:" + "\n" + "    Рівень складності - легко:";
	for (rslt_pair& single_pair : easy_best_marks) {
		str = str + "\n        " + single_pair.theme + "  -  " + std::to_string(single_pair.mark) + "/5";
	}
	str = str + "\n" + "    Рівень складності - нормально:";
	for (rslt_pair& single_pair : normal_best_marks) {
		str = str + "\n        " + single_pair.theme + "  -  " + std::to_string(single_pair.mark) + "/9";
	}
	str = str + "\n" + "    Рівень складності - складно:";
	for (rslt_pair& single_pair : hard_best_marks) {
		str = str + "\n        " + single_pair.theme + "  -  " + std::to_string(single_pair.mark) + "/12";
	}
	str = str + "\n" + "\n" + "Інформація про останню сесію гри:" + "\n" + "    Складність  -  " + exam.getTaskDiff();
	for (rslt_pair& single_pair : curr_marks) {
		str = str + "\n    " + single_pair.theme + "  -  " + std::to_string(single_pair.mark) + "/" + std::to_string(int(exam.getMaxCountTask() * exam.getDiffFactor()));
	}

	TextStatistics->setText(str);
}

int changeMenu;

// метод для обробки подій вікна
void windowEventHandling(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		window.setMouseCursor(cursor);
		if (sf::Event::Closed == event.type) { stopProgram(window); }
		/*if (sf::Event::KeyReleased == event.type) {
			if (event.key.code == sf::Keyboard::Key::Num1) { setMenu(menu_main); std::cout << "Menu: " << Menu << std::endl; }
			if (event.key.code == sf::Keyboard::Key::Num2) { setMenu(menu_lobby);  std::cout << "Menu: " << Menu << std::endl; }
			if (event.key.code == sf::Keyboard::Key::Num3) { setMenu(menu_game);  std::cout << "Menu: " << Menu << std::endl; }
			if (event.key.code == sf::Keyboard::Key::Num4) { setMenu(menu_test);  std::cout << "Menu: " << Menu << std::endl; }
			if (event.key.code == sf::Keyboard::Key::Num5) { setMenu(menu_stat);  std::cout << "Menu: " << Menu << std::endl; }
			if (event.key.code == sf::Keyboard::Key::Num6) { setMenu(menu_inf);  std::cout << "Menu: " << Menu << std::endl; }
		}*/

		if (sf::Event::KeyReleased == event.type) {
			if ((event.key.code == sf::Keyboard::Key::W) || (event.key.code == sf::Keyboard::Key::Space) || (event.key.code == sf::Keyboard::Key::Up)) { button_up = false; }
			if ((event.key.code == sf::Keyboard::Key::S) || (event.key.code == sf::Keyboard::Key::LShift) || (event.key.code == sf::Keyboard::Key::Down)) { button_down = false; }
			if ((event.key.code == sf::Keyboard::Key::A) || (event.key.code == sf::Keyboard::Key::Left)) { button_left = false; }
			if ((event.key.code == sf::Keyboard::Key::D) || (event.key.code == sf::Keyboard::Key::Right)) { button_right = false; }
			if ((event.key.code == sf::Keyboard::Key::E) || (event.key.code == sf::Keyboard::Key::RControl)) { button_interact = false; }
		}

		if (sf::Event::KeyPressed == event.type) {
			if ((event.key.code == sf::Keyboard::Key::W) || (event.key.code == sf::Keyboard::Key::Space) || (event.key.code == sf::Keyboard::Key::Up)) { button_up = true; }
			if ((event.key.code == sf::Keyboard::Key::S) || (event.key.code == sf::Keyboard::Key::LShift) || (event.key.code == sf::Keyboard::Key::Down)) { button_down = true; }
			if ((event.key.code == sf::Keyboard::Key::A) || (event.key.code == sf::Keyboard::Key::Left)) { button_left = true; }
			if ((event.key.code == sf::Keyboard::Key::D) || (event.key.code == sf::Keyboard::Key::Right)) { button_right = true; }
			if ((event.key.code == sf::Keyboard::Key::E) || (event.key.code == sf::Keyboard::Key::RControl)) { button_interact = true; }
		}
	}
	if (Menu == menu_game) {
		if (button_left) { player.move(-1, 0); }
		if (button_right) { player.move(1, 0); }
		if (button_up) { player.move(0, -1); }
		if (button_down) { player.move(0, 1); }
		if (button_interact) { player.openDoor(); }
	}
	

	if(window.hasFocus() && changeMenu == Menu)
	switch (Menu) {
	case menu_main:
		if (ButtonMenuStart->Released()) {
			setMenu(menu_lobby);
		}
		if (ButtonMenuContinue->Released()) { setMenu(menu_game); ButtonLabirintFinish->setVisible(false); ButtonLabirintBack->setVisible(true);}
		if (ButtonMenuStatic->Released()) { setMenu(menu_stat); update_statistics(); }
		if (ButtonMenuInf->Released()) {setMenu(menu_inf); }
		SliderMusic->setCanUpdatePresed(true);
		SliderSound->setCanUpdatePresed(true);
		break;
	case menu_game:
		if (ButtonLabirintBack->Released()) {  setMenu(menu_main); }
		if (ButtonLabirintFinish->Released()) { update_statistics(); setMenu(menu_stat);}
		break;
	case menu_lobby:
		if (ButtonLobbyBack->Released()) { setMenu(menu_main); }
		if (ButtonLobbyEasy->Released()) { restart_all(); exam.set_difficulty(0); InProgress = true; ButtonLabirintFinish->setVisible(false); ButtonLabirintBack->setVisible(true); ButtonMenuContinue->setVisible(true);  setMenu(menu_game); }
		if (ButtonLobbyNormal->Released()) { restart_all(); exam.set_difficulty(1); InProgress = true; ButtonLabirintFinish->setVisible(false); ButtonLabirintBack->setVisible(true); ButtonMenuContinue->setVisible(true);  setMenu(menu_game); }
		if (ButtonLobbyHard->Released()) { restart_all(); exam.set_difficulty(2); InProgress = true; ButtonLabirintFinish->setVisible(false); ButtonLabirintBack->setVisible(true); ButtonMenuContinue->setVisible(true);  setMenu(menu_game); }
		break;
	case menu_test:
		if (ButtonTestBack->Released()) { setMenu(menu_game); }
		if (ButtonTest1->Released()) { exam.answer_chosen(0); }
		if (ButtonTest2->Released()) { exam.answer_chosen(1); }
		if (ButtonTest3->Released()) { exam.answer_chosen(2); }
		if (ButtonTest4->Released()) { exam.answer_chosen(3); }
		if (ButtonTestFinish->Released()) { exam.stop_test(); }
		break;
	case menu_stat:
		if (ButtonStatBack->Released()) { setMenu(menu_main); }
		break;
	case menu_inf:
		if (ButtonInfBack->Released()) { setMenu(menu_main); }
		break;
	default:
		break;
	}

	changeMenu = Menu;
}

int curr_music = -1;

void updateSoundAndMusic() {
	SoundClick_in.setVolume(SliderSound->getValue() * 100);
	SoundClick_out.setVolume(SliderSound->getValue() * 100);
	SoundCorrect.setVolume(SliderSound->getValue() * 100);
	SoundWrong.setVolume(SliderSound->getValue() * 100);
	SoundDoor_open.setVolume(SliderSound->getValue() * 100);
	for (int i = 0; i < maxStepSounds; i++) {
		SoundStep[i].setVolume(SliderSound->getValue() * 100);
	}
	for (int i = 0; i < maxMusicTracks; i++) {
		music[i].setVolume(SliderMusic->getValue() * 100);
	}
	bool play = false;
	for (int i = 0; i < maxMusicTracks; i++) {
		if (music[i].getStatus() == sf::Music::Playing)play = true;
	}
	if (!play) {
		int a = rand() % maxMusicTracks;
		while (a == curr_music) {
			a = rand() % maxMusicTracks;
		}
		curr_music = a;
		music[curr_music].play();
	}
	
}

// метод для оновлення інтерфейсу
void UpdateGraphic(sf::RenderWindow& window) {
	if (window.getSize().y < 400) window.setSize(sf::Vector2u(window.getSize().x, 400));
	window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));

	sizeBlock = window.getSize().y / float(1.35);
	if (Menu == menu_main) Form_menu.updateForm(window);
	if (Menu == menu_lobby)Form_lobby.updateForm(window);
	if (Menu == menu_game) Form_labirint.updateForm(window);
	if (Menu == menu_test) Form_test.updateForm(window);
	if (Menu == menu_stat) Form_stat.updateForm(window);
	if (Menu == menu_inf)  Form_inf.updateForm(window);
	ButtonMenuContinue->setVisible(InProgress);

	float winWidth = window.getSize().x;
	float winHeight = window.getSize().y;
	if (windowAspectRatio > winHeight / winWidth) window.setSize(sf::Vector2u(winHeight / windowAspectRatio, winHeight));
}

// метод для відображення графіки
void GraphicRender(sf::RenderWindow& window) {

	window.clear();
	if (Menu == menu_main) {
		Form_menu.drawBackground(window);
		Form_menu.draw(window);
	}
	if (Menu == menu_lobby) {
		Form_lobby.drawBackground(window);
		Form_lobby.draw(window);
	}
	if (Menu == menu_game) {
		GameMap.draw(window);
		player.drawPlayer(window);
		Form_labirint.draw(window);
	}
	if (Menu == menu_test) {
		Form_test.drawBackground(window);
		Form_test.draw(window);
	}
    if (Menu == menu_stat) {
		Form_stat.drawBackground(window);
		Form_stat.draw(window);
	}
	if (Menu == menu_inf) {
		Form_inf.drawBackground(window);
		Form_inf.draw(window);
	}
	window.display();
}