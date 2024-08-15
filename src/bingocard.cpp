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
    std::shuffle(&tempVals[0], &tempVals[15], std::default_random_engine(seed));
    std::shuffle(&tempVals[15], &tempVals[30], std::default_random_engine(seed));
    std::shuffle(&tempVals[30], &tempVals[45], std::default_random_engine(seed));
    std::shuffle(&tempVals[45], &tempVals[60], std::default_random_engine(seed));
    std::shuffle(&tempVals[60], &tempVals[75], std::default_random_engine(seed));
    //*/
    //std::cout << seed << ": ";
    //for (int i = 0; i < 75; i++) { std::cout << tempVals[i] << ' '; } 
    //std::cout << '\n';
    
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

// Results

Results::Results(std::string typ) {
    type = typ;
    for (int i = 0; i < 75; i++) {
        wins[i] = 0;
    }
    cardCount = 0;
}

Results::Results() {
    type = "";
    for (int i = 0; i < 75; i++) {
        wins[i] = 0;
    }
    cardCount = 0;
}

Results::~Results() {}

void Results::Clear() {
    for (int i = 0; i < 75; i++) {
        wins[i] = 0;
    }
    cardCount = 0;
}

std::string Results::Type() {
    return type;
}

long long Results::WinCount(short value) {
    return wins[value];
}

long long Results::Count() {
    return cardCount;
}

double Results::WinChance(short value) {
    return (double)wins[value] / (double)cardCount;
}

void Results::Add(short value) {
    wins[value]++;
    cardCount++;
}

void Results::AddMultiple(short value, long long count) {
    wins[value] += count;
    cardCount += count;
}