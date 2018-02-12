#ifndef __linux__
	#include "stdafx.h"
#endif

#include <sstream>
#include <vector>
#include <utility>
#include <fstream>

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

std::pair<unsigned, unsigned> DiskDefragmentation::compute(std::string & input)
{

	unsigned squaresUsed = 0;
	std::vector<std::vector<int>> discBlocks;
	for (unsigned row = 0; row < 128; ++row) {
		std::stringstream rowcontent;
		rowcontent << input << '-' << row;

		std::string rowHash = KnotHash::compute_pt2(rowcontent);
		discBlocks.emplace_back(std::vector<int>());
		for (unsigned i = 0; i < rowHash.length(); i += 8)
		{
			unsigned value = std::stoul(rowHash.substr(i, 8), 0, 16);
			for (unsigned j = 0; j < 32; ++j)
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

	unsigned groupCount = 0;
	for (unsigned y = 0; y < discBlocks.size(); ++y)
		for (unsigned x = 0; x < discBlocks[y].size(); ++x)
			if (discBlocks[y][x] == BLOCK_USED)
				markGroupMembers(discBlocks, y, x, ++groupCount);

	/*std::ofstream _out2("post.csv", std::ofstream::out | std::ofstream::trunc);
	for (unsigned y = 0; y < discBlocks.size(); ++y)
	{
		for (unsigned x = 0; x < discBlocks[y].size(); ++x)
			_out2 << discBlocks[y][x] << ',';
		_out2 << '\n';
	}*/

	return std::make_pair(squaresUsed, groupCount);
}

void DiskDefragmentation::markGroupMembers(std::vector<std::vector<int>>& discBlocks, unsigned startY, unsigned startX, unsigned groupId)
{
	discBlocks[startY][startX] = groupId;
	if (startX > 0 && discBlocks[startY][startX-1] == BLOCK_USED)
		markGroupMembers(discBlocks, startY, startX - 1, groupId);
	if (startX + 1 < discBlocks[startY].size() && discBlocks[startY][startX + 1] == BLOCK_USED)
		markGroupMembers(discBlocks, startY, startX + 1, groupId);
	if (startY > 0 && discBlocks[startY-1][startX] == BLOCK_USED)
		markGroupMembers(discBlocks, startY - 1, startX, groupId);
	if (startY + 1 < discBlocks.size() && discBlocks[startY + 1][startX] == BLOCK_USED)
		markGroupMembers(discBlocks, startY + 1, startX, groupId);
}
