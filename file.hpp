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

    File(const File&) = delete;
    File& operator=(const File&) = delete;
};

#endif //FILE_HPP