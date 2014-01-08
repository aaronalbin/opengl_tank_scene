#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "Util.h"
#include "Vertex.h"
#include "Face.h"

namespace openGLDriver {

	class ModelLoader
	{
	private:
		std::vector<std::string> m_properties;
		std::vector<Vertex> m_vertices;
		std::vector<Face> m_faces;
		int m_numFaces;
		int m_numVertices;

	public:
		ModelLoader();
		~ModelLoader();
		bool load(const std::string& filename);
		void printModel();
		std::vector<Vertex> getVertices();
		std::vector<Face> getFaces();
		void flipNormals();
		void flipTexture();
		void clear();
	};

}
