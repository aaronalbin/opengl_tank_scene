#pragma once

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <GL/glut.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "Vertex.h"
#include "Util.h"

namespace openGLDriver {

	class Model
	{
	private:
		int m_numVertices, m_numIndices;
		std::vector<Vertex> m_vertexList;
		std::vector<GLuint> m_indexList;
		float m_shininess;
		glm::vec3 m_ambientColor;
		glm::vec3 m_diffuseColor;
		glm::vec3 m_specularColor;

	public:
		Model();
		~Model();
		std::vector<Vertex> getVertexList();
		std::vector<GLuint> getIndexList();
		int getNumVertices();
		int getNumIndices();
		void setVertexList(const std::vector<Vertex>& vertexList);
		void setIndexList(const std::vector<GLuint>& indexList);
		glm::vec3 getAmbientColor();
		glm::vec3 getDiffuseColor();
		glm::vec3 getSpecularColor();
		float getShininess();
		void setAmbientColor(const glm::vec3& ambientColor);
		void setDiffuseColor(const glm::vec3& diffuseColor);
		void setSpecularColor(const glm::vec3& specularColor);
		void setShininess(const float& shininess);
		void computeTangents();
	};

}
