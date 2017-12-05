#pragma once

#include <istream>

class CorruptionChecksum
{
public:
	CorruptionChecksum();
	~CorruptionChecksum();

	unsigned compute(std::istream& input);
};

