#pragma once

#include <istream>
#include <sstream>

class CorruptionChecksum
{
public:
	CorruptionChecksum();
	~CorruptionChecksum();

	static unsigned compute(std::istream& input);

	static std::stringstream testinput;
};

