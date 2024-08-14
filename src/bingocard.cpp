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

short BingoCard::PlayBingo(funcPtr winCheck) {

}

BingoCard::~BingoCard() {

}

bool CheckCrossout() {

}

// Results

Results::Results(std::string typ) {
    type = typ;
    for (int i = 0; i < 75; i++) {
        wins[i] = 0;
    }
    cardCount = 0;
}

Results::~Results() {

}

void Results::Add(short value) {
    wins[value - 1]++;
    cardCount++;
}