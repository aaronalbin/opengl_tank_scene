#pragma once

#include <iostream>

namespace openGLDriver {

	class Vertex
	{
	private:
		float m_x, m_y, m_z, m_w, m_nx, m_ny, m_nz, m_s, m_t, m_tanx, m_tany, m_tanz, m_bitanx, m_bitany, m_bitanz;

	public:
		Vertex();
		Vertex(const float& x, const float& y, const float& z, const float& w);
		Vertex(const float& x, const float& y, const float& z, const float& w, const float& nx, const float& ny, const float& nz);
		Vertex(const float& x, const float& y, const float& z, const float& w, const float& nx, const float& ny, const float& nz, const float& s, const float& t);
		Vertex(const float& x, const float& y, const float& z, const float& w, const float& nx, const float& ny, const float& nz, const float& s, const float& t, const float& tx, const float& ty, const float& tz, const float& bx, const float& by, const float& bz);
		~Vertex();
		void setPosition(const float& x, const float& y, const float& z, const float& w);
		void setX(const float& x);
		void setY(const float& y);
		void setZ(const float& z);
		void setW(const float& w);
		void setNX(const float& nx);
		void setNY(const float& ny);
		void setNZ(const float& nz);
		void setS(const float& s);
		void setT(const float& t);
		void setTanX(const float& tanx);
		void setTanY(const float& tany);
		void setTanZ(const float& tanz);
		void setBitanX(const float& tanx);
		void setBitanY(const float& tany);
		void setBitanZ(const float& tanz);
		float getX();
		float getY();
		float getZ();
		float getW();
		float getNX();
		float getNY();
		float getNZ();
		float getS();
		float getT();
		float getTanX();
		float getTanY();
		float getTanZ();
		float getBitanX();
		float getBitanY();
		float getBitanZ();
		void toString();
	};

}
