#pragma once
#include <string>
#include <vector>
#include <utility>

class DiskDefragmentation
{
public:
	DiskDefragmentation();
	~DiskDefragmentation();

	static std::pair<unsigned, unsigned>  compute(const std::string& input);
private:
	static void markGroupMembers(std::vector<std::vector<int>> &discBlocks, unsigned y, unsigned x, int groupId);
};

