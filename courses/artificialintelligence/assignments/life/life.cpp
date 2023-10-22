#include <vector>
#include <iostream>

//Convert the 1d array to 2d using: [width * row + column]
//Convert the 2d array to 1d using: [(i / w)] [(i % w)]

//Functions

std::vector<bool> readBoard(const int &columns, const int &rows);

void printBoard(const std::vector<bool> &grid, const int &columns, const int &rows);

void runRules(std::vector<bool> &grid, const int &columns, const int &rows);

int numNeighbors(const int &cell, const std::vector<bool> &grid, const int &columns, const int &rows);

int main(){

  std::vector<bool> grid;

  //clear the board to start
  grid.clear();

  int columns, rows, turns;

  //Takes in input from tests
  std::cin >> columns >> rows >> turns;
  grid = readBoard(columns, rows); //creates the board from the test file

  int i;
  for(i = 0; i < turns; i++) //loops through the specified amount of turns
  {
    runRules(grid, columns, rows);

    //Prints the updated board
    printBoard(grid, columns, rows);
  }

  return 0;
};

// The purpose of this function is to create a board based off the input from the test files.
std::vector<bool> readBoard(int columns, int rows) {
  std::vector<bool> board;
  board.reserve(columns * rows);

  char c;  // used to temporarily store the characters coming in from the tests
  int i, j;
  for (i = 0; i < columns * rows; i++)
  {
    std::cin >> c;
    switch (c)
    {
      case '.':
        board.push_back(false); //pushes an empty space (life does not exist there)
        break;
      case '#':
        board.push_back(true); //pushes a filled space (life exists there)
        break;
      default:
        i--; // go back one
        break;
    }
  }
  return board;
}

// The purpose of this function is to print out the entire board
void printBoard(const std::vector<bool> &grid, int columns, int rows)
{
  int x, y;
  for(x = 0; x < columns; x++)
  {
    for(y = 0; y < rows; y++)
    {
      std::cout << (grid[x * (columns * rows) + y] ? '#' : '.');
    }
    std::cout << std::endl;
  }
}

// The purpose of this function is to run through the grid and perform the rules of the game of life
void runRules(std::vector<bool> &grid, int columns, int rows)
{
  /*
   * Rules:
  Any live cell with fewer than two live neighbours dies, as if by underpopulation.
  Any live cell with two or three live neighbours lives on to the next generation.
  Any live cell with more than three live neighbours dies, as if by overpopulation.
  Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
   */

  //goes through each cell in the grid, and check the rules against it
  int x, y, neighbors;
  for(x = 0; x < columns; x++)
  {
    for(y = 0; y < rows; y++)
    {
        neighbors = numNeighbors(columns*rows * x + y, grid, columns, rows); //gets the amount of neighbors for the current cell

        if(grid[columns*rows * x + y]) //checks if the cell is alive
        {
          switch (neighbors)
          {
            case 2: //nothing needed here because 2 and 3 lead to the same outcome
            case 3: grid[columns*rows * x + y] = true;
              break;
            default: grid[columns*rows * x + y] = false; //any neighbor amount that is not 2 or 3 kills the cell
              break;
          }
        }
        else if(neighbors == 3) //checks if the dead cell has exactly 3 live neighbors
        {
          grid[columns*rows * x + y] = true;
        }
    }
  }
}

//The purpose of this function is to check how many neighbors of a cell are alive
int numNeighbors(int cell, const std::vector<bool> &grid, int columns, int rows)
{
  //TODO: check the amount of neighbors the current cell has and return it

  std::pair<int, int> p;
  p.first =

  if(p.y %2 == 0) //if even row
  {
    return
        w.Get(p + Point2D(-1, -1)) + //Top Left
        w.Get(p + Point2D(0, -1)) + //Top Right
        w.Get(p + Point2D(-1, 0)) + //Left
        w.Get(p + Point2D(1, 0)) +
        w.Get(p + Point2D(-1, 1)) +
        w.Get(p + Point2D(0, 1));
  }
  else
  {
    return
        w.Get(p + Point2D(0, -1)) + //Top Left
        w.Get(p + Point2D(1, -1)) + //Top Right
        w.Get(p + Point2D(-1, 0)) + //Left
        w.Get(p + Point2D(1, 0)) +
        w.Get(p + Point2D(0, 1)) +
        w.Get(p + Point2D(1, 1));
  }

  return 0; //TODO: change this
}

bool isValidPoint(std::pair<int, int> point, int columns, int rows)
{
  if(point.first < 0) point.first += rows;
  if(point.first >= rows) point.first %= rows;
  if(point.second < 0) point.second += columns;
  if(point.second >= columns) point.second %= columns;
  auto index = point.second * columns * rows + point.first;
  auto squareGrid = columns * rows;
  if(index >= squareGrid) index %= squareGrid;
  return
}
