#include <string>

#include "part.h"

bool Part::contains(size_t x, size_t y)
{
    if (x != row)
        return false;

    int numberSize = std::to_string(number).size();
    for (int i = 0; i < numberSize; ++i) {
        if (y == column - i)
            return true;
    }
    return false;
}