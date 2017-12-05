#include "stdafx.h"
#include "CorruptionChecksum.h"

#include <string>
#include <sstream>
#include <climits>

CorruptionChecksum::CorruptionChecksum()
{
}


CorruptionChecksum::~CorruptionChecksum()
{
}

unsigned CorruptionChecksum::compute(std::istream& input)
{
	unsigned checksum = 0;

	std::string line;
	std::getline(input, line);
	while (!line.empty())
	{
		std::stringstream inputLine(line);
		std::string value;
		int max = 0;
		int min = INT_MAX;
		do
		{
			std::getline(inputLine, value, '\t');
			auto number = std::stoi(value);
			if (number > max)
				max = number;
			if (number < min)
				min = number;
		} while (!inputLine.eof());

		checksum += max - min;
		line.clear();
		std::getline(input, line);
	}

	return checksum;
}
