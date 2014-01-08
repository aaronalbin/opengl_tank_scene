#include "Trackball.h"

namespace openGLDriver {

	Trackball::Trackball() : m_width(800), m_height(800), m_angle(0.0), m_trackingMouse(false), m_redrawContinue(false), m_trackballMove(false), m_axis(glm::vec3(0.0, 0.0, 0.0)), m_lastPos(glm::vec3(0.0, 0.0, 0.0)), m_modelState(glm::mat4(1.0f)) {
	}

	Trackball::~Trackball() {
	}

	glm::vec3 Trackball::ptov(const int& x, const int& y) {
		float d, a;
		glm::vec3 v;

		// project x, y onto hemi-sphere centered within width, height
		v[0] = (2.0f * x - m_width) / m_width;
		v[1] = (m_height - 2.0f * y) / m_height;
		d = (float)sqrt(v[0] * v[0] + v[1] * v[1]);
		v[2] = (float)cos((M_PI / 2.0f) * ((d < 1.0f) ? d : 1.0f));
		a = 1.0f / (float)sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
		v[0] *= a;
		v[1] *= a;
		v[2] *= a;

		return v;
	}

	int Trackball::getWidth() {
		return m_width;
	}

	int Trackball::getHeight() {
		return m_height;
	}

	int Trackball::getStartX() {
		return m_startX;
	}

	int Trackball::getStartY() {
		return m_startY;
	}

	float Trackball::getAngle() {
		return m_angle;
	}

	bool Trackball::getTrackingMouse() {
		return m_trackingMouse;
	}

	bool Trackball::getRedrawContinue() {
		return m_redrawContinue;
	}

	bool Trackball::getTrackballMove() {
		return m_trackballMove;
	}

	glm::vec3 Trackball::getAxis() {
		return m_axis;
	}

	glm::vec3 Trackball::getLastPos() {
		return m_lastPos;
	}

	glm::mat4 Trackball::getModelState() {
		return m_modelState;
	}

	void Trackball::setAngle(const float& angle) {
		m_angle = angle;
	}

	void Trackball::setAxis(const glm::vec3& axis) {
		m_axis = axis;
	}

	void Trackball::setLastPos(const glm::vec3& lastPos) {
		m_lastPos = lastPos;
	}

	void Trackball::setTrackingMouse(const bool& state) {
		m_trackingMouse = state;
	}

	void Trackball::setRedrawContinue(const bool& state) {
		m_redrawContinue = state;
	}

	void Trackball::setTrackballMove(const bool& state) {
		m_trackballMove = state;
	}

	void Trackball::setCurX(const int& curX) {
		m_curX = curX;
	}
	
	void Trackball::setCurY(const int& curY) {
		m_curY = curY;
	}

	void Trackball::setStartX(const int& startX) {
		m_startX = startX;
	}
	
	void Trackball::setStartY(const int& startY) {
		m_startY = startY;
	}

	void Trackball::setViewport(const int& w, const int& h) {
		m_width = w;
		m_height = h;
	}

	void Trackball::setModelState(const glm::mat4& model) {
		m_modelState = model;
	}
	
}
