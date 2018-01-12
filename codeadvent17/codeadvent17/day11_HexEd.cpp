#include "day11_HexEd.h"

#include <cmath>
#include <string>

std::string HexEd::testInput = "day11_input.txt";

struct HexEd::CubeCoord {
public:
  int x{0};
  int y{0};
  int z{0};

  CubeCoord(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  void moveBy(const CubeCoord &cc) {
    this->x += cc.x;
    this->y += cc.y;
    this->z += cc.z;
  }

  unsigned distanceTo(const CubeCoord &cc) {
    auto dist_x = std::abs(this->x - cc.x);
    auto dist_y = std::abs(this->y - cc.y);
    auto dist_z = std::abs(this->z - cc.z);

    return (dist_x + dist_y + dist_z) / 2;
  }
};

std::pair<unsigned, unsigned> HexEd::compute(std::istream &input) {
  std::string direction;
  CubeCoord pos{0, 0, 0};
  const CubeCoord ZERO_POS{0,0,0};
  unsigned max_distance = 0;

  while (std::getline(input, direction, ',')) {
    auto moveBy = getMove(direction);
    pos.moveBy(moveBy);
    auto distance = pos.distanceTo(ZERO_POS);
    if (distance > max_distance)
      max_distance = distance;
  }

  return std::make_pair(pos.distanceTo(ZERO_POS), max_distance);
}

HexEd::CubeCoord HexEd::getMove(const std::string &direction) {
  if (direction == "n")
    return CubeCoord{0, 1, -1};
  if (direction == "ne")
    return CubeCoord{1, 0, -1};
  if (direction == "se")
    return CubeCoord{1, -1, 0};
  if (direction == "s")
    return CubeCoord{0, -1, 1};
  if (direction == "sw")
    return CubeCoord{-1, 0, 1};
  if (direction == "nw")
    return CubeCoord{-1, 1, 0};

  return CubeCoord{0, 0, 0};
}
