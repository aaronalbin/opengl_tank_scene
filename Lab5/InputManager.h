#pragma once

#include <iostream>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "SceneManager.h"

namespace openGLDriver {

	class InputManager
	{

	private:

	public:
		InputManager();
		~InputManager();
		void handleMouseButtonPress(SceneManager& scene, int button, int state, int x, int y);
		void handleMouseMove(SceneManager& scene, int x, int y);
		void handleKeyboard(SceneManager& scene, unsigned char key, int x, int y);
		void startMotion(SceneManager& scene, const int& x, const int& y);
		void stopMotion(SceneManager& scene, const int& x, const int& y);
	};

}

