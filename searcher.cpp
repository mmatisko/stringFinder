#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstring>
#include <deque>

#include "searcher.hpp"


Searcher::Searcher(const std::string t_phrase) : m_phrase(t_phrase) {}

Searcher::~Searcher() {
    m_phrase.clear();
}

void Searcher::processSearching(FileQueue& t_files) {
    while(!t_files.empty()) {
        scanFileForPhrase(t_files.front());
        t_files.pop();
    }
}

void Searcher::scanFileForPhrase(const FilePtr t_candidate) {
    std::deque<char> buffer;
    const unsigned short partSize = 10;
    unsigned int counter = 0, phraseLength = m_phrase.length();
    unsigned short nextStringPart, controlDequeOffset = 0;

    Console::printDebugInfo({"Processing file: ", t_candidate->getFileName()});
    do {
        std::string tempPhrase = (phraseLength > partSize) ? m_phrase.substr(0, partSize) : m_phrase;
        nextStringPart = 1;

        if(buffer.back() != EOF) {  // previously reached EOF, not any chars to read
            loadToBuffer(t_candidate, buffer);
        }
        if(buffer.size() < phraseLength) { break; }

        while(controlDequeOffset <= 3) {  // prefix offset
            while(comparePhrases(tempPhrase, buffer, controlDequeOffset + partSize * (nextStringPart - 1))) {
                if(phraseLength <= (nextStringPart * partSize)) { // found a phrase
                    Console::printPhraseOccurency(t_candidate, buffer, counter, controlDequeOffset, phraseLength);
                    break;
                } else {  // check next part of searched string
                    if(phraseLength > ((nextStringPart + 1) * partSize)) {  // next part have full size
                        tempPhrase = m_phrase.substr(partSize * nextStringPart, partSize); 
                    } else {  // next part is last with reduced size
                        tempPhrase = m_phrase.substr(partSize * nextStringPart, phraseLength - (partSize * nextStringPart));
                    }
                }
                ++nextStringPart;
            }
            ++controlDequeOffset;
            ++counter;
        }
        buffer.pop_front();
        --controlDequeOffset;
    } while(t_candidate->hasCharToRead() || (buffer.size() >= phraseLength));
}

void Searcher::loadToBuffer(const FilePtr t_candidate, std::deque<char>& t_buffer) {
    char currentChar;
    while(t_buffer.size() < 1000) {
        currentChar = t_candidate->getNextChar();
        if(currentChar == EOF) {
            break;
        } else {
            t_buffer.push_back(currentChar);
        }
    }
}

bool Searcher::comparePhrases(const std::string& t_phrase, const std::deque<char>& t_buffer, const unsigned int t_offset) {
    for(size_t i = 0; i < t_phrase.length(); ++i) {
        if(t_phrase.at(i) != t_buffer[t_offset + i]) {
            return false;
        }
    }
    return true;
}
