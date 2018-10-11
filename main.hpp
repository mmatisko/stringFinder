#ifndef MAIN_HPP
#define MAIN_HPP

#include <cstring>
#include <iostream>
#include <vector>

#include "file.hpp"
#include "searcher.hpp"

void cleanMemory(std::vector<File*>& files);

void processPath(std::vector<File*>& files, std::string pathString);
void processDirectory(std::vector<File*>& files, std::string dirPath);
void processFile(std::vector<File*>& files, std::string filePath);

bool pathIsFile(const char* path);
bool pathIsDir(const char* path);

void searchForPhrase(std::vector<File*>& files, std::string searchedPhrase);


#endif //MAIN_HPP