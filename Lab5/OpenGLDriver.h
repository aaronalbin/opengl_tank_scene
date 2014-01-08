#pragma once

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GL/glut.h>
#include "SceneManager.h"
#include "InputManager.h"
#include "Renderer.h"

namespace openGLDriver {

	class OpenGLDriver {

	private:
		std::string m_title;
		SceneManager m_scene;
		InputManager m_input;
		Renderer m_render;

	protected:
		static OpenGLDriver *m_instance;

	public:
		// Constants
		const static int WINDOW_WIDTH = 800;
		const static int WINDOW_HEIGHT = 800;
		const static int WINDOW_X_POSITION = 100;
		const static int WINDOW_Y_POSITION = 100;

		OpenGLDriver();
		OpenGLDriver(const std::string& title);
		~OpenGLDriver();
		void init();
		void setInstance();
		void start(int argc, char** argv);
		void display();
		void reshape(int w, int h);
		void idle();
		void mouseButtonPress(int button, int state, int x, int y);
		void mouseMove(int x, int y);
		void keyboard(unsigned char key, int x, int y);

		// static functions passed to GLUT callbacks
		static void reshapeWrapper(int w, int h);
		static void displayWrapper();
		static void idleWrapper();
		static void mouseButtonPressWrapper(int button, int state, int x, int y);
		static void mouseMoveWrapper(int x, int y);
		static void keyboardWrapper(unsigned char key, int x, int y);
	};

}