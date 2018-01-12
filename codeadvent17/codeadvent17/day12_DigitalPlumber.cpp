#include "day12_DigitalPlumber.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <numeric>

std::string DigitalPlumber::testInput("day12_input.txt");

struct Villager {
  bool isConnectedTo0{false};
  int isAsking{0};
  int groupLeader = NONE_LEADER;
  std::set<unsigned> pipesTo;

  static const int NONE_LEADER = -1;
};

void setGroupLeader(unsigned villagerId, unsigned groupLeaderId,
                    std::map<unsigned, Villager> &villageMap);

std::pair<unsigned, size_t> DigitalPlumber::compute(std::istream &input) {
  const std::regex NUMBER("(\\d+)");
  std::map<unsigned, Villager> villageMap;

  std::string record;
  while (std::getline(input, record)) {
    std::smatch match;
    if (std::regex_search(record, match, NUMBER)) {
      unsigned id = std::stoul(match[1]);

      std::string str = match.suffix();
      while (std::regex_search(str, match, NUMBER)) {
        auto x = std::stoul(match[1]);
        if (x != id)
          villageMap[id].pipesTo.insert(x);
        str = match.suffix();
      }
    }
  }

  for (unsigned id = 0; id < villageMap.size(); ++id) {
    auto *vil = &villageMap[id];
    if (vil->groupLeader == Villager::NONE_LEADER) {
      vil->groupLeader = id;
      setGroupLeader(id, id, villageMap);
    }
  }

  std::set<unsigned> leaders;
  unsigned assignedTo0Cnt = 0;
  for (auto villager : villageMap) {
      leaders.insert(villager.second.groupLeader);
      if (villager.second.groupLeader == 0)
        ++assignedTo0Cnt;
  }

  return std::make_pair(assignedTo0Cnt, leaders.size());
}

void setGroupLeader(unsigned villagerId, unsigned groupLeaderId,
                    std::map<unsigned, Villager> &villageMap) {
  villageMap[villagerId].groupLeader = groupLeaderId;
  for (auto vilId : villageMap[villagerId].pipesTo) {
    if (villageMap[vilId].groupLeader == Villager::NONE_LEADER)
      setGroupLeader(vilId, groupLeaderId, villageMap);
  }
}
