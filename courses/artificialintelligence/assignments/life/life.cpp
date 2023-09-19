#include <vector>
#include <iostream>

//Functions

std::string getTestFile();


int main(){

  int x = 0;
  int y = 0;

  std::vector<bool> grid[2];

  //clear the board to start
  grid[0].clear();
  grid[1].clear();

  //uses console input and output

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

  //Resizes the grid to the new size
  grid[0].resize(x);
  grid[1].resize(y);

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
      validInput = true;
      std::string testFile = getTestFile();
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

  //TODO: Load in the test file to the board

  //TODO: Print the board

  //prints the board

  //printBoard({columns, lines});

  //TODO: Run all four rules on the board

  //TODO: Print the updated board

  //TODO: Compare with output file

  return 0;
};

std::string getTestFile()
{
  bool validInput = false;
  std::string fileName;
  while(!validInput)
  {
    std::cout << "What is the name of the test file you wish to test?" << std::endl;
    std::cout << "FileName: ";
    std::cin >> fileName;

    //TODO; determine if it is valid or not
    validInput = true; //temporary
  }
  return fileName;
}