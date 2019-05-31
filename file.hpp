#ifndef FILE_HPP
#define FILE_HPP

#include <iostream>
#include <fstream>
#include <cstring>


class File {
private:
    std::string m_filePath;
    std::string m_fileName;
    std::ifstream m_fileStream;

public:
    File(const std::string t_filePath);
    ~File();

    void open(void); 
    char getNextChar(void);
    bool hasCharToRead(void);
    std::string& getFileName(void);

    // make class non-copyable
    File(const File&) = delete;
    File& operator=(const File&) = delete;
    // make class non-movable
    File(const File&& f) = delete;
    File& operator=(const File&& f) = delete;
};

#endif //FILE_HPP