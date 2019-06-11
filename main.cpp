#include "console.hpp"
#include "filesystem.hpp"
#include "main.hpp"
#include "searcher.hpp"
#include <atomic>


using namespace std;

int main (const int argc, char *argv[]) {
	const clock_t begin = clock();
    
	cmdArgsTesting(argc, const_cast<const char**>(argv));
    const string path = argv[1];
    const string phrase = argv[2];

	atomic<bool> complete_flag = false;
	std::shared_ptr<StringFinder::FileQueue> buffer = make_shared<StringFinder::FileQueue>();
	StringFinder::FileSystem fs(path, buffer, complete_flag);
	StringFinder::Searcher searcher(phrase, buffer, complete_flag);

	std::thread filesystem_thread(&StringFinder::FileSystem::runTraversingPath, &fs);
	std::thread searcher_thread(&StringFinder::Searcher::runProcessSearching, &searcher);

	filesystem_thread.join();
	searcher_thread.join();
    
    const clock_t end = clock();
    const double elapsed_secs = (static_cast<double>(end) - begin) / CLOCKS_PER_SEC;
	StringFinder::Console::printDebugInfo("Elapsed time: ", elapsed_secs, "s");

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	auto a = getchar();
#endif
}

void cmdArgsTesting(const int argc, const char *argv[]) {
	if (argc != 3) {
		throw length_error("Received wrong number of cmd params: " \
			"should receive exactly 3 params, for more information see help!");
	}
	if (strlen(argv[1]) < 3 || strlen(argv[1]) > 128) {
		throw length_error("Received cmd second parameter (phrase) with incorrect length!");
	}
	if (strlen(argv[2]) < 3 || strlen(argv[2]) > 1000) {
		throw invalid_argument("Received third cmd parameter (path) with incorrect length!");
	}
}
