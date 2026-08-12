#include <iostream>
#include <string>

bool isNumberValid(const std::string &str) {
  bool has_only_digits_and_dots = std::all_of(str.begin(), str.end(), [](unsigned char c){
    return std::isdigit(c) || c == '.';
  });

  if(!has_only_digits_and_dots) {return false;}

  int number_of_dots = 0;
  for(char c:str) {
    if (c == '.') {number_of_dots++;}
  }
  if(number_of_dots > 1) {return false;}

  if (str[0] == '.' || str[str.length() - 1] == '0') {return false;}
  return true;
}

int main() {
  std::cout << "Hello and welcome to the square rooter algorithm!" << std::endl;
  std::cout << "An algorithm completely built with native C++ (No external dependencies)" << std::endl;
  std::cout << "-----------\n\n";
  std::cout << "Please enter the number you want to square root:\n";

  std::string input;
  std::cin >> input;

  if(!isNumberValid(input)) {
    std::cout << "Error! the provided number is not a number. Please provide a real number!\n";
    return 1;
  }
  
  return 0;
}
