#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "bingocard.h"

void BingoThread();

int UserChoose();
Results* BingoSelect();
bool FreeSpaceSelect();

int main() {
    Results* results = BingoSelect();
    bool freeSpace = FreeSpaceSelect();
    

    return 0;
}

void BingoThread() {

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
        std::cout << "Error\n";
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
        std::cout << "Error\n";
    }

    if (userChoice == 1) {
        return true;
    }
    else {
        return false;
    }
}

unsigned int ThreadCount() {
    int userChoice;

    while (true) {
        std::cout 
        << "Input Thread Count: "
        << std::endl;

        userChoice = UserChoose();
        if (userChoice >= 1 && userChoice <= 64) {
            break;
        }
        std::cout << "Error\n";
    }

    switch (userChoice) {
        case 1:

    }
}

