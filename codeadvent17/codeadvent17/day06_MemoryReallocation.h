#pragma once

#include <istream>
#include <vector>
#include <sstream>
#include <utility>

class MemoryReallocation
{
public:
	MemoryReallocation();
	~MemoryReallocation();

	static std::pair<unsigned, unsigned> compute(std::istream& input);

	static std::stringstream testinput;

private:
	static std::vector<unsigned> readInput(std::istream& input);
	static unsigned computeHash(const std::vector<unsigned>& memoryBanks);
	static void reallocate(std::vector<unsigned>& memoryBanks);

	static void MemoryReallocation::debugPrint(const std::vector<unsigned>& v);
};

