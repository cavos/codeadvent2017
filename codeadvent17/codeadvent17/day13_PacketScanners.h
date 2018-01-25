#pragma once

#include <istream>
#include <sstream>
#include <vector>
#include <utility>

class PacketScanners
{
public:
	PacketScanners();
	~PacketScanners();

	static unsigned compute(std::istream& input);
	static unsigned compute_pt2(std::istream& input);

	static std::stringstream input;
private:
	static std::vector<std::pair<unsigned, unsigned>> readInput(std::istream& input);
	static unsigned getScannerPos(unsigned picosecond, unsigned depth);
};

