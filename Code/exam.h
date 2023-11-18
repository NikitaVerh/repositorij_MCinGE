#pragma execution_character_set("utf-8")
#pragma once
#include "classesForTasks.h"
#include <string>

class Exam {
private:
	Task curr_task;
	int correct_button;
	int counter_task;
	int max_count_task;
	string task_theme;
	string task_diff;
	int mark;
	vector<string> difficulties;
public:

	Exam(){};

	void load_tasks();

	void set_difficulty(int diff);

	void start_test(string theme);

	void next_task();

	void answer_chosen(int code_button);

	void stop_test();
};