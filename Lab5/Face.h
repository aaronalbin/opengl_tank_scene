#pragma once

#include <GL/glut.h>

namespace openGLDriver {

	class Face
	{
	private:
		GLuint m_v1, m_v2, m_v3, m_v4;

	public:
		Face();
		Face(const GLuint& v1, const GLuint& v2, const GLuint& v3);
		Face(const GLuint& v1, const GLuint& v2, const GLuint& v3, const GLuint& v4);
		~Face();
		GLuint getV1();
		GLuint getV2();
		GLuint getV3();
		GLuint getV4();
	};

}
