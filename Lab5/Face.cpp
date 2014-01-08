#include "Face.h"

namespace openGLDriver {

	Face::Face() {
	}

	Face::Face(const GLuint& v1, const GLuint& v2, const GLuint& v3) : m_v1(v1), m_v2(v2), m_v3(v3), m_v4(-1) {
	}

	Face::Face(const GLuint& v1, const GLuint& v2, const GLuint& v3, const GLuint& v4) : m_v1(v1), m_v2(v2), m_v3(v3), m_v4(v4) {
	}

	Face::~Face() {
	}

	GLuint Face::getV1() {
		return m_v1;
	}

	GLuint Face::getV2() {
		return m_v2;
	}

	GLuint Face::getV3() {
		return m_v3;
	}

	GLuint Face::getV4() {
		return m_v4;
	}
}
