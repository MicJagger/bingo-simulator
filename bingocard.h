#pragma once
#ifndef _BINGOCARD_H
#define _BINGOCARD_H

#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>
using namespace std;

class BingoCard {
	char values[24];
	bool checks[24];
public:
	BingoCard();
	~BingoCard() {}

	void GenerateValues();
	bool CheckValue(char value);
	bool CheckBingo();
	bool CheckFull();
};

class Counter {
	long long totalGamesPlayed;
	long long winValues[52];
public:
	Counter();
	~Counter() {}

	void AddValue(int winValue);
	void AddValueMultiple(int winIndex, long long count);

	double Chance(int winValue);
	long long WinValue(int index);
	long long TotalGames();
};

#endif
