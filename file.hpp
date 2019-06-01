#ifndef FILE_HPP
#define FILE_HPP

#include <cstring>
#include <iostream>
#include <fstream>
#include <memory>
#include <queue>


class File {
private:
    std::string m_filePath;
    std::string m_fileName;
    std::ifstream m_fileStream;
    short bufferIndex = 0;
    constexpr static short bufferLength = 1000;
    std::unique_ptr<char[]> readBuffer;

protected:
    void cacheBuffer(void);

public:
    explicit File(const std::string t_filePath);
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

typedef std::shared_ptr<File> FilePtr;
typedef std::queue<FilePtr> FileQueue;

#endif //FILE_HPP