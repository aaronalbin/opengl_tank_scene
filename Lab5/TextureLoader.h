#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <GL/glut.h>
#include "Util.h"

namespace openGLDriver {

	//struct Pixel {
		//unsigned int r, g, b;
	//};

	class TextureLoader
	{

	private:
		int m_width, m_height;
		int m_maxVal;
		std::vector<GLubyte> m_pixels;

	public:
		TextureLoader();
		~TextureLoader();
		int readInteger(std::istream& fin);
		bool readHeader(std::istream& fin);
		bool load(const std::string& filename);
		int getWidth();
		int getHeight();
		int getMaxVal();
		std::vector<GLubyte> getPixels();
		void printTexture();
		void clear();
	};

}
