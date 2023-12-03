#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

#include "part.h"

class Schematic
{
public:
    Schematic(std::ifstream &inputFile);
    ~Schematic();

    void print();
    void printPartNumbers();
    void printPartNumbersSum();
    void printGears();


private:
    std::vector<std::vector<unsigned char>> matrix; 
    std::vector<Part *> parts;

    bool isNumber(unsigned char symbol);
    Part *getPartAt(size_t x, size_t y);
    void searchForPartNumbers();
    bool hasPartSymbols(size_t x, size_t y);
    void checkNumberEnded(size_t i, size_t j, std::string &numberString);
    bool isGear(size_t x, size_t y, int &gearRatio);
    bool isPart(size_t x, size_t y, size_t size);
};