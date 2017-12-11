#pragma once

#include <istream>
#include <sstream>

class InverseCaptcha
{
public:
	InverseCaptcha();
	~InverseCaptcha();

	static unsigned compute(std::istream& inputStream);
	static unsigned compute_pt2(std::istream& inputStream);

	static std::stringstream testinput;
	static std::stringstream testinput_pt2;
};

