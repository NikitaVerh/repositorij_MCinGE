#pragma execution_character_set("utf-8")
#pragma once
#include "GlobalVariablesOfClasses.h"
#include "exam.h"

void Exam::load_tasks() {
	task_union.readTasksFromJson();
	difficulties = task_union.getDifficults(task_union.getThemes()[0]);
};
void Exam::set_difficulty(int diff) {
	task_diff = difficulties[diff];
}
void Exam::start_test(string theme) {
	if (theme == "") return;
	task_union.resetAllTasks();
	mark = 0;
	counter_task = 0;
	max_count_task = 5;
	srand((unsigned int)(time(0)));
	task_theme = theme;
	next_task();
	ButtonF4_1->setVisible(true);
	ButtonF4_2->setVisible(true);
	ButtonF4_3->setVisible(true);
	ButtonF4_4->setVisible(true);
	Menu = menu_test;
}
void Exam::next_task() {
	curr_task = task_union.getTask(task_theme, task_diff);
	TextBlackboard->setText(curr_task.getExercise());
	correct_button = rand() % 4;
	vector<string> answers = curr_task.getAnswers();
	answers.insert(answers.begin() + correct_button, curr_task.getCorrectAnswer());
	ButtonF4_1->setText(answers[0]);
	ButtonF4_2->setText(answers[1]);
	ButtonF4_3->setText(answers[2]);
	ButtonF4_4->setText(answers[3]);
}
void Exam::answer_chosen(int code_button) {
	if (code_button == correct_button) mark++;
	counter_task++;
	if (counter_task < max_count_task) next_task();
	else stop_test();
}
void Exam::stop_test() {
	//peredat ocenku v tablichku
	TextBlackboard->setText(L"Ваша оцінка: " + std::to_string(mark) + "/" + std::to_string(max_count_task));
	ButtonF4_1->setVisible(false);
	ButtonF4_2->setVisible(false);
	ButtonF4_3->setVisible(false);
	ButtonF4_4->setVisible(false);
}
