#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <cstring>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <stdexcept>

#include "file.hpp"


namespace fs = std::filesystem;

class FileSystem {
private:
    std::filesystem::path m_system_path;
    FileQueue m_files;
    bool m_traverse_complete;

public:
    explicit FileSystem(const std::string t_system_path);
    ~FileSystem();

    bool pathIsValid(void);
    FileQueue& getFiles(void);
    
    void traversePath(void);
    void processDirectory(const fs::path& t_directory_path);
    void processFile(const fs::path& t_file_path);
    void processPath(const fs::path& t_path);
    bool traversalComplete(void);

    // make class non-copyable
    FileSystem(const FileSystem& f) = delete;
    FileSystem& operator=(const FileSystem& f) = delete;
    // make class non-movable
    FileSystem(const FileSystem&& f) = delete;
    FileSystem& operator=(const FileSystem&& f) = delete;
};

#endif //FILESYSTEM_HPP