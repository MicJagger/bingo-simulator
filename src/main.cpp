#include <iostream>

#include "bingocard.h"

int userChoose();
Results* bingoSelect();
bool freeSpace();

int main() {
    Results* results = bingoSelect();

    

    return 0;
}

// ensure proper user input, return 0 else
int userChoose() {
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
Results* bingoSelect() {
    int userChoice;

    while (true) {
        std::cout 
        << "Select a Bingo Game Type: \n"
        << "1. Crossout (full card)\n"
        << "2. tbd\n"
        << std::endl;

        userChoice = userChoose();
        if (userChoice >= 1 && userChoice <= 2) {
            break;
        }
    }

    switch (userChoice) {
        case 1:

    }
}

// true/false for free space
bool freeSpace() {
    int userChoice;

    while (true) {
        std::cout 
        << "Free Space? \n"
        << "1. Yes\n"
        << "2. No\n"
        << std::endl;

        userChoice = userChoose();
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