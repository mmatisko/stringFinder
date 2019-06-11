#ifndef SEARCHER_HPP
    #define SEARCHER_HPP

	#include <atomic>
    #include <deque>

    #include "filequeue.hpp"
    

    namespace StringFinder {
        class Searcher {
		public:
			explicit Searcher(std::string t_phrase, std::shared_ptr<FileQueue>& t_files, std::atomic<bool>& complete_flag);
			~Searcher();
			void runProcessSearching() const;
			void scanFileForPhrase(const FilePtr& t_candidate) const;

			// make class non-copyable
			Searcher(const Searcher&) = delete;
			Searcher& operator=(const Searcher&) = delete;
			// make class non-movable
			Searcher(const Searcher&& s) = delete;
			Searcher& operator=(const Searcher&& s) = delete;

        protected:
			static void loadToBuffer(const FilePtr& t_candidate, std::deque<char>& t_buffer);
            bool iterateWholePhrase(const unsigned int& t_phrase_length, const unsigned int& t_next_string_part, std::string& t_temp_phrase) const;
            static bool comparePhrases(const std::string& t_phrase, const std::deque<char>& t_buffer, const unsigned int t_offset);
        
		private:
			std::atomic<bool>& m_searching_complete;
			constexpr static unsigned int PART_SIZE = 10;
			constexpr static unsigned int BUFFER_SIZE = 1000;
			std::string m_phrase;
			std::shared_ptr<FileQueue> m_files;
        };
    }

#endif //SEARCHER_HPP