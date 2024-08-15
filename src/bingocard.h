#pragma once
#ifndef _BINGOCARD_H
#define _BINGOCARD_H

#include <random>
#include <string>

// individual card, gets created and deleted

class BingoCard {
    short values[25];
    bool checks[25];
    short callOrder[75];
public:
    BingoCard(bool freeSpace, long long seed);
    ~BingoCard();
    // play
    short PlayBingoCrossout();
};

// results for compiling wins, spawned once per thread plus one overall

class Results {
    std::string type;
    long long wins[75];
    long long cardCount;
public:
    Results(std::string typ);
    Results();
    ~Results();
    void Clear();

    std::string Type();
    long long WinCount(short value);
    long long Count();
    double WinChance(short value);

    void Add(short value);
    void AddMultiple(short value, long long count);
};

#endif