#pragma once

#include <istream>

class InverseCaptcha
{
public:
	InverseCaptcha();
	~InverseCaptcha();

	unsigned compute(std::istream& inputStream);
};

