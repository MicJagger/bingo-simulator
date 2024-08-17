#pragma once
#ifndef _BINGOCARD_H
#define _BINGOCARD_H

#include "stdincludes.h"

#include "highrandom.h"

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