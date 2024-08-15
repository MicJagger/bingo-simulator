#include "bingocard.h"

// BingoCard

BingoCard::BingoCard(bool freeSpace, long long seed) {
    for (int i = 0; i < 75; i++) {
        callOrder[i] = i + 1;
    }
    
    
    
    
    for (int i = 0; i < 25; i++) {
        checks[i] = false;
        //values[i] = ;
    }
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

}

void Results::Add(short value) {
    wins[value]++;
    cardCount++;
}

void Results::AddMultiple(short value, long long count) {
    wins[value] += count;
    cardCount += count;
}