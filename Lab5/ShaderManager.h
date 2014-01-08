#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#ifdef WIN32 /*[*/
#include <io.h>
#endif /*]*/
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Vertex.h"
#include "Util.h"

namespace openGLDriver {

	typedef enum {
		EVertexShader,
		EFragmentShader,
	} EShaderType;

	class ShaderManager
	{
	private:
		GLchar *m_vertexShaderSource;
		GLchar *m_fragmentShaderSource;
		GLuint m_vertexShaderObject;
		GLuint m_fragmentShaderObject;
		GLuint m_programObject;

	public:
		ShaderManager();
		~ShaderManager();
		GLuint setup(char *filename);
		void checkGraphics();
		int shaderSize(const std::string& fileName, EShaderType shaderType);
		int readShader(char *fileName, EShaderType shaderType, char *shaderText, int size);
		int readShaderSource(char *fileName, GLchar **vertexShader, GLchar **fragmentShader);
		GLint getUniLoc(GLuint program, const GLchar *name);
		GLuint getProgramObject();
	};

}
