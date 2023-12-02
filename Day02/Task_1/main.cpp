#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

void chopName(std::string &line)
{
    int pos = line.find(':');
    line = line.substr(pos + 1);
}

void defineCubesForSet(std::string set, int &red, int &green, int &blue)
{
    std::istringstream stream(set);
    for (std::string colorData; std::getline(stream, colorData, ',');) {
        std::string number = "";
        for (int i = 0; i < colorData.size(); ++i) {        
            if (colorData[i] == ' ') {
                continue;
            } else if (colorData[i] >= '0' && colorData[i] <= '9') {
                number += colorData[i];
            } else {
                switch(colorData[i]) {
                    case 'r': 
                        red = stoi(number);
                        break;
                    case 'g':
                        green = stoi(number);
                        break;
                    case 'b':
                        blue = stoi(number);
                        break;
                }
                break;
            }
        }
    }
}

bool isGameValid(int red, int green, int blue) {
    const int redLimit = 12;
    const int greenLimit = 13;
    const int blueLimit = 14;

    return red <= redLimit && green <= greenLimit && blue <= blueLimit;
}

int main()
{
    std::ifstream inputFile;
    if (!readFile(inputFile)) {
        std::cerr << "ERROR: Can't open input file\n"; 
        return 1;
    }

    int sum = 0;
    int gameCounter = 1;
    for (std::string game; std::getline(inputFile, game);) {
        chopName(game);
        bool isValid = true;
        std::istringstream stream(game);
        for (std::string set; std::getline(stream, set, ';');) {
            int redCubes = 0;
            int greenCubes = 0;
            int blueCubes = 0;
            defineCubesForSet(set, redCubes, greenCubes, blueCubes);
            isValid &= isGameValid(redCubes, greenCubes, blueCubes);
        }
        

        if (isValid) {
            std::cout << "Game N" << gameCounter << " fits. ";
            sum += gameCounter;
            std::cout << "Sum = " << sum << '\n';
        } else {
            std::cout << "Game N" << gameCounter << " doesn't fit. ";
            std::cout << "Values = " << game << '\n';
        }
        gameCounter++;
    }
}