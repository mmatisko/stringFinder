#include <iostream>

#include "console.hpp"
#include "filesystem.hpp"


void StringFinder::Console::printPhraseOccurency(const FilePtr t_candidate, const std::deque<char>& t_buffer, const unsigned int t_counter, 
const unsigned short t_controlDequeOffset, const unsigned int t_phraseLength) {
    std::string occurency = "";        
    const unsigned short suffixLimit = (t_buffer.size() >= (t_phraseLength + 3)) ? 
                                (t_controlDequeOffset + t_phraseLength + 3) : t_buffer.size();
    if(t_controlDequeOffset > 0) { 
        occurency += formatPrefixSuffix(t_buffer, 0, t_controlDequeOffset);
    }
    occurency += "..." + formatPrefixSuffix(t_buffer, t_phraseLength + t_controlDequeOffset, suffixLimit);
    std::cout << t_candidate->getFileName() << "(" << t_counter << "): " << occurency << std::endl;
}

std::string StringFinder::Console::formatPrefixSuffix(const std::deque<char>& t_buffer, const unsigned short t_from, 
const unsigned short t_to) {
    std::string result = "";
    for(unsigned short i = t_from; i < t_to; ++i) {
        switch(t_buffer[i]){
            case '\n': {
                result += "\\n"; 
                break;
            }
            case '\t': { 
                result += "\\t";
                break;
            }
            default: {
                result += t_buffer[i];
            }
        }
    }
    return result;
}