#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <initializer_list>
#include <iostream>
#include <string>

#include "file.hpp"


    namespace StringFinder {
        class Console {
        public:
			// make object from class non-creatable
			Console() = delete;
			// make class non-copyable
			Console(const Console& c) = delete;
			Console& operator=(const Console& c) = delete;
			// make class non-movable
			Console(const Console&& c) = delete;
			Console& operator=(const Console&& c) = delete;

			static char getSystemSlash();
            static std::string toString(std::string t_input);
            static std::string toString(const char t_inputs[]);
            static std::string toString(char t_inputs[]);
            template <typename T> static std::string toString(T t_input);
            template <typename... Args> static std::string toString(std::string t_input, Args... t_args);
            template <typename... Args> static void printDebugInfo(const Args&... t_message_parts);
            static void printNonCrashException(std::initializer_list<std::string> t_exception_parts);
            static void printPhraseOccurence(const FilePtr& t_candidate, const std::deque<char>& t_buffer,
                                             unsigned int t_counter, unsigned int t_control_deque_offset, unsigned int t_phrase_length); 

        private:
            static std::string formatPrefixSuffix(const std::deque<char>& t_buffer, unsigned int t_from, unsigned int t_to);
        };

        inline std::string Console::toString(std::string t_input) {
            return t_input;
        }

        inline std::string Console::toString(const char t_inputs[]) {
            return std::string(t_inputs);
        }

        inline std::string Console::toString(char t_inputs[]) {
            return std::string(t_inputs);
        }

        template <typename T>
        inline std::string Console::toString(T t_input) {
            return std::to_string(t_input);
        }

        template <typename... Args>
        inline std::string Console::toString(std::string t_input, Args... t_args) {
            return t_input + toString(t_args...);
        }

        template <typename... Args>
        inline void Console::printDebugInfo(const Args&... t_message_parts) {
            std::string output = "[DEBUG] ";
            output += toString(t_message_parts...);
            std::cout << output << std::endl;
        }

        inline void Console::printNonCrashException(const std::initializer_list<std::string> t_exception_parts) {
            std::cout << "[EXCEPTION] ";
            for(const auto& elem : t_exception_parts ) {
                std::cout << elem;
            }
            std::cout << std::endl;
        }
    }

#endif //CONSOLE_HPP