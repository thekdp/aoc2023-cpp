#pragma once

#include <cstddef>

class Part
{
public:

    int number      = 0;
    size_t row      = 0;
    size_t column   = 0;

    bool contains(size_t x, size_t y);
};