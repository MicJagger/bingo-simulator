#include <iostream>

#include "bingocard.h"

int main() {

    std::string userInput;
    int userChoice;
    while (true) {
        std::cout 
        << "Select a Bingo Game Type: \n"
        << "1. Crossout (full card)\n"
        << "2. tbd\n"
        << std::endl;

        std::cin >> userInput;
        try {
            userChoice = stoi(userInput);
            break;
        } 
        catch (...) {
            std::cout << "Error: Invalid Choice. Please Try Again." << std::endl;
        }
    }

    switch (userChoice) {
            case 1:

        }

        

    return 0;
}