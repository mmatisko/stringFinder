#ifndef MAIN_HPP
#define MAIN_HPP

#include <cstring>
#include <iostream>
#include <vector>

#include "file.hpp"
#include "searcher.hpp"

bool cmdArgsTesting(int argc, const char *argv[]);
void cleanMemory(std::vector<std::shared_ptr<File>>& files);

void processPath(std::vector<std::shared_ptr<File>>& files, std::string t_pathString);
void processDirectory(std::vector<std::shared_ptr<File>>& files, std::string t_dirPath);
void processFile(std::vector<std::shared_ptr<File>>& files, const std::string t_filePath);

void checkErrno(std::string action);
bool pathIsFile(const char* path);
bool pathIsDir(const char* path);
struct stat getPathInfo(const char* t_path);

void searchForPhrase(const std::vector<std::shared_ptr<File>>& files, const std::string t_searchedPhrase);


#endif //MAIN_HPP