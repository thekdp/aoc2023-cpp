#include "almanac.h"


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
    auto almanac = new Almanac();
    // almanac->launchFirstAlgotithm(inputFile)
    almanac->launchSecondAlgotithm(inputFile);

    std::cin.get();
}