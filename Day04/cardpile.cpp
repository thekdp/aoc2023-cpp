#include "cardpile.h"

CardPile::CardPile(std::ifstream &input)
{
    readInput(input);
}

uint32_t CardPile::calculateTotalPoints()
{
    uint32_t totalScore = 0;
    for (auto card : cards) {
        uint32_t cardScore = card->getPoints();
        // std::cout << "Card #" << card->getIndex() << " worth " << cardScore << " points\n";
        totalScore += cardScore;
    }
    return totalScore;
}

uint32_t CardPile::calculateScratchCards(uint32_t index)
{
    if (index == 0) {
        std::fill(copies.begin(), copies.end(), 1);
    }

    uint32_t matches = cards[index]->getNumberOfMatches();
    for (size_t i = 1; i <= matches; ++i) {
        copies[index + i] += copies[index];
        
    }
    // std::cout << "Card #" << index + 1 << " has " << copies[index] << " copies and " << matches << " matches\n";
    auto totalCopies = copies[index];
    if (index != 219) {
        totalCopies += this->calculateScratchCards(index + 1);
    }
    return totalCopies;  
}

void CardPile::readInput(std::ifstream &input)
{
    std::string line;
    uint32_t index = 1;
    while (std::getline(input, line)) {
        auto card = new Card(line, index);
        cards.push_back(card);
        index++;
    }
}
