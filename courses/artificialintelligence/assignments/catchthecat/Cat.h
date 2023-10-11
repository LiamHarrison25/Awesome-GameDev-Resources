#ifndef CAT_h
#define CAT_h
#include "IAgent.h"
#include <queue>
#include <map>

struct Cat : public IAgent {
  std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) override{

    //Convert the 1d array to 2d using: [width * row + column]
    //Convert the 2d array to 1d using: [(i / w)] [(i % w)]

    std::pair<int, int> exitPoint;

    std::queue<std::pair<int, int>> frontier;

    //Stores the neighbors that have been reached
    std::vector<int> reached;

    //Map that stores where a point came from. The key is a linearized point, and the data is a 2d point which is where it came from.
    std::map<int, std::pair<int, int>> cameFrom;

    int oneDimensionCatPosition = sideSize * catPos.second + catPos.first;

    frontier.push(catPos);

    //loop to create the cameFrom map
    while(!frontier.empty()) //loops until the frontier is empty
    {
      std::pair currentPos = frontier.front();
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

          frontier.emplace(oneDimensionNeighbor, oneDimensionCatPosition); //adds the neighbor and where it came from to the frontier
          reached.push_back(oneDimensionNeighbor); //adds the neighbor to reached
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

  std::vector<std::pair<int, int>> getNeighbors(std::pair<int, int> catP)
  {

    std::vector<std::pair<int,int>> neighbors;

    if(catP.second %2 == 0) //if row is even
    {
      neighbors.push_back(std::pair(catP.first - 1, catP.second - 1)); //Top left
      neighbors.push_back(std::pair(catP.first, catP.second - 1)); //Top right
      neighbors.push_back(std::pair(catP.first + 1, catP.second)); // right
      neighbors.push_back(std::pair(catP.first, catP.second + 1)); //bottom right
      neighbors.push_back(std::pair(catP.first - 1, catP.second + 1)); //bottom left
      neighbors.push_back(std::pair(catP.first - 1, catP.second)); //left
    }
    else
    {
      neighbors.push_back(std::pair(catP.first, catP.second - 1)); //Top left
      neighbors.push_back(std::pair(catP.first + 1, catP.second - 1)); //Top right
      neighbors.push_back(std::pair(catP.first + 1, catP.second)); // right
      neighbors.push_back(std::pair(catP.first + 1, catP.second + 1)); //bottom right
      neighbors.push_back(std::pair(catP.first, catP.second + 1)); //bottom left
      neighbors.push_back(std::pair(catP.first - 1, catP.second)); //left
    }

    return neighbors;
  }

};

#endif
