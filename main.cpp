#include <ctime>
#include <memory>
#include <stdexcept>

#include "console.hpp"
#include "filesystem.hpp"
#include "main.hpp"
#include "searcher.hpp"


using namespace std;

int main (int argc, char *argv[]) {
    string path, phrase;

    clock_t begin = clock();
    if (cmdArgsTesting(argc, (const char **)argv)) {
        path = argv[1];
        phrase = argv[2];

        try {
            unique_ptr<StringFinder::FileSystem> fs = make_unique<StringFinder::FileSystem>(path);
            unique_ptr<StringFinder::Searcher> searcher = make_unique<StringFinder::Searcher>(phrase);
            searcher->processSearching(fs->getFiles());
        } catch(const bad_alloc& e) {
            throw runtime_error(e.what());
        }
    } 
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    StringFinder::Console::printDebugInfo({"Elapsed time: ", std::to_string(elapsed_secs), "s"});
}

bool cmdArgsTesting(int argc, const char *argv[]) {
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
