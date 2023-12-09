#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <thread>
#include <ranges>
#include <mutex>

struct ConverterRule
{
    uint64_t destination    = 0;
    uint64_t source         = 0;
    uint64_t length         = 0;
};

class Converter
{
public:
    Converter(std::string name = "");
    void addRule(std::string line);
    std::vector<ConverterRule> getRules();
    std::string getName();
    uint64_t convertValue(uint64_t value);
private:
    std::string name = "";
    std::vector<ConverterRule> rules;
};