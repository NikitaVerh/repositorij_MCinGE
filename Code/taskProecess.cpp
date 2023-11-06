//#pragma once 
//#include "taskProecess.h"
//
//using json = nlohmann::json;
//
//struct Question {
//    std::string problem;
//    std::string answer;
//    std::vector<std::string> options;
//};
//
//#pragma region from_json
//void from_json(const json& j, Question& q) {
//    j.at("problem").get_to(q.problem);
//    j.at("answer").get_to(q.answer);
//    j.at("options").get_to(q.options);
//    q.options.push_back(q.answer);
//    std::random_shuffle(q.options.begin(), q.options.end());
//}
//#pragma endregion
//
//#pragma region chooseCategory
//std::string chooseCategory(const json& tasks)
//{
//    std::cout << "Виберіть предмет для складання сессії: " << std::endl;
//    std::vector<std::string> categories;
//    int index = 1;
//    for (auto& el : tasks.items())
//    {
//        std::cout << index << ". " << el.key() << std::endl;
//        categories.push_back(el.key());
//        index++;
//    }
//
//    int categoryIndex;
//    std::cin >> categoryIndex;
//
//    if (categoryIndex < 1 || categoryIndex > categories.size())
//    {
//        std::cerr << "Неправильний номер дисципліни!" << std::endl;
//        exit(1);
//    }
//
//    return categories[categoryIndex - 1];
//}
//#pragma endregion
//
//#pragma region loadQuestionsForCategoryAndDifficulty
//std::vector<Question> loadQuestionsForCategoryAndDifficulty(const json& tasks, const std::string& category,
//    const std::string& difficulty) {
//    std::vector<Question> questions;
//
//    if (!tasks[category].contains(difficulty) || tasks[category][difficulty].size() < 5)
//    {
//        std::cerr << "Недостатньо задач для рівня " << difficulty << " в дисципліні " << category << "." << std::endl;
//        exit(1);
//    }
//
//    auto currentQuestions = tasks[category][difficulty].get<std::vector<Question>>();
//    std::random_shuffle(currentQuestions.begin(), currentQuestions.end());
//    questions.insert(questions.end(), currentQuestions.begin(), currentQuestions.begin() + 5);
//
//    return questions;
//}
//#pragma endregion 
//
//#pragma region playGame
//bool playGame(std::vector<Question>& questions, const std::string& level) {
//    int errors = 0;
//    std::cout << "Розпочинаємо рівень: " << level << std::endl;
//
//    for (int i = 0; i < 5 && errors < 3; ++i) {
//        const auto& q = questions[i];
//
//        std::cout << "Розв'яжіть задачу: " << q.problem << std::endl;
//        for (size_t j = 0; j < q.options.size(); ++j) {
//            std::cout << j + 1 << ". " << q.options[j] << std::endl;
//        }
//
//        std::cout << "Ваша відповідь: ";
//        int userAnswerIndex;
//        std::cin >> userAnswerIndex;
//
//        if (userAnswerIndex < 1 || userAnswerIndex > q.options.size()) {
//            std::cerr << "Неправильний номер варіанта!" << std::endl;
//            errors++;
//        }
//        else {
//            const auto& userAnswer = q.options[userAnswerIndex - 1];
//            if (userAnswer == q.answer) {
//                std::cout << "Правильно!" << std::endl;
//            }
//            else {
//                std::cout << "Не вірно. Правильна відповідь: " << q.answer << std::endl;
//                errors++;
//            }
//        }
//    }
//
//    if (errors < 3) {
//        std::cout << "Вітаю! Ви успішно пройшли рівень: " << level << std::endl;
//        return true;
//    }
//    else {
//        std::cout << "На жаль, ви допустили занадто багато помилок на рівні " << level << ". Спробуйте ще раз!" << std::endl;
//        return false;
//    }
//}
//#pragma endregion 
//
////основний метод(нескінеч цикл,виклик playGame(), chooseCategory(), loadQuestionsForCategoryAndDifficulty()) +++
//#pragma region runEntireGame
//bool runEntireGame(json& tasks) {
//    // Ініціалізація генератора випадкових чисел
//    srand(static_cast<unsigned>(time(nullptr)));
//
//    char answer;
//    do {
//        std::string category = chooseCategory(tasks);
//        bool success = true;
//
//        for (const std::string& level : { "easy", "medium", "hard" }) {
//            auto questions = loadQuestionsForCategoryAndDifficulty(tasks, category, level);
//            if (!playGame(questions, level)) {
//                std::cout << "На жаль, ви не склали сесію на рівні " << level << ". Спробуйте ще раз!" << std::endl;
//                success = false;
//                break;
//            }
//        }
//
//        if (success) {
//            std::cout << "Вітаємо! Ви успішно пройшли всі рівні в категорії '" << category << "'!" << std::endl;
//        }
//
//        std::cout << "Хочете зіграти ще раз? (y/n): ";
//        std::cin >> answer;
//        if (answer != 'y' && answer != 'Y') {
//            break;
//        }
//    } while (true);
//
//    return true;
//}
//#pragma endregion 
//
////
//
//
////завантаження прикладів +++
//#pragma region loadQuestions
//bool loadQuestions(const std::string& filename, json& tasks) {
//    std::ifstream file(filename);
//    if (!file.is_open()) {
//        std::cerr << "Не вдалось відкрити файл " << filename << std::endl;
//        return false;
//    }
//    file >> tasks;
//    return true;
//}
//#pragma endregion
//
//
//
////тимчасово непотрібні
//#pragma region runTask
////void runTask()
////{
////    srand(static_cast<unsigned>(time(0)));
////
////    json tasks;
////    if (!loadQuestions("tasks.json", tasks))
////    {
////        std::cerr << "Помилка при завантаженні питань." << std::endl;
////    }
////
////    char answer;
////    do
////    {
////        runGame(tasks);
////        std::cout << "Хочете зіграти ще раз? (y/n): ";
////        std::cin >> answer;
////    } while (answer == 'y' || answer == 'Y');
////}
//#pragma endregion
//
//Task getTask(int themeIndex) {
//    json tasks;
//
//    std::vector<std::string> categories;
//    for (auto& el : tasks.items()) {
//        categories.push_back(el.key());
//    }
//
//    //після прототипу
//    /*if (themeIndex < 0 || themeIndex >= categories.size()) {
//        throw std::out_of_range("Theme index is out of range.");
//    }*/
//
//    std::string category = categories[themeIndex];
//
//    std::string difficulty = "easy";
//    std::vector<Question> questions = loadQuestionsForCategoryAndDifficulty(tasks, category, difficulty);
//
//    if (questions.empty()) {
//        throw std::runtime_error("No questions available for the chosen category and difficulty.");
//    }
//
//    Question chosenQuestion = questions[rand() % questions.size()];
//    Task task;
//    task.setTask(
//        sf::String(chosenQuestion.problem),
//        sf::String(chosenQuestion.options[0]),
//        sf::String(chosenQuestion.options[1]),
//        sf::String(chosenQuestion.options[2]),
//        sf::String(chosenQuestion.options[3]),
//        sf::String(chosenQuestion.answer)
//    );
//
//    return task;
//}
//
//void stopTest() {
//    //std::cout << "Тест завершено." << std::endl;
//}
//
//#pragma region runGame
////bool runGame(const json& tasks) {
////    std::string category = chooseCategory(tasks);
////
////    for (const std::string& level : { "easy", "normal", "hard" }) {
////        std::vector<Question> questions = loadQuestionsForCategoryAndDifficulty(tasks, category, level);
////        if (!playGame(questions, level)) {
////            std::cout << "На жаль, ви не склали сесію на рівні " << level << ". Чекаємо на перездачі!" << std::endl;
////            return false;
////        }
////    }
////
////    std::cout << "Вітаю, ви склали сесію з дисципліни '" << category << "'!" << std::endl;
////    return true;
////}
//#pragma endregion 