#include "save.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#pragma region statistics
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

void loadStatistics(const std::string& filename)
{
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
#pragma endregion

#pragma region labyrinth
void loadLabyrinth(const std::string& filename, Map& gameMap)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for loading");
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
                throw std::runtime_error("Unknown block type");
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
    file.close();
    
}

void saveLabyrinth(const std::string& filename, Map& gameMap) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for saving");
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

    file.close();
}
#pragma endregion

#pragma region player
void loadPlayerPosition(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for loading player position");
    }

    float x, y;
    file >> x >> y;

    if (!file.fail()) {
        player.setX(x);
        player.setY(y);
    }
    else {
        throw std::runtime_error("Error reading player position from file");
    }

    file.close();
}

void savePlayerPosition(const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for saving player position");
    }

    file << player.getX() << " " << player.getY();
    file.close();
}


#pragma endregion 

#pragma region marks
void saveMarks(const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for saving marks");
    }

    // Збереження curr_marks
    file << curr_marks.size() << "\n";
    for (const auto& mark : curr_marks) {
        file << mark.mark << " " << mark.theme << "\n";
    }

    file.close();
}

void loadMarks(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for loading marks");
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
            if (file >> mark >> std::ws && std::getline(file, theme)) {
                curr_marks.push_back(rslt_pair(mark, theme));
            }
            else {
                throw std::runtime_error("Error reading marks from file");
            }
        }
    }

    file.close();
}
#pragma endregion 

#pragma region exam
void loadExamData(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for loading exam data");
    }

    double diffFactor;
    int maxCountTask;
    std::string taskDiff;

    if (file >> diffFactor && file >> maxCountTask && std::getline(file >> std::ws, taskDiff)) {
        exam.setDiffFactor(diffFactor);
        exam.setMaxCountTask(maxCountTask);
        exam.setTaskDiff(taskDiff);
    }
    else {
        throw std::runtime_error("Error reading exam data from file");
    }

    file.close();
}

void saveExamData(const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for saving exam data");
    }

    file << exam.getDiffFactor() << "\n";
    file << exam.getMaxCountTask() << "\n";
    file << exam.getTaskDiff() << "\n";

    file.close();
}
#pragma endregion

#pragma region slider
void saveSliderData(const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for saving slider data");
    }

    file << SliderMusic->getValue() << "\n";
    file << SliderSound->getValue() << "\n";

    file.close();
}

void loadSliderData(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for loading slider data");
    }

    float musicValue, soundValue;

    if (file >> musicValue) {
        SliderMusic->setValue(musicValue);
    }
    else {
        throw std::runtime_error("Error reading music slider value from file");
    }

    if (file >> soundValue) {
        SliderSound->setValue(soundValue);
    }
    else {
        throw std::runtime_error("Error reading sound slider value from file");
    }

    file.close();
}
#pragma endregion