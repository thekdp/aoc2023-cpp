#include <iostream>
#include <fstream>
#include <string>
#include <array>

const std::array<std::string, 9> g_numbers = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};


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

int getDecimal(std::string line)
{
    std::string subString = "";
    for (int i = 0; i < line.size(); ++i) {

        if (line[i] >= '0' && line[i] <= '9') { 
            return charToInt(line[i]);
        }
        subString += line[i];

        for (int j = 0; j < g_numbers.size(); ++j) {         

            int startPos = subString.size() - g_numbers[j].size();
            if (startPos < 0)
            {
                continue;
            }
            std::string choppedEnd = subString.substr(startPos);

            if (choppedEnd == g_numbers[j])
            {
                // g_number's Index + 1 = Int
                return j + 1;
            }
        }
    }

    std::cerr << "ERROR: No valid number found in line: "<< line << "\n"; 
    return -1;
}

int getIntegral(std::string line)
{
    std::string subString = "";
    for (int i = line.size() - 1; i > -1; --i) {

        if (line[i] >= '0' && line[i] <= '9') { 
            return charToInt(line[i]);
        }
        subString = line[i] + subString;

        for (int j = 0; j < g_numbers.size(); ++j) {         

            std::string choppedStart = subString.substr(0, g_numbers[j].size());

            if (choppedStart == g_numbers[j])
            {
                // g_number's Index + 1 = Int
                return j + 1;
            }
        }
    }

    std::cerr << "ERROR: No valid number found in line: "<< line << "\n"; 
    return -1;
}

int getCalibrationFromLine(std::string &line)
{   
    return getDecimal(line) * 10 + getIntegral(line);
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
        std::cout << line << " => ";
        int calib = getCalibrationFromLine(line);
        std::cout << calib << "\n";
        sum += calib;
    }
    std::cout << '\n' << "RESULT: " << sum << '\n';
}