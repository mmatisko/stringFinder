#ifndef MAIN_HPP
#define MAIN_HPP

#include <cstring>
#include <iostream>
#include <vector>

//#include "file.hpp"
//#include "searcher.hpp"


bool cmdArgsTesting(int argc, const char *argv[]);
FileQueue& processPath(std::string path); 
void searchForPhrase(FileQueue& files, const std::string t_searchedPhrase);

#endif //MAIN_HPP