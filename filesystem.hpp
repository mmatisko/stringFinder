#ifndef FILESYSTEM_HPP
    #define FILESYSTEM_HPP

    #include <filesystem>

    #include "filequeue.hpp"


    namespace StringFinder {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	namespace fs = std::experimental::filesystem::v1;
#else
	namespace fs = std::filesystem;
#endif
        

        class FileSystem {
		public:
			explicit FileSystem(const std::string& t_system_path, std::shared_ptr<FileQueue>& t_files);
			~FileSystem();

			bool pathIsValid() const;
			std::shared_ptr<FileQueue>& getFiles();

			void traversePath();
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
            fs::path m_system_path;
			std::shared_ptr<FileQueue> m_files;
            bool m_traverse_complete;    
        };
    }

#endif //FILESYSTEM_HPP