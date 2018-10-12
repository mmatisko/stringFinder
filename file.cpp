#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>

#include "file.hpp"

File::File(const std::string t_filePath) {
    size_t position = t_filePath.length() - 1;
    while (t_filePath.at(position--) != '/') {
        if(position == 0) { break; }
    }
    m_fileName = t_filePath.substr(position + 1, t_filePath.length() - position - 1);
    m_filePath = t_filePath;
    m_fileStream.open(m_filePath);
}

File::~File() {
    m_fileStream.close();
}

std::string& File::getFileName(void) {
    return m_fileName;
}

char File::getNextChar(void) {
    char value = EOF;
    if (m_fileStream.is_open() && !m_fileStream.eof()) {
        m_fileStream.get(value);
    }
    return value;
}

bool File::isEof(void) {
    return !m_fileStream.is_open() || m_fileStream.eof(); 
}
