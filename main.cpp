#include "filesystem.hpp"
#include "main.hpp"
#include "searcher.hpp"

#include <cstring>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>

using namespace std;

int main (int argc, char *argv[]) {
    string path, phrase;

    if (cmdArgsTesting(argc, (const char **)argv)) {
        path = argv[1];
        phrase = argv[2];

        try {
            unique_ptr<FileSystem> fs = make_unique<FileSystem>(path);
            unique_ptr<Searcher> searcher = make_unique<Searcher>(phrase);
            searcher->processSearching(fs->getFiles());
        } catch(const bad_alloc& e) {
            cout << "Allocation of objects failed: " << e.what() << '\n';
        }
    } 
}

bool cmdArgsTesting(int argc, const char *argv[]) {
    if (argc == 3) {
        if (strlen(argv[1]) > 1)
            if (strlen(argv[2]) > 2 && strlen(argv[2]) <= 128)
                return true;
            else 
                throw invalid_argument("Received third cmd parameter with incorrect length!");
        else 
            throw length_error("Received cmd second parameter with incorrect length!");
    } else
        throw length_error("Received wrong number of cmd params: " \
            "should receive exactly 3 params, for more information see help!");
        
    return false;
}
