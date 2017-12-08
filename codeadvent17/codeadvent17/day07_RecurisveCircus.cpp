#include "stdafx.h"

#include <vector>
#include <regex>
#include <algorithm>
#include "day07_RecurisveCircus.h"


struct RecurisveCircus::TowerNode
{
	std::string name;
	std::vector<std::string> holding;
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

	std::vector<TowerNode> candidates;
	std::string line;
	while (std::getline(input, line))
	{
		std::smatch match;
		if (std::regex_search(line, match, regex)) {
			if (!isHoldedBy(candidates, match[1])) {
				TowerNode node = makeNode(match, regex);
				if (node.holding.size() > 0) {
					pruneHoldees(node, candidates);
					candidates.emplace_back(node);
				}
			}			
		}
	}

	return candidates[0].name;
}

bool RecurisveCircus::isHoldedBy(const std::vector<TowerNode>& candidates, const std::string name)
{
	auto iter = std::find_if(candidates.begin(), candidates.end(), 
							 [&](const TowerNode& node) { 
									auto it = std::find_if(node.holding.begin(), node.holding.end(),
														   [&](const std::string& str) { return str == name; });
									return it != node.holding.end();
							}
	);
	return (iter != candidates.end());
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

void RecurisveCircus::pruneHoldees(const TowerNode & node, std::vector<TowerNode>& candidates)
{
	for (auto holdee : node.holding)
		candidates.erase(std::remove_if(candidates.begin(), 
										candidates.end(), 
										[&](TowerNode& node) { return node.name == holdee; }),
						 candidates.end());
}


std::stringstream RecurisveCircus::testintput1(R"input(pbga (66)
xhth (57)
ebii (61)
havc (66)
ktlj (57)
fwft (72) -> ktlj, cntj, xhth
qoyq (66)
padx (45) -> pbga, havc, qoyq
tknk (41) -> ugml, padx, fwft
jptl (61)
ugml (68) -> gyxo, ebii, jptl
gyxo (61)
cntj (57))input");

std::ifstream RecurisveCircus::testinput2("day07_input.txt", std::ifstream::in);