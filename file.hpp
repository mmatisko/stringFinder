#ifndef FILE_HPP
#define FILE_HPP

#include <iostream>
#include <fstream>
#include <cstring>

class File {
private:
    std::string filePath;
    std::string fileName;
    std::ifstream fileStream;

public:
    File(std::string filePath);
    ~File();

    char getNextChar(void);
    bool isEof(void);
    std::string& getFileName(void);

    File(const File&) = delete;
    File& operator=(const File&) = delete;
};

#endif //FILE_HPP