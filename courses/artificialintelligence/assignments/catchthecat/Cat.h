#ifndef CAT_h
#define CAT_h
#include "IAgent.h"
#include <queue>

struct Cat : public IAgent {
  std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) override{

    //Convert the 1d array to 2d using: [width * row + column]
    //Convert the 2d array to 1d using: [(i / w) ] [(i % w)]

    std::vector<std::pair<int, int>> neighbors = getNeighbors(catPos);

    //TODO: Change this to hold a struct that stores the location and previous instead
    //first int is location, second is where it came from
    std::queue<std::pair<int, int>> frontier;

    //Stores the neighbors that have been reached
    std::vector<int> reached;

    int oneDimensionCatPosition = sideSize * catPos.second + catPos.first;

    //finds the nearest exit:
    std::pair<int, int> exit = findNearestExit(catPos, world, sideSize);

    int i;
    for(i = 0; i < neighbors.size(); i++)
    {
      //check if neighbor is false
      int oneDimensionNeighbor = sideSize * neighbors[i].second + neighbors[i].first;
      if(!world[oneDimensionNeighbor]) //checks if neighbor is available to move to
      {
        //TODO: check if neighbor has not been reached
        //TODO: check if it has reached the exit. If it has, exit out of the for loop
        frontier.emplace(oneDimensionNeighbor, oneDimensionCatPosition); //adds the neighbor and where it came from to the frontier
        reached.push_back(oneDimensionNeighbor); //adds the neighbor to reached
      }
    }

    std::pair<int, int> current = exit;
    std::pair<int, int> previous;

    //goes through the frontier until it reaches the cat position
    while(current != catPos)
    {
      previous = current;
      std::pair<int, int> next =  frontier.front(); //TODO: will have to change this
      frontier.pop();
      //sets current to the node that it came from
      current = std::pair<int, int>(next.second / sideSize, next.second % sideSize);
    }
    return previous; //returns the previous position which is the next for the cat to move

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

  std::pair<int, int> findNearestExit(std::pair<int, int> catP, const std::vector<bool>& world, int sideSize)
  {
    //TODO: find the nearest exit to the cat

    //get all outside hexagons



    //check which one is the closest to the cat
    //return that one


    return std::pair(0,0); //TODO: change this
  }

};

#endif
