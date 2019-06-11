#include "console.hpp"


void StringFinder::Console::printPhraseOccurence(const FilePtr& t_candidate, const std::deque<char>& t_buffer, const unsigned int t_counter, 
const unsigned int t_control_deque_offset, const unsigned int t_phrase_length) {
    std::string occurence = t_candidate->getFileName() + "(" + std::to_string(t_counter) + "): ";        
    const unsigned int suffix_limit = (static_cast<unsigned int>(t_buffer.size()) > (t_control_deque_offset + t_phrase_length + 3)) ?
                                (static_cast<unsigned long long>(t_control_deque_offset) + t_phrase_length + 3) : static_cast<unsigned int>(t_buffer.size());
    if(t_control_deque_offset > 0) { 
        occurence += formatPrefixSuffix(t_buffer, 0, t_control_deque_offset);
    }
    occurence += "..." + formatPrefixSuffix(t_buffer, t_phrase_length + t_control_deque_offset, suffix_limit);
	doConcurrentPrint(occurence);
}

std::string StringFinder::Console::formatPrefixSuffix(const std::deque<char>& t_buffer, const unsigned int t_from, const unsigned int t_to) {
    std::string result;
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

char StringFinder::Console::getSystemSlash() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	return '\\';
#else
	return '/';
#endif
}
