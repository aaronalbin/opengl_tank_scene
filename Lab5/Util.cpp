#include "Util.h"

namespace Util {

	float Util::degToRad(const float& deg) {
		return deg * (float)(M_PI / 180.0f);
	}

	std::vector<std::string> Util::split(const std::string &s, const char& delim) {
		std::vector<std::string> tokens;
		std::stringstream ss(s);
		std::string tok;
		while (getline(ss, tok, delim)) {
			tokens.push_back(tok);
		}
		return tokens;
	}

	std::string numToStr(const int &num) {
		std::stringstream sstm;
		sstm << num;
		return sstm.str();
	}

	std::string numToStr(const long &num) {
		std::stringstream sstm;
		sstm << num;
		return sstm.str();
	}

	std::string numToStr(const double &num) {
		std::stringstream sstm;
		sstm << num;
		return sstm.str();
	}
	
	std::string numToStr(const float &num) {
		std::stringstream sstm;
		sstm << num;
		return sstm.str();
	}

	std::string numToStr(const size_t &num) {
		std::stringstream sstm;
		sstm << num;
		return sstm.str();
	}
	
	int strToNum(const std::string &str) {
		int val;
		std::stringstream sstm(str);
		if (!(sstm >> val)) {
			val = 0;
		}
		return val;
	}
}
