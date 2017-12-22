#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <regex>
#include <list>
#include <map>



class RecurisveCircus
{
public:
	RecurisveCircus();
	~RecurisveCircus();

	static std::string compute(std::istream& input);
	static unsigned compute_pt2(std::istream& input);

	static std::stringstream testintput1;
	static std::ifstream testinput2;

private:

	struct TowerNode;
	static bool isOnBlackList(const std::vector<std::string>& blacklist, const std::string& name);
	static TowerNode makeNode(std::smatch& match);
	static void pruneHoldees(const TowerNode& node, std::list<TowerNode>& candidates);
	static unsigned computeTotalWeight(std::map<std::string, TowerNode>& circusNodes, const std::string& holdee);

	static unsigned findInvalidWeight(const std::string nodeName);

	static std::map<std::string, TowerNode> circusNodes_;
};

