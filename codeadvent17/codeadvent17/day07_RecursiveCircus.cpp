#include "stdafx.h"

#include <vector>
#include <list>
#include <regex>
#include <algorithm>
#include "day07_RecursiveCircus.h"
#include <iostream>


struct RecurisveCircus::TowerNode
{
	std::string name;
	std::vector<std::string> holding;

	void print() {
		std::cout << name << " -> ";
		for (auto s : holding)
			std::cout << s << ",";
		std::cout << "\n";
	}
};

RecurisveCircus::RecurisveCircus()
{
}


RecurisveCircus::~RecurisveCircus()
{
}

std::string RecurisveCircus::compute(std::istream & input)
{
	std::string bottomProgramName;
	std::regex regex("([a-z]+)");

	std::list<TowerNode> candidates;
	std::vector<std::string> blacklist;
	std::string line;
	while (std::getline(input, line))
	{
		int size = candidates.size();
		std::smatch match;
		if (std::regex_search(line, match, regex)) {
			auto node = makeNode(match, regex);
			if (node.holding.size() > 0) {
				pruneHoldees(node, candidates);
				if (!isOnBlackList(blacklist, node.name))
					candidates.emplace_back(node);
				
				for (auto s : node.holding)
					blacklist.push_back(s);
				
				std::sort(blacklist.begin(), blacklist.end());
			}
		}
	}
	return candidates.begin()->name;
}

bool RecurisveCircus::isOnBlackList(const std::vector<std::string>& blacklist, const std::string& name) {
	auto it = std::binary_search(blacklist.begin(), blacklist.end(), name);
	return (it != blacklist.end());
}

RecurisveCircus::TowerNode RecurisveCircus::makeNode(std::smatch & match, std::regex& regex)
{
	TowerNode node;
	node.name = match[1];
	std::string str = match.suffix();
	while (std::regex_search(str, match, regex))
	{
		node.holding.push_back(match[1]);
		str = match.suffix();
	}
	return node;
}

void RecurisveCircus::pruneHoldees(const TowerNode & node, 
						std::list<TowerNode>& candidates)
{
	for (auto holdee : node.holding) {
		candidates.remove_if([&holdee](TowerNode& node) { return node.name == holdee;});
	}
}


std::stringstream RecurisveCircus::testintput1(R"input(pbga (66)
tknk (41) -> ugml, padx, fwft
xhth (57)
ebii (61)
havc (66)
ktlj (57)
fwft (72) -> ktlj, cntj, xhth
qoyq (66)
padx (45) -> pbga, havc, qoyq
jptl (61)
ugml (68) -> gyxo, ebii, jptl
gyxo (61)
cntj (57))input");

std::ifstream RecurisveCircus::testinput2("day07_input.txt", std::ifstream::in);
