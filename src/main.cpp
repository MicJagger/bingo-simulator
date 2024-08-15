#include <atomic>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

#include "bingocard.h"
#include "tests.cpp"

void BingoThreadCrossout(Results* results, std::atomic<bool>& running, 
                         bool freeSpace, unsigned long long seedStart);

int UserChoose();
Results* BingoSelect();
bool FreeSpaceSelect();

void PrintResults(Results* results);

int main() {
    bool runTests = false;
    if (runTests) {
        
    }
    Results* results = BingoSelect();
    bool freeSpace = FreeSpaceSelect();
    unsigned int threadCount = ThreadCount();

    // divides 2^64 by threadCount to get ~equally spaced starting values
    unsigned long long index = round(((double)0x8000000000000000 / (double)threadCount) * 2);

    std::vector<std::thread> threads;
    std::vector<Results*> threadResults;
    std::atomic<bool> running;

    std::string returnWait;
    for (int i = 0; i < threadCount; i++) {
        threadResults.push_back(new Results());
    }
    // main loop
    while (true) {
        running = true;
        std::cout << "Running bingo simulations\n";
        if (results->Type() == "Crossout") {
            for (int i = 0; i < threadCount; i++) {
                threads.push_back(std::thread(BingoThreadCrossout, 
                threadResults[i], running, freeSpace, index * i + threadResults[i]->Count()));
            }
        }

        std::cout << "Input to pause" << std::endl;
        std::cin >> returnWait;
        running = false;

        for (int i = 0; i < threadCount; i++) {
            threads[i].join();
        }
        threads.clear();
        results->Clear();
        for (int i = 0; i < threadCount; i++) {
            for (int j = 0; j < 75; j++) {
                results->AddMultiple(j, threadResults[i]->WinCount(j));
            }
        }

    }
    
    

    return 0;
}

void BingoThreadCrossout(Results* results, std::atomic<bool>& running, 
                         bool freeSpace, unsigned long long seedStart) {
    while (running) {
        BingoCard card = BingoCard(freeSpace, seedStart);
        //short winValue = card.PlayBingo(winType);

        seedStart++;
    }
}

void PrintResults(Results* results) {
	for (int i = 0; i < 75; i++) {
        // how many times it won in that many moves (display i + 1)
		std::cout << i + 1 << " calls happened ";
		std::cout << std::setw(16) << std::right << results->WinCount(i);
        // total chance 
		std::cout << " times with a chance of ";
		std::cout << std::setw(11) << std::right << 100 * results->WinChance(i) << "%" << '\n';
	}
}

// ensure proper user input, return 0 else
int UserChoose() {
    std::string userInput;
    std::cin >> userInput;
        try {
            return stoi(userInput);
        } 
        catch (...) {
            std::cout << "Error: Invalid Choice. Please Try Again." << std::endl;
            return 0;
        }
}

// select bingo game type
Results* BingoSelect() {
    int userChoice;

    while (true) {
        std::cout 
        << "Select a Bingo Game Type: \n"
        << "1. Crossout (full card)\n"
        << "2. tbd"
        << std::endl;

        userChoice = UserChoose();
        if (userChoice >= 1 && userChoice <= 2) {
            break;
        }
    }

    switch (userChoice) {
        case 1:
            return new Results("Crossout");
    }
}

// true/false for free space
bool FreeSpaceSelect() {
    int userChoice;

    while (true) {
        std::cout 
        << "Free Space? \n"
        << "1. Yes\n"
        << "2. No"
        << std::endl;

        userChoice = UserChoose();
        if (userChoice >= 1 && userChoice <= 2) {
            break;
        }
    }

    if (userChoice == 1) {
        return true;
    }
    else {
        return false;
    }
}

// gather desired thread count
unsigned int ThreadCount() {
    int userChoice;

    while (true) {
        std::cout 
        << "Input Thread Count: "
        << std::endl;

        userChoice = UserChoose();
        if (userChoice >= 1 && userChoice <= 256) {
            break;
        }
    }

    return userChoice;
}
