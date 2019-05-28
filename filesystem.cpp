#include "filesystem.hpp"
#include <filesystem>
#include <stdexcept>


FileSystem::FileSystem(const std::string t_systemPath) {
    m_systemPath = fs::u8path(t_systemPath);
    if (pathIsValid()) {
        std::cout << "[DEBUG] Path correct!" << std::endl;
    } else {
        throw std::invalid_argument("Received path which does not exist or is unavailable!");
    }
}

FileSystem::~FileSystem() {}

bool FileSystem::pathIsValid(void) {
    return fs::exists(m_systemPath);
}

void FileSystem::traversePath(void) {
    processPath(m_systemPath);
}

void FileSystem::processDirectory(const fs::path& directoryPath) {
    std::cout << "[DEBUG] Processing folder: " << directoryPath.u8string() << std::endl;
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        processPath(entry.path());
    }
}

void FileSystem::processFile(const fs::path& filePath) {
    auto filename = filePath.filename();
    m_files.push_back(std::make_shared<File>(filePath.u8string()));
    std::cout << "[DEBUG] File found! Adding to processing path " << filename << std::endl;
}

void FileSystem::processPath(const fs::path& path) {
    if (fs::is_directory(path)) {
        processDirectory(path);
    } else if (fs::is_regular_file(path)) {
        processFile(path);
    }
}

FileVector& FileSystem::getFiles(void) {
    return m_files;
}