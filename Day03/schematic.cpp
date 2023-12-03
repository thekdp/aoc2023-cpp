#include "schematic.h"

Schematic::Schematic(std::ifstream &inputFile)
{
    std::vector<unsigned char> line = {};
    while (!inputFile.eof()) {
        unsigned char symbol = inputFile.get();
        if (symbol != '\n')  {
            line.push_back(symbol);
        } else {
            matrix.push_back(line);
            line.clear();
        }
    }
    searchForPartNumbers();
}

Schematic::~Schematic()
{
}

void Schematic::print()
{
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            std::cout << matrix[i][j];
        }
        std::cout << '\n';
    }
}

void Schematic::printPartNumbers()
{
    for (auto part : parts) {
        std::cout << part->number << '\n';
    }
}

void Schematic::printPartNumbersSum()
{
    uint64_t sum = 0;
    for (auto part : parts) {
        sum += part->number;
    }
    std::cout << "Sum of all parts: " << sum << '\n';
}

void Schematic::searchForPartNumbers()
{
    std::string numberString = "";
    for (size_t i = 0; i < matrix.size(); ++i) {
        checkNumberEnded(i - 1, matrix[i].size() - 1, numberString);
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            if (isNumber(matrix[i][j])) {
                numberString += matrix[i][j];
                continue;
            }
            checkNumberEnded(i, j, numberString);
        }
    }
}

bool Schematic::hasPartSymbols(size_t x, size_t y)
{
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (x + i < 0 || x + i >= matrix.size())
                continue;
            if (y + j < 0 || y + j >= matrix[x].size())
                continue;
            if (isNumber(matrix[x + i][y + j]))
                continue;
            if (matrix[x + i][y + j] == '.')
                continue;

            return true;
        }
    }
    return false;
}

void Schematic::checkNumberEnded(size_t i, size_t j, std::string &numberString)
{
    if (!numberString.empty() && isPart(i, j - 1, numberString.size())) {
        Part *part = new Part {
            .number = std::stoi(numberString),
            .row = i,
            .column = j - 1
        };
        parts.push_back(part);
        numberString.clear();
    } else {
        numberString.clear();
    }
}

void Schematic::printGears()
{
    uint64_t sum = 0;
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] != '*')
                continue;  
            int gearRatio;           
            if (!isGear(i, j, gearRatio))
                continue;
            // std::cout << "Found gear at: {" << i - 1 << ", " << j - 1 << "}. Ratio: " << gearRatio << '\n'; 
            sum += gearRatio;
        }
    }
    std::cout << "Gear ratio sum: " << sum << '\n';
}

bool Schematic::isGear(size_t i, size_t j, int &gearRatio)
{
    std::set<Part *> adjacentParts = {};
    for (int x = -1; x < 2; ++x) {
        for (int y = -1; y < 2; ++y) {
            if (x + i < 0 || x + i >= matrix.size())
                continue;
            if (y + j < 0 || y + j >= matrix[x].size())
                continue;

            Part *part = getPartAt(x + i, y + j);
            if (!part)
                continue;

            adjacentParts.insert(part);
        }
    }

    if (adjacentParts.size() == 2) {
        gearRatio = 1;
        for (auto part : adjacentParts)
        {
            gearRatio *= part->number;
        }
        return true;
    }
    return false;

}

Part *Schematic::getPartAt(size_t x, size_t y)
{
    for (auto part : parts) {
        if (part->contains(x, y))
            return part; 
    }
    return nullptr;
}

bool Schematic::isNumber(unsigned char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

bool Schematic::isPart(size_t x, size_t y, size_t size)
{
    for (size_t offset = 0; offset < size; ++offset) {
        if (hasPartSymbols(x, y - offset)) {
            return true;
        }
    }
    return false;
}
