#include "filequeue.hpp"

void StringFinder::FileQueue::add(const FilePtr& t_input) {
	std::unique_lock<std::mutex> locker(m_mutex);
	m_cond.wait(locker, [this]() {return m_buffer.size() < SIZE; });
	m_buffer.push_back(t_input);
	locker.unlock();
	m_cond.notify_all();
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

StringFinder::FilePtr StringFinder::FileQueue::remove() {
	std::unique_lock<std::mutex> locker(m_mutex);
	m_cond.wait(locker, [this]() {return !m_buffer.empty(); });
	FilePtr last = m_buffer.back();
	m_buffer.pop_back();
	locker.unlock();
	m_cond.notify_all();
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	return last;
}


