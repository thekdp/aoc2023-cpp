#include <iostream>
#include <fstream>

#include "cardpile.h"

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
        std::cin.get();
        return 1;
    }

    auto cardPile = new CardPile(inputFile);
    std::cout << "Total score is " << cardPile->calculateTotalPoints() << '\n';
    std::cout << "Total number of copies is " << cardPile->calculateScratchCards(0) << '\n';
    std::cin.get();
}