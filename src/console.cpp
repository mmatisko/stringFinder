#include <string_finder/console.hpp>

void StringFinder::Console::printPhraseOccurence(const FilePtr& t_candidate, const std::deque<char>& t_buffer, const unsigned int t_offset,
    const unsigned int t_control_deque_offset, const unsigned int t_phrase_length)
{
    std::string occurence = t_candidate->getFileName() + "(" + std::to_string(t_offset) + "): ";
	// compute how many chars after searched phrase we've actually got
    const unsigned int suffix_limit = (static_cast<unsigned int>(t_buffer.size()) > (t_control_deque_offset + t_phrase_length + 3))
        ? static_cast<unsigned long long>(t_control_deque_offset) + t_phrase_length + 3
        : static_cast<unsigned int>(t_buffer.size());

    if (t_control_deque_offset > 0)
    {  // check if we've got some chars for prefix and format prefix to string
        occurence += formatPrefixSuffix(t_buffer, 0, t_control_deque_offset);
    } // now format suffix, add to string and print

    occurence += "..." + formatPrefixSuffix(t_buffer, t_phrase_length + t_control_deque_offset, suffix_limit);
	doConcurrentPrint(occurence);
}

std::string StringFinder::Console::formatPrefixSuffix(const std::deque<char>& t_buffer, const unsigned int t_from, const unsigned int t_to)
{
    std::string result;
    for (unsigned int i = t_from; i < t_to; ++i) {
        switch (t_buffer[i]){
            case '\n': {
                result += "\\n";
                break;
            }
            case '\t': {
                result += "\\t";
                break;
            }
            default: {
                result += t_buffer[i];
            }
        }
    }
    return result;
}

char StringFinder::Console::getSystemSlashDelimiter()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__) // Windows version
	return '\\';
#else  // Linux version
	return '/';
#endif
}
