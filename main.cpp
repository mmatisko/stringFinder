#include "console.hpp"
#include "filesystem.hpp"
#include "main.hpp"
#include "searcher.hpp"
#include <atomic>


using namespace std;

int main (const int argc, char *argv[]) {
	const clock_t begin = clock();
    if (cmdArgsTesting(argc, const_cast<const char **>(argv))) {
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

		/*
        try {
            unique_ptr<StringFinder::FileSystem> fs = make_unique<StringFinder::FileSystem>(path);
            const unique_ptr<StringFinder::Searcher> searcher = make_unique<StringFinder::Searcher>(phrase);
            searcher->runProcessSearching(fs->getFiles());
        } catch(const bad_alloc& e) {
            throw runtime_error(e.what());
        }*/
    }
    const clock_t end = clock();
    const double elapsed_secs = (static_cast<double>(end) - begin) / CLOCKS_PER_SEC;
    StringFinder::Console::printDebugInfo("Elapsed time: ", std::to_string(elapsed_secs), "s");

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	auto a = getchar();
#endif
}

bool cmdArgsTesting(const int argc, const char *argv[]) {
    if (argc == 3) {
        if (strlen(argv[1]) > 2 && strlen(argv[1]) <= 128) {
            if (strlen(argv[2]) > 2 && strlen(argv[2]) <= 1000) {
                return true;
            } else { 
                throw invalid_argument("Received third cmd parameter (path) with incorrect length!");
            }
        } else {
            throw length_error("Received cmd second parameter (phrase) with incorrect length!");
        }
    } else {
        throw length_error("Received wrong number of cmd params: " \
            "should receive exactly 3 params, for more information see help!");
    }
    return false;
}
