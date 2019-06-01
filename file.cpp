#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>

#include "file.hpp"


StringFinder::File::File(const std::string t_file_path) {
    size_t position = t_file_path.length() - 1;
    while (t_file_path.at(position) != '/') {
        --position;
        if(position == 0) { break; }
    }
    m_file_name = t_file_path.substr(position + 1, t_file_path.length() - position - 1);
    m_file_path = t_file_path;
    m_read_buffer = std::make_unique<char[]>(BUFFER_LENGTH);
    try {
        open();
    } catch(const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
    }
}

StringFinder::File::~File() {
    try {
        m_file_stream.close();
    } catch(const std::ifstream::failure& e) {
        std::cout << "Exception while closing file " << m_file_path << " : " << e.what() << std::endl;
    }
    m_file_path.clear();
    m_file_name.clear();
}

void StringFinder::File::open() {
    try {
        m_file_stream.open(m_file_path);
    } catch(const std::ifstream::failure& e) {
        std::cout << "Exception while opening file " << m_file_path << " : " << e.what() << std::endl;
    }
}

std::string& StringFinder::File::getFileName(void) {
    return m_file_name;
}

bool StringFinder::File::hasCharToRead(void) const {
    return m_file_stream.good(); 
}

char StringFinder::File::getNextChar(void) {
    if (m_buffer_index == BUFFER_LENGTH) {
        cacheBuffer();
    }
    char nextChar = m_read_buffer[m_buffer_index];
    if (nextChar != EOF) {
        ++m_buffer_index;
    }
    return nextChar;
}

void StringFinder::File::cacheBuffer(void) {
    if (this->hasCharToRead()) {
        try {
            m_file_stream.read(m_read_buffer.get(), BUFFER_LENGTH);
            m_buffer_index = 0;
        } catch(const std::ifstream::failure& e) {
            std::cout << "Exception while reading file " << m_file_path << " : " << e.what() << std::endl;
        }
    }
}
