#include "results.h"

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
