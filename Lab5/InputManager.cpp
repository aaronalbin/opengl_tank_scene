#include "InputManager.h"

namespace openGLDriver {

	InputManager::InputManager() {
	}

	InputManager::~InputManager() {
	}

	void InputManager::handleMouseButtonPress(SceneManager& scene, int button, int state, int x, int y) {

		if(button==GLUT_LEFT_BUTTON) {
			switch(state) {
			case GLUT_DOWN:
				y = scene.getTrackball().getHeight() - y;
				startMotion(scene, x, y);
				break;
			case GLUT_UP:
				stopMotion(scene, x, y);
				break;
			} 
		}
	}

	void InputManager::handleMouseMove(SceneManager& scene, int x, int y) {
		float dx, dy, dz;
		glm::vec3 curPos = scene.getTrackball().ptov(x, y);
		if(scene.getTrackball().getTrackingMouse()) {
			glm::vec3 lastPos = scene.getTrackball().getLastPos();
			dx = curPos[0] - lastPos[0];
			dy = curPos[1] - lastPos[1];
			dz = curPos[2] - lastPos[2];

			if (dx || dy || dz) {
				scene.getTrackball().setAngle(90.0f * sqrt(dx*dx + dy*dy + dz*dz));

				glm::vec3 axis;
				axis[0] = lastPos[1]*curPos[2] - lastPos[2]*curPos[1];
				axis[1] = lastPos[2]*curPos[0] - lastPos[0]*curPos[2];
				axis[2] = lastPos[0]*curPos[1] - lastPos[1]*curPos[0];

				lastPos[0] = curPos[0];
				lastPos[1] = curPos[1];
				lastPos[2] = curPos[2];

				scene.getTrackball().setAxis(axis);
				scene.getTrackball().setLastPos(lastPos);
			}
		}
		glutPostRedisplay();
	}

	void InputManager::handleKeyboard(SceneManager& scene, unsigned char key, int x, int y) {

		switch(key) {
		case 'w':
			if (scene.getWireframe())
				scene.setWireframe(false);
			else
				scene.setWireframe(true);
			break;
		case 27:		// escape key 
			exit(0);
			break;
		}

		glutPostRedisplay();
	}

	void InputManager::startMotion(SceneManager& scene, const int& x, const int& y) {
		scene.getTrackball().setTrackingMouse(true);
		scene.getTrackball().setRedrawContinue(false);
		scene.getTrackball().setStartX(x); 
		scene.getTrackball().setStartY(y);
		scene.getTrackball().setCurX(x);
		scene.getTrackball().setCurY(y);
		glm::vec3 lastPos = scene.getTrackball().ptov(x, y);
		scene.getTrackball().setLastPos(lastPos);
		scene.getTrackball().setTrackballMove(true);
	}

	void InputManager::stopMotion(SceneManager& scene, const int& x, const int& y) {
		
		scene.getTrackball().setTrackingMouse(false);

		if (scene.getTrackball().getStartX() != x || scene.getTrackball().getStartY() != y) {
			scene.getTrackball().setRedrawContinue(true);
		} 
		else {
			scene.getTrackball().setAngle(0.0f);
			scene.getTrackball().setRedrawContinue(false);
			scene.getTrackball().setTrackballMove(false);
		}
	}
}