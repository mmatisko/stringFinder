#include "console.hpp"


void StringFinder::Console::printPhraseOccurency(const FilePtr t_candidate, const std::deque<char>& t_buffer, const unsigned int t_counter, 
const unsigned short t_control_deque_offset, const unsigned int t_phrase_length) {
    std::string occurency = t_candidate->getFileName() + "(" + std::to_string(t_counter) + "): ";        
    const unsigned short suffixLimit = (t_buffer.size() >= (t_phrase_length + 3)) ? 
                                (t_control_deque_offset + t_phrase_length + 3) : t_buffer.size();
    if(t_control_deque_offset > 0) { 
        occurency += formatPrefixSuffix(t_buffer, 0, t_control_deque_offset);
    }
    occurency += "..." + formatPrefixSuffix(t_buffer, t_phrase_length + t_control_deque_offset, suffixLimit);
    std::cout << occurency << std::endl;
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