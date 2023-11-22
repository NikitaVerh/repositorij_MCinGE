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
	double diff_factor;
	vector<string> difficulties;
public:
	Exam() { task_diff = "інформація відсутня"; };

	double getDiffFactor() const { return diff_factor; }
	int getMaxCountTask() const { return max_count_task; }
	std::string getTaskDiff() const { return task_diff; }

	// Сетери
	void setDiffFactor(double value) { diff_factor = value; }
	void setMaxCountTask(int value) { max_count_task = value; }
	void setTaskDiff(const std::string& value) { task_diff = value; }

	void load_tasks();

	void set_difficulty(int diff);

	void start_test(string theme);

	void next_task();

	void answer_chosen(int code_button);

	void stop_test();

	int is_completed(string theme);

	void blackboard_result(int mark);

	bool session_end();
};