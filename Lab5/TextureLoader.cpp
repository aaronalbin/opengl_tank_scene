#include "TextureLoader.h"

namespace openGLDriver {

	TextureLoader::TextureLoader() : m_width(0), m_height(0), m_maxVal(0) {
	}

	TextureLoader::~TextureLoader() {
	}

	int TextureLoader::readInteger(std::istream& fin) {
		unsigned char ch;
		int got = 0, done = 0, accum = 0, inComment = 0;
		while (!done) {
			ch = fin.get();

			if (inComment) {
				if (ch=='\n')
					inComment=0;
				continue;
			}

			if (isdigit(ch)) {
				accum = accum*10 + ch-'0';
				got = 1;
			}
			else if (ch=='#')
				inComment = 1;
			else if (!ch || !strchr(" \t\r\n", ch)) {
				std::cout << "PPM readInteger: invalid character" << std::endl;
				exit(1);
			}
			else if (got)
				done = 1;
		}
		return accum;
	}

	bool TextureLoader::readHeader(std::istream& fin) {
		if ((m_width = readInteger(fin)) < 0) {
			std::cout << "PPM: invalid width" << std::endl;
			return false;
		}
		if ((m_height = readInteger(fin)) < 0) {
			std::cout << "PPM: invalid height" << std::endl;
			return false;
		}
		if ((m_maxVal = readInteger(fin)) != 255) {
			std::cout << "PPM: max color not 255" << std::endl;
			return false;
		}
	}
	
	bool TextureLoader::load(const std::string& filename) {
		std::cout << "Loading Texture begin." << std::endl;

		std::string line;
		std::istringstream iss;
		std::ifstream fin(filename.c_str());

		if (!fin) {
			std::cout << "Cannot read texture file " << filename << "." << std::endl;
			return false;
		}

		getline(fin, line);
		if (line != "P3") {
			std::cout << "PPM not in expected P3 color ascii format. " << std::endl;
			return false;
		}

		getline(fin, line);
		iss.str(line);
		iss >> m_width;
		iss >> m_height;
		iss.clear();

		getline(fin, line);
		iss.str(line);
		iss >> m_maxVal;
		iss.clear();

		m_pixels.resize(m_width * m_height * 3);
		int count = 0;

		while (getline(fin, line)) {
			iss.str(line);
			int n;
			while (iss >> n) {
				if (n > 255) {
					std::cout << "PPM contains pixel data > 255." << std::endl;
					return false;
				}
				GLubyte b = static_cast<GLubyte>(n);
				m_pixels[count] = b;
				count++;
			}
			iss.clear();
		} 
		std::cout << "Loading Texture end." << std::endl;
		return true;
	}

	int TextureLoader::getWidth() {
		return m_width;
	}
	
	int TextureLoader::getHeight() {
		return m_height;
	}
	
	int TextureLoader::getMaxVal() {
		return m_maxVal;
	}
	
	std::vector<GLubyte> TextureLoader::getPixels() {
		return m_pixels;
	}

	void TextureLoader::printTexture() {
		std::cout << "Texture info:" << std::endl;
		std::cout << "width: " << m_width << ", height: " << m_height << ", maxVal: " << m_maxVal << std::endl;
		std::cout << "pixels size: " << m_pixels.size() << std::endl;
	}

	void TextureLoader::clear() {
		m_width = 0;
		m_height = 0;
		m_maxVal = 0;
		m_pixels.clear();
	}
}
