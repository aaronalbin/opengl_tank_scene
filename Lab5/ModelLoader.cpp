#include "ModelLoader.h"

namespace openGLDriver {

	ModelLoader::ModelLoader() : m_numVertices(0), m_numFaces(0) {
	}

	ModelLoader::~ModelLoader() {
	}

	bool ModelLoader::load(const std::string& filename) {
		bool end_header = false;
		int vCount = 0;
		int fCount = 0;
		std::string line;
		std::ifstream fin(filename.c_str());

		while (getline(fin, line)) {
			std::vector<std::string> tokens = Util::split(line, ' ');

			if (tokens.size() == 0)		// skip blank line
				continue;
			else if (tokens.size() == 1) {
				if (tokens[0] == "end_header") {
					end_header = true;
				}
			}
			else {
				if (!end_header) {	// read header metadata
					if (tokens[0] == "element" && tokens[1] == "vertex") {
						m_numVertices = atof(tokens[2].c_str());
						m_vertices.resize(m_numVertices);
					}
					if (tokens[0] == "element" && tokens[1] == "face") {
						m_numFaces = atof(tokens[2].c_str());
						m_faces.resize(m_numFaces);
					}
					if (tokens[0] == "property" && (tokens[1] == "float32" || tokens[1] == "float")) {
						m_properties.push_back(tokens[2]);
					}
				}
				else {
					// big assumption here: properties.size != vertex_indices size (should be safe assuming triangles)
					if (tokens.size() == m_properties.size()) {
						if (tokens.size() == 6) {  // no texture
							m_vertices[vCount] = Vertex(atof(tokens[0].c_str()), atof(tokens[1].c_str()), atof(tokens[2].c_str()), 1.0, atof(tokens[3].c_str()), atof(tokens[4].c_str()), atof(tokens[5].c_str()));
						}
						else if (tokens.size() == 8) {  // has texture coord
							m_vertices[vCount] = Vertex(atof(tokens[0].c_str()), atof(tokens[1].c_str()), atof(tokens[2].c_str()), 1.0, atof(tokens[3].c_str()), atof(tokens[4].c_str()), atof(tokens[5].c_str()), atof(tokens[6].c_str()), atof(tokens[7].c_str()));
						}
						else if (tokens.size() == 14) {  // has tangent, bitangent vectors
							m_vertices[vCount] = Vertex(atof(tokens[0].c_str()), atof(tokens[1].c_str()), atof(tokens[2].c_str()), 1.0, atof(tokens[3].c_str()), atof(tokens[4].c_str()), atof(tokens[5].c_str()), atof(tokens[6].c_str()), atof(tokens[7].c_str()), atof(tokens[8].c_str()), atof(tokens[9].c_str()), atof(tokens[10].c_str()), atof(tokens[11].c_str()), atof(tokens[12].c_str()), atof(tokens[13].c_str()));
						}
						vCount++;
					}
					else {
						if (atoi(tokens[0].c_str()) == 3) {
							m_faces[fCount] = Face(atoi(tokens[1].c_str()), atoi(tokens[2].c_str()), atoi(tokens[3].c_str()));
							fCount++;
						}
						else if (atoi(tokens[0].c_str()) == 4) {
							m_faces[fCount] = Face(atoi(tokens[1].c_str()), atoi(tokens[2].c_str()), atoi(tokens[3].c_str()), atoi(tokens[4].c_str()));
							fCount++;
						}
					}
				}
			}
		} 
		
		fin.seekg(0);
		fin.close();
		//printModel();
		return true;
	}

	void ModelLoader::printModel() {
		std::cout << "Num vertices: " << m_numVertices << ", Num faces: " << m_numFaces << std::endl;
		for (size_t i = 0; i < m_vertices.size(); i++) {
			std::cout << m_vertices[i].getX() << ", " << m_vertices[i].getY() << ", " << m_vertices[i].getZ() << std::endl;
		}
		std::cout << std::endl;
		for (size_t i = 0; i < m_faces.size(); i++) {
			if (m_faces[i].getV4() != -1)
				std::cout << m_faces[i].getV1() << ", " << m_faces[i].getV2() << ", " << m_faces[i].getV3() << ", " << m_faces[i].getV4() << std::endl;
			else
				std::cout << m_faces[i].getV1() << ", " << m_faces[i].getV2() << ", " << m_faces[i].getV3() << std::endl;
		}
	}

	std::vector<Vertex> ModelLoader::getVertices() {
		return m_vertices;
	}

	std::vector<Face> ModelLoader::getFaces() {
		return m_faces;
	}

	void ModelLoader::flipNormals() {
		for (size_t i = 0; i < m_vertices.size(); i++) {
			m_vertices[i].setNX(-m_vertices[i].getNX());
			m_vertices[i].setNY(-m_vertices[i].getNY());
			m_vertices[i].setNZ(-m_vertices[i].getNZ());
		}
	}

	void ModelLoader::flipTexture() {
		for (size_t i = 0; i < m_vertices.size(); i++) {
			m_vertices[i].setT(-m_vertices[i].getT());
		}
	}

	void ModelLoader::clear() {
		m_properties.clear();
		m_faces.clear();
		m_vertices.clear();
		m_numFaces = 0;
		m_numVertices = 0;
	}
}
