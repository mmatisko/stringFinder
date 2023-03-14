#include <string_finder/console.hpp>
#include <string_finder/searcher.hpp>

StringFinder::Searcher::Searcher(std::string t_phrase, std::shared_ptr<FileQueue>& t_files, std::atomic<bool>& complete_flag)
    : m_phrase(std::move(t_phrase))
    , m_files(t_files)
    , m_searching_complete(complete_flag) {}

StringFinder::Searcher::~Searcher()
{
    m_phrase.clear();
}

void StringFinder::Searcher::runProcessSearching() const
{
    while (m_files.get()->hasItems() || !m_searching_complete)
  {
		FilePtr file = m_files.get()->remove();
		if (file != nullptr)
        {
			scanFileForPhrase(file);
		}
        else
        {
            break;
        }
    }
}

void StringFinder::Searcher::scanFileForPhrase(const FilePtr& t_candidate) const
{
    std::deque<char> buffer;
    unsigned int counter = 0, control_deque_offset = 0;
    const auto phrase_length = static_cast<unsigned int>(m_phrase.length());

	t_candidate.get()->open();
    Console::printDebugInfo("Processing file: ", t_candidate->getFileName());

    do
    {
        std::string temp_phrase = (phrase_length > PART_SIZE) ? m_phrase.substr(0, PART_SIZE) : m_phrase;
        unsigned int next_string_part = 1;

		if (buffer.size() < phrase_length || (!buffer.empty() && buffer.back() != EOF))
        {  // load chars if we do not have enough characters in buffer
            loadToBuffer(t_candidate, buffer);
        }
		if (buffer.size() < phrase_length)
        {
            break;
        }  // if not have enough characters after loading, end

        for (;control_deque_offset <= 3; ++control_deque_offset)
        {   // check first three chars and then check 4th character only (left 3 for prefix print)
            while (comparePhrases(temp_phrase, buffer, control_deque_offset + PART_SIZE * (next_string_part - 1)))
            {
                if (iterateWholePhrase(phrase_length, next_string_part, temp_phrase))
                {
                    Console::printPhraseOccurence(t_candidate, buffer, counter, control_deque_offset, phrase_length);
                    break;
                }
                ++next_string_part;
            }
            ++counter;
        }
        buffer.pop_front();
        --control_deque_offset;
    } while (buffer.size() >= phrase_length || t_candidate->hasCharToRead());

	t_candidate.get()->close();
	Console::printDebugInfo("File ", t_candidate->getFileName(), " processed.");
}

void StringFinder::Searcher::loadToBuffer(const FilePtr& t_candidate, std::deque<char>& t_buffer)
{
	while(t_buffer.size() < BUFFER_SIZE)
  {
		// loading character from file buffer
        char current_char = t_candidate->getNextChar();
		// inserting character to processing deque (inserted character may vary using different search algorithm, like Shift-and / Shift-or algorithm).
        t_buffer.push_back(current_char);
        if (current_char == EOF)
        {
            break;
        }
    }
}

inline bool StringFinder::Searcher::iterateWholePhrase(const unsigned int& t_phrase_length, const unsigned int& t_next_string_part, std::string& t_temp_phrase) const
{
    if (t_phrase_length <= (t_next_string_part * PART_SIZE))
    { // found a phrase
        return true;
    }
	// check next part of searched string
	if (t_phrase_length > ((t_next_string_part + 1) * PART_SIZE))
    {  // next part has full size
        t_temp_phrase = m_phrase.substr(PART_SIZE * static_cast<size_t>(t_next_string_part), PART_SIZE);
    } else
    {  // next part is last with reduced size
        t_temp_phrase = m_phrase.substr(PART_SIZE * static_cast<size_t>(t_next_string_part), t_phrase_length - (PART_SIZE * t_next_string_part));
    }
    return false;
}

bool StringFinder::Searcher::comparePhrases(const std::string& t_phrase, const std::deque<char>& t_buffer, const unsigned int t_offset) {
    for (size_t i = 0; i < t_phrase.length(); ++i)
    {
        if (t_phrase.at(i) != t_buffer[t_offset + i])
        {
            return false;
        }
    }
    return true;
}
