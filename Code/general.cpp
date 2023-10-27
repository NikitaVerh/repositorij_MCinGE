#include <iostream>

// метод, що запускається один раз при запуску програми
void startProgram() {} 

// метод для обробки програми (виконується постійно)
void processAll() {
	std::cout << "Кто прочитает, тот негр";
	std::cout << ",";
	std::cout << "Hello kursa41";
	std::cout << "Bye kursa41";
	std::cout << "Azazazazazzaza";
}

// метод що повертає стан програми (виконувати/не виконувати)
bool aliveProgram() {
	startProgram();
} 