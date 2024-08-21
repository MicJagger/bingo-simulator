#pragma once
#ifndef _RESULTS_HPP
#define _RESULTS_HPP

#include "stdincludes.hpp"

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