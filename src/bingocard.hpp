#pragma once
#ifndef _BINGOCARD_HPP
#define _BINGOCARD_HPP

#include "stdincludes.hpp"

// individual card
class BingoCard {
    short values[25];
    /*
    0 5 10 15 20
    1 6 11 16 21
    2 7 12 17 22
    3 8 13 18 23
    4 9 14 19 24
    */
    short callOrder[75];
    int hits;
    // 0000   0001   1111   |1111   1|11 [1]   11|11   111|1   1111
public:
    BingoCard();
    ~BingoCard();
    // setup
    void Setup(bool freeSpace, std::vector<unsigned int>& seeds, bool changeCall);
    // play
    short PlayBingoCrossout();
    short PlayBingo();
private: // helper function(s)
    inline void Place(short value);
    inline bool CheckCrossout();
    inline bool CheckBingo();
};

#endif