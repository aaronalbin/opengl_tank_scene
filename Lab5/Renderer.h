#pragma once

#include <stack>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "SceneManager.h"

namespace openGLDriver {

	class Renderer
	{
	private:
		void drawFloor(SceneManager& scene, glm::mat4& view, glm::mat4& model, glm::mat4& projection, glm::vec4& lightPosition, std::stack<glm::mat4>& mv);
		void drawCubeMap(SceneManager& scene, glm::mat4& view, glm::mat4& model, glm::mat4& projection, glm::vec4& lightPosition, std::stack<glm::mat4>& mv);
		void drawSU(SceneManager& scene, glm::mat4& view, glm::mat4& model, glm::mat4& projection, glm::vec4& lightPosition, std::stack<glm::mat4>& mv);
		void drawReflectSphere(SceneManager& scene, glm::mat4& view, glm::mat4& model, glm::mat4& projection, glm::vec4& lightPosition, std::stack<glm::mat4>& mv);
		void drawSUShadow(SceneManager& scene, glm::mat4& view, glm::mat4& model, glm::mat4& projection, glm::vec4& lightPosition, std::stack<glm::mat4>& mv);
		glm::mat4 getShadowMatrix(const glm::vec4& plane, const glm::vec4& lightPosition);
		glm::vec4 findPlane(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2);
		void getFloorTopPlane(SceneManager& scene, glm::vec3& v0, glm::vec3& v1, glm::vec3& v2);

	public:
		Renderer();
		~Renderer();
		void handleDisplay(SceneManager& scene);
	};

}
