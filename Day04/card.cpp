#include "card.h"

Card::Card(std::string line, uint32_t ind) : index(ind)
{
    chopName(line);
    getValues(line);
}

uint32_t Card::getPoints()
{
    uint32_t score = getNumberOfMatches();
    if (score != 0) {
        score = pow(2, score - 1);
    }
    return score;
}

uint32_t Card::getNumberOfMatches()
{
    uint32_t score = 0;
    for (auto winningValue : winningValues) {
        for (auto ourValue : ourValues) {
            if (winningValue == ourValue) {
                score++;
                break;
            }
        }
    }
    return score;
}

uint32_t Card::getIndex()
{
    return index;
}

void Card::chopName(std::string &line)
{
    size_t begin = line.find(':') + 1;
    line = line.substr(begin);
    
}

void Card::getValues(std::string &line)
{
    size_t delimeterPos = line.find('|');

    std::string winningValuesLine   = line.substr(0, delimeterPos);
    std::string ourValuesLine       = line.substr(delimeterPos + 1);

    std::istringstream winningStream(winningValuesLine);
    std::string winningValue;

    uint32_t i = 0;
    while(std::getline(winningStream, winningValue, ' ')) {
        if (winningValue.empty())
            continue;      
        winningValues[i] = std::stoi(winningValue);
        i++;
    }

    std::istringstream ourStream(ourValuesLine);
    std::string ourValue;

    i = 0;
    while(std::getline(ourStream, ourValue, ' ')) {
        if (ourValue.empty())
            continue;
        ourValues[i] = std::stoi(ourValue);
        i++;
    }
}
