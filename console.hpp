#ifndef CONSOLE_HPP
    #define CONSOLE_HPP

	#include <deque>
    #include <initializer_list>
    #include <iostream>
	#include <mutex>
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

			template <typename T, typename... Args> static std::string toString(T t_input, Args... t_args);
            template <typename... Args> static void printDebugInfo(const Args&... t_message_parts);
            static void printNonCrashException(std::initializer_list<std::string> t_exception_parts);
            static void printPhraseOccurence(const FilePtr& t_candidate, const std::deque<char>& t_buffer,
                                             unsigned int t_counter, unsigned int t_control_deque_offset, unsigned int t_phrase_length); 

        protected:
            static std::string formatPrefixSuffix(const std::deque<char>& t_buffer, unsigned int t_from, unsigned int t_to);
			static void doConcurrentPrint(const std::string& t_text);
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
        std::string Console::toString(T t_input) {
            return std::to_string(t_input);
        }

        template <typename T, typename... Args>
        std::string Console::toString(T t_input, Args... t_args) {
            return toString(t_input) + toString(t_args...);
        }

        template <typename... Args>
        void Console::printDebugInfo(const Args&... t_message_parts) {
            std::string output = "[DEBUG] ";
            output += toString(t_message_parts...);
			doConcurrentPrint(output);
        }

        inline void Console::printNonCrashException(const std::initializer_list<std::string> t_exception_parts) {
			std::string output = "[EXCEPTION] ";
			std::for_each(t_exception_parts.begin(), t_exception_parts.end(), [&output](const std::string& elem){ output += elem; });
			doConcurrentPrint(output);
        }

		inline void Console::doConcurrentPrint(const std::string& t_text) {
			static std::mutex m_mutex;
			std::unique_lock<std::mutex> locker(m_mutex);
			std::cout << t_text << std::endl;
			locker.unlock();
        }
    }

#endif //CONSOLE_HPP