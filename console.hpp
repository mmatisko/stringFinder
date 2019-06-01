#ifndef CONSOLE_HPP
    #define CONSOLE_HPP

    #include <cstring>
    #include <initializer_list>
    #include <iostream>
    #include <stdexcept>

    #include "file.hpp"


    namespace StringFinder {
        class Console {
        public:
            static void printDebugInfo(const std::initializer_list<std::string> t_message_parts);
            static void printNonCrashException(const std::initializer_list<std::string> t_exception_parts);
            static void printPhraseOccurency(const FilePtr t_candidate, const std::deque<char>& t_buffer, 
                const unsigned int t_counter, const unsigned short t_control_deque_offset, const unsigned int t_phrase_length); 

        private:
            static std::string formatPrefixSuffix(const std::deque<char>& t_buffer, const unsigned short t_from, 
                const unsigned short t_to);

            // make object from class non-creatable
            Console() = delete;
            // make class non-copyable
            Console(const Console& c) = delete;
            Console& operator=(const Console& c) = delete;
            // make class non-movable
            Console(const Console&& c) = delete;
            Console& operator=(const Console&& c) = delete;
        };

        inline void Console::printDebugInfo(const std::initializer_list<std::string> t_message_parts) {
            std::cout << "[DEBUG] ";
            for( auto elem : t_message_parts ) {
                std::cout << elem;
            }
            std::cout << std::endl;
        }

        inline void Console::printNonCrashException(const std::initializer_list<std::string> t_exception_parts) {
            std::cout << "[EXCEPTION] ";
            for( auto elem : t_exception_parts ) {
                std::cout << elem;
            }
            std::cout << std::endl;
        }
    }

#endif //CONSOLE_HPP