#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <filesystem>
#include <atomic>

#include "filequeue.hpp"

namespace StringFinder
{
	namespace fs = std::filesystem;

    class FileSystem
    {
	public:
		FileSystem(const std::string& t_system_path, std::shared_ptr<FileQueue>& t_files, std::atomic<bool>& complete_flag);
		~FileSystem();

		bool pathIsValid() const;
		std::shared_ptr<FileQueue>& getFiles();

		void runTraversingPath();
		void processDirectory(const fs::path& t_directory_path);
		void processFile(const fs::path& t_file_path) const;
		void processPath(const fs::path& t_path);
		bool traversalComplete() const;

		// make class non-copyable
		FileSystem(const FileSystem& f) = delete;
		FileSystem& operator=(const FileSystem& f) = delete;
		// make class non-movable
		FileSystem(const FileSystem&& f) = delete;
		FileSystem& operator=(const FileSystem&& f) = delete;

    private:
		// own variables
		fs::path m_system_path;
		// references / pointer to shared variables
		std::atomic<bool>& m_traverse_complete;
		std::shared_ptr<FileQueue> m_files;
    };
}

#endif //FILESYSTEM_HPP