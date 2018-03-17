#ifndef __linux__
	#include "stdafx.h"
#endif

#include <sstream>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>

#include "day14_DiskDefragmentation.h"
#include "day10_KnotHash.h"

const int BLOCK_FREE = 0;
const int BLOCK_USED = -1;

DiskDefragmentation::DiskDefragmentation()
{
}


DiskDefragmentation::~DiskDefragmentation()
{
}

std::pair<unsigned, unsigned> DiskDefragmentation::compute(const std::string & input)
{

	//std::ofstream _debug("debug.txt", std::ofstream::out | std::ofstream::trunc);
	//std::ifstream _debug("d14_test.txt");

	unsigned squaresUsed = 0;
	std::vector<std::vector<int>> discBlocks;
	for (unsigned row = 0; row < 128; ++row) {
		std::stringstream rowcontent;
		rowcontent << input << '-' << row;
		std::string rowHash = KnotHash::compute_pt2(rowcontent);
		
		discBlocks.emplace_back(std::vector<int>());
		for (unsigned i = 0; i < rowHash.length(); i += 2)
		{
			unsigned value = std::stoul(rowHash.substr(i, 2), 0, 16);
			for (unsigned j = 0; j < 8; ++j)
				if (value & (0x01 << j))
				{
					++squaresUsed;
					discBlocks[row].push_back(BLOCK_USED);
				}
				else
					discBlocks[row].push_back(BLOCK_FREE);
		}
	}

	/*std::ofstream _out("pre.csv", std::ofstream::out | std::ofstream::trunc);
	for (unsigned y = 0; y < discBlocks.size(); ++y)
	{
		for (unsigned x = 0; x < discBlocks[y].size(); ++x)
			_out << discBlocks[y][x] << ',';
		_out << '\n';
	}*/

	std::cout << discBlocks.size() << " - " << discBlocks[0].size() << "\n";

	int groupCount = 0;
	for (unsigned y = 0; y < discBlocks.size(); ++y)
		for (unsigned x = 0; x < discBlocks[y].size(); ++x)
			if (discBlocks[y][x] == BLOCK_USED)
				markGroupMembers(discBlocks, y, x, ++groupCount);

	return std::make_pair(squaresUsed, groupCount);
}

void DiskDefragmentation::markGroupMembers(std::vector<std::vector<int>> &discBlocks, unsigned startY, unsigned startX, int groupId)
{
	if (startX < 0 || startY < 0 || startY >= discBlocks.size() || startX >= discBlocks[startY].size())
		return;

	if (discBlocks[startY][startX] == BLOCK_USED)
	{
		discBlocks[startY][startX] = groupId;
		markGroupMembers(discBlocks, startY, startX - 1, groupId);
		markGroupMembers(discBlocks, startY, startX + 1, groupId);
		markGroupMembers(discBlocks, startY - 1, startX, groupId);
		markGroupMembers(discBlocks, startY + 1, startX, groupId);
	}
}
