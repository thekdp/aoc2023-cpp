#include <iostream>
#include <fstream>

#include "schematic.h"

#define LOGGING

bool readFile(std::ifstream &input)
{
    input.open("input.txt");
    return input.is_open();
}


int main()
{
    std::ifstream inputFile;
    if (!readFile(inputFile)) {
        std::cerr << "ERROR: Can't open input file\n"; 
        return 1;
    }

    auto schematic = new Schematic(inputFile);
    schematic->printPartNumbersSum();
    schematic->printGears();


    std::cin.get();
}