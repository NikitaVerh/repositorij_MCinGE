#include "save.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


void updateOrAddMark(std::vector<rslt_pair>& marks, const std::string& theme, int newMark) {
    for (auto& markPair : marks) {
        if (markPair.theme == theme) {
            if (markPair.mark < newMark) {
                markPair.mark = newMark;
            }
            return;
        }
    }
    marks.push_back(rslt_pair(newMark, theme));
}

void loadStatistics(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string difficulty, theme, markStr;
        int mark;

        std::getline(iss, difficulty, ',');
        std::getline(iss, theme, ',');
        std::getline(iss, markStr);

        if (difficulty == "session") {
            last_difficulty = theme;
            test_amnt = std::stoi(markStr);
            continue;
        }

        mark = std::stoi(markStr);

        if (difficulty == "easy") {
            updateOrAddMark(easy_best_marks, theme, mark);
        }
        else if (difficulty == "normal") {
            updateOrAddMark(normal_best_marks, theme, mark);
        }
        else if (difficulty == "hard") {
            updateOrAddMark(hard_best_marks, theme, mark);
        }
    }
}


void saveStatistics(const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }

    // Збереження найкращих балів
    auto writeMarks = [&file](const std::vector<rslt_pair>& marks, const std::string& type) {
        for (const auto& pair : marks) {
            file << type << "," << pair.theme << "," << pair.mark << std::endl;
        }
        };

    writeMarks(easy_best_marks, "easy");
    writeMarks(normal_best_marks, "normal");
    writeMarks(hard_best_marks, "hard");

    // Збереження останніх балів
    for (const auto& pair : last_marks) {
        file << "last," << pair.theme << "," << pair.mark << std::endl;
    }

    // Збереження інформації про останню сесію та кількість пройдених тестів
    file << "session," << last_difficulty << "," << test_amnt << std::endl;

    file.close();
}















//int findIndexInVector(const std::vector<rslt_pair>& vec, const std::string& theme) {
//    for (size_t i = 0; i < vec.size(); ++i) {
//        if (vec[i].theme == theme) {
//            return i;
//        }
//    }
//    return -1; // Возвращает -1, если тема не найдена
//}
//
//void updateVector(std::vector<rslt_pair>& vec, const std::string& theme, int mark) {
//    int index = findIndexInVector(vec, theme);
//    if (index != -1) {
//        vec[index].mark = mark;
//    }
//    else {
//        // Если тема не найдена, можно добавить новую запись или обработать этот случай по-другому
//        std::cerr << "Тема не найдена: " << theme << '\n';
//    }
//}
//void saveStatistics(const std::string& filename)
//{
//    std::ofstream file(filename);
//
//    if (!file.is_open()) {
//        std::cerr << "Не удалось открыть файл для записи." << std::endl;
//        return;
//    }
//
//    // Сохранение общей статистики
//    file << "Общая статистика\n";
//    file << "Последняя сложность," << last_difficulty << "\n";
//    file << "Количество игровых сессий," << game_sessions << "\n";
//    file << "Количество тестов," << test_amnt << "\n\n";
//
//    // Функция для сохранения вектора rslt_pair
//    auto saveVector = [&file](const std::string& title, const std::vector<rslt_pair>& vec) {
//        file << title << "\n";
//        for (const auto& pair : vec) {
//            file << pair.theme << "," << pair.mark << "\n";
//        }
//        file << "\n";
//        };
//
//    // Сохранение результатов по категориям
//    saveVector("Лучшие результаты (Легко)", easy_best_marks);
//    saveVector("Лучшие результаты (Нормально)", normal_best_marks);
//    saveVector("Лучшие результаты (Сложно)", hard_best_marks);
//    saveVector("Последние результаты", last_marks);
//
//    file.close();
//}

//void loadStatistics(const std::string& filename)
//{
//    std::ifstream file(filename);
//
//    if (!file.is_open()) {
//        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
//        return;
//    }
//
//    std::string line;
//
//    // Очистка векторов перед загрузкой новых данных
//   /* easy_best_marks.clear();
//    normal_best_marks.clear();
//    hard_best_marks.clear();
//    last_marks.clear();*/
//
//    // Пропускаем заголовки общей статистики
//    std::getline(file, line); // "Общая статистика"
//    std::getline(file, line); // "Последняя сложность"
//    std::getline(file, line); // Значение последней сложности
//    last_difficulty = line.substr(line.find(',') + 1);
//
//    std::getline(file, line); // "Количество игровых сессий"
//    std::getline(file, line); // Значение количества игровых сессий
//    try {
//        game_sessions = std::stoi(line.substr(line.find(',') + 1));
//    }
//    catch (const std::invalid_argument& e) {
//        std::cerr << "Неверный аргумент при преобразовании строки в число: " << e.what() << '\n';
//        return;
//    }
//    catch (const std::out_of_range& e) {
//        std::cerr << "Число вне допустимого диапазона: " << e.what() << '\n';
//        return;
//    }
//
//    std::getline(file, line); // "Количество тестов"
//    std::getline(file, line); // Значение количества тестов
//    try {
//        test_amnt = std::stoi(line.substr(line.find(',') + 1));
//    }
//    catch (const std::invalid_argument& e) {
//        std::cerr << "Неверный аргумент при преобразовании строки в число: " << e.what() << '\n';
//        return;
//    }
//    catch (const std::out_of_range& e) {
//        std::cerr << "Число вне допустимого диапазона: " << e.what() << '\n';
//        return;
//    }
//
//    std::getline(file, line); // Пустая строка
//
//    // Функция для чтения вектора пар
//    auto loadAndUpdateVector = [&file](std::vector<rslt_pair>& vec) {
//        std::string line;
//        while (std::getline(file, line) && !line.empty()) {
//            std::istringstream iss(line);
//            std::string theme;
//            std::string markStr;
//            int mark;
//            if (std::getline(iss, theme, ',') && std::getline(iss, markStr)) {
//                try {
//                    mark = std::stoi(markStr);
//                    updateVector(vec, theme, mark);
//                }
//                catch (const std::invalid_argument& e) {
//                    std::cerr << "Неверный формат оценки: " << markStr << '\n';
//                }
//                catch (const std::out_of_range& e) {
//                    std::cerr << "Оценка вне допустимого диапазона: " << markStr << '\n';
//                }
//            }
//        }
//        };
//    // Чтение результатов по категориям
//    std::getline(file, line); // "Лучшие результаты (Легко)"
//    loadAndUpdateVector(easy_best_marks);
//    std::getline(file, line); // "Лучшие результаты (Нормально)"
//    loadAndUpdateVector(normal_best_marks);
//    std::getline(file, line); // "Лучшие результаты (Сложно)"
//    loadAndUpdateVector(hard_best_marks);
//    std::getline(file, line); // "Последние результаты"
//    loadAndUpdateVector(last_marks);
//
//    file.close();
//}