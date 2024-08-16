#include "bingocard.h"

// BingoCard

BingoCard::BingoCard() {
    
}

BingoCard::~BingoCard() {}

void BingoCard::Setup(bool freeSpace, std::vector<unsigned int>& seeds, bool changeCall) {
    short tempVals[75]; // used for bingocard order
    if (changeCall) { // if changing callOrder, shuffle the call order + rest of setup
        for (int i = 0; i < 25; i++) {
            checks[i] = false;
            callOrder[i] = i + 1;
            tempVals[i] = i + 1;
        }
        for (int i = 25; i < 75; i++) {
            callOrder[i] = i + 1;
            tempVals[i] = i + 1;
        }
        std::shuffle(&callOrder[0], &callOrder[75], std::default_random_engine(seeds[0]));
        seeds[0]++;
    }
    else { // else just shuffle / reset the bingocard
        for (int i = 0; i < 25; i++) {
            checks[i] = false;
            tempVals[i] = i + 1;
        }
        for (int i = 25; i < 75; i++) {
            tempVals[i] = i + 1;
        }
    }

    // generate random values on card
    std::shuffle(&tempVals[ 0], &tempVals[15], std::default_random_engine(seeds[1]));
    std::shuffle(&tempVals[15], &tempVals[30], std::default_random_engine(seeds[2]));
    std::shuffle(&tempVals[30], &tempVals[45], std::default_random_engine(seeds[3]));
    std::shuffle(&tempVals[45], &tempVals[60], std::default_random_engine(seeds[4]));
    std::shuffle(&tempVals[60], &tempVals[75], std::default_random_engine(seeds[5]));
    // transfer to card
    for (int i = 0; i < 25; i++) {
        values[i] = tempVals[3 * i];
    }

    ///*
    std::cout << seeds[0] - 1 << " " << seeds[1] << " " << seeds[2] << " " << seeds[3] << " " << seeds[4] << " " << seeds[5] << " "<< '\n';
    for (int i = 0; i < 75; i++) { std::cout << tempVals[i] << ' '; }
    std::cout << '\n';
    for (int i = 0; i < 25; i++) { std::cout << values[i] << ' '; }
    std::cout << '\n';
    for (int i = 0; i < 75; i++) { std::cout << callOrder[i] << ' '; }  
    std::cout << '\n' << std::endl; //*/

    // increment seeds
    seeds[1] += 5;
    seeds[2] += 7;
    seeds[3] += 11;
    seeds[4] += 13;
    seeds[5] += 17;

    if (freeSpace) {
        checks[12] = true;
    }
}

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
