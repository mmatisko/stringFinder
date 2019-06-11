#ifndef FILEQUEUE_HPP
	#define FILEQUEUE_HPP

	#include <mutex>

	#include "file.hpp"


	namespace StringFinder {
		class FileQueue {
		public:
			FileQueue() = default;
			void add(const FilePtr& t_input);
			FilePtr remove();
			bool hasItems();

			// make class non-copyable
			FileQueue(const FileQueue& f) = delete;
			FileQueue& operator=(const FileQueue& f) = delete;
			// make class non-movable
			FileQueue(const FileQueue&& f) = delete;
			FileQueue& operator=(const FileQueue&& f) = delete;

		private:
			std::mutex m_mutex;
			std::condition_variable m_cond;

			std::deque<FilePtr> m_buffer;
			constexpr static unsigned int SIZE = 10;
		};
	}

#endif //FILEQUEUE_HPP


