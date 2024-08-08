#include "bingocard.h"

BingoCard::BingoCard() {
	GenerateValues();
}

void BingoCard::GenerateValues() {
	auto now = std::chrono::high_resolution_clock::now();
	srand(now.time_since_epoch().count() % 0x100000000);
	for (int i = 0; i < 5; i++) {
		values[i] = rand() % 15 + 1;
		for (int j = 0; j < i; j++) {
			if (values[i] == values[j]) {
				i--;
			}
		}
	}
	for (int i = 5; i < 10; i++) {
		values[i] = rand() % 15 + 16;
		for (int j = 5; j < i; j++) {
			if (values[i] == values[j]) {
				i--;
			}
		}
	}
	for (int i = 10; i < 14; i++) { // N Column
		values[i] = rand() % 15 + 31;
		for (int j = 10; j < i; j++) {
			if (values[i] == values[j]) {
				i--;
			}
		}
	}
	for (int i = 14; i < 19; i++) {
		values[i] = rand() % 15 + 46;
		for (int j = 14; j < i; j++) {
			if (values[i] == values[j]) {
				i--;
			}
		}
	}
	for (int i = 19; i < 24; i++) {
		values[i] = rand() % 15 + 61;
		for (int j = 19; j < i; j++) {
			if (values[i] == values[j]) {
				i--;
			}
		}
	}
	std::fill_n(checks, 24, false);

	//for (int i = 0; i < 24; i++) { cout << (int)values[i] << '\n'; }
}

bool BingoCard::CheckValue(char value) {
	for (int i = 0; i < 24; i++) {
		if (value == values[i]) {
			checks[i] = true;
			return true;
		}
	}
	return false;
}

bool BingoCard::CheckBingo() {

	return false;
}

bool BingoCard::CheckFull() {
	for (int i = 0; i < 24; i++) {
		if (!checks[i]) {
			return false;
		}
	}
	return true;
}

// Counter

Counter::Counter() {
	std::fill_n(winValues, 52, 0);
	totalGamesPlayed = 0;
}

void Counter::AddValue(int winValue) {
	winValues[winValue - 24]++;
	totalGamesPlayed++;
}

void Counter::AddValueMultiple(int winIndex, long long count) {
	winValues[winIndex] += count;
	totalGamesPlayed += count;
}

double Counter::Chance(int winValue) {
	return (double)winValues[winValue - 24] / (double)totalGamesPlayed;
}

long long Counter::WinValue(int index) {
	return winValues[index];
}

long long Counter::TotalGames() {
	return totalGamesPlayed;
}
