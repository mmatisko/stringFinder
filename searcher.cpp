#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstring>
#include <deque>

#include "searcher.hpp"

Searcher::Searcher(std::string phrase) {
    this->phrase = phrase;
}

Searcher::~Searcher() {}

void Searcher::processSearching(std::vector<File*>& files) {
    for_each(files.begin(), files.end(), [this](File* candidate) {scanFileForPhrase(candidate);});
}

void Searcher::scanFileForPhrase(File* candidate) {
    std::string tempPhrase; 
    std::deque<char> buffer;
    unsigned int counter = 0;
    unsigned short nextStringPart, controlDequeOffset = 0;

    std::cout << "Processing file: " << candidate->getFileName() << std::endl;
    do {
        tempPhrase = (phrase.length() > 8) ? phrase.substr(0, 8) : phrase;
        nextStringPart = 1;

        loadToBuffer(candidate, buffer);
        if(buffer.size() < phrase.length()) break;

        while(controlDequeOffset < 3) {
            while(comparePhrases(tempPhrase, buffer, controlDequeOffset + 8*(nextStringPart-1))) {
                ++nextStringPart;
                if(phrase.length() <= 8*nextStringPart) { // found a phrase
                    printPhraseOccurency(candidate, buffer, counter, controlDequeOffset);
                    break;
                } else {
                    tempPhrase = (phrase.length() > nextStringPart*8) ? phrase.substr(8*nextStringPart, 8) : 
                                phrase.substr(8*nextStringPart, phrase.length() - 8*nextStringPart);
                }
            }
            ++controlDequeOffset;
            ++counter;
        }
        buffer.pop_front();
        --controlDequeOffset;
    } while(!candidate->isEof() || (buffer.size() >= phrase.length()));
}

void Searcher::loadToBuffer(File* candidate, std::deque<char>& buffer) {
    while(buffer.size() < 134) {  //to store whole searched phrase with potential maximum lenght
        char currentChar = candidate->getNextChar();
        if(currentChar == EOF) {
            break;
        } else {
            buffer.push_back(currentChar);
        }
    }
}

bool Searcher::comparePhrases(std::string& first, std::deque<char>& second, unsigned int offset) {
    for(size_t i = 0; i < first.length(); ++i) {
        if(first.at(i) != second[offset+i])
            return false;
    }
    return true;
}

void Searcher::printPhraseOccurency(File* candidate, std::deque<char>& buffer, unsigned int counter, unsigned short controlDequeOffset) {
    unsigned short suffixLimit = buffer.size() >= (phrase.length() + 3) ? 
                                (controlDequeOffset + phrase.length() + 3) : buffer.size();
    std::cout << candidate->getFileName() << "(" << counter << "): ";
    if(controlDequeOffset > 0) { // print prefix
        printPrefixSuffix(buffer, 0, controlDequeOffset);
    }
    std::cout << "..."; // print dots
    printPrefixSuffix(buffer, phrase.length() + controlDequeOffset, suffixLimit);
    std::cout << std::endl;
}

void Searcher::printPrefixSuffix(std::deque<char>& buffer, unsigned short from, unsigned short to){
    for(unsigned short i = from; i < to; ++i) { // print suffix
        switch(buffer[i]){
            case '\n': 
                std::cout << "\\n"; break;
            case ' ': 
                if (buffer[i+1] == ' ' && buffer[i+2] == ' ' && buffer[i+3] == ' ') {
                    i+=3;
                    std::cout << "\\t";
                    break;
                }
            default:
                std::cout << buffer[i];
        }
    }
}