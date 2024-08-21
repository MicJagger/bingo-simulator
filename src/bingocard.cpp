#include "bingocard.hpp"

// BingoCard

BingoCard::BingoCard() {
    
}

BingoCard::~BingoCard() {}

void BingoCard::Setup(bool freeSpace, std::vector<unsigned int>& seeds, bool changeCall) {
    hits = 0;
    if (freeSpace) {
        hits = hits | (1 << 12);
    }
    short tempVals[75]; // used for bingocard order
    if (changeCall) { // if changing callOrder, shuffle the call order + rest of setup
        for (int i = 0; i < 75; i++) {
            callOrder[i] = i + 1;
            tempVals[i] = i + 1;
        }
        std::shuffle(&callOrder[0], &callOrder[75], std::default_random_engine(seeds[0]));
        seeds[0]++;
    }
    else { // else just shuffle / reset the bingocard
        for (int i = 0; i < 75; i++) {
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

    /*
    std::cout << seeds[0] - 1 << " " << seeds[1] << " " << seeds[2] << " " 
              << seeds[3]     << " " << seeds[4] << " " << seeds[5] << " "<< '\n';
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
}

short BingoCard::PlayBingoCrossout() {
    int index = 0;
    for (index; index < 24; index++) {
        Place(callOrder[index]);
    }
    // increments to 24 before being called or returned
    while (true) {
        if (CheckCrossout()) {
            return index - 1;
            // if reached 75, return 74 to wins[74]++

            // im not sure why doing index + something doesnt cause undefined
            // if its extreme is causes crashing or clearly off data, but when it's
            // say + 0, then it just causes the percents to be a bit higher at the top
            // to be honest, i am COMPLETELY LOST on why that happens
            // probably compiler issue / quirk idk
        }
        Place(callOrder[index]);
        index++;
    }
}

inline void BingoCard::Place(short value) {
    for (int i = 0; i < 25; i++) {
        if (value == values[i]) { // set bit position to 1 if found
            hits = hits | (1 << i);
            return;
        }
    }
}

inline bool BingoCard::CheckCrossout() {
    if (hits == 0x01FFFFFF) { // last 25 bits are ones
        return true;
    }
    return false;
}
