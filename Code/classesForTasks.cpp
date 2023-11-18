#pragma execution_character_set("utf-8")
#include "classesForTasks.h"

Task Difficult::getExercise()
{
    srand(time(NULL)); // ініціалізація генератора випадкових чисел

    if (countUsed >= exercises.size()) {
        // Усі завдання вже використані
        throw std::runtime_error("Усі завдання вже використані");
        // Або можна повертати спеціальне значення, наприклад, порожнє завдання
        // return Task();
    }

    int index;
    bool found = false;
    while (!found) {
        index = rand() % exercises.size(); // вибір випадкового індексу завдання
        if (!exercises[index].getUsed()) {
            // Якщо завдання ще не використане, зупиняємо пошук
            found = true;
        }
    }

    exercises[index].setUsed(); // позначаємо завдання як використане
    countUsed++; // збільшуємо кількість використаних завдань
    return exercises[index]; // повертаємо вибране завдання
}

void Difficult::addExercise(Task task)
{
    exercises.push_back(task);
}

void Difficult::resetAllTasks()
{
    for (auto& task : exercises) {
        task.resetUsed();
    }
    countUsed = 0;
}

void Theme::addDifficult(string value)
{
    Difficult newDifficult(value);
    difficults.push_back(newDifficult);
}

void Theme::addExercise(string difficult, Task task)
{
    for (auto& d : difficults) {
        if (d.getDifficult() == difficult) {
            d.addExercise(task);
            break;
        }
    }
}

Task Theme::getTask(string difficult)
{
    for (auto& d : difficults) {
        if (d.getDifficult() == difficult) {
            return d.getExercise();
        }
    }
    return Task(); // повернути порожній Task, якщо не знайдено
}

std::vector<string> Theme::getDifficults()
{
    std::vector<string> diffValues;
    for (auto& d : difficults) {
        diffValues.push_back(d.getDifficult());
    }
    return diffValues;
}

void Theme::resetAllTasks()
{
    for (auto& d : difficults) {
        d.resetAllTasks();
    }
}

void Union::addTheme(string value)
{
    Theme newTheme(value);
    themes.push_back(newTheme);
}

void Union::addTask(string theme, string difficult, Task task)
{
    for (auto& t : themes) {
        if (t.getTheme() == theme) {
            bool found = false;
            for (auto& d : t.getDifficults()) {
                if (d == difficult) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                t.addDifficult(difficult);
            }
            t.addExercise(difficult, task);
            break;
        }
    }
}

Task Union::getTask(string theme, string difficult)
{
    for (auto& t : themes) {
        if (t.getTheme() == theme) {
            return t.getTask(difficult);
        }
    }
    return Task(); // повернути порожній Task, якщо не знайдено
}

std::vector<string> Union::getThemes()
{
    std::vector<string> themeValues;
    for (auto& t : themes) {
        themeValues.push_back(t.getTheme());
    }
    return themeValues;
}

//std::vector<string> Union::getDifficults(string theme)
//{
//    for (auto& t : themes) {
//        if (t.getTheme() == theme) {
//            return t.getDifficults();
//        }
//    }
//    return std::vector<string>(); // повернути порожній вектор, якщо не знайдено
//}

void Union::resetAllTasks()
{
    for (auto& t : themes) {
        t.resetAllTasks();
    }
}

void Union::readTasksFromJson()
{
    std::ifstream file("Resources/json/task.json");
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл task.json" << std::endl;
        return;
    }
    json j;
    file >> j;

    for (auto& theme : j.items()) {
        string themeName = theme.key();
        addTheme(themeName);

        for (auto& diff : theme.value().items()) {
            string difficulty = diff.key();

            for (auto& task : diff.value()) {
                string problem = task["problem"];
                string answer = task["answer"];
                std::vector<string> options = task["options"].get<std::vector<string>>();

                Task newTask(problem, answer, options);
                addTask(themeName, difficulty, newTask);
            }
        }
    }
}
