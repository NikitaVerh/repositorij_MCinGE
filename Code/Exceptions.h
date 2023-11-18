#pragma once
#include <stdexcept>
#include <string>
#include <exception>

class UIException : public std::runtime_error {
public:
    UIException(const std::string& message) : std::runtime_error(message) {}
};


class TaskParseException : public std::exception {
private:
    std::string errorMessage;
    mutable std::string fullMessage;

public:
    TaskParseException(const std::string& msg)
        : errorMessage(msg) {}

    const char* what() const noexcept override {
        fullMessage = "Помилка при обробці завдання: " + errorMessage;
        return fullMessage.c_str();
    }
};


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


class ResourceLoadException : public std::exception {
private:
    std::string filename;
    mutable std::string fullMessage; // Используйте mutable для изменения в const методе

public:
    ResourceLoadException(const std::string& file)
        : filename(file) {}

    const char* what() const noexcept override {
        fullMessage = "Не вдалося завантажити ресурс: " + filename;
        return fullMessage.c_str();
    }

    const std::string& getFilename() const {
        return filename;
    }
};



