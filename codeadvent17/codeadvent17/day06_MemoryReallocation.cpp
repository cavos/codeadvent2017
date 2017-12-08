#include "stdafx.h"
#include "day06_MemoryReallocation.h"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

std::stringstream MemoryReallocation::testinput("10	3	15	10	5	15	5	15	9	2	5	8	5	2	3	6");

MemoryReallocation::MemoryReallocation()
{
}


MemoryReallocation::~MemoryReallocation()
{
}

void MemoryReallocation::debugPrint(const std::vector<unsigned>& v) {
	std::cout << "\t" << computeHash(v) << " => ";
	for (auto u : v)
		std::cout << u << " ";
	std::cout << "\n";
}

unsigned MemoryReallocation::compute(std::istream & input)
{
	std::vector<unsigned> memoryBanks = readInput(input);
	std::vector<unsigned> stateHashes;

	auto duplicateRedistributionIt = stateHashes.end();
	while (duplicateRedistributionIt == stateHashes.end())
	{
		stateHashes.emplace_back(computeHash(memoryBanks));
		reallocate(memoryBanks);
		duplicateRedistributionIt = std::find(stateHashes.begin(), stateHashes.end(), computeHash(memoryBanks));
	}
	return stateHashes.size();
}

std::vector<unsigned> MemoryReallocation::readInput(std::istream & input)
{
	std::vector<unsigned> inputData;
	std::string line;
	while (std::getline(input, line, '\t'))
		inputData.emplace_back(std::stoi(line));

	return inputData;
}

unsigned MemoryReallocation::computeHash(const std::vector<unsigned>& memoryBanks) {
	unsigned hash = memoryBanks.size();
	for (auto& i : memoryBanks) {
		hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	}
	return hash;
}

void MemoryReallocation::reallocate(std::vector<unsigned>& memoryBanks) {
	auto maxBlocks = std::max_element(memoryBanks.begin(), memoryBanks.end());

	auto blocksToRedistribute = *maxBlocks;
	*maxBlocks = 0;
	auto iter = maxBlocks + 1;
	while (blocksToRedistribute > 0)
	{
		if (iter == memoryBanks.end())
			iter = memoryBanks.begin();
		*iter += 1;
		iter++;
		blocksToRedistribute--;
	}
}