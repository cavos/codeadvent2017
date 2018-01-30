#pragma once

#include <istream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>

class PermutationPromenade
{
public:
	PermutationPromenade();
	~PermutationPromenade();

	static std::ifstream input;

	static std::string compute(std::istream& input, const std::string& dancersPositions = "abcdefghijklmnop");
	static std::string compute_pt2(std::istream& input);

private:
	static std::vector<std::tuple<char, char, char>> parse(std::istream& input);
	static std::string dance(std::string dancers, const std::vector<std::tuple<char, char, char>>& danceMoves);
};

