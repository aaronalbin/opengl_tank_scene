#pragma once

#define _USE_MATH_DEFINES	// to use M_PI
#include <cmath>
#include <string>
#include <vector>
#include <sstream>

namespace Util {

	float degToRad(const float& deg);
	std::vector<std::string> split(const std::string &s, const char& delim);
	std::string numToStr(const int &num);
	std::string numToStr(const long &num);
	std::string numToStr(const double &num);
	std::string numToStr(const float &num);
	std::string numToStr(const size_t &num);
	int strToNum(const std::string &str);
}
