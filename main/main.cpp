#include "main.hpp"

#include <string_finder/console.hpp>
#include <string_finder/filesystem.hpp>
#include <string_finder/searcher.hpp>

#include <atomic>

using namespace std;

int main (const int argc, char *argv[])
{
	const clock_t begin = clock();

	//check cmd args and process them
	cmdArgsTesting(argc, const_cast<const char**>(argv));
    const string path = argv[1];
    const string phrase = argv[2];

	// create filesystem object for path traversing and searcher object for searching required phrase
	atomic<bool> complete_flag = false;
	std::shared_ptr<StringFinder::FileQueue> buffer = make_shared<StringFinder::FileQueue>();
	StringFinder::FileSystem fs(path, buffer, complete_flag);
	StringFinder::Searcher searcher_one(phrase, buffer, complete_flag);
	StringFinder::Searcher searcher_two(phrase, buffer, complete_flag);

	// start threads
	std::thread filesystem_thread(&StringFinder::FileSystem::runTraversingPath, &fs);
	std::thread searcher_thread_one(&StringFinder::Searcher::runProcessSearching, &searcher_one);
	std::thread searcher_thread_two(&StringFinder::Searcher::runProcessSearching, &searcher_two);

	// wait for thread to be done
	filesystem_thread.join();
	searcher_thread_one.join();
	searcher_thread_two.join();

	// print time if debug logging in console class is enabled
    const clock_t end = clock();
    const double elapsed_secs = (static_cast<double>(end) - begin) / CLOCKS_PER_SEC;
	StringFinder::Console::printDebugInfo("Elapsed time: ", elapsed_secs, "s");

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	std::ignore = getchar();
#endif
}

void cmdArgsTesting(const int argc, const char *argv[])
{
	if (argc != 3)
    {
		throw length_error("Received wrong number of cmd params: " \
			"should receive exactly 3 params: program name, path for searching and searched phrase!");
	}
	if (strlen(argv[1]) < 3 || strlen(argv[1]) > 128)
    {
		throw length_error("Received cmd second parameter (phrase) with incorrect length, should be in range <3, 128>!");
	}
	if (strlen(argv[2]) < 3 || strlen(argv[2]) > 1000)
    {
		throw invalid_argument("Received third cmd parameter (path) with incorrect length, should be in range <3, 1000>!");
	}
}
