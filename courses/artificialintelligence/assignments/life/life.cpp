#include <vector>
#include <iostream>
#include <fstream>

//Functions

void getGridSize(std::vector<bool> &grid);

void setGridSize(std::vector<bool> grid, int x, int y);

std::string getTestFile(std::ifstream &testFile);

std::ifstream loadTestFile(std::vector<bool> &grid);

void printBoard(std::vector<bool> &grid);

int main(){

  std::vector<bool> grid[2];
  std::fstream file;

  //clear the board to start
  grid[0].clear();
  grid[1].clear();

  //get the grid size from the user
  getGridSize(*grid);

  //Get the test file from the user
  //std::string fileName = getTestFile(file);

  //Load in the test file into the grid
  loadTestFile(*grid);

  //prints the board
  printBoard(*grid);

  //TODO: Run all four rules on the board

  //Prints the updated board
  printBoard(*grid);

  //TODO: Compare with output file

  return 0;
};

//The purpose of this function is to get the size of the grid from the user
void getGridSize(std::vector<bool> *grid)
{
  int x = 0;
  int y = 0;

  std::cout << "How big do you want the board to be?" << std::endl;

  while (x <= 1)
  {
    std::cout << "Size of x: ";
    std::cin >> x;

    if(x <= 1)
    {
      std::cout << std::endl << "Please type in a number above 0" << std::endl;
    }
  }

  while (y <= 1)
  {
    std::cout << std::endl << "Size of y: ";
    std::cin >> y;

    if(y <= 1)
    {
      std::cout << std::endl << "Please type in a number above 0" << std::endl;
    }
  }

  setGridSize(*grid, x, y);
}

//The purpose of this function is to set a new size to the grid
void setGridSize(std::vector<bool> *grid, int x, int y)
{
  //Resizes the grid to the new size
  grid[0].resize(x);
  grid[1].resize(y);
}

//The purpose of this function is to get a file name for a test file from the user
std::string getTestFile(std::ifstream file)
{
  std::string testFile;

  //Gets a test from user
  bool validInput = false;
  while (!validInput)
  {
    std::cout << "Would you like to load in a test?" << std::endl;

    char userInput = ' ';
    std::cout <<  "(Y/n): ";
    std::cin >> userInput;

    if(userInput == 'y' || userInput == 'Y')
    {
      validInput = false;
      while(!validInput)
      {

        std::string fileName;

        std::cout << "What is the name of the test file you wish to test?" << std::endl;
        std::cout << "FileName: ";
        std::cin >> fileName;

        file.open(testFile);
        if(file.good())
        {
          validInput = true;
          return fileName;
        }
        else
        {
          std::cout << "Please input a valid test file" << std::endl;
        }
      }

      break;
    }
    else if (userInput == 'n' || userInput == 'N')
    {
      validInput = true;
    }
    else
    {
      std::cout << std::endl << "Please type in a valid input. (Y/n)" << std::endl;
    }
  }
}

//The purpose of this function is to load in a test file into the grid
std::ifstream loadTestFile(std::vector<bool> &grid)
{
  //TODO: Load in the test file to the board
}

void printBoard(std::vector<bool> &grid)
{
  //TODO: Print the board
}



