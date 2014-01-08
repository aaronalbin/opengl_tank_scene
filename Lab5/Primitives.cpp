#include "Primitives.h"

namespace openGLDriver {

	Primitives::Primitives() : m_numVertices(0), m_numIndices(0) {
	}

	Primitives::~Primitives() {
	}

	std::vector<Vertex> Primitives::getVertexList() {
		return m_vertexList;
	}

	std::vector<GLuint> Primitives::getIndexList() {
		return m_indexList;
	}

	int Primitives::getNumVertices() {
		return m_numVertices;
	}

	int Primitives::getNumIndices() {
		return m_numIndices;
	}

	void Primitives::setVertexList(const std::vector<Vertex>& vertexList) {
		m_vertexList = vertexList;
		m_numVertices = vertexList.size();
	}
	
	void Primitives::setIndexList(const std::vector<GLuint>& indexList) {
		m_indexList = indexList;
		m_numIndices = indexList.size();
	}

}
