#pragma once
#include "interface.h"
#include "map.h"

extern Form Form_menu; //меню
extern Form Form_lobby; //лобі
extern Form Form_labirint; //лабіринт
extern Form Form_test; //кабінет
extern Form Form_stat; //статистика
extern Form Form_inf; //інформація

extern Button* ButtonMenuStart;
extern Button* ButtonMenuContinue;
extern Button* ButtonMenuStatic;
extern Button* ButtonMenuInf;
extern Button* ButtonLobbyEasy;
extern Button* ButtonLobbyNormal;
extern Button* ButtonLobbyHard;
extern Button* ButtonLobbyBack;
extern Button* ButtonLabirint;
extern Button* ButtonLabirintBack;

extern Button* ButtonTest;
extern Button* ButtonTest1;
extern Button* ButtonTest2;
extern Button* ButtonTest3;
extern Button* ButtonTest4;
extern Button* ButtonTestBack;
extern Button* ButtonTestFinish;

extern Button* ButtonStatBack;
extern Button* ButtonInfBack;

extern TextCanvas* TextBlackboard;

extern Map GameMap;
extern Player player;