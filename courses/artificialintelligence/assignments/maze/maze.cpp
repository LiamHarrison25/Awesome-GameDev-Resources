// add your imports here
#include <vector>

struct Point2D
{

};

struct Direction
{

};

int main(){
  // code here
  int steps;

  Point2D limits;




}

void breakWall(Point2D p, Direction d)
{
  switch(d)
  {
    case Direction::Up:
      horizontals[limits.x*p.y +p.x] = false;
      break;
    case Direction::Right:
      verticals[limits.x*p.y+p.x+1] = false;
      break;
    case Direction::Down:
      horizontals[limits.x * (p.y+1)+p.x] = false;
      break;
    case Direction::Left:
      verticals[limits.x*p.y+p.x] = false;
      break;
  }
}

bool isThereWall(Point2D p, Direction d)
{
  switch(d)
  {
    case Direction::Up:
      return horizontals[limits.x*p.y +p.x] = false;
      break;
    case Direction::Right:
      return verticals[limits.x*p.y+p.x+1] = false;
      break;
    case Direction::Down:
      return horizontals[limits.x * (p.y+1)+p.x] = false;
      break;
    case Direction::Left:
      return verticals[limits.x*p.y+p.x] = false;
      break;
  }
}

bool getVisited(Point2D p)
{
  return visited[limits.x*p.y + p.x];
}

bool setVisited(Point2D p, bool state)
{
  visited[limits.x*p.y + p.x] = state;
}

std::vector<Point2D> getVisitables(Point2D p)
{

}