#pragma once
#ifndef _BINGOCARD_H
#define _BINGOCARD_H

#include <algorithm>
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

// individual card, gets created and deleted
class BingoCard {
    short values[25];
    bool checks[25];
    short callOrder[75];
public:
    BingoCard(bool freeSpace, long long seed);
    ~BingoCard();
    // play
    short PlayBingoCrossout();
};

#endif