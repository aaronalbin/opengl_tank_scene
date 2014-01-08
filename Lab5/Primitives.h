#pragma once

#define _USE_MATH_DEFINES	// to use M_PI
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <GL/glut.h>
#include "Vertex.h"
#include "Util.h"

namespace openGLDriver {

	class Primitives
	{
	protected:
		int m_numVertices, m_numIndices;
		std::vector<Vertex> m_vertexList;
		std::vector<GLuint> m_indexList;

	public:
		Primitives();
		~Primitives();
		std::vector<Vertex> getVertexList();
		std::vector<GLuint> getIndexList();
		int getNumVertices();
		int getNumIndices();
		void setVertexList(const std::vector<Vertex>& vertexList);
		void setIndexList(const std::vector<GLuint>& indexList);
	};

}
