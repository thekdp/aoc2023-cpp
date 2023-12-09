#include "converter.h"

Converter::Converter(std::string _name) : name(_name)
{
}

void Converter::addRule(std::string line)
{
    std::istringstream stream(line);
    std::string value;
    ConverterRule rule;
    for (int i = 0; std::getline(stream, value, ' '); ++i) {
        switch (i)
        {
        case 0:
            rule.destination = std::stoull(value);
            break;
        case 1:
            rule.source = std::stoull(value);
            break;
        case 2:
            rule.length = std::stoull(value);
            break;
        }
    }
    rules.push_back(rule);
}

std::vector<ConverterRule> Converter::getRules()
{
    return rules;
}

std::string Converter::getName()
{
    return name;
}

uint64_t Converter::convertValue(uint64_t value)
{
    for (auto rule : rules) {
        if (rule.source <= value && rule.source + rule.length > value) {
            value += rule.destination - rule.source;
            return value;
        }
    }
    return value;
}
