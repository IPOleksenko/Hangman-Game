#pragma once

#include <windows.h>
#include <vector>
#include <random>
#include "words.h"

LPCWSTR GetRandomWord(const LPCWSTR strings[], const int size)
{
    std::random_device rd;  
    std::mt19937 mt(rd());  
    std::uniform_int_distribution<int> dist(0, (sizeof(words) / sizeof(words[0])) - 1);

    if (size == 0) {
        return nullptr;
    }
    return strings[dist(mt)];
}
