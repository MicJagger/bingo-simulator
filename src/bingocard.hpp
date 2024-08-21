#pragma once
#ifndef _BINGOCARD_HPP
#define _BINGOCARD_HPP

#include "stdincludes.hpp"

#include "highrandom.hpp"

// individual card
class BingoCard {
    short values[25];
    short callOrder[75];
    int hits;
public:
    BingoCard();
    ~BingoCard();
    // setup
    void Setup(bool freeSpace, std::vector<unsigned int>& seeds, bool changeCall);
    // play
    short PlayBingoCrossout();
private: // helper function(s)
    inline void Place(short value);
    inline bool CheckCrossout();
};

#endif