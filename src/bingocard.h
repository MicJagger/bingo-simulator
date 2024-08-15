#include <random>
#include <string>

typedef bool(funcPtr)();

// individual card, gets created and deleted

class BingoCard {
    short values[25];
    bool checks[25];
    short callOrder[75];
public:
    BingoCard(bool freeSpace, long long seed);
    ~BingoCard();
    short PlayBingo(funcPtr winCheck);
    // checks
    bool CheckCrossout();
};

// results for compiling wins, spawned once per thread plus one overall

class Results {
    std::string type;
    long long wins[75];
    long long cardCount;
public:
    Results(std::string typ);
    ~Results();

    long long WinCount(short value);
    long long Count();

    void Add(short value);
    void AddMultiple(short value, long long count);
};