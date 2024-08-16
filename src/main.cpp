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

#include "bingocard.h"
#include "highrandom.h"
#include "results.h"
#include "tests.cpp"

void BingoThreadCrossout(Results* results, std::atomic<bool>& running, bool freeSpace,
                         std::vector<unsigned int>& seeds, bool changeCall);
void PrintResults(Results* results, short preDet);

int UserChoose();
Results* BingoSelect();
bool FreeSpaceSelect();
unsigned int ThreadCount();

int main() {

    // if on windows for windows-based stuff such as time, does almost nothing currently
    bool onWindows = true;
    // display time info
    bool timeData = true;

    bool runTests = false;
    if (runTests) {
        
        return 0;
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
    //unsigned long long index = round(((double)0x8000000000000000 / (double)threadCount) * 2);

    // divides 2^32 by threadcount to get ~equally spaced starting seeds
    unsigned int index = round(((double)0x100000000 / (double)threadCount));

    std::vector<std::thread> threads; // function threads
    std::vector<Results*> threadResults; // individual counters
    std::atomic<bool> running; // keeps the threads running
    std::string returnWait; // pause "button"

    // will keep track of rng seeds in order to randomize bingo cards / calls
    // I wasn't going to use vectors but after lots of issues with other data types, here we are
    std::vector<std::vector<unsigned int>> seeds;
    // [thread1:[calls, col1, col2, col3, col4, col5], thread2:[6], thread3:[6], ...]
    // seeds will be changed as different (prime?) numbers, such as +1, +3, +5, +7, +11, +13
    // seeds start at (2^32 / threadCount * threadIndex (+ 1?)), (equally spread)  -  eg 1, 2^31 + 1

    for (unsigned int i = 0; i < threadCount; i++) {
        threadResults.push_back(new Results());
        unsigned int seedStart = index * i;
        std::vector<unsigned int> seedStarts = {seedStart, seedStart, seedStart, seedStart, seedStart, seedStart};
        seeds.push_back(seedStarts);
    }

    double totalTimeTaken = 0;

    // main loop
    while (true) {
        running = true;
        std::cout << "\nRunning bingo simulations\n";
        // timer - WINDOWS-BASED, WILL UPDATE FOR UNIX MAYBE EVENTUALLY
        auto start = std::chrono::high_resolution_clock::now();
        if (results->Type() == "Crossout") {
            for (int i = 0; i < threadCount; i++) {
                threads.push_back(std::thread(BingoThreadCrossout, 
                threadResults[i], ref(running), freeSpace, ref(seeds[i]), true));
            }
        }

        std::cout << "Input to pause" << std::endl;
        std::cin >> returnWait;
        running = false;
        // timer - WINDOWS-BASED, WILL UPDATE FOR UNIX MAYBE EVENTUALLY
        auto end = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < threadCount; i++) {
            threads[i].join();
        }
        auto duration = end - start;
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        double milliTime = milliseconds.count();
        threads.clear();
        
        results->Clear();
        for (int i = 0; i < threadCount; i++) {
            for (int j = 0; j < 75; j++) {
                results->AddMultiple(j, threadResults[i]->WinCount(j));
            }
        }

        PrintResults(results, 45);
        
        if (onWindows && timeData) {
            totalTimeTaken += milliTime;
            double totalSeconds = totalTimeTaken / 1000;
            double totalMinutes = totalSeconds / 60;
            double totalHours = totalMinutes / 60;
            double count = results->Count();
            std::cout << "Total seconds: " << totalSeconds << " seconds\n";
            std::cout << "Total minutes: " << totalMinutes << " minutes\n";
            std::cout << "Total hours: "   << totalHours   << " hours\n";
            std::cout << "Average cards per second: " << count / totalSeconds << " cards\n";
            std::cout << "Average cards per minute: " << count / totalMinutes << " cards\n";
            std::cout << "Average cards per hour: "   << count / totalHours   << " cards\n";
            std::cout << "Average cards per second per thread: " << (count / totalSeconds) / threadCount << " cards\n";
            std::cout << "Average cards per minute per thread: " << (count / totalMinutes) / threadCount << " cards\n";
            std::cout << "Average cards per hour per thread: "   << (count / totalHours) / threadCount   << " cards\n";
        }

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

void BingoThreadCrossout(Results* results, std::atomic<bool>& running, bool freeSpace,
                         std::vector<unsigned int>& seeds, bool changeCall) {
    while (running) {
        BingoCard card = BingoCard();
        card.Setup(freeSpace, seeds, changeCall);
        results->Add(card.PlayBingoCrossout());
    }
}

void PrintResults(Results* results, short preDet) {
    std::cout << '\n';
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
        std::cout << "Chance of Bingo in <= " << value << " moves: " << aggregate * 100 << "%" << std::endl;
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
