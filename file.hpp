#ifndef FILE_HPP
#define FILE_HPP

#include <cstring>
#include <iostream>
#include <fstream>
#include <memory>
#include <queue>


class File {
private:
    std::string m_file_path;
    std::string m_file_name;
    std::ifstream m_file_stream;
    short m_buffer_index = 0;
    constexpr static short BUFFER_LENGTH = 1000;
    std::unique_ptr<char[]> m_read_buffer;

protected:
    void cacheBuffer(void);

public:
    explicit File(const std::string t_file_path);
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