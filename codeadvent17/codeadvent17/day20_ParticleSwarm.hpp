#pragma once

#include <cmath>
#include <istream>
#include <regex>
#include <stdexcept>
#include <string>
#include <limits>
#include <iostream>
#include <list>
#include <set>
#include <algorithm>

using i64 = long long;

struct Vec3D {
  i64 x;
  i64 y;
  i64 z;

  Vec3D(i64 x, i64 y, i64 z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  Vec3D &add(const Vec3D other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  bool operator==(const Vec3D& other) const {
    return this->x==other.x && this->y==other.y && this->z==other.z;
  }
};
const Vec3D ZERO(0, 0, 0);
i64 manhattanDistace(const Vec3D &pointA, const Vec3D &pointB);

struct Particle {
  Vec3D position;
  Vec3D velocity;
  Vec3D acceleration;

  Particle() : position(0,0,0), velocity(0,0,0), acceleration(0,0,0) {}

  static Particle make(Vec3D &&pos, Vec3D &&vel, Vec3D &&acc) {
    Particle p;
    p.position = pos;
    p.velocity = vel;
    p.acceleration = acc;
    return p;
  }

  bool operator< (const Particle& other) const {
    return manhattanDistace(this->position, ZERO) < manhattanDistace(other.position, ZERO);
  }

  bool operator== (const Particle& other) const {
    return position == other.position;
  }
};

class ParticleSwarm {
public:
  static unsigned compute(std::istream &input);
  static unsigned compute_pt2(std::istream &input);

private:
  static Particle parseParticle(const std::string &particleStr);
  static void runSimulation(Particle &particle, const unsigned ITERATIONS);
  static void resolveCollisions(std::list<Particle> &particles);
};

unsigned ParticleSwarm::compute(std::istream &input) {
  unsigned particleID = 0;
  unsigned currentParticleID = 0;
  i64 minDistance = std::numeric_limits<i64>::max();
  const unsigned ITERATIONS = 100000;

  std::string line;
  while (std::getline(input, line)) {
    auto particle = parseParticle(line);
    runSimulation(particle, ITERATIONS);
    // std::cout << "p<" << particle.position.x << ','
    //                   << particle.position.y << ','
    //                   << particle.position.z << ">\n";
    auto distance = manhattanDistace(particle.position, ZERO);
    if (distance < minDistance || minDistance == -1) {
      minDistance = distance;
      particleID = currentParticleID;
      std::cout << "pID:" << particleID << ", distance: " << distance << '\n';
    }

    currentParticleID++;
  }

  return particleID;
}

Particle ParticleSwarm::parseParticle(const std::string &particleStr) {
  // p=<-317,1413,1507>, v=<19,-102,-108>, a=<1,-3,-3>

  std::regex pieces_regex(
      R"regex(p=<(-?\d+),(-?\d+),(-?\d+)>, v=<(-?\d+),(-?\d+),(-?\d+)>, a=<(-?\d+),(-?\d+),(-?\d+)>)regex");
  std::smatch pieces_match;
  if (std::regex_match(particleStr, pieces_match, pieces_regex)) {
    Vec3D position = Vec3D(std::stoi(pieces_match[1].str()),
                           std::stoi(pieces_match[2].str()),
                           std::stoi(pieces_match[3].str()));
    Vec3D velocity = Vec3D(std::stoi(pieces_match[4].str()),
                           std::stoi(pieces_match[5].str()),
                           std::stoi(pieces_match[6].str()));
    Vec3D acceleration = Vec3D(std::stoi(pieces_match[7].str()),
                               std::stoi(pieces_match[8].str()),
                               std::stoi(pieces_match[9].str()));

    return Particle::make(std::move(position), std::move(velocity),
                          std::move(acceleration));
  } else
    throw std::runtime_error("Failed to parse particle!");
}

void ParticleSwarm::runSimulation(Particle &particle,
                                  const unsigned ITERATIONS) {
  // first simulation must be done manually
  particle.velocity.add(particle.acceleration);

  // sum of arythmetic progression
  auto computation = [ITERATIONS](i64 a1, i64 r) {
    return ((2 * a1 + (ITERATIONS - 1) * r) / 2) * ITERATIONS;
  };

  particle.position.x +=
      computation(particle.velocity.x, particle.acceleration.x);
  particle.position.y +=
      computation(particle.velocity.y, particle.acceleration.y);
  particle.position.z +=
      computation(particle.velocity.z, particle.acceleration.z);
}

i64 manhattanDistace(const Vec3D &pointA, const Vec3D &pointB) {
  return std::abs(pointA.x - pointB.x) + std::abs(pointA.y - pointB.y) +
         std::abs(pointA.z - pointB.z);
}

unsigned ParticleSwarm::compute_pt2(std::istream &input) {
  //auto comparatorFun = [](const Particle& a, const Particle& b){ return a.position == b.position;};
  std::list<Particle> particles;

  std::string line;
  while (std::getline(input, line)) {
    particles.push_back(parseParticle(line));
  }

  auto updateFun = [](Particle &p) {
    p.velocity.add(p.acceleration);
    p.position.add(p.velocity);
  };

  const unsigned ITERATIONS = 10000;
  unsigned iteration = 0;
  while (iteration < ITERATIONS) {
    resolveCollisions(particles);
    for (auto& p : particles)
      updateFun(p);
    
    ++iteration;
  }

  return particles.size();
}

void ParticleSwarm::resolveCollisions(std::list<Particle> &particles) {
  std::list<Particle> toRemove;
  for (auto p : particles)
    if (std::count(particles.begin(), particles.end(), p) > 1)
      toRemove.push_back(p);

  for (auto x : toRemove)
    particles.remove(x);
}
