#include "save.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#pragma region statistics
void saveStatistics(const std::string& filename) {
    std::ofstream file;

    try {
        file.open(filename);
        if (!file.is_open()) {
            throw FileIOException("Не вдалося відкрити файл для запису: " + filename);
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

        // Збереження інформації про останню сесію та кількість пройдених тестів
        file << "session," << game_sessions << "," << test_amnt << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Виняток при збереженні статистики: " << e.what() << std::endl;
        throw;  
    }

    if (file.is_open()) {
        file.close();
    }
}

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
    std::ifstream file;

    try {
        file.open(filename);
        if (!file.is_open()) {
            throw FileIOException("Не вдалося відкрити файл для читання: " + filename);
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string difficulty, theme, markStr;
            int mark;

            std::getline(iss, difficulty, ',');
            std::getline(iss, theme, ',');
            std::getline(iss, markStr);

            try {
                if (difficulty == "session") {
                    game_sessions = std::stoi(theme);
                    test_amnt = std::stoi(markStr);
                    continue;
                }

                mark = std::stoi(markStr);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Помилка при перетворенні рядка у число: " << e.what() << std::endl;
                continue; // Пропускаємо невірний рядок і продовжуємо читання
            }

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
    catch (const std::exception& e) {
        std::cerr << "Виняток при завантаженні статистики: " << e.what() << std::endl;
        isReadedGood = false;
        throw;  
    }

    if (file.is_open()) {
        file.close();
    }
}
#pragma endregion

#pragma region labyrinth
void loadLabyrinth(const std::string& filename, Map& gameMap) {
    std::ifstream file;

    try {
        file.open(filename);
        if (!file.is_open()) {
            throw FileIOException("Не вдалося відкрити файл для читання: " + filename);
        }

        for (int i = 0; i < mapWidth; ++i) {
            for (int j = 0; j < mapHeight; ++j) {
                int type, idTexture;
                bool wallLeft, wallRight;
                std::string theme;
                file >> type >> wallLeft >> wallRight >> idTexture;
                std::getline(file, theme); // Читаємо тему, яка може містити пробіли

                Block* block = nullptr;
                switch (type) {
                case type_block_wall:
                    block = new BlockWall();
                    break;
                case type_block_door:
                    block = new BlockDoor();
                    break;
                case type_block_ladder:
                    block = new BlockLadder();
                    break;
                default:
                    throw std::runtime_error("Unknown block type: " + std::to_string(type));
                }

                block->setWallLeft(wallLeft);
                block->setWallRight(wallRight);
                block->setIdTexture(idTexture);
                theme.erase(0, 1);
                block->setTheme(theme);

                gameMap.setBlock(i, j, block);
            }
        }
        gameMap.setNewHitboxes();
    }
    catch (const std::exception& e) {
        std::cerr << "Виняток при завантаженні лабіринту: " << e.what() << std::endl;
        isReadedGood = false;
        throw;  
    }

    if (file.is_open()) {
        file.close();
    }
}

void saveLabyrinth(const std::string& filename, Map& gameMap) {
    std::ofstream file;

    try {
        file.open(filename);
        if (!file.is_open()) {
            throw FileIOException("Не вдалося відкрити файл для запису: " + filename);
        }

        for (int i = 0; i < mapWidth; ++i) {
            for (int j = 0; j < mapHeight; ++j) {
                Block& block = gameMap.getMapBlock(i, j);
                file << block.getTypeBlock() << " "
                    << block.getWallLeft() << " "
                    << block.getWallRight() << " "
                    << block.getIdTexture() << " "
                    << block.getTheme() << "\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Виняток при збереженні лабіринту: " << e.what() << std::endl;
        throw;  
    }

    if (file.is_open()) {
        file.close();
    }
}
#pragma endregion

#pragma region player
void loadPlayerPosition(const std::string& filename) {
    std::ifstream file;

    try {
        file.open(filename);
        if (!file.is_open()) {
            throw FileIOException("Не вдалося відкрити файл для читання: " + filename);
        }

        float x, y;
        int y_s;
        file >> x >> y >> y_s;

        if (file.fail()) {
            throw FileIOException("Помилка при читанні позиції гравця з файлу: " + filename);
        }

        player.setX(x);
        player.setY(y);
        Y_start_climbing = y_s;
    }
    catch (const std::exception& e) {
        std::cerr << "Виняток при завантаженні позиції гравця: " << e.what() << std::endl;
        isReadedGood = false;
        throw;  
    }

    if (file.is_open()) {
        file.close();
    }
}

void savePlayerPosition(const std::string& filename) {
    std::ofstream file;

    try {
        file.open(filename);
        if (!file.is_open()) {
            throw FileIOException("Не вдалося відкрити файл для запису: " + filename);
        }

        file << player.getX() << " " << player.getY() << " " << Y_start_climbing;
    }
    catch (const std::exception& e) {
        std::cerr << "Виняток при збереженні позиції гравця: " << e.what() << std::endl;
        throw;  
    }

    if (file.is_open()) {
        file.close();
    }
}
#pragma endregion 

#pragma region marks
void saveMarks(const std::string& filename) {
    std::ofstream file;

    try {
        file.open(filename);
        if (!file.is_open()) {
            throw FileIOException("Не вдалося відкрити файл для запису: " + filename);
        }

        // Збереження curr_marks
        file << curr_marks.size() << "\n";
        for (const auto& mark : curr_marks) {
            file << mark.mark << " " << mark.theme << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Виняток при збереженні оцінок: " << e.what() << std::endl;
        throw; // Перекидання винятку далі
    }

    if (file.is_open()) {
        file.close();
    }
}

void loadMarks(const std::string& filename) {
    std::ifstream file;

    try {
        file.open(filename);
        if (!file.is_open()) {
            throw FileIOException("Не вдалося відкрити файл для читання: " + filename);
        }

        // Перевірка, чи файл не пустий
        if (file.peek() == std::ifstream::traits_type::eof()) {
            // Файл пустий, можна ініціалізувати дані за замовчуванням або просто повернутися
            return;
        }

        // Завантаження curr_marks
        size_t size;
        if (file >> size) {
            curr_marks.clear();
            for (size_t i = 0; i < size; ++i) {
                int mark;
                std::string theme;
                if (!(file >> mark >> std::ws && std::getline(file, theme))) {
                    throw FileIOException("Помилка при читанні оцінок з файлу: " + filename);
                }
                curr_marks.push_back(rslt_pair(mark, theme));
            }
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Виняток при завантаженні оцінок: " << e.what() << std::endl;
        isReadedGood = false;
        // Можливо, додати додаткову обробку помилок тут
        throw; // Перекидання винятку далі, якщо потрібно
    }

    if (file.is_open()) {
        file.close();
    }
}
#pragma endregion 

#pragma region exam
void loadExamData(const std::string& filename) {
    std::ifstream file;

    try {
        file.open(filename);
        if (!file.is_open()) {
            throw FileIOException("Не вдалося відкрити файл для читання: " + filename);
        }

        double diffFactor;
        int maxCountTask;
        std::string StaskDiff;
        bool LoadProgress;

        if (!(file >> diffFactor && file >> maxCountTask && std::getline(file >> std::ws, StaskDiff) && file >> LoadProgress)) {
            throw FileIOException("Помилка при читанні даних іспиту з файлу: " + filename);
        }

        exam.setDiffFactor(diffFactor);
        exam.setMaxCountTask(maxCountTask);
        exam.setTaskDiff(StaskDiff);
        InProgress = LoadProgress;

    }
    catch (const std::exception& e) {
        std::cerr << "Виняток при завантаженні даних іспиту: " << e.what() << std::endl;
        isReadedGood = false;
        throw;   
    }

    if (file.is_open()) {
        file.close();
    }
}
void saveExamData(const std::string& filename) {
    std::ofstream file;

    try {
        file.open(filename);
        if (!file.is_open()) {
            throw FileIOException("Не вдалося відкрити файл для запису: " + filename);
        }

        file << exam.getDiffFactor() << "\n";
        file << exam.getMaxCountTask() << "\n";
        file << exam.getTaskDiff() << "\n";
        file << InProgress << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Помилка при збереженні даних іспиту: " << e.what() << std::endl;
        throw;  
    }

    if (file.is_open()) {
        file.close();
    }
}
#pragma endregion

#pragma region slider
void saveSliderData(const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw FileIOException("Не вдалося відкрити файл для запису: " + filename);
    }

    try {
        file << SliderMusic->getValue() << "\n";
        file << SliderSound->getValue() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Помилка при збереженні даних слайдера: " << e.what() << std::endl;
        // Можливо, додати додаткову обробку помилок тут
        throw; // Перекидання винятку далі, якщо потрібно
    }

    file.close();
}

void loadSliderData(const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw ResourceLoadException(filename);
        }

        float musicValue, soundValue;

        if (!(file >> musicValue)) {
            throw ResourceLoadException(filename);
        }
        SliderMusic->setValue(musicValue);

        if (!(file >> soundValue)) {
            throw ResourceLoadException(filename);
        }
        SliderSound->setValue(soundValue);

    }
    catch (const ResourceLoadException& e) {
        std::cerr << "Виняток: " << e.what() << std::endl;
        isReadedGood = false; // Встановлення isReadedGood у false тут
    }
}

#pragma endregion