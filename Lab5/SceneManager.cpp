#include "SceneManager.h"

namespace openGLDriver {

	SceneManager *SceneManager::m_sceneInstance = NULL;

	SceneManager::SceneManager() : m_wireframe(false), m_animate(false) {
	}

	SceneManager::~SceneManager() {
	}
	
	void SceneManager::setInstance() {
		m_sceneInstance = this;
	}
	
	void SceneManager::init() {
		std::cout << "Loading resources..." << std::endl;
		setInstance();
		initShader();
		loadFloor();
		loadSU();
		loadSphere();
		loadCubeMap();
		initVBO();
		std::cout << "Done." << std::endl;
	}

	void SceneManager::initShader() {
		m_bumpShader.setup("resources/shaders/phong_shader_bump");
		m_cubeMapShader.setup("resources/shaders/cubemap_shader");
		m_reflectShader.setup("resources/shaders/reflect_shader");
		m_plainShader.setup("resources/shaders/plain_shader");
		m_emptyShader.setup("resources/shaders/empty_shader");
	}

	bool SceneManager::loadFloor() {
		if (!m_modelLoader.load("resources/models/cube.ply")) {
			return false;
		}

		std::vector<Face> faces = m_modelLoader.getFaces();
		std::vector<GLuint> indexList(faces.size() * 3);

		int count = 0;
		for (size_t i = 0; i < faces.size(); i++) {
			indexList[count] = faces[i].getV1();
			count++;
			indexList[count] = faces[i].getV2();
			count++;
			indexList[count] = faces[i].getV3();
			count++;
		}

		m_floor.setIndexList(indexList);

		std::vector<Vertex> vertexList = m_modelLoader.getVertices();

		m_floor.setVertexList(vertexList);
		m_modelLoader.clear();

		m_floor.setAmbientColor(glm::vec3(0.2, 0.2, 0.2));
		m_floor.setDiffuseColor(glm::vec3(1.0, 0.1, 0.1));
		m_floor.setSpecularColor(glm::vec3(0.7, 0.7, 0.7));
		m_floor.setShininess(7.5);

		return true;
	}

	bool SceneManager::loadSU() {
		if (!m_modelLoader.load("resources/models/SU-122-54.ply")) {
			return false;
		}

		m_modelLoader.flipTexture();

		std::vector<Face> faces = m_modelLoader.getFaces();
		std::vector<GLuint> indexList(faces.size() * 3);

		int count = 0;
		for (size_t i = 0; i < faces.size(); i++) {
			indexList[count] = faces[i].getV1();
			count++;
			indexList[count] = faces[i].getV2();
			count++;
			indexList[count] = faces[i].getV3();
			count++;
		}

		m_su.setIndexList(indexList);

		std::vector<Vertex> vertexList = m_modelLoader.getVertices();
		
		m_su.setVertexList(vertexList);
		m_modelLoader.clear();

		m_su.setAmbientColor(glm::vec3(0.2, 0.2, 0.2));
		m_su.setDiffuseColor(glm::vec3(1.0, 1.0, 1.0));
		m_su.setSpecularColor(glm::vec3(0.7, 0.7, 0.7));
		m_su.setShininess(7.5);

		m_textureHandle[1] = SOIL_load_OGL_texture( "resources/textures/SU122_54.dds", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glBindTexture( GL_TEXTURE_2D, 0 );
		
		m_textureHandle[2] = SOIL_load_OGL_texture( "resources/textures/SU122_54_NM.dds", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glBindTexture( GL_TEXTURE_2D, 0 );
		
		return true;
	}

	bool SceneManager::loadSphere() {
		if (!m_modelLoader.load("resources/models/sphere.ply")) {
			return false;
		}

		std::vector<Face> faces = m_modelLoader.getFaces();
		std::vector<GLuint> indexList(faces.size() * 3);

		int count = 0;
		for (size_t i = 0; i < faces.size(); i++) {
			indexList[count] = faces[i].getV1();
			count++;
			indexList[count] = faces[i].getV2();
			count++;
			indexList[count] = faces[i].getV3();
			count++;
		}

		m_sphere.setIndexList(indexList);

		std::vector<Vertex> vertexList = m_modelLoader.getVertices();

		m_sphere.setVertexList(vertexList);
		m_modelLoader.clear();

		m_sphere.setAmbientColor(glm::vec3(0.3, 0.3, 0.3));
		m_sphere.setDiffuseColor(glm::vec3(1.0, 1.0, 1.0));
		m_sphere.setSpecularColor(glm::vec3(0.7, 0.7, 0.7));
		m_sphere.setShininess(8.5);

		return true;
	}

	bool SceneManager::loadCubeMap() {

		m_textureHandle[0] = SOIL_load_OGL_cubemap( "resources/textures/mountain/mountain_west.bmp",
                                          "resources/textures/mountain/mountain_east.bmp", 
                                          "resources/textures/mountain/mountain_up.bmp",
                                          "resources/textures/mountain/mountain_down.bmp",
                                          "resources/textures/mountain/mountain_south.bmp",
                                          "resources/textures/mountain/mountain_north.bmp",
                                          SOIL_LOAD_AUTO,
                                          SOIL_CREATE_NEW_ID,
                                          SOIL_FLAG_MIPMAPS );

		// To prevent artifacts at the edges, use clamping at texture bounds.
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 
		// Make sure we unbind and disable the cube map texture.
		glBindTexture( GL_TEXTURE_CUBE_MAP, 0 );
		//glDisable( GL_TEXTURE_CUBE_MAP );

		return true;
	}

	void SceneManager::initVBO() {

		glGenBuffers(4, m_vboHandle);
		glGenBuffers(4, m_vboIndex);
		
		// floor
		glBindBuffer(GL_ARRAY_BUFFER, m_vboHandle[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*m_floor.getNumVertices(), &m_floor.getVertexList().front(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*m_floor.getNumIndices(), &m_floor.getIndexList().front(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
		// skybox
		glBindBuffer(GL_ARRAY_BUFFER, m_vboHandle[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*m_cubeMap.getNumVertices(), &m_cubeMap.getVertexList().front(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*m_cubeMap.getNumIndices(), &m_cubeMap.getIndexList().front(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// SU
		glBindBuffer(GL_ARRAY_BUFFER, m_vboHandle[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*m_su.getNumVertices(), &m_su.getVertexList().front(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex[2]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*m_su.getNumIndices(), &m_su.getIndexList().front(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
		// sphere
		glBindBuffer(GL_ARRAY_BUFFER, m_vboHandle[3]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*m_sphere.getNumVertices(), &m_sphere.getVertexList().front(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex[3]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*m_sphere.getNumIndices(), &m_sphere.getIndexList().front(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	GLuint SceneManager::getFloorVBOHandle() {
		return m_vboHandle[0];
	}
	
	GLuint SceneManager::getFloorVBOIndex() {
		return m_vboIndex[0];
	}

	GLuint SceneManager::getCubeMapVBOHandle() {
		return m_vboHandle[1];
	}
	
	GLuint SceneManager::getCubeMapVBOIndex() {
		return m_vboIndex[1];
	}

	GLuint SceneManager::getSUVBOHandle() {
		return m_vboHandle[2];
	}
	
	GLuint SceneManager::getSUVBOIndex() {
		return m_vboIndex[2];
	}

	GLuint SceneManager::getSphereVBOHandle() {
		return m_vboHandle[3];
	}
	
	GLuint SceneManager::getSphereVBOIndex() {
		return m_vboIndex[3];
	}

	GLuint SceneManager::getCubeMapTextureHandle() {
		return m_textureHandle[0];
	}

	GLuint SceneManager::getSUTextureHandle() {
		return m_textureHandle[1];
	}

	GLuint SceneManager::getSUTextureNormalHandle() {
		return m_textureHandle[2];
	}

	Model SceneManager::getFloor() {
		return m_floor;
	}

	Model SceneManager::getSU() {
		return m_su;
	}

	Model SceneManager::getSphere() {
		return m_sphere;
	}

	Cube SceneManager::getCubeMap() {
		return m_cubeMap;
	}

	ShaderManager SceneManager::getBumpShader() {
		return m_bumpShader;
	}

	ShaderManager SceneManager::getCubeMapShader() {
		return m_cubeMapShader;
	}

	ShaderManager SceneManager::getReflectShader() {
		return m_reflectShader;
	}

	ShaderManager SceneManager::getPlainShader() {
		return m_plainShader;
	}

	ShaderManager SceneManager::getEmptyShader() {
		return m_emptyShader;
	}

	void SceneManager::setWireframe(const bool& state) {
		m_wireframe = state;
	}

	bool SceneManager::getWireframe() {
		return m_wireframe;
	}

	Trackball& SceneManager::getTrackball() {
		return m_trackball;
	}

}
