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
        }
        Place(callOrder[index]);
        index++;
    }
}

short BingoCard::PlayBingo() {
    int index = 0;
    for (index; index < 4; index++) {
        Place(callOrder[index]);
    }
    while (true) {
        if (CheckBingo()) {
            return index - 1;
        }
        Place(callOrder[index]);
        index++;
    }
}

// Private Helper Functions

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

inline bool BingoCard::CheckBingo() {
    // 0000  000|0  0001 | 0000  1|000  01|00  001|0  0001 
    const int checkRow = 0x108421;

    //                                         000|1  1111
    const int checkColumn = 0x1F;

    // 0000  000|1  0000 | 0100  0|001  00|00  010|0  0001 
    const int checkDiagTlBr = 0x01041041;

    // 0000  000|0  0001 | 0001  0|001  00|01  000|1  0000 
    const int checkDiagBlTr = 0x00111110;

    // check rows (most likely)
    for (int i = 0; i < 5; i++) {
        if ((hits & (checkRow << i)) == (checkRow << i)) {
            //std::cout << hits << '\n' << (checkRow << i) << '\n' 
            //          << (hits & (checkRow << i)) << '\n' << '\n';
            return true;
        }
    }
    // check columns
    for (int i = 0; i < 25; i += 5) {
        if ((hits & (checkColumn << i)) == (checkColumn << i)) {
            //std::cout << hits << '\n' << (checkColumn << i) << '\n' 
            //            << (hits & (checkColumn << i)) << '\n' << '\n';
            return true;
        }
    }
    // check diags
    if ((hits & checkDiagTlBr) == checkDiagTlBr) {
        //std::cout << hits << '\n' << (checkDiagTlBr) << '\n' << (hits & checkDiagTlBr) << '\n' << '\n';
        return true;
    }
    if ((hits & checkDiagBlTr) == checkDiagBlTr) {
        //std::cout << hits << '\n' << (checkDiagBlTr) << '\n' << (hits & checkDiagBlTr) << '\n' << '\n';
        return true;
    }
    return false;
}
