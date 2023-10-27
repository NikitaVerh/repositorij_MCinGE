#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#pragma once
#include "general.cpp"

int main() {
    startProgram();
    while (aliveProgram()) {
        processAll();
        std::cout << "test 2 chela";
    }
}
