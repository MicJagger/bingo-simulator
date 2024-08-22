#include "stdincludes.hpp"

#include "bingocard.hpp"
#include "highrandom.hpp"
#include "results.hpp"
#include "tests.cpp"

void BingoThreadCrossout(Results* results, std::atomic<bool>& running, bool freeSpace,
                         std::vector<unsigned int>& seeds, bool changeCall);
void BingoThread        (Results* results, std::atomic<bool>& running, bool freeSpace,
                         std::vector<unsigned int>& seeds, bool changeCall);
void PrintResults(Results* results, short preDet, int threadCount, double& totalTime, double milli);

// Import / Export

void ImportCSV(Results* res, double& timeTaken);
void ExportCSV(Results* res, double& timeTaken);

// Helper Functions

int UserChoose(int floor, int ceil);
Results* BingoSelect();
bool FreeSpaceSelect();
unsigned int ThreadCount();

int main() {
    // if on windows for windows-based stuff such as time, does almost nothing currently
    bool onWindows = true;
    // display time info
    bool timeData = true;

    // total time in milliseconds
    double totalTimeTaken = 0;

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
    if (threadCount == 0) {
        delete results;
        return 0;
    }

    std::cout << "Would you like to input from values.csv?\n"
              << "1. Yes\n"
              << "2. No" << std::endl;
    int input = UserChoose(1, 2);
    if (input == 1) {
        ImportCSV(results, totalTimeTaken);
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

    // main loop
    while (true) {
        running = true;
        std::cout << "\nRunning bingo simulations\n";
        // timer - WINDOWS-BASED, WILL UPDATE FOR UNIX MAYBE EVENTUALLY (I love Unix/Linux I'm sorry :( )
        auto start = std::chrono::high_resolution_clock::now();
        
        if (results->Type() == "Crossout") {
            for (int i = 0; i < threadCount; i++) {
                threads.push_back(std::thread(BingoThreadCrossout, 
                threadResults[i], ref(running), freeSpace, ref(seeds[i]), true));
            }
        }
        if (results->Type() == "Bingo") {
                for (int i = 0; i < threadCount; i++) {
                threads.push_back(std::thread(BingoThread, 
                threadResults[i], ref(running), freeSpace, ref(seeds[i]), true));
            }
        }

        std::cout << "Input to pause" << std::endl;
        std::cin >> returnWait;
        running = false;
        // timer - WINDOWS-BASED AGAIN
        auto end = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < threadCount; i++) {
            threads[i].join();
        }
        auto duration = end - start;
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        double milliTime = milliseconds.count();
        threads.clear();

        for (int i = 0; i < threadCount; i++) {
            for (int j = 0; j < 75; j++) {
                results->AddMultiple(j, threadResults[i]->WinCount(j));
            }
            threadResults[i]->Clear();
        }

        PrintResults(results, 45, threadCount, totalTimeTaken, milliTime);

        int choice;
        while (true) {
            std::cout << "Input 0 to quit, -1 to continue, "
                      << "-2 to output, or other to change thread count" << std::endl;
            choice = UserChoose(-2, 256);
            if (choice == 0) {
                break;
            }
            else if (choice == -2) {
                ExportCSV(results, totalTimeTaken);
            }
            else if (choice >= 1) {
                threadCount = choice;
            }
            
            // if export is selected, repeat menu
            if (choice != -2) {
                break;
            }
        }

    }
    for (int i = 0; i < threadCount; i++) {
        delete threadResults[i];
    }
    return 0;
}

// Function Definitions

// Play Crossout Bingo
void BingoThreadCrossout(Results* results, std::atomic<bool>& running, bool freeSpace,
                         std::vector<unsigned int>& seeds, bool changeCall) {
    while (running) {
        BingoCard card = BingoCard();
        card.Setup(freeSpace, seeds, changeCall);
        results->Add(card.PlayBingoCrossout());
    }
}

// Play Bingo
void BingoThread        (Results* results, std::atomic<bool>& running, bool freeSpace,
                         std::vector<unsigned int>& seeds, bool changeCall) {
    while (running) {
        BingoCard card = BingoCard();
        card.Setup(freeSpace, seeds, changeCall);
        results->Add(card.PlayBingo());
    }
}

// Output results
void PrintResults(Results* results, short preDet, int threadCount, double& totalTime, double milli) {
    double aggregateChance = 0;
    double cardChance;
    std::cout << '\n';
	for (int i = 0; i < 75; i++) {
        // how many times it won in that many moves (display i + 1)
        if (i < 9) {
            std::cout << ' '; // make them even
        }
		std::cout << i + 1 << "  calls happened  ";
		std::cout << std::setw(16) << std::right << results->WinCount(i);
        
        // chance 
		std::cout << "  times with a chance of  ";
		std::cout << std::setw(11) << std::right << results->WinChance(i) * 100 << "%";
        
        // 1 in how many cards
        cardChance = 1 / results->WinChance(i);
        std::cout << "  or 1 in  ";
        std::cout << std::setw(11) << std::right << cardChance << "  cards";
        
        // aggregate chance
        aggregateChance += results->WinChance(i);
        std::cout << "  and aggregate chance so far of  ";
        std::cout << std::setw(11) << std::right << aggregateChance * 100 << "%";
        
        // 1 in how many cards
        cardChance = 1 / aggregateChance;
        std::cout << "  or 1 in  ";
        std::cout << std::setw(11) << std::right << cardChance << "  cards";
        
        std::cout << '\n';
	}
    std::cout << "Total Games: " << results->Count() << '\n';
    std::cout << "Calculations done using: " << threadCount << " threads" << '\n';

    totalTime += milli;
    double totalSeconds = totalTime / 1000;
    double totalMinutes = totalSeconds / 60;
    double totalHours = totalMinutes / 60;
    double count = results->Count();
    std::cout << "Total seconds: " << totalSeconds << " seconds\n";
    std::cout << "Total minutes: " << totalMinutes << " minutes\n";
    std::cout << "Total hours:   " << totalHours   << " hours\n";
    std::cout << "Average cards per second: " << count / totalSeconds << " cards\n";
    std::cout << "Average cards per minute: " << count / totalMinutes << " cards\n";
    std::cout << "Average cards per hour:   "   << count / totalHours   << " cards\n";
    std::cout << "Average cards per second per thread: " << (count / totalSeconds) / threadCount << " cards\n";
    std::cout << "Average cards per minute per thread: " << (count / totalMinutes) / threadCount << " cards\n";
    std::cout << "Average cards per hour per thread:   " << (count / totalHours) / threadCount   << " cards\n";
}

// Import / Export

// Import from values.csv
void ImportCSV(Results* res, double& totalTime) {
    std::ifstream in;
    in.open("values.csv");
    if (!in.is_open()) {
        std::cout << "Failed to open values.csv" << '\n';
        return;
    }
    std::string value;
    //std::cout << "starting loop" << '\n';
    for (int i = 0; i < 75; i++) {
        std::getline(in, value, ',');
        std::getline(in, value, ',');
        // this is unsafe if the user tampered with the .csv
        res->AddMultiple(i, stoi(value));
        //std::cout << i << " and " << value << '\n';
        std::getline(in, value, '\n');
    }
    std::getline(in, value, '\n');
    std::getline(in, value, '\n');
    // yeah unsafe again just dont mess with the csv for right now
    totalTime += stod(value);
    std::cout << "Data Imported from values.csv" << std::endl;
    in.close();
}

// Export to values.csv
void ExportCSV(Results* res, double& totalTime) {
    std::ofstream out;
    out.open("values.csv");
    if (!out.is_open()) {
        std::cout << "Failed to open values.csv" << '\n';
        return;
    }
    for (int i = 0; i < 75; i++) {
        out << i + 1 << ',' << res->WinCount(i) << ',' << res->WinChance(i) << '\n';
    }
    out << res->Count() << '\n';
    out << totalTime << '\n';
    std::cout << "Data Exported to values.csv" << std::endl;
    out.close();
}

// Helper Functions

// ensure proper user input, return 0 else
int UserChoose(int floor, int ceil) {
    std::string userInput;
    while (true) {
        std::cin >> userInput;
        try {
            if (stoi(userInput) >= floor && stoi(userInput) <= ceil) {
                return stoi(userInput);
            }
            else {
                std::cout << "Error: Invalid Choice. Please Try Again." << std::endl;
            }
        } 
        catch (...) {
            std::cout << "Error: Invalid Choice. Please Try Again." << std::endl;
            return 0;
        }
    }
}

// select bingo game type
Results* BingoSelect() {
    int userChoice;

    std::cout 
    << "Select a Bingo Game Type: \n"
    << "0. Quit\n"
    << "1. Crossout (full card)\n"
    << "2. Bingo (standard)"
    << std::endl;
    userChoice = UserChoose(0, 2);

    switch (userChoice) {
        case 0:
            return new Results("quit");
        case 1:
            return new Results("Crossout");
        case 2:
            return new Results("Bingo");
    }

    return new Results("undefined");
}

// true/false for free space
bool FreeSpaceSelect() {
    int userChoice;

    std::cout 
    << "Free Space? \n"
    << "1. Yes\n"
    << "2. No"
    << std::endl;
    userChoice = UserChoose(1, 2);

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

    std::cout 
    << "Input Thread Count: "
    << std::endl;
    userChoice = UserChoose(0, 256);

    return userChoice;
}
