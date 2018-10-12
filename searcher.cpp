#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstring>
#include <deque>

#include "searcher.hpp"

Searcher::Searcher(std::string t_phrase) : m_phrase(t_phrase) {}

Searcher::~Searcher() {}

void Searcher::processSearching(const std::vector<std::shared_ptr<File>>& t_files) {
    for_each(t_files.begin(), t_files.end(), [this](std::shared_ptr<File> candidate) {scanFileForPhrase(candidate);});
}

void Searcher::scanFileForPhrase(const std::shared_ptr<File> t_candidate) {
    std::deque<char> buffer;
    unsigned int counter = 0;
    unsigned short nextStringPart, controlDequeOffset = 0;

    std::cout << "Processing file: " << t_candidate->getFileName() << std::endl;
    do {
        std::string tempPhrase = (m_phrase.length() > 8) ? m_phrase.substr(0, 8) : m_phrase;
        nextStringPart = 1;

        loadToBuffer(t_candidate, buffer);
        if(buffer.size() < m_phrase.length()) break;

        while(controlDequeOffset < 3) {
            while(comparePhrases(tempPhrase, buffer, controlDequeOffset + 8*(nextStringPart-1))) {
                ++nextStringPart;
                if(m_phrase.length() <= 8*nextStringPart) { // found a phrase
                    printPhraseOccurency(t_candidate, buffer, counter, controlDequeOffset);
                    break;
                } else {
                    tempPhrase = (m_phrase.length() > nextStringPart*8) ? m_phrase.substr(8*nextStringPart, 8) : 
                                m_phrase.substr(8*nextStringPart, m_phrase.length() - 8*nextStringPart);
                }
            }
            ++controlDequeOffset;
            ++counter;
        }
        buffer.pop_front();
        --controlDequeOffset;
    } while(!t_candidate->isEof() || (buffer.size() >= m_phrase.length()));
}

void Searcher::loadToBuffer(const std::shared_ptr<File> t_candidate, std::deque<char>& t_buffer) {
    while(t_buffer.size() < 134) {  //to store whole searched phrase with potential maximum lenght
        char currentChar = t_candidate->getNextChar();
        if(currentChar == EOF) {
            break;
        } else {
            t_buffer.push_back(currentChar);
        }
    }
}

bool Searcher::comparePhrases(const std::string& t_phrase, const std::deque<char>& t_buffer, const unsigned int t_offset) {
    for(size_t i = 0; i < t_phrase.length(); ++i) {
        if(t_phrase.at(i) != t_buffer[t_offset + i])
            return false;
    }
    return true;
}

void Searcher::printPhraseOccurency(const std::shared_ptr<File> t_candidate, const std::deque<char>& t_buffer, 
        const unsigned int t_counter, const unsigned short t_controlDequeOffset) {
    const unsigned short suffixLimit = t_buffer.size() >= (m_phrase.length() + 3) ? 
                                (t_controlDequeOffset + m_phrase.length() + 3) : t_buffer.size();
    std::cout << t_candidate->getFileName() << "(" << t_counter << "): ";
    std::string occurency = "";
    if(t_controlDequeOffset > 0) { 
        occurency += formatPrefixSuffix(t_buffer, 0, t_controlDequeOffset);
    }
    occurency += "..." + formatPrefixSuffix(t_buffer, m_phrase.length() + t_controlDequeOffset, suffixLimit);
    std::cout << occurency << std::endl;
    }

std::string Searcher::formatPrefixSuffix(const std::deque<char>& t_buffer, const unsigned short t_from, const unsigned short t_to) {
    std::string result = "";
    for(unsigned short i = t_from; i < t_to; ++i) {
        switch(t_buffer[i]){
            case '\n': 
                result += "\\n"; break;
            case ' ': 
                if (t_buffer[i+1] == ' ' && t_buffer[i+2] == ' ' && t_buffer[i+3] == ' ') {
                    i += 3;
                    result += "\\t";
                    break;
                }
            default:
                result += t_buffer[i];
        }
    }
    return result;
}