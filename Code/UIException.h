#pragma once
#include <stdexcept>
#include <string>

class UIException : public std::runtime_error {
public:
    UIException(const std::string& message) : std::runtime_error(message) {}
};

