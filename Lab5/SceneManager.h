#pragma once

#include <stdlib.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "soil/include/SOIL.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "Model.h"
#include "ModelLoader.h"
#include "Logger.h"
#include "ShaderManager.h"
#include "Trackball.h"
#include "TextureLoader.h"
#include "Cube.h"

namespace openGLDriver {

	class SceneManager
	{
	private:
		GLuint m_vboHandle[4];	// 0 is floor, 1 is skybox, 2 is SU, 3 is sphere
		GLuint m_vboIndex[4];  // 0 is floor, 1 is skybox, 2 is SU, 3 is sphere
		GLuint m_textureHandle[3];  // 0 is cubemap, 1 is SU color, 2 is SU color
		Model m_floor;
		Model m_su;
		Model m_sphere;
		Cube m_cubeMap;
		ModelLoader m_modelLoader;
		ShaderManager m_bumpShader;
		ShaderManager m_cubeMapShader;
		ShaderManager m_reflectShader;
		ShaderManager m_plainShader;
		ShaderManager m_emptyShader;
		bool m_wireframe;
		bool m_animate;
		Trackball m_trackball;
		TextureLoader m_textureLoader;

	protected:
		static SceneManager *m_sceneInstance;

	public:
		SceneManager();
		~SceneManager();
		void init();
		void initVBO();
		void initShader();
		bool loadFloor();
		bool loadSU();
		bool loadSphere();
		bool loadCubeMap();
		GLuint getFloorVBOHandle();
		GLuint getFloorVBOIndex();
		GLuint getSUVBOHandle();
		GLuint getSUVBOIndex();
		GLuint getCubeMapVBOHandle();
		GLuint getCubeMapVBOIndex();
		GLuint getSphereVBOHandle();
		GLuint getSphereVBOIndex();
		GLuint getSUTextureHandle();
		GLuint getSUTextureNormalHandle();
		GLuint getCubeMapTextureHandle();
		void setInstance();
		Model getFloor();
		Model getSU();
		Model getSphere();
		Cube getCubeMap();
		ShaderManager getBumpShader();
		ShaderManager getCubeMapShader();
		ShaderManager getReflectShader();
		ShaderManager getPlainShader();
		ShaderManager getEmptyShader();
		void setWireframe(const bool& state);
		bool getWireframe();
		Trackball& getTrackball();
	};

}
