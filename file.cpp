#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>

#include "file.hpp"


File::File(std::string filePath) {
    size_t position = filePath.length() - 1;
    while (filePath.at(position) != '/') {
        position -= 1;
        if(position == 0) break;
    }
    this->fileName = filePath.substr(position + 1, filePath.length() - position - 1);
    this->filePath = filePath;
    this->fileStream.open(filePath);
}

File::~File() {
    fileStream.close();
}

std::string& File::getFileName(void) {
    return fileName;
}

char File::getNextChar(void) {
    char value = EOF;
    if (fileStream.is_open() && !fileStream.eof()) {
        fileStream.get(value);
    }
    return value;
}

bool File::isEof(void) {
    return !fileStream.is_open() || fileStream.eof(); 
}
