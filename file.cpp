#include "console.hpp"
#include "file.hpp"


StringFinder::File::File(const std::string& t_file_path) {
	// looking for position of last path delimiter
    size_t position = t_file_path.length() - 1;
    while (t_file_path.at(position) != Console::getSystemSlashDelimiter()) {  
        --position;
        if(position == 0) { break; }
    } // extracting filename from whole path by last delimiter position
    m_file_name = t_file_path.substr(position + 1, t_file_path.length() - position - 1);
    m_file_path = t_file_path;
    m_read_buffer = std::make_unique<char[]>(BUFFER_LENGTH);
}

StringFinder::File::~File() {
    m_file_path.clear();
    m_file_name.clear();
	m_read_buffer.reset();
}

void StringFinder::File::close() {
	try {
		if (m_file_stream.is_open()) {
			m_file_stream.close();
		}
	} catch (const std::ifstream::failure& e) {
		Console::printNonCrashException({"Exception while closing file ", m_file_path, " : ", e.what()});
	}
}

void StringFinder::File::open() {
    try {
        m_file_stream.open(m_file_path);
    } catch(const std::ifstream::failure& e) {
        Console::printNonCrashException({"Exception while opening file ", m_file_path, " : ", e.what()});
    }
}

std::string& StringFinder::File::getFileName() {
    return m_file_name;
}

bool StringFinder::File::hasCharToRead() const {
	return m_file_stream.good(); // last read did not return EOF or failed
}

char StringFinder::File::getNextChar() {
    if (m_buffer_index == BUFFER_LENGTH) {  // if index is length of buffer, read next chars
        cacheBuffer();
    }
    char nextChar = m_read_buffer[m_buffer_index];  // read next char, if it's null char, we've got EOF
	if (nextChar != '\0') {
		++m_buffer_index;
	} else {
		nextChar = EOF;
    }
    return nextChar;
}

void StringFinder::File::cacheBuffer() {
    if (this->hasCharToRead()) {
        try {
            m_file_stream.read(m_read_buffer.get(), BUFFER_LENGTH);
            m_buffer_index = 0;
        } catch(const std::ifstream::failure& e) {
            Console::printNonCrashException({"Exception while reading file ", m_file_path, " : ", e.what()});
        }
    }
}
