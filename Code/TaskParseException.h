#pragma once
#include <exception>
#include <string>

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
