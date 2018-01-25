#include "stdafx.h"
#include "PacketScanners.h"

#include <string>
#include <iostream>
#include <cmath>

std::stringstream PacketScanners::input(R"(0: 3
1: 2
2: 4
4: 4
6: 5
8: 6
10: 8
12: 8
14: 6
16: 6
18: 9
20: 8
22: 6
24: 10
26: 12
28: 8
30: 8
32: 14
34: 12
36: 8
38: 12
40: 12
42: 12
44: 12
46: 12
48: 14
50: 12
52: 12
54: 10
56: 14
58: 12
60: 14
62: 14
64: 14
66: 14
68: 14
70: 14
72: 14
74: 20
78: 14
80: 14
90: 17
96: 18)");

PacketScanners::PacketScanners()
{
}


PacketScanners::~PacketScanners()
{
}

unsigned PacketScanners::compute(std::istream & input)
{
	std::vector<std::pair<unsigned, unsigned>> scannerPositions = readInput(input);

	unsigned tripSeverity = 0;
	for (auto scanner : scannerPositions)
		if (getScannerPos(scanner.first, scanner.second) == 0)
			tripSeverity += scanner.first * scanner.second;

	input.clear();
	input.seekg(0, std::ios::beg);

	return tripSeverity;
}

unsigned PacketScanners::compute_pt2(std::istream& input)
{
	std::vector<std::pair<unsigned, unsigned>> scannerPositions = readInput(input);

	unsigned delay = 0;
	bool caught = true;
	while (caught)
	{
		caught = false;
		for (auto scanner : scannerPositions)
			if (getScannerPos(scanner.first + delay, scanner.second) == 0)
			{
				caught = true;
				++delay;
				break;
			}
	}

	return delay;
}

std::vector<std::pair<unsigned, unsigned>> PacketScanners::readInput(std::istream& input)
{
	std::vector<std::pair<unsigned, unsigned>> scannerPositions;

	std::string line;
	while (std::getline(input, line))
	{
		unsigned layer = std::stoul(line.substr(0, line.find(':')));
		unsigned depth = std::stoul(line.substr(line.find(':') + 1));
		scannerPositions.emplace_back(std::make_pair(layer, depth));
	}

	return scannerPositions;
}

unsigned PacketScanners::getScannerPos(unsigned picosecond, unsigned indepth)
{
	const unsigned depth = indepth - 1;
	unsigned trip = picosecond / depth;
	unsigned scannerPos;
	if (trip % 2)
		scannerPos = depth - picosecond % depth;
	else
		scannerPos = picosecond % depth;

	return scannerPos;
}
