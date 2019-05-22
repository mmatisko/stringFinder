#include "main.hpp"
#include "searcher.hpp"

#include <cstring>
#include <dirent.h>
#include <errno.h>
#include <experimental/filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>

using namespace std;

int main (int argc, char *argv[]) {
    string path, phrase;
    vector<shared_ptr<File>> files;

    if (cmdArgsTesting(argc, (const char **)argv)) {
        path = argv[1];
        phrase = argv[2];

        processPath(files, path);
        searchForPhrase(files, phrase);
        cleanMemory(files);
    } 
}

bool cmdArgsTesting(int argc, const char *argv[]) {
    if (argc == 3) {
        if (strlen(argv[1]) > 1)
            if (strlen(argv[2]) > 2 && strlen(argv[2]) <= 128)
                return true;
            else 
                throw invalid_argument("Received third parameter with incorrect length!");
        else 
            throw length_error("Received second parameter with incorrect length!");
    } else
        throw length_error("Received wrong number of cli params: " \
            "should receive exactly 3 params, for more information see help!");
        
    return false;
}

void cleanMemory(vector<shared_ptr<File>>& t_files) {
    t_files.clear();
}

void processPath(vector<shared_ptr<File>>& t_files, string t_pathString) {
    const char* path = t_pathString.c_str();
    
    if (pathIsDir(path)) { 
        processDirectory(t_files, t_pathString);
    } else if (pathIsFile(path)) {
        processFile(t_files, t_pathString);
    } else {
        throw invalid_argument("Received invalid second parameter with invalid path!");
    }
}

void processDirectory(vector<shared_ptr<File>>& t_files, string t_dirPath) {
    if(t_dirPath.at(t_dirPath.length()-1) != '/') {
        t_dirPath += "/";
    }
    cout << "[DEBUG] Found directory: " << t_dirPath << endl;
    
    struct dirent *structure;  
    DIR* directory = opendir(t_dirPath.c_str());
    checkErrno("opening");

    const char* actualFilePath;
    while ((structure = readdir(directory)) != nullptr) {
        if (strncmp(structure->d_name, ".", 1) != 0 && strncmp(structure->d_name, "..", 2) != 0) {
            string tempString = t_dirPath;
            tempString += string(structure->d_name);
            actualFilePath = tempString.c_str(); 

            if (pathIsDir(actualFilePath)) {
                processDirectory(t_files, actualFilePath);
            } else if (pathIsFile(actualFilePath)) {
                processFile(t_files, actualFilePath);
            } else {
                cout << "[WARNING] Invalid file/directory found: " << tempString << ", program will continue..."<< endl;
            }
        }
    }
    checkErrno("reading");
        
    closedir(directory);
    checkErrno("closing");
}

void checkErrno(string action) {
    if (errno != 0)
        throw runtime_error("Error while " + action + " file directory!");

}

void processFile(vector<shared_ptr<File>>& t_files, const string t_filePath) {
    cout << "[DEBUG] Found file: " << t_filePath << endl;
    t_files.push_back(make_shared<File>(t_filePath));
}    

bool pathIsFile(const char* t_path) {
    return S_ISREG(getPathInfo(t_path).st_mode);
}

bool pathIsDir(const char* t_path) {
    return S_ISDIR(getPathInfo(t_path).st_mode);
}

struct stat getPathInfo(const char* t_path) {
    struct stat buf;
    stat(t_path, &buf);
    return buf;
}

void searchForPhrase(const vector<shared_ptr<File>>& t_files, const string t_searchedPhrase) {
    std::shared_ptr<Searcher> searcher = make_shared<Searcher>(t_searchedPhrase);
    searcher->processSearching(t_files);
}
