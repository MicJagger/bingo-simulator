#pragma once
#ifndef _BINGOCARD_H
#define _BINGOCARD_H

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "highrandom.h"

// individual card
class BingoCard {
    short values[25];
    bool checks[25];
    short callOrder[75];
public:
    BingoCard();
    ~BingoCard();
    // setup
    void Setup(bool freeSpace, std::vector<unsigned int>& seeds, bool changeCall);
    // play
    short PlayBingoCrossout();
};

#endif