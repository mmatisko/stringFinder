#include "main.hpp"
#include "searcher.hpp"

#include <cstring>
#include <dirent.h>
#include <iostream>
#include <memory>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>

using namespace std;

int main (int argc, char *argv[]) {
    string path, phrase;
    vector<shared_ptr<File>> files;

    if (argc == 3){
        path = argv[1];
        phrase = argv[2]; // TO DO: add verification of params

        processPath(files, path);
        searchForPhrase(files, phrase);
        cleanMemory(files);
    } else {
        cout << "Wrong number of cli params: " << argc << 
            ", you should provide exactly 2 params: path of files and searched phrase!" << endl;
    }
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
        cout << "Incorrect file/directory path!" << endl;
    }
}

void processDirectory(vector<shared_ptr<File>>& t_files, string t_dirPath) {
    if(t_dirPath.at(t_dirPath.length()-1) != '/') {
        t_dirPath += "/";
    }
    cout << "Found directory: " << t_dirPath << endl;
    
    struct dirent* structure;  
    DIR* directory = opendir(t_dirPath.c_str());
    while ((structure = readdir(directory)) != nullptr) {
        if (strncmp(structure->d_name, ".", 1) != 0 && strncmp(structure->d_name, "..", 2) != 0) {
            string tempString = t_dirPath;
            tempString += string(structure->d_name);
            const char* actualFilePath = tempString.c_str(); 

            if (pathIsDir(actualFilePath)) {
                processDirectory(t_files, actualFilePath);
            } else if (pathIsFile(actualFilePath)) {
                processFile(t_files, actualFilePath);
            } else {
                cout << "Not valid file/directory: " << tempString << endl;
            }
        }
    }
}

void processFile(vector<shared_ptr<File>>& t_files, const string t_filePath) {
    cout << "Found file: " << t_filePath << endl;
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
