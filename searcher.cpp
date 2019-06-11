#include "console.hpp"
#include "searcher.hpp"


StringFinder::Searcher::Searcher(std::string t_phrase, std::shared_ptr<FileQueue>& t_files, std::atomic<bool>& complete_flag)
: m_searching_complete(complete_flag), m_phrase(std::move(t_phrase)), m_files(t_files) {}

StringFinder::Searcher::~Searcher() {
    m_phrase.clear();
}

void StringFinder::Searcher::runProcessSearching() const {
    while(m_files.get()->hasItems() || !m_searching_complete) { // TODO: test complete flag
        scanFileForPhrase(m_files.get()->remove());
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
                if (iterateWholePhrase(phrase_length, next_string_part, temp_phrase)) {
                    Console::printPhraseOccurence(t_candidate, buffer, counter, control_deque_offset, phrase_length);
                    break;
                }
                ++next_string_part;
            }
            ++counter;
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
