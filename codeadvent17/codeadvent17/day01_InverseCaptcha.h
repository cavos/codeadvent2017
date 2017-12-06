#pragma once

#include <istream>
#include <sstream>

class InverseCaptcha
{
public:
	InverseCaptcha();
	~InverseCaptcha();

	static unsigned compute(std::istream& inputStream);

	static std::stringstream testinput;
};

