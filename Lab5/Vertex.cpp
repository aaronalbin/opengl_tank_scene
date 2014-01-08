#include "Vertex.h"

namespace openGLDriver {

	Vertex::Vertex() {
	}

	Vertex::Vertex(const float& x, const float& y, const float& z, const float& w) : 
		m_x(x), m_y(y), m_w(w), m_z(z), m_nx(-1), m_ny(-1), m_nz(-1), m_s(-1), m_t(-1), m_tanx(0), m_tany(0), m_tanz(0), m_bitanx(0), m_bitany(0), m_bitanz(0) {
	}
	
	Vertex::Vertex(const float& x, const float& y, const float& z, const float& w, const float& nx, const float& ny, const float& nz) : 
		m_x(x), m_y(y), m_z(z), m_w(w), m_nx(nx), m_ny(ny), m_nz(nz), m_s(-1), m_t(-1), m_tanx(0), m_tany(0), m_tanz(0), m_bitanx(0), m_bitany(0), m_bitanz(0) {
	}

	Vertex::Vertex(const float& x, const float& y, const float& z, const float& w, const float& nx, const float& ny, const float& nz, const float& s, const float& t) : 
		m_x(x), m_y(y), m_z(z), m_w(w), m_nx(nx), m_ny(ny), m_nz(nz), m_s(s), m_t(t), m_tanx(0), m_tany(0), m_tanz(0), m_bitanx(0), m_bitany(0), m_bitanz(0) {
	}
	
	Vertex::Vertex(const float& x, const float& y, const float& z, const float& w, const float& nx, const float& ny, const float& nz, const float& s, const float& t, const float& tx, const float& ty, const float& tz, const float& bx, const float& by, const float& bz) : 
		m_x(x), m_y(y), m_z(z), m_w(w), m_nx(nx), m_ny(ny), m_nz(nz), m_s(s), m_t(t), m_tanx(tx), m_tany(ty), m_tanz(tz), m_bitanx(bx), m_bitany(by), m_bitanz(bz) {
	}

	Vertex::~Vertex() {
	}

	void Vertex::setPosition(const float& x, const float& y, const float& z, const float& w) {
		m_x = x;
		m_y = y;
		m_z = z;
		m_w = w;
	}

	void Vertex::setX(const float& x) {
		m_x = x;	
	}
	
	void Vertex::setY(const float& y) {
		m_y = y;	
	}
	
	void Vertex::setZ(const float& z) {
		m_z = z;	
	}

	void Vertex::setW(const float& w) {
		m_w = w;	
	}
	
	void Vertex::setNX(const float& nx) {
		m_nx = nx;
	}

	void Vertex::setNY(const float& ny) {
		m_ny = ny;
	}

	void Vertex::setNZ(const float& nz) {
		m_nz = nz;
	}

	void Vertex::setS(const float& s) {
		m_s = s;
	}

	void Vertex::setT(const float& t) {
		m_t = t;
	}

	void Vertex::setTanX(const float& tanx) {
		m_tanx = tanx;
	}

	void Vertex::setTanY(const float& tany) {
		m_tany = tany;
	}

	void Vertex::setTanZ(const float& tanz) {
		m_tanz = tanz;
	}

	void Vertex::setBitanX(const float& bitanx) {
		m_bitanx = bitanx;
	}

	void Vertex::setBitanY(const float& bitany) {
		m_bitany = bitany;
	}

	void Vertex::setBitanZ(const float& bitanz) {
		m_bitanz = bitanz;
	}

	float Vertex::getX() {
		return m_x;
	}

	float Vertex::getY() {
		return m_y;
	}

	float Vertex::getZ() {
		return m_z;
	}

	float Vertex::getW() {
		return m_w;
	}

	float Vertex::getNX() {
		return m_nx;
	}

	float Vertex::getNY() {
		return m_ny;
	}

	float Vertex::getNZ() {
		return m_nz;
	}

	float Vertex::getS() {
		return m_s;
	}

	float Vertex::getT() {
		return m_t;
	}

	float Vertex::getTanX() {
		return m_tanx;
	}

	float Vertex::getTanY() {
		return m_tany;
	}

	float Vertex::getTanZ() {
		return m_tanz;
	}

	float Vertex::getBitanX() {
		return m_bitanx;
	}

	float Vertex::getBitanY() {
		return m_bitany;
	}

	float Vertex::getBitanZ() {
		return m_bitanz;
	}

	void Vertex::toString() {
		std::cout << m_x << " " << m_y << " " << m_z << " " << m_nx << " " << m_ny << " " << m_nz << " " << m_s << " " << m_t << " " << m_tanx << " " << m_tany << " " << m_tanz << std::endl;
	}
}
