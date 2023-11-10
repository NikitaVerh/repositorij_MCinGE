#pragma once
#include <exception>
#include <string>

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



