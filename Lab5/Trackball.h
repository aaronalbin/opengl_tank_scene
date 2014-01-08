#pragma once

#define _USE_MATH_DEFINES	// to use M_PI
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

namespace openGLDriver {

	class Trackball {

	private:
		float m_angle;
		glm::vec3 m_axis;
		bool m_trackingMouse;
		bool m_redrawContinue;
		bool m_trackballMove;
		int m_width, m_height;
		glm::vec3 m_lastPos;
		int m_curX, m_curY;
		int m_startX, m_startY;
		glm::mat4 m_modelState;

	public:
		Trackball();
		~Trackball();
		glm::vec3 ptov(const int& x, const int& y);
		int getWidth();
		int getHeight();
		int getStartX();
		int getStartY();
		float getAngle();
		bool getTrackingMouse();
		bool getRedrawContinue();
		bool getTrackballMove();
		glm::vec3 getAxis();
		glm::vec3 getLastPos();
		glm::mat4 getModelState();
		void setAngle(const float& angle);
		void setAxis(const glm::vec3& axis);
		void setLastPos(const glm::vec3& lastPos);
		void setTrackingMouse(const bool& state);
		void setRedrawContinue(const bool& state);
		void setTrackballMove(const bool& state);
		void setCurX(const int& curX);
		void setCurY(const int& curY);
		void setStartX(const int& startX);
		void setStartY(const int& startY);
		void setViewport(const int& w, const int& h);
		void setModelState(const glm::mat4& model);
	};

}
