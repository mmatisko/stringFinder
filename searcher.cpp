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
    unsigned int counter = 0, phraseLength = m_phrase.length();
    unsigned short nextStringPart, controlDequeOffset = 0;

    Console::printDebugInfo({"Processing file: ", t_candidate->getFileName()});
    do {
        std::string tempPhrase = (phraseLength > 8) ? m_phrase.substr(0, 8) : m_phrase;
        nextStringPart = 1;

        if(buffer.back() != EOF) {
            loadToBuffer(t_candidate, buffer);
        }
        if(buffer.size() < phraseLength) { break; }

        while(controlDequeOffset <= 3) {
            while(comparePhrases(tempPhrase, buffer, controlDequeOffset + 8*(nextStringPart - 1))) {
                ++nextStringPart;
                if(phraseLength <= 8 * nextStringPart) { // found a phrase
                    Console::printPhraseOccurency(t_candidate, buffer, counter, controlDequeOffset, phraseLength);
                    break;
                } else {
                    if(phraseLength > nextStringPart*8) {
                        tempPhrase = m_phrase.substr(8 * nextStringPart, 8);
                    } else {
                        tempPhrase = m_phrase.substr(8 * nextStringPart, phraseLength - 8 * nextStringPart);
                    }
                }
            }
            ++controlDequeOffset;
            ++counter;
        }
        buffer.pop_front();
        --controlDequeOffset;
    } while(!t_candidate->isEof() || (buffer.size() >= phraseLength));
}

void Searcher::loadToBuffer(const FilePtr t_candidate, std::deque<char>& t_buffer) {
    char currentChar;
    while(t_buffer.size() < 134) {
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
