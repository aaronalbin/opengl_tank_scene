#include "Model.h"

namespace openGLDriver {

	Model::Model() : m_numVertices(0), m_numIndices(0) {
		// set default material properties
		m_ambientColor = glm::vec3(0.1, 0.1, 0.3);
		m_diffuseColor = glm::vec3(0.3, 0.4, 0.9);
		m_specularColor = glm::vec3(0.8, 0.8, 0.8);
		m_shininess = 1.0;
	}

	Model::~Model() {
	}

	std::vector<Vertex> Model::getVertexList() {
		return m_vertexList;
	}

	std::vector<GLuint> Model::getIndexList() {
		return m_indexList;
	}

	int Model::getNumVertices() {
		return m_numVertices;
	}

	int Model::getNumIndices() {
		return m_numIndices;
	}

	void Model::setVertexList(const std::vector<Vertex>& vertexList) {
		m_vertexList = vertexList;
		m_numVertices = vertexList.size();
	}
	
	void Model::setIndexList(const std::vector<GLuint>& indexList) {
		m_indexList = indexList;
		m_numIndices = indexList.size();
	}

	glm::vec3 Model::getAmbientColor() {
		return m_ambientColor;
	}
	
	glm::vec3 Model::getDiffuseColor() {
		return m_diffuseColor;
	}
	
	glm::vec3 Model::getSpecularColor() {
		return m_specularColor;
	}
	
	float Model::getShininess() {
		return m_shininess;
	}

	void Model::setAmbientColor(const glm::vec3& ambientColor) {
		m_ambientColor = ambientColor;
	}
	
	void Model::setDiffuseColor(const glm::vec3& diffuseColor) {
		m_diffuseColor = diffuseColor;
	}
	
	void Model::setSpecularColor(const glm::vec3& specularColor) {
		m_specularColor = specularColor;
	}
	
	void Model::setShininess(const float& shininess) {
		m_shininess = shininess;
	}

	
	void Model::computeTangents() {

		for (size_t i = 0; i < m_indexList.size(); i += 3) {

			Vertex v1 = m_vertexList[m_indexList[i]];
			Vertex v2 = m_vertexList[m_indexList[i+1]];
			Vertex v3 = m_vertexList[m_indexList[i+2]];

			glm::vec3 pos1 = glm::vec3(v1.getX(), v1.getY(), v1.getZ());
			glm::vec3 pos2 = glm::vec3(v2.getX(), v2.getY(), v2.getZ());
			glm::vec3 pos3 = glm::vec3(v3.getX(), v3.getY(), v3.getZ());
			glm::vec2 tex1 = glm::vec2(v1.getS(), v1.getT());
			glm::vec2 tex2 = glm::vec2(v2.getS(), v2.getT());
			glm::vec2 tex3 = glm::vec2(v3.getS(), v3.getT());
			
			glm::vec3 normal = glm::normalize(glm::cross((pos2 - pos1), (pos3 - pos1)));

			glm::vec3 edge1 = glm::normalize(pos2 - pos1);
			glm::vec3 edge2 = glm::normalize(pos3 - pos1);

			glm::vec2 texEdge1 = glm::normalize(tex2 - tex1);
			glm::vec2 texEdge2 = glm::normalize(tex3 - tex1);

			float det = (texEdge1.x * texEdge2.y) - (texEdge1.y * texEdge2.x);

			glm::vec3 tangent;
			//glm::vec3 bitangentTest;
			if(fabsf(det) < 1e-6f) {
				tangent.x = 1.0;
				tangent.y = 0.0;
				tangent.z = 0.0;

				//bitangentTest.x = 0.0;
				//bitangentTest.y = 0.0;
				//bitangentTest.z = 1.0;

			}
			else {
				det = 1.0 / det;

				tangent.x = (texEdge2.y * edge1.x - texEdge1.y * edge2.x) * det;
				tangent.y = (texEdge2.y * edge1.y - texEdge1.y * edge2.y) * det;
				tangent.z = (texEdge2.y * edge1.z - texEdge1.y * edge2.z) * det;

				//bitangentTest.x = (-texEdge2.x * edge1.x + texEdge1.x * edge2.x) * det;
				//bitangentTest.y = (-texEdge2.x * edge1.y + texEdge1.x * edge2.y) * det;
				//bitangentTest.z = (-texEdge2.x * edge1.z + texEdge1.x * edge2.z) * det;

				glm::normalize(tangent);
				//glm::normalize(bitangentTest);
			}

			//glm::vec3 bitangent = glm::cross(normal, tangent);
			//float crossInv = (glm::dot(bitangent, bitangentTest) < 0.0) ? -1.0 : 1.0;
			//bitangent *= crossInv;

			m_vertexList[m_indexList[i]].setTanX(tangent.x);
			m_vertexList[m_indexList[i]].setTanY(tangent.y);
			m_vertexList[m_indexList[i]].setTanZ(tangent.z);
			m_vertexList[m_indexList[i+1]].setTanX(tangent.x);
			m_vertexList[m_indexList[i+1]].setTanY(tangent.y);
			m_vertexList[m_indexList[i+1]].setTanZ(tangent.z);
			m_vertexList[m_indexList[i+2]].setTanX(tangent.x);
			m_vertexList[m_indexList[i+2]].setTanY(tangent.y);
			m_vertexList[m_indexList[i+2]].setTanZ(tangent.z);

			//m_vertexList[m_indexList[i]].setBitanX(bitangent.x);
			//m_vertexList[m_indexList[i]].setBitanY(bitangent.y);
			//m_vertexList[m_indexList[i]].setBitanZ(bitangent.z);
			//m_vertexList[m_indexList[i+1]].setBitanX(bitangent.x);
			//m_vertexList[m_indexList[i+1]].setBitanY(bitangent.y);
			//m_vertexList[m_indexList[i+1]].setBitanZ(bitangent.z);
			//m_vertexList[m_indexList[i+2]].setBitanX(bitangent.x);
			//m_vertexList[m_indexList[i+2]].setBitanY(bitangent.y);
			//m_vertexList[m_indexList[i+2]].setBitanZ(bitangent.z);
			
			//m_vertexList[m_indexList[i]].setNX(normal.x);
			//m_vertexList[m_indexList[i]].setNY(normal.y);
			//m_vertexList[m_indexList[i]].setNZ(normal.z);
			//m_vertexList[m_indexList[i+1]].setNX(normal.x);
			//m_vertexList[m_indexList[i+1]].setNY(normal.y);
			//m_vertexList[m_indexList[i+1]].setNZ(normal.z);
			//m_vertexList[m_indexList[i+2]].setNX(normal.x);
			//m_vertexList[m_indexList[i+2]].setNY(normal.y);
			//m_vertexList[m_indexList[i+2]].setNZ(normal.z);
			
		}
	}

}
