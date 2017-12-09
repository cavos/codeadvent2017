#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <regex>
#include <list>

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
	static bool isOnBlackList(const std::vector<std::string>& blacklist, const std::string& name);
	static TowerNode makeNode(std::smatch& match, std::regex& regex);
	static void pruneHoldees(const TowerNode& node, std::list<TowerNode>& candidates);
};
