#include "Logger.h"

namespace openGLDriver {

	Logger::Logger() {
	}

	Logger::Logger(const std::string &filename) {
		init(filename);
	}

	Logger::~Logger() {
		m_stream.close();
	}

	void Logger::init(const std::string &filename) {
		m_stream.open(filename.c_str(), std::ios::out);
	}

	void Logger::write(const std::string &line) {
		m_stream << line << std::endl;
	}

	void Logger::close() {
		m_stream.close();
	}

}
