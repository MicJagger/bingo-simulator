#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "bingocard.h"

void BingoThread(Results* results, std::atomic<bool>& running, unsigned long long seedStart);

int UserChoose();
Results* BingoSelect();
bool FreeSpaceSelect();

int main() {
    Results* results = BingoSelect();
    bool freeSpace = FreeSpaceSelect();
    unsigned int threadCount = ThreadCount();

    // divides 2^64 by threadCount to get ~equally spaced starting values
    unsigned long long index = round(((double)0x8000000000000000 / (double)threadCount) * 2);

    std::vector<std::thread> threads;
    std::vector<Results*> threadResults;
    std::atomic<bool> running;

    std::string returnWait;
    // main loop
    while (true) {
        running = true;
        std::cout << "Running bingo simulations\n";
        for (int i = 0; i < threadCount; i++) {
            threadResults.push_back(new Results());
            threads.push_back(std::thread(BingoThread, threadResults[i], running, index * i));
        }

        std::cout << "Input to pause" << std::endl;
        std::cin >> returnWait;
        running = false;


    }
    
    

    return 0;
}

void BingoThread(Results* results, std::atomic<bool>& running, unsigned long long seedStart) {

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

