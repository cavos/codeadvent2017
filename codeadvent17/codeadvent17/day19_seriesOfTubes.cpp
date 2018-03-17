#include "day19_SeriesOfTubes.h"

#include <boost/optional.hpp>
#include <iostream>
#include <vector>

struct Vec2D {
  int x;
  int y;

  Vec2D(const Vec2D &other) = default;

  Vec2D(int x, int y) {
    this->x = x;
    this->y = y;
  }

  void moveBy(const Vec2D &m) {
    x += m.x;
    y += m.y;
  }

  bool operator==(const Vec2D &other) {
    return this->x == other.x && this->y == other.y;
  }

  bool operator!=(const Vec2D &other) { return !(*this == other); }

  Vec2D neg() const {
    return Vec2D(-x, -y);
  }
};

class Labirynth {
public:
  Labirynth() = default;

  bool inBounds(const Vec2D &pos) {
    bool x = (0 <= pos.x && pos.x < (int)data_.front().size());
    bool y = (0 <= pos.y && pos.y < (int)data_.size());
    return x && y;
  }

  Vec2D getEntryPointPos() const {
    Vec2D pos(0, 0);
    pos.x = data_.front().find('|');
    return pos;
  }

  boost::optional<char> at(const Vec2D &pos) {
    if (!inBounds(pos))
      return boost::optional<char>();
    return boost::optional<char>(data_[pos.y][pos.x]);
  }

  void readInput(std::istream &input) {
    data_.reserve(204);
    std::string line;
    while (std::getline(input, line)) {
      data_.emplace_back(line);
    }
  }

  void printDebug(const Vec2D &pos) {
    for (int y = pos.y - 4; y <= pos.y + 4; ++y) {
      for (int x = pos.x - 4; x <= pos.x + 4; ++x) {
        auto c = at(Vec2D(x, y));
        if (pos.x == x && pos.y == y)
          std::cout << '@';
        else if (c)
          std::cout << c.get();
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  }

private:
  std::vector<std::string> data_;
};

static const Vec2D DIR_N(0, -1);
static const Vec2D DIR_S(0, 1);
static const Vec2D DIR_W(-1, 0);
static const Vec2D DIR_E(1, 0);
static const std::vector<Vec2D> DIRECTIONS{DIR_N, DIR_S, DIR_W, DIR_E};

std::string SeriesOfTubes::compute(std::istream &input) {
  Labirynth labirynth;
  labirynth.readInput(input);

  Vec2D pos = labirynth.getEntryPointPos();
  Vec2D direction = DIR_S;

  auto getDirection = [&]() {
    std::cout << "get dir: ";
    Vec2D nextDir(direction);
    for (auto d : DIRECTIONS) {
      if (d != direction.neg()) {
        auto tile = labirynth.at(Vec2D(pos.x + d.x, pos.y + d.y));
        if (tile) {
          std::cout << "t[" << d.x << ',' << d.y << "]:'"  << tile.get() << "',";
          if ((d == DIR_W || d == DIR_E) && tile.get() == '-') {            
            std::cout << "-->" << d.x << ',' << d.y << '\n';
            nextDir = d;
            break;
          } else if (tile == '|') {
            std::cout << "---->" << d.x << ',' << d.y << '\n';
            nextDir = d;
            break;
          }
        }
        else
          std::cout << "outb,";
      }
    }
    
    return nextDir;
  };

  std::string pathWord;
  unsigned stepsTaken = 0;
  while (labirynth.inBounds(pos)) {
    //std::cout << "at: " << pos.x << ',' << pos.y << " (" << pathWord << ")\n";
    //labirynth.printDebug(pos);
    auto c = labirynth.at(pos);
    if (isalpha(c.get()))
      pathWord += c.get();
    else if (c == '+')
      direction = getDirection();
    pos.moveBy(direction);
    ++stepsTaken;
    //std::cin.ignore();
  }

  std::cout << "day19 - steps taken: " << stepsTaken-1 << '\n'; // -1 -> last step is out of bounds
  return pathWord;
}
