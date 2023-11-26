#pragma once
#include <stdexcept>
#include <string>
#include <exception>

class UIException : public std::runtime_error {
public:
    UIException(const std::string& message) : std::runtime_error(message) {}
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

class FileIOException : public std::runtime_error {
public:
    FileIOException(const std::string& message) : std::runtime_error(message) {}
};

