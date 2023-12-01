#include <iostream>
#include <fstream>
#include <string>

bool readFile(std::ifstream &input)
{
    input.open("input.txt");
    return input.is_open();
}

int charToInt(char symbol)
{
    // according to ASCII code
    return symbol - 48;
}

int getCalibrationFromLine(std::string &line)
{   
    int decimal;
    int integral;

    for (int i = 0; i < line.size(); ++i) {
        if (line[i] >= '0' && line[i] <= '9') {
            decimal = charToInt(line[i]) * 10;  
            break;        
        }
    }

    for (int i = line.size() - 1; i > -1; --i) {
        if (line[i] >= '0' && line[i] <= '9') {
            integral = charToInt(line[i]); 
            break;           
        }
    }

    return decimal + integral;
}

int main()
{
    std::ifstream inputFile;
    if (!readFile(inputFile)) {
        std::cerr << "ERROR: Can't open input file\n"; 
        return 1;
    }

    int sum = 0;

    for (std::string line; std::getline(inputFile, line); ) {
        sum += getCalibrationFromLine(line);
    }
    std::cout << '\n' << "RESULT: " << sum << '\n';
}