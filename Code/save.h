#pragma once
#include "GlobalVariablesOfClasses.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


void loadPlayerPosition(const std::string& filename);
void savePlayerPosition(const std::string& filename);

void saveStatistics(const std::string& filename);
void loadStatistics(const std::string& filename);

void saveLabyrinth(const std::string& filename, Map& gameMap);
void loadLabyrinth(const std::string& filename, Map& gameMap);

void saveMarks(const std::string& filename);
void loadMarks(const std::string& filename);

void saveExamData(const std::string& filename);
void loadExamData(const std::string& filename);

void saveSliderData(const std::string& filename);
void loadSliderData(const std::string& filename);