#pragma once
#include "GlobalVariablesOfClasses.h"


Form Form_menu;
Form Form_lobby;
Form Form_labirint;
Form Form_test;
Form Form_stat;
Form Form_inf;

Button* ButtonMenuStart = new Button();
Button* ButtonMenuContinue = new Button();
Button* ButtonMenuStatic = new Button();
Button* ButtonMenuInf = new Button();
Button* ButtonLobbyBack = new Button();
Button* ButtonLobbyEasy = new Button();
Button* ButtonLobbyNormal = new Button();
Button* ButtonLobbyHard = new Button();
Button* ButtonLabirint = new Button();
Button* ButtonLabirintBack = new Button();
Button* ButtonTestFinish = new Button();

Button* ButtonTest = new Button();
Button* ButtonTest1 = new Button();
Button* ButtonTest2 = new Button();
Button* ButtonTest3 = new Button();
Button* ButtonTest4 = new Button();
Button* ButtonTestBack = new Button();

Button* ButtonStatBack = new Button();
Button* ButtonInfBack = new Button();

TextCanvas* TextBlackboard = new TextCanvas();

Map GameMap;
Player player;

Union task_union;
Exam exam;