#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <regex>

class RecurisveCircus
{
public:
	RecurisveCircus();
	~RecurisveCircus();

	static std::string compute(std::istream& input);

	static std::stringstream testintput1;
	static std::ifstream testinput2;

private:

	struct TowerNode;
	static bool isHoldedBy(const std::vector<TowerNode>& candidates, const std::string name);
	static TowerNode makeNode(std::smatch& match, std::regex& regex);
	static void pruneHoldees(const TowerNode& node, std::vector<TowerNode>& candidates);
};

