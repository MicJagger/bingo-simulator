#include <string>

// individual card, gets created and deleted

class BingoCard {

public:
    
};

// one-time results for storing mass results

class Results {
    std::string type;
    long long wins[75];
    long long cardCount;
public:
    Results(std::string _type);
    ~Results();
};