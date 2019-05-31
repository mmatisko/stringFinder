#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <cstring>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>

#include "file.hpp"


namespace fs = std::filesystem;

typedef std::shared_ptr<File> FilePtr;
typedef std::queue<FilePtr> FileQueue;

class FileSystem {
private:
    std::filesystem::path m_systemPath;
    FileQueue m_files;
    bool m_traverseComplete;

public:
    FileSystem(const std::string t_systemPath);
    ~FileSystem();

    bool pathIsValid(void);
    FileQueue& getFiles(void);
    
    void traversePath(void);
    void processDirectory(const fs::path& directoryPath);
    void processFile(const fs::path& filePath);
    void processPath(const fs::path& path);
    bool traversalComplete(void);

    // make class non-copyable
    FileSystem(const FileSystem& f) = delete;
    FileSystem& operator=(const FileSystem& f) = delete;
    // make class non-movable
    FileSystem(const FileSystem&& f) = delete;
    FileSystem& operator=(const FileSystem&& f) = delete;
};

#endif //FILESYSTEM_HPP