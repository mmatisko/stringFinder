#ifndef CONSOLE_HPP
    #define CONSOLE_HPP

    #include <cstring>
    #include <initializer_list>
    #include <iostream>
    #include <stdexcept>
    #include <string>

    #include "file.hpp"


    namespace StringFinder {
        class Console {
        public:
            static std::string toString(std::string input);
            static std::string toString(const char input[]);
            static std::string toString(char input[]);
            template <typename T> static std::string toString(T input);
            template <typename... Args> static std::string toString(std::string input, Args... args);
            template <typename... Args> static void printDebugInfo(const Args&... t_message_parts);
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

        inline std::string Console::toString(std::string input) {
            return input;
        }

        inline std::string Console::toString(const char input[]) {
            return std::string(input);
        }

        inline std::string Console::toString(char input[]) {
            return std::string(input);
        }

        template <typename T>
        inline std::string Console::toString(T input) {
            return std::to_string(input);
        }

        template <typename... Args>
        inline std::string Console::toString(std::string input, Args... args) {
            return input + toString(args...);
        }

        template <typename... Args>
        inline void Console::printDebugInfo(const Args&... t_message_parts) {
            std::string output = "[DEBUG] ";
            output += toString(t_message_parts...);
            std::cout << output << std::endl;
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