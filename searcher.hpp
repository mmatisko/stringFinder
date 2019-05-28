#ifndef SEARCHER_HPP
#define SEARCHER_HPP

#include <cstring>
#include <deque>
#include <memory>
#include <vector>

#include "file.hpp"
#include "filesystem.hpp"

class Searcher {
private:
    std::string m_phrase;

protected:
    void loadToBuffer(const FilePtr t_candidate, std::deque<char>& t_buffer);
    bool comparePhrases(const std::string& t_first, const std::deque<char>& t_second, const unsigned int t_offset);
    void printPhraseOccurency(const FilePtr t_candidate, const std::deque<char>& t_buffer,
         const unsigned int t_counter, const unsigned short t_controlDequeOffset);
    std::string formatPrefixSuffix(const std::deque<char>& t_buffer, const unsigned short t_from, const unsigned short t_to);

public:
    Searcher(const std::string t_phrase);
    ~Searcher();
    void processSearching(FileQueue& t_files);
    void scanFileForPhrase(const FilePtr t_candidate);
};

#endif //SEARCHER_HPP