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
    // extra shuffling optional (this is mainly here for testing)
    if (false) {
        std::shuffle(&tempVals[ 0], &tempVals[15], std::default_random_engine(seeds[1]));
        std::shuffle(&tempVals[15], &tempVals[30], std::default_random_engine(seeds[2]));
        std::shuffle(&tempVals[30], &tempVals[45], std::default_random_engine(seeds[3]));
        std::shuffle(&tempVals[45], &tempVals[60], std::default_random_engine(seeds[4]));
        std::shuffle(&tempVals[60], &tempVals[75], std::default_random_engine(seeds[5]));
    }
    // transfer to card
    for (int i = 0; i < 25; i++) {
        values[i] = tempVals[3 * i];
    }

    /*
    std::cout << seeds[0] - 1 << " " << seeds[1] << " " << seeds[2] << " " << seeds[3] << " " << seeds[4] << " " << seeds[5] << " "<< '\n';
    for (int i = 0; i < 75; i++) { std::cout << tempVals[i] << ' '; }
    std::cout << '\n';
    for (int i = 0; i < 25; i++) { std::cout << values[i] << ' '; }
    std::cout << '\n';
    for (int i = 0; i < 75; i++) { std::cout << callOrder[i] << ' '; }  
    std::cout << '\n' << std::endl; //*/

    // change seeds
    seeds[1] += 3581;
    seeds[2] += 4421;
    seeds[3] += 5281;
    seeds[4] += 6143;
    seeds[5] += 7001;
    // just some random primes off https://en.wikipedia.org/wiki/List_of_prime_numbers
    // idk im not a mathematician im guessing and making sure these lists don't repeat

    if (freeSpace) {
        checks[12] = true;
    }
}

short BingoCard::PlayBingoCrossout() {
    for (int i = 0; i < 24; i++) {
        Place(callOrder[i]);
    }
    int caller = 23; // it increments to 24 before being called or returned
    bool win;
    while (true) {
        // sort of "slow" checker for crossout, maybe optimize later if possible
        win = true;
        for (int i = 0; i < 25; i++) {
            if (!checks[i]) {
                win = false;
                break;
            }
        }
        caller++;
        // if all were true, return index (+1), which is number of calls
        if (win) {
            return caller;
        }

        // if it breaks somehow this should go off
        if (caller >= 75) {
            std::cout << "never won ???" << '\n';
            return -1;
        }
        
        Place(callOrder[caller]);        
    }
}

inline void BingoCard::Place(short value) {
    for (int i = 0; i < 25; i++) {
        if (value == values[i]) {
            checks[i] = true;
            return;
        }
    }
}
