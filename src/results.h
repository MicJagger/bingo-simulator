#pragma once
#ifndef _RESULTS_H
#define _RESULTS_H

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <vector>

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