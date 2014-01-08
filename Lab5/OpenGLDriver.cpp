#include "OpenGLDriver.h"

namespace openGLDriver {

	OpenGLDriver *OpenGLDriver::m_instance = NULL;

	OpenGLDriver::OpenGLDriver() {
		m_title = "DEFAULT";
	}

	OpenGLDriver::OpenGLDriver(const std::string& title) : m_title(title) {
	}

	OpenGLDriver::~OpenGLDriver() {
	}

	void OpenGLDriver::setInstance() {
		m_instance = this;
	}

	void OpenGLDriver::init() {
		m_scene.init();
	}

	void OpenGLDriver::start(int argc, char** argv) {
		setInstance();	// set instance to self for callback wrapper functions

		// initialize glut
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
		glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		glutInitWindowPosition(WINDOW_X_POSITION, WINDOW_Y_POSITION);
		glutCreateWindow(m_title.c_str());

		// initialize glew
		GLenum glewInitResult;
		glewExperimental = GL_TRUE;
		glewInitResult = glewInit();
  
		if (GLEW_OK != glewInitResult) {
			std::cerr << "Error: " << glewGetErrorString(glewInitResult) << std::endl;
			exit(1);
		}

		// function callbacks to wrapper functions
		glutReshapeFunc(reshapeWrapper);
		glutDisplayFunc(displayWrapper);
		glutIdleFunc(idleWrapper);
		glutMouseFunc(mouseButtonPressWrapper);
		glutMotionFunc(mouseMoveWrapper);
		glutKeyboardFunc(keyboardWrapper);

		init();
		glutMainLoop();

	}

	void OpenGLDriver::reshape(int w, int h) {
		m_scene.getTrackball().setViewport(w, h);
	}

	void OpenGLDriver::display() {
		m_render.handleDisplay(m_scene);
	}

	void OpenGLDriver::idle() {
		if (m_scene.getTrackball().getRedrawContinue()) {
			glutPostRedisplay();
		}
	}

	void OpenGLDriver::mouseButtonPress(int button, int state, int x, int y) {
		m_input.handleMouseButtonPress(m_scene, button, state, x, y);
	}

	void OpenGLDriver::mouseMove(int x, int y) {
		m_input.handleMouseMove(m_scene, x, y);
	}

	void OpenGLDriver::keyboard(unsigned char key, int x, int y) {
		m_input.handleKeyboard(m_scene, key, x, y);
	}

	// static glut callback functions:

	void OpenGLDriver::reshapeWrapper(int w, int h) {
		m_instance->reshape(w, h);
	}

	void OpenGLDriver::displayWrapper() {
		m_instance->display();
	}

	void OpenGLDriver::idleWrapper() {
		m_instance->idle();
	}

	void OpenGLDriver::mouseButtonPressWrapper(int button, int state, int x, int y) {
		m_instance->mouseButtonPress(button, state, x, y);
	}

	void OpenGLDriver::mouseMoveWrapper(int x, int y) {
		m_instance->mouseMove(x, y);
	}

	void OpenGLDriver::keyboardWrapper(unsigned char key, int x, int y) {
		m_instance->keyboard(key, x, y);
	}

}