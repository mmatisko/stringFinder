#include <string_finder/filequeue.hpp>

StringFinder::FileQueue::~FileQueue()
{
	if (!m_buffer.empty())
  {
		m_buffer.clear();
	}
}

void StringFinder::FileQueue::add(const FilePtr& t_input)
{  // add filePtr until buffer is full, then wait
	std::unique_lock<std::mutex> locker(m_mutex);
	m_cond.wait(locker, [this]() {return m_buffer.size() < SIZE; });
	m_buffer.push_back(t_input);
	locker.unlock();
	m_cond.notify_one();
	std::this_thread::sleep_for(std::chrono::milliseconds(5));
}

StringFinder::FilePtr StringFinder::FileQueue::remove()
{  // try get filePtr, if there's not for 20ms timeout, return nullptr
	std::unique_lock<std::mutex> locker(m_mutex);
	m_cond.wait_for(locker, std::chrono::milliseconds(20));
	if (m_buffer.empty())
    {
		return nullptr;
	}
	FilePtr last = m_buffer.back();
	m_buffer.pop_back();
	locker.unlock();
	m_cond.notify_all();
	return last;
}

bool StringFinder::FileQueue::hasItems()
{  // thread-safe check if buffer has items or is empty
	std::unique_lock<std::mutex> locker(m_mutex);
	const bool hasItems = !m_buffer.empty();
	locker.unlock();
	return hasItems;
}
