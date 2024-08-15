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

short BingoCard::PlayBingo(funcPtr winCheck) {

}

// could probably be optimized, "slow"
bool BingoCard::CheckCrossout() {
    for (int i = 0; i < 25; i++) {
        if (!checks[i]) {
            return false;
        }
    }
    return true;
}

// Results

Results::Results(std::string typ) {
    type = typ;
    for (int i = 0; i < 75; i++) {
        wins[i] = 0;
    }
    cardCount = 0;
}

Results::~Results() {}

long long Results::WinCount(short value) {
    return wins[value - 1];
}

long long Results::Count() {
    return cardCount;
}

void Results::Add(short value) {
    wins[value - 1]++;
    cardCount++;
}

void Results::AddMultiple(short value, long long count) {
    wins[value - 1] += count;
    cardCount += count;
}