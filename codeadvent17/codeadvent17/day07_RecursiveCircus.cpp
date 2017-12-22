#include "stdafx.h"

#include "day07_RecursiveCircus.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <regex>
#include <vector>

struct RecurisveCircus::TowerNode {
  std::string name;
  unsigned weight;
  std::vector<std::string> holding;
  unsigned totalWeight = 0;
};

std::map<std::string, RecurisveCircus::TowerNode> RecurisveCircus::circusNodes_;

const std::regex REGX_node(R"regex((\w+) \((\d+)\))regex");
const std::regex REGX_holdees(R"regx((\w+))regx");

RecurisveCircus::RecurisveCircus() {}

RecurisveCircus::~RecurisveCircus() {}

std::string RecurisveCircus::compute(std::istream &input) {
  std::string bottomProgramName;

  std::list<TowerNode> candidates;
  std::vector<std::string> blacklist;
  std::string line;
  while (std::getline(input, line)) {
    std::smatch match;
    if (std::regex_search(line, match, REGX_node)) {
      auto node = makeNode(match);
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

  input.clear();
  input.seekg(0, std::ios::beg);
  return candidates.begin()->name;
}

bool RecurisveCircus::isOnBlackList(const std::vector<std::string> &blacklist,
                                    const std::string &name) {
  return std::binary_search(blacklist.begin(), blacklist.end(), name);
}

RecurisveCircus::TowerNode RecurisveCircus::makeNode(std::smatch &match) {
  assert(match.size() == 3);

  TowerNode node;
  node.name = match[1];
  node.weight = std::stoi(match[2]);
  std::string str = match.suffix();
  while (std::regex_search(str, match, REGX_holdees)) {
    node.holding.push_back(match[1]);
    str = match.suffix();
  }
  return node;
}

void RecurisveCircus::pruneHoldees(const TowerNode &node,
                                   std::list<TowerNode> &candidates) {
  for (auto holdee : node.holding) {
    candidates.remove_if(
        [&holdee](TowerNode &node) { return node.name == holdee; });
  }
}

unsigned RecurisveCircus::compute_pt2(std::istream &input) {
  std::string line;
  while (std::getline(input, line)) {
    std::smatch match;
    if (std::regex_search(line, match, REGX_node)) {
      auto node = makeNode(match);
      circusNodes_[node.name] = node;
      // std::cout << ">>" << node.name << "\n";
    }
  }

  static const std::string ROOT_NODE = "azqje";
  return findInvalidWeight(ROOT_NODE);
}

//TODO !!!!!! needs rework!
unsigned RecurisveCircus::findInvalidWeight(const std::string nodeName) {
  auto *node = &circusNodes_[nodeName];
  std::vector<std::pair<unsigned, unsigned>> childWeights;
  unsigned invalidWeight = 0;
  // first, we ask children if they have element with invalid weight
  for (auto n : node->holding) {
    invalidWeight = findInvalidWeight(n);
    if (invalidWeight)
      break;
    else {
      auto it = std::find_if(childWeights.begin(), childWeights.end(),
                             [&](const auto &item) {
                               return item.first == circusNodes_[n].totalWeight;
                             });
      if (it != childWeights.end())
        it->second += 1;
      else
        childWeights.emplace_back(
            std::make_pair(circusNodes_[n].totalWeight, 1));
    }
  }

  if (invalidWeight == 0) {
    if (childWeights.size() > 1) {
      unsigned unbalanced, balanced;
      if (childWeights[0].second > childWeights[1].second) {
        unbalanced = childWeights[1].first;
        balanced = childWeights[0].first;
      } else {
        balanced = childWeights[1].first;
        unbalanced = childWeights[0].first;
      }

      int offset = balanced - unbalanced;
      for (auto n : node->holding) {
        if (circusNodes_[n].totalWeight == unbalanced)
          invalidWeight = circusNodes_[n].weight + offset;
      }
    } else {
      node->totalWeight = node->weight;
      if (!childWeights.empty())
        node->totalWeight +=
            childWeights.front().first * childWeights.front().second;
    }
  }

  // std::cout << node->name << "(" << node->totalWeight << ")" << "\n";

  return invalidWeight;
}

unsigned RecurisveCircus::computeTotalWeight(
    std::map<std::string, TowerNode> &circusNodes, const std::string &holdee) {
  auto node = circusNodes[holdee];
  return 0;
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
