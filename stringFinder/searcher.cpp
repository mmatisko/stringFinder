#include "console.hpp"
#include "searcher.hpp"
#include <utility>


StringFinder::Searcher::Searcher(std::string t_phrase) : m_phrase(std::move(t_phrase)) {}

StringFinder::Searcher::~Searcher() {
    m_phrase.clear();
}

void StringFinder::Searcher::processSearching(FileQueue& t_files) const{
    while(!t_files.empty()) {
        scanFileForPhrase(t_files.front());
        t_files.pop();
    }
}

void StringFinder::Searcher::scanFileForPhrase(const FilePtr& t_candidate) const {
    std::deque<char> buffer;
    unsigned int counter = 0, control_deque_offset = 0;
    const auto phrase_length = static_cast<unsigned int>(m_phrase.length());

    Console::printDebugInfo("Processing file: ", t_candidate->getFileName());
    do {
        std::string temp_phrase = (phrase_length > PART_SIZE) ? m_phrase.substr(0, PART_SIZE) : m_phrase;
        unsigned int next_string_part = 1;

		if(buffer.size() < phrase_length || (!buffer.empty() && buffer.back() != EOF)) {  // previously reached EOF, not any chars to read
            loadToBuffer(t_candidate, buffer);
        }
		if (buffer.size() < phrase_length) { break; }

        for(;control_deque_offset <= 3; ++control_deque_offset) {   //for(;;) { //control_deque_offset <= 3;) {  // prefix offset
            while(comparePhrases(temp_phrase, buffer, control_deque_offset + PART_SIZE * (next_string_part - 1))) {
#ifndef FUN
                if (iterateWholePhrase(phrase_length, next_string_part, temp_phrase)) {
                    Console::printPhraseOccurence(t_candidate, buffer, counter, control_deque_offset, phrase_length);
                    break;
                }
                else {
                    ++next_string_part;
                }
#else
                if(phrase_length <= (next_string_part * PART_SIZE)) { // found a phrase
                    Console::printPhraseOccurence(t_candidate, buffer, counter, control_deque_offset, phrase_length);
                    break;
                } else {  // check next part of searched string
                    if(phrase_length > ((next_string_part + 1) * PART_SIZE)) {  // next part have full size
                        temp_phrase = m_phrase.substr(static_cast<size_t>(PART_SIZE) * next_string_part, PART_SIZE);
                    } else {  // next part is last with reduced size
                        temp_phrase = m_phrase.substr(static_cast<size_t>(PART_SIZE) * next_string_part, phrase_length - (PART_SIZE * next_string_part));
                    }
                }
                ++next_string_part;
#endif
            }
            ++counter;
            if (counter % 100 == 0)
                Console::printDebugInfo("Counter: ", counter);
        }
        buffer.pop_front();
        --control_deque_offset;
    } while((buffer.size() >= phrase_length) || t_candidate->hasCharToRead());
}

void StringFinder::Searcher::loadToBuffer(const FilePtr& t_candidate, std::deque<char>& t_buffer) {
	while(t_buffer.size() < BUFFER_SIZE) {
        char current_char = t_candidate->getNextChar();
        t_buffer.push_back(current_char);
        if(current_char == EOF) {
            break;
        }
    }
}

inline bool StringFinder::Searcher::iterateWholePhrase(const unsigned int& t_phrase_length, const unsigned int& t_next_string_part, std::string& t_temp_phrase) const {
    if(t_phrase_length <= (t_next_string_part * PART_SIZE)) { // found a phrase
        return true;
    } else {  // check next part of searched string
        if(t_phrase_length > ((t_next_string_part + 1) * PART_SIZE)) {  // next part have full size
            t_temp_phrase = m_phrase.substr(PART_SIZE * static_cast<size_t>(t_next_string_part), PART_SIZE);
        } else {  // next part is last with reduced size
            t_temp_phrase = m_phrase.substr(PART_SIZE * static_cast<size_t>(t_next_string_part), t_phrase_length - (PART_SIZE * t_next_string_part));
        }
    }
    return false;
}

bool StringFinder::Searcher::comparePhrases(const std::string& t_phrase, const std::deque<char>& t_buffer, const unsigned int t_offset) {
    //Console::printDebugInfo({"Phrase: ", std::to_string(t_buffer[t_offset])});
    for(size_t i = 0; i < t_phrase.length(); ++i) {
        if(t_phrase.at(i) != t_buffer[t_offset + i]) {
            return false;
        }
    }
    return true;
}
