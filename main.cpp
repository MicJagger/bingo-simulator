#include "bingocard.h"
using namespace std;

void PlayBingo(Counter* counter, atomic<bool>& running) {
	std::chrono::steady_clock::time_point now;
	
	while (running) {
		now = std::chrono::high_resolution_clock::now();
		//srand(now.time_since_epoch().count() % 0x100000000);
		char number_order[75]{};
		for (int i = 0; i < 75; i++) {
			number_order[i] = i + 1;
		}
		shuffle(&number_order[0], &number_order[74], default_random_engine(now.time_since_epoch().count() % 0x100000000)); // generate random order of values
		
		// Start-ish
		BingoCard card; // auto-generates card
		for (int i = 0; i < 75; i++) {
			if (card.CheckValue(number_order[i])) { // check number generated order, check it off if on the card
				if (card.CheckFull()) { // if on the card, check if the card is full
					counter->AddValue(i + 1); // add onto the counter for value (i + 1) as a win
					break;
				}
			}
		}
	}
}

int main() {
	int threadCount = 16;
	vector<Counter*> counts;
	vector<thread> simulation;
	atomic<bool> running { true };
	Counter finalCount;
	string returnWait;

	while (true) {
		running = true;

		for (int i = 0; i < threadCount; i++) {
			counts.push_back(new Counter);
			simulation.push_back(thread(PlayBingo, counts[i], ref(running)));
		}

		cout << "Input to Pause" << endl;
		cin >> returnWait;
		running = false;

		for (int i = 0; i < threadCount; i++) {
			simulation[i].join();
		}
		simulation.clear();

		for (int i = 0; i < threadCount; i++) {
			for (int j = 0; j < 52; j++) {
				finalCount.AddValueMultiple(j, counts[i]->WinValue(j)); // transfer threaded counters to main counter
			}
			delete counts[i];
		}
		counts.clear();

		for (int i = 0; i < 52; i++) {
			cout << i + 24 << " calls happened ";
			cout << setw(16) << right << finalCount.WinValue(i); // how many times it won in that many moves
			cout << " times with a chance of ";
			cout << setw(11) << right << 100 * finalCount.Chance(i + 24) << "%" << '\n'; // total chance 
		}
		cout << "Total Games: " << finalCount.TotalGames() << endl;

		short maxCalls = 45;
		long long wins = 0;
		for (int i = 0; i < maxCalls - 23; i++) {
			wins += finalCount.WinValue(i);
		}
		cout << "Chance in less than " << maxCalls << ": ";
		cout << 100 * (double)wins / (double)finalCount.TotalGames() << "% from " << wins << " games" << '\n';

		cout << "Continue? Y/y for yes" << '\n';
		cin >> returnWait;
		if (returnWait != "Y" && returnWait != "y") {
			break;
		}
	}

	return 0;
}