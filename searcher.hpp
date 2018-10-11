#ifndef SEARCHER_HPP
#define SEARCHER_HPP

#include <cstring>
#include <vector>
#include <deque>

#include "file.hpp"

class Searcher {
private:
    std::string phrase;

protected:
    void loadToBuffer(File* candidate, std::deque<char>& buffer);
    bool comparePhrases(std::string& first, std::deque<char>& second, unsigned int offset);
    void Searcher::printPhraseOccurency(File* candidate, std::deque<char>& buffer, unsigned int counter, unsigned short controlDequeOffset);
    void printPrefixSuffix(std::deque<char>& buffer, unsigned short from, unsigned short to);

public:
    Searcher(std::string phrase);
    ~Searcher();
    void processSearching(std::vector<File*>& files);
    void scanFileForPhrase(File* candidate);
    
};


#endif //SEARCHER_HPP