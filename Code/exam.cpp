#pragma execution_character_set("utf-8")
#pragma once
#include "GlobalVariablesOfClasses.h"
#include "exam.h"
#include "general.h"
#include <algorithm>
#include "save.h"

void Exam::load_tasks() {
	task_union.readTasksFromJson();
	difficulties = task_union.getDifficults(task_union.getThemes()[0]);
};
void Exam::set_difficulty(int diff) {
	if (diff == 0) task_diff = "easy";
	if (diff == 1) task_diff = "normal";
	if (diff == 2) task_diff = "hard";
	if (task_diff == "easy") diff_factor = 1;
	if (task_diff == "normal") diff_factor = 1.8;
	if (task_diff == "hard") diff_factor = 2.4;
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
	ButtonTest1->setVisible(true);
	ButtonTest2->setVisible(true);
	ButtonTest3->setVisible(true);
	ButtonTest4->setVisible(true);
	ButtonTestFinish->setVisible(true);
	ButtonTestBack->setVisible(false);
	setMenu(menu_test);
	SoundDoor_open.play();
}
void Exam::next_task() {
	curr_task = task_union.getTask(task_theme, task_diff);
	TextBlackboard->setText(curr_task.getExercise());
	correct_button = rand() % 4;
	vector<string> answers = curr_task.getAnswers();
	answers.insert(answers.begin() + correct_button, curr_task.getCorrectAnswer());
	ButtonTest1->setText(answers[0]);
	ButtonTest2->setText(answers[1]);
	ButtonTest3->setText(answers[2]);
	ButtonTest4->setText(answers[3]);
}
void Exam::answer_chosen(int code_button) {
	if (code_button == correct_button) { mark++; SoundCorrect.play(); }
	else { SoundWrong.play(); }
	counter_task++;
	if (counter_task < max_count_task) next_task();
	else stop_test();
}

int Exam::is_completed(string theme) {
	for (rslt_pair& single_pair : curr_marks) {
		if (single_pair.theme == theme) {
			if (single_pair.mark != 0) return single_pair.mark;
		}
	}
	return 0;
}

void Exam::blackboard_result(int mark) {
	TextBlackboard->setText("Ваша оцінка: " + std::to_string(mark) + "/" + std::to_string(int(diff_factor*max_count_task)));
	setMenu(menu_test);
	ButtonTest1->setVisible(false);
	ButtonTest2->setVisible(false);
	ButtonTest3->setVisible(false);
	ButtonTest4->setVisible(false);
	ButtonTestFinish->setVisible(false);
	ButtonTestBack->setVisible(true);
}

bool Exam:: session_end() {
	for (rslt_pair& single_pair : curr_marks) {
		if (single_pair.mark == 0) return false;
	}
	return true;
}


void Exam::stop_test() {
	mark = round(mark*diff_factor);
	blackboard_result(mark);
	if (mark > 0) ++test_amnt;
	for (rslt_pair& single_pair : curr_marks) {
		if (single_pair.theme == task_theme) {
			single_pair.mark = mark;
			break;
		}
	}
	if (task_diff == "easy") {
		for (rslt_pair& single_pair : easy_best_marks) {
			if (single_pair.theme == task_theme) {
				if (single_pair.mark < mark) single_pair.mark = mark;
				break;
			}
		}
	}
	if (task_diff == "normal") {
		for (rslt_pair& single_pair : normal_best_marks) {
			if (single_pair.theme == task_theme) {
				if (single_pair.mark < mark) single_pair.mark = mark;
				break;
			}
		}
	}
	if (task_diff == "hard") {
		for (rslt_pair& single_pair : hard_best_marks) {
			if (single_pair.theme == task_theme) {
				if (single_pair.mark < mark) single_pair.mark = mark;
				break;
			}
		}
	}
	if (session_end()) {
		ButtonLabirintFinish->setVisible(true);
		ButtonLabirintBack->setVisible(false);
		game_sessions++;
		InProgress = false;
	}
}
