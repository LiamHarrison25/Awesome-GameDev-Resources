//
// Created by Liam on 10/24/2023.
//

#ifndef AWESOME_GAMEDEV_RESOURCES_FUNCTIONS_H
#define AWESOME_GAMEDEV_RESOURCES_FUNCTIONS_H

#include <queue>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>

struct AStarNode;

struct Point2D
{
  int32_t x;
  int32_t y;

  //Constructors:

  Point2D(int32_t x, int32_t y): x(x), y(y) {}
  //converts pair<int, int> to Point2D
  Point2D(const std::pair<int32_t, int32_t>& p): x(p.first), y(p.second) {}
  Point2D() {x = 0; y = 0;}; //default constructor

  //for unordered_set unordered_map
  uint64_t hash() const noexcept { return ((uint64_t)x) << 32 | (uint64_t)y; }

  //Operator overloads:

  //for priority_queue, map, set
  bool operator < (const Point2D& p) const {return x < p.x || (x == p.x && y < p.y);}
  Point2D& operator=(const Point2D& p)= default;
  Point2D& operator=(const std::pair<int32_t, int32_t>& p){
    x = p.first;
    y = p.second;
    return *this;
  }
  bool operator==(const Point2D& p) const { return x == p.x && y == p.y; }
  bool operator!=(const Point2D& p) const{ return x != p.x || y != p.y; }

  //functions for getting the neighbors of the node
  std::vector<Point2D> getNeighbors()
  {

    std::vector<Point2D> neighbors;

    if(y %2 == 0) //if row is even
    {
      neighbors.emplace_back(x - 1, y - 1); //Top left
      neighbors.emplace_back(x, y - 1); //Top right
      neighbors.emplace_back(x + 1, y); // right
      neighbors.emplace_back(x, y + 1); //bottom right
      neighbors.emplace_back(x - 1, y + 1); //bottom left
      neighbors.emplace_back(x - 1, y); //left
    }
    else
    {
      neighbors.emplace_back(x, y - 1); //Top left
      neighbors.emplace_back(x + 1, y - 1); //Top right
      neighbors.emplace_back(x + 1, y); // right
      neighbors.emplace_back(x + 1, y + 1); //bottom right
      neighbors.emplace_back(x, y + 1); //bottom left
      neighbors.emplace_back(x - 1, y); //left
    }

    return neighbors;
  }
};

namespace std {
  template <> struct hash<Point2D>
  {
    std::size_t operator()(const Point2D& p) const noexcept
    {
      return p.hash();
    }
  };
}

struct AStarNode
{
  Point2D pos;
  float accumulatedCost;
  float heuristic;

  //constructors
  AStarNode(const std::pair<int32_t, int32_t>& p) {pos.x = p.first; pos.y = p.second; accumulatedCost = 0; heuristic = 0;}
  AStarNode() { pos.x = 0; pos.y = 0; accumulatedCost = 0; heuristic = 0;}
  AStarNode(const std::pair<int32_t, int32_t>&p, float accumulatedCost , float heuristic) {pos.x = p.first; pos.y = p.second; this->heuristic = heuristic; this->accumulatedCost = accumulatedCost; }
  AStarNode(const Point2D &p, float accumulatedCost, float heuristic) {pos.x = p.x; pos.y = p.y; this->heuristic = heuristic; this->accumulatedCost = accumulatedCost;}

  //for priority queue
  bool operator < (const AStarNode& n) const
  {
    return this->accumulatedCost + this->heuristic > n.accumulatedCost + n.heuristic;
  }
};

#endif  // AWESOME_GAMEDEV_RESOURCES_FUNCTIONS_H
