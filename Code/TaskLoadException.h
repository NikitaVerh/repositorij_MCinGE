#pragma once
#include <exception>
#include <string>

class TaskLoadException : public std::exception {
private:
    std::string filename;
    std::string errorDescription;
    mutable std::string fullMessage; // Використовуємо mutable для змін у const методі

public:
    TaskLoadException(const std::string& file, const std::string& description)
        : filename(file), errorDescription(description) {}

    const char* what() const noexcept override {
        fullMessage = "Помилка завантаження завдання з файлу: " + filename + ". Опис помилки: " + errorDescription;
        return fullMessage.c_str();
    }

    const std::string& getFilename() const {
        return filename;
    }

    const std::string& getDescription() const {
        return errorDescription;
    }
};
