#pragma once
#include <stdexcept>
#include <string>

class PlayerException : public std::runtime_error {
public:
    PlayerException(const std::string& message) : std::runtime_error(message) {}
};

