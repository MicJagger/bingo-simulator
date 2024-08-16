#include "bingocard.h"

// BingoCard

BingoCard::BingoCard(bool freeSpace, long long seed) {
    short tempVals[75];
    for (int i = 0; i < 25; i++) {
        checks[i] = false;
        callOrder[i] = i + 1;
        tempVals[i] = i + 1;
    }
    for (int i = 25; i < 75; i++) {
        callOrder[i] = i + 1;
        tempVals[i] = i + 1;
    }
    
    // generate random values on card
    

    ///*
    std::cout << seed << ": ";
    for (int i = 0; i < 75; i++) { std::cout << tempVals[i] << ' '; } 
    std::cout << '\n'; //*/
    
    // shuffle the call order
    std::shuffle(&tempVals[0], &tempVals[75], std::default_random_engine(seed));

    if (freeSpace) {
        checks[12] = true;
    }
}

BingoCard::~BingoCard() {}

short BingoCard::PlayBingoCrossout() {

    // sort of "slow" checker for crossout, maybe optimize later if possible
    bool win = true;
    for (int i = 0; i < 25; i++) {
        if (!checks[i]) {
            win = false;
            break;
        }
    }
    
    return 75;
}
