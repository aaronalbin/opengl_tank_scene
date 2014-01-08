#pragma once

#include <string>
#include <fstream>

namespace openGLDriver {

	class Logger
	{
	private:
		std::ofstream m_stream;

	public:
		Logger();
		Logger(const std::string &filename);
		~Logger();
		void init(const std::string &filename);
		void write(const std::string& line);
		void close();
	};

}