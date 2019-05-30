#include <filesystem>
#include <stdexcept>

#include "console.hpp"
#include "filesystem.hpp"


FileSystem::FileSystem(const std::string t_systemPath) {
    m_systemPath = fs::u8path(t_systemPath);
    if (pathIsValid()) {
        Console::printDebugInfo({"Path correct!"});
        traversePath();
    } else {
        throw std::invalid_argument("Received path which does not exist or is unavailable!");
    }
}

FileSystem::~FileSystem() {}

bool FileSystem::pathIsValid(void) {
    return fs::exists(m_systemPath);
}

void FileSystem::traversePath(void) {
    m_traverseComplete = false;
    processPath(m_systemPath);
    m_traverseComplete = true;
}

void FileSystem::processDirectory(const fs::path& directoryPath) {
    Console::printDebugInfo({"Processing folder: ", directoryPath.u8string()});
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        processPath(entry.path());
    }
}

void FileSystem::processFile(const fs::path& filePath) {
    auto filename = filePath.filename();
    try{
        auto file = std::make_shared<File>(filePath.u8string());
        m_files.push(file);
    } catch(const std::bad_alloc& e) {
        throw std::runtime_error(e.what());
    }
    
    Console::printDebugInfo({"File found! Adding to processing file: ", filePath});
}

void FileSystem::processPath(const fs::path& path) {
    if (fs::is_directory(path)) {
        processDirectory(path);
    } else if (fs::is_regular_file(path)) {
        processFile(path);
    }
}

bool FileSystem::traversalComplete(void) {
    return m_traverseComplete;
}

FileQueue& FileSystem::getFiles(void) {
    return m_files;
}
