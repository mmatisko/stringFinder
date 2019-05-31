#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <cstring>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

#include "filesystem.hpp"


class Console {
public:
    static void printDebugInfo(std::initializer_list<std::string> messagePart);
    static void printPhraseOccurency(const FilePtr t_candidate, const std::deque<char>& t_buffer, const unsigned int t_counter, 
        const unsigned short t_controlDequeOffset, const unsigned int phraseLength);
    static std::string formatPrefixSuffix(const std::deque<char>& t_buffer, const unsigned short t_from, const unsigned short t_to);

private:
    Console() = delete;
    Console(const Console& c) = delete;
    Console& operator=(const Console& c) = delete;

    Console(const Console&& c) = delete;
    Console& operator=(const Console&& c) = delete;
};

#endif //CONSOLE_HPP