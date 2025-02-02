#ifndef CAT_h
#define CAT_h

#include "IAgent.h"
#include "functions.h"

struct Cat : public IAgent {

  inline float getDistanceToBorder(Point2D point2D, int32_t sideSize)
  {
    //NOTE: this may not be the correct way to find the distance to the border
    return  sideSize/2 - abs(point2D.y) + sideSize/2 - abs(point2D.x); //TODO: Fix this function
  }

  std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) override{

    //NOTE: Convert the 1d array to 2d using: [width * row + column]
    //NOTE: Convert the 2d array to 1d using: [(i / w)] [(i % w)]

    Point2D exitPoint;

    //Queue used to move through the entire grid
    std::priority_queue<AStarNode> frontier;

    //Map that stores where a point came from. The key is a Point2D, and the data is a Point2D which is where it came from.
    std::unordered_map<Point2D, Point2D> cameFrom;

    AStarNode catPosition(catPos, 0, getDistanceToBorder(catPos, sideSize));
    frontier.push(catPosition);
    cameFrom[catPosition.pos]= catPosition.pos;

    //SECTION: loop to create the cameFrom map
    while(!frontier.empty()) //loops until the frontier is empty
    {
      auto currentPos = frontier.top();
      frontier.pop();

      if(sideSize *  currentPos.pos.y + currentPos.pos.x == sideSize / 2 || sideSize * currentPos.pos.y + currentPos.pos.x == -sideSize / 2)
      {
        exitPoint = currentPos.pos;
        break;
      }

      //SECTION: check neighbors
      std::vector<Point2D> neighbors = currentPos.pos.getNeighbors();
      int i;
      for(i = 0; i < neighbors.size(); i++)
      {
        //check if neighbor is false
        int oneDimensionNeighbor = sideSize * neighbors[i].y + neighbors[i].x;
        if(!world[oneDimensionNeighbor]  && !cameFrom.contains(neighbors[i]) && abs(neighbors[i].x) <= sideSize/2 && abs(neighbors[i].y) <= sideSize/2) //checks if neighbor is available to move to and if it has already been reached
        {
          frontier.emplace(neighbors[i], currentPos.accumulatedCost + 1, getDistanceToBorder(neighbors[i], sideSize)); //adds the neighbor to the frontier
          cameFrom[neighbors[i]] = currentPos.pos; //adds where it came from //BUG: cameFrom is not working properly, and is creating an infinite loop below
        }
      }
    }
    //std::pair<int, int> current = exitPoint;
    std::vector<Point2D> path;

    //SECTION: goes through the frontier until it reaches the cat position
    while(exitPoint != catPosition.pos)
    {
      path.push_back(cameFrom[exitPoint]); //BUG: the path does not go to (0, 0) and loops infinitely
    }
    return std::pair(path[path.size() -1].x, path[path.size() -1].y);
  }

};

#endif
