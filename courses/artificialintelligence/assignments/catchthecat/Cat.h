#ifndef CAT_h
#define CAT_h
#include "IAgent.h"
#include <queue>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>


struct Point2D
{
  int32_t x;
  int32_t y;

  //Constructors
  Point2D(int32_t x, int32_t y): x(x), y(y) {}
  //converts pair<int, int> to Point2D
  Point2D(const std::pair<int32_t, int32_t>& p): x(p.first), y(p.second) {}
  Point2D() {x = 0; y = 0;}; //default constructor

  //for unordered_set unordered_map
  uint64_t hash() const noexcept { return ((uint64_t)x) << 32 | (uint64_t)y; }

  //for priority_queue, map, set
  bool operator < (const Point2D& p) const {return x < p.x || (x == p.x && y < p.y); }



  //add operators, accessor, NE(), etc

  //functions for getting the neighbors of the node
  std::vector<std::pair<int, int>> getNeighbors()
  {

    std::vector<std::pair<int,int>> neighbors;

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

  //for priority queue
  bool operator < (const AStarNode& n) const
  {
    return this->accumulatedCost + this->heuristic < n.accumulatedCost + n.heuristic;
  }
};

struct Cat : public IAgent {
  std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) override{

    //Convert the 1d array to 2d using: [width * row + column]
    //Convert the 2d array to 1d using: [(i / w)] [(i % w)]

    std::pair<int, int> exitPoint;

    //Queue used to move through the entire grid
    std::queue<AStarNode> frontier;

    //Stores the points that are currently in the frontier
    std::unordered_set<int> frontierSet;

    //Stores the neighbors that have been reached
    std::unordered_set<int> reached; //stores the point by linearizing the std pair

    //Map that stores where a point came from. The key is a linearized point, and the data is a 2d point which is where it came from.
    std::unordered_map<int, AStarNode> cameFrom;

    int oneDimensionCatPosition = sideSize * catPos.second + catPos.first;

    AStarNode catPosition(catPos);

    frontier.push(catPos);

    //loop to create the cameFrom map
    while(!frontier.empty()) //loops until the frontier is empty
    {
      auto currentPos = frontier.front();
      frontier.pop();

      if(sideSize *  currentPos.second + currentPos.first == sideSize / 2 || sideSize * currentPos.second + currentPos.first == -sideSize / 2)
      {
        exitPoint = currentPos;
        break;
      }

      //check neighbors
      std::vector<std::pair<int, int>> neighbors = getNeighbors(currentPos);
      int i;
      for(i = 0; i < neighbors.size(); i++)
      {
        //check if neighbor is false
        int oneDimensionNeighbor = sideSize * neighbors[i].second + neighbors[i].first;
        if(!world[oneDimensionNeighbor]) //checks if neighbor is available to move to
        {
          //TODO: check if neighbor has not been reached
          //TODO: check if neighbor is in frontier set

          frontier.emplace(oneDimensionNeighbor, oneDimensionCatPosition); //adds the neighbor and where it came from to the frontier
          frontierSet.insert(oneDimensionNeighbor);
          reached.insert(oneDimensionNeighbor); //adds the neighbor to reached
          cameFrom.emplace(oneDimensionNeighbor, currentPos); //adds where it came from
        }
      }

    }

    std::pair<int, int> current = exitPoint;
    std::vector<std::pair<int, int>> path;

    //goes through the frontier until it reaches the cat position
    while(current != catPos)
    {
      current = cameFrom[sideSize * current.first + current.second];
      path.push_back(current);
    }

    return path[path.size() -2];
  }

};

//template <typename T, typename priorityT>
//struct priority_queue
//{
//  typedef std::pair< priorityT, T> element;
//  std:: priority_queue<element, std::vector<element>, std::greater<element>> elements;
//
//  //The purpose of this function is to check if the priority queue is empty
//  [[nodiscard]] bool isEmpty() const
//  {
//    return elements.empty();
//  }
//
//  //The purpose of this function is to push an item into the priority queue
//  void push(T item, priorityT priorityT1)
//  {
//    elements.emplace(priorityT1, item);
//  }
//
//  //The purpose of this function is to pop the best item, and return it
//  T pop()
//  {
//    T bestItem = elements.top().second;
//    elements.pop();
//    return bestItem;
//  }
//
//};

#endif
