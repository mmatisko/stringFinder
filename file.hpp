#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
#include <memory>


namespace StringFinder {
    class File {
    public:
        explicit File(const std::string& t_file_path);
        ~File();

        void open(); 
        char getNextChar();
        bool hasCharToRead() const;
        std::string& getFileName();

        // make class non-copyable
        File(const File&) = delete;
        File& operator=(const File&) = delete;
        // make class non-movable
        File(const File&& f) = delete;
        File& operator=(const File&& f) = delete;

	protected:
		void close();
		void cacheBuffer();

	private:
		std::string m_file_path;
		std::string m_file_name;
		std::ifstream m_file_stream;
		short m_buffer_index = 1000;
		constexpr static int BUFFER_LENGTH = 1000;
		std::unique_ptr<char[]> m_read_buffer;
    };

    typedef std::shared_ptr<File> FilePtr;
}

#endif //FILE_HPP