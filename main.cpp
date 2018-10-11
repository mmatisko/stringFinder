#include "main.hpp"
#include "searcher.hpp"

#include <cstring>
#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>

using namespace std;

int main (int argc, char *argv[]) {
    string path, phrase;
    vector<File*> files;

    if (argc == 3){
        path = argv[1];
        phrase = argv[2];

        processPath(files, path);
        searchForPhrase(files, phrase);

        cleanMemory(files);
    } else {
        cout << "Wrong number of cli params: " << argc << endl;
    }
}

void cleanMemory(vector<File*>& files) {
    for (unsigned long i = 0; i < files.size(); ++i) {
        delete files[i];
    }
    files.clear();
}

void processPath(vector<File*>& files, string pathString) {
    const char* path = pathString.c_str();
    
    if (pathIsDir(path)) { 
        processDirectory(files, pathString);
    } else if (pathIsFile(path)) {
        processFile(files, pathString);
    } else {
        cout << "Incorrect file/directory path!" << endl;
    }
}

void processDirectory(vector<File*>& files, string dirPath) {
    if(dirPath.at(dirPath.length()-1) != '/') {
        dirPath += "/";
    }
    cout << "Found directory: " << dirPath << endl;
    
    struct dirent* structure;  
    DIR* directory = opendir(dirPath.c_str());
    while ((structure = readdir(directory)) != NULL) {
        if (strncmp(structure->d_name, ".", 1) != 0 && strncmp(structure->d_name, "..", 2) != 0) {
            string tempString = dirPath;
            tempString += string(structure->d_name);
            const char* actualFilePath = tempString.c_str(); 

            if (pathIsDir(actualFilePath)) {
                processDirectory(files, actualFilePath);
            } else if (pathIsFile(actualFilePath)) {
                processFile(files, actualFilePath);
            } else {
                cout << "Not valid file/directory: " << tempString << endl;
            }
        }
    }
}

void processFile(vector<File*>& files, string filePath) {
    cout << "Found file: " << filePath << endl;
    files.push_back(new File(filePath));
}    

bool pathIsFile(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}

bool pathIsDir(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

void searchForPhrase(vector<File*>& files, string searchedPhrase) {
    Searcher* searcher = new Searcher(searchedPhrase);
    searcher->processSearching(files);
}
