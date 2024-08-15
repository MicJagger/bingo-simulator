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
void PrintResults(Results* results, short preDet);

int UserChoose();
Results* BingoSelect();
bool FreeSpaceSelect();
unsigned int ThreadCount();

int main() {
    bool runTests = false;
    if (runTests) {
        
    }

    Results* results = BingoSelect();
    if (results->Type() == "quit") {
        delete results;
        return 0;
    }
    bool freeSpace = FreeSpaceSelect();
    unsigned int threadCount = ThreadCount();
    if (threadCount == -1) {
        delete results;
        return 0;
    }

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
        std::cout << "\nRunning bingo simulations\n";
        if (results->Type() == "Crossout") {
            for (int i = 0; i < threadCount; i++) {
                threads.push_back(std::thread(BingoThreadCrossout, 
                threadResults[i], ref(running), freeSpace, index * (long long)i + threadResults[i]->Count()));
            }
        }

        std::cout << "Input to pause\n" << std::endl;
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

        PrintResults(results, 45);

        std::cout << "Input to continue, q to quit" << std::endl;
        std::cin >> returnWait;
        if (returnWait == "q") {
            break;
        }
    }
    for (int i = 0; i < threadCount; i++) {
        delete threadResults[i];
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

void PrintResults(Results* results, short preDet) {
	for (int i = 0; i < 75; i++) {
        // how many times it won in that many moves (display i + 1)
        if (i < 9) {
            std::cout << ' '; // make them even
        }
		std::cout << i + 1 << " calls happened ";
		std::cout << std::setw(16) << std::right << results->WinCount(i);
        // total chance 
		std::cout << " times with a chance of ";
		std::cout << std::setw(11) << std::right << results->WinChance(i) * 100 << "%" << '\n';
	}
    std::cout << "Total Games: " << results->Count() << std::endl;

    if (preDet > 0) {
        int value = preDet;
        if (preDet < 5) {
            std::cout << "\nInput a value to get aggregate chance of that or below: \n";
            value = UserChoose();
        }
        double aggregate = 0;
        for (int i = 0; i < value; i++) {
            aggregate += results->WinChance(i);
        }
        std::cout << "Chance of Bingo in <=" << value << " moves: " << aggregate * 100 << "%" << std::endl;
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
        << "2. tbd" //<< '\n'
        //<< "-1. Quit"
        << std::endl;

        userChoice = UserChoose();
        if ((userChoice >= 1 && userChoice <= 2) || userChoice == -1) {
            break;
        }
    }

    switch (userChoice) {
        case -1:
            return new Results("quit");
        case 1:
            return new Results("Crossout");
    }

    return new Results("undefined");
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
        if ((userChoice >= 1 && userChoice <= 256) || userChoice == -1) {
            break;
        }
    }

    return userChoice;
}
