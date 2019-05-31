#ifndef SEARCHER_HPP
#define SEARCHER_HPP

#include <cstring>
#include <deque>
#include <memory>
#include <vector>

#include "file.hpp"


class Searcher {
private:
    std::string m_phrase;

protected:
    void loadToBuffer(const FilePtr t_candidate, std::deque<char>& t_buffer);
    bool comparePhrases(const std::string& t_first, const std::deque<char>& t_second, const unsigned int t_offset);

public:
    explicit Searcher(const std::string t_phrase);
    ~Searcher();
    void processSearching(FileQueue& t_files);
    void scanFileForPhrase(const FilePtr t_candidate);

    // make class non-copyable
    Searcher(const Searcher&) = delete;
    Searcher& operator=(const Searcher&) = delete;
    // make class non-movable
    Searcher(const Searcher&& s) = delete;
    Searcher& operator=(const Searcher&& s) = delete;
};

#endif //SEARCHER_HPP