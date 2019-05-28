#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include "file.hpp"
#include <cstring>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>

namespace fs = std::filesystem;

typedef std::vector<std::shared_ptr<File>> FileVector;

class FileSystem {
private:
    std::filesystem::path m_systemPath;
    FileVector m_files;

public:
    FileSystem(const std::string t_systemPath);
    ~FileSystem();

    bool pathIsValid(void);
    FileVector& getFiles(void);
    
    void traversePath(void);
    void processDirectory(const fs::path& directoryPath);
    void processFile(const fs::path& filePath);
    void processPath(const fs::path& path);

    FileSystem(const File&) = delete;
    FileSystem& operator=(const File&) = delete;
};

#endif //FILESYSTEM_HPP