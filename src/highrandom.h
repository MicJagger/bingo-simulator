#pragma once
#ifndef _HIGHRANDOM_H
#define _HIGHRANDOM_H

#include <algorithm>
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

// may be used later for higher random seeds

namespace rnd {
    
};

// old code
/*
std::shuffle(&tempVals[0], &tempVals[15], std::default_random_engine(seed));
std::shuffle(&tempVals[15], &tempVals[30], std::default_random_engine(seed));
std::shuffle(&tempVals[30], &tempVals[45], std::default_random_engine(seed));
std::shuffle(&tempVals[45], &tempVals[60], std::default_random_engine(seed));
std::shuffle(&tempVals[60], &tempVals[75], std::default_random_engine(seed));
//*/

#endif