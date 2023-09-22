// add your imports here

#include <fstream>
#include <iostream>
#include <istream>

std::string getTestName();

int getTestNumber();

int xorShift(int number);

int main(){
  // code here

  //Takes in the data from a test file
  int number = getTestNumber();

  //Run xor shift
  int newNumber = xorShift(number);

  //output the new values

  std::cout << std::endl << "The new randomized number is: " << newNumber << std::endl;

}

//The purpose of this function is to get a test name from the user
std::string getTestName()
{
  std::cout << std::endl << "Please enter the name of the test: ";
  std::string userInput;
  std::cin >> userInput;
  return userInput;
}

//The purpose of this function is to load in a test file and output the value from it
int getTestNumber()
{
  std::string userInput;
      bool validTest = false;
  while(!validTest)
  {
    //gets file name from user
    userInput = getTestName();

    //load in from file
    std::fstream file;
    file.open(userInput);

    //check if file opens
    if(file.good())
    {
      std::cout << std::endl << "file loaded successfully" << std::endl;

      //read the files 32-bit number
      int numOutput = file.get();

      validTest = true;

      return numOutput;

    }
  }
}


//The purpose of this function is to take the number and xor shift it to output a sudo-random number
int xorShift(int number)
{
  //TODO: do the xorShift on the number to randomize it



  return 0;
}