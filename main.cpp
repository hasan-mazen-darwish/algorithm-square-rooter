#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "BigNumber.h"

bool isNumberValid(const std::string &str) {
  bool has_only_digits_and_dots = std::all_of(str.begin(), str.end(), [](unsigned char c){
    return std::isdigit(c) || c == '.';
  });

  if(!has_only_digits_and_dots) {return false;}

  int number_of_dots = 0;
  for(char c:str) {
    if (c == '.') {number_of_dots++;}
    if(number_of_dots > 1) {return false;}
  }

  bool hasDotInTheBeginning = str[0] == '.';
  bool hasDotInTheEnd = str[str.length() - 1] == '.';

  if (hasDotInTheBeginning || hasDotInTheEnd) {return false;}
  return true;
}

struct Parts {
  std::vector<uint> whole;
  std::vector<uint> decimal;
};

Parts dissectStringNumber(const std::string &input) {
  Parts parts = {{}, {}};

  size_t dotIndex = input.find('.');
  std::string wholeString = input;
  std::string decimalString = "";
  if(dotIndex != std::string::npos) {
    wholeString = input.substr(0, dotIndex);
    decimalString = input.substr(dotIndex + 1);
  }

  for (int i=0; i<wholeString.length() ; i++) {
    if(wholeString[i] != '0') break;
    else wholeString.pop_back();
  }
  if(wholeString == "") wholeString = "00";

  for (int i=decimalString.length()-1 ; i>=0 ; i--) {
    if(decimalString[i] != '0') break;
    else decimalString.pop_back();
  }

  // Here I am checking if the whole numbers are pairs like 1234 or not like 12345
  bool isWholePartPairs = wholeString.length()%2 == 0;
  // Same for the decimals
  bool isDecimalPartPairs = decimalString.length()%2 == 0;

  if(!isWholePartPairs) {
    parts.whole.push_back(wholeString[0] - '0');
    wholeString = wholeString.substr(1, wholeString.length()-2);
  }
  for(int i=0 ; i<wholeString.length() ; i+=2) {
    parts.whole.push_back(std::stoi(wholeString.substr(i, 2)));
  }

  if(decimalString == "") return parts;

  for(int i=0 ; i<decimalString.length()-1 ; i+=2) {
    parts.decimal.push_back(std::stoi(decimalString.substr(i, 2)));
  }

  if(!isDecimalPartPairs) {
    parts.decimal.push_back(
          10*(decimalString[decimalString.length()-1]-'0')
        );
    decimalString.pop_back();
  }
  
  return parts;
}


unsigned int d;
BigNumber num; // The result of 20*number+d

unsigned int& nextDigit(BigNumber& number, BigNumber& nextColumnNumber) {
  for(d=0; d<10; d++) {
    num = number*20 + d;
    if(num == nextColumnNumber) return d;
  }
  return d; // Just to get rid of the compiler error.
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

  std::cout << "\nGot it. The number you provided is " << input << ".\n";
  std::cout << "Now, please provide the number of digits you want to approximate to:\n";

  unsigned int digits;
  std::cin >> digits;

  if(std::cin.fail()) {
    std::cout << "Invalid digits input!\n";
    return 1;
  }

  std::cout << "\nGot it. So, you're approximating the square root of the number " << input << " to " << digits << " digits.\n";

  Parts parts = dissectStringNumber(input);
  std::vector<uint> whole = parts.whole;
  std::vector<uint> decimal = parts.decimal;

  std::cout << "Please set the name of the output file: (automatically added .txt, don't include it)\n";
  std::string filename;
  std::cin >> filename;
  filename += ".txt";
  std::ofstream outFile(filename);
  if(!outFile.is_open()) {
    std::cout << "\nERROR: failed to open create file "<<filename<<" !\n";
    return 1;
  }
  std::cout << "\nGot it! saving the file into (" << filename << "). \n";
  
  // -----
  // The part that will actually calculate the root:
  // -----

  BigNumber number;
  BigNumber nextColumnNumber; // The resulted number from number*100+nextTwoDigits
  BigNumber bestColumnPrediction; // The number that we subtract nextColumnNumber from
  unsigned int nextDPrediction; // The next digit prediction
  unsigned int nextTwoDigits; // The 2 digits we are working on.

  for(unsigned int i=0; i<digits; i++) {
    // Here we start the loop. So, we need to guess the number
    // d that d*(20*number + d) < (100*number + next 2 digits)^2

    if(i<parts.whole.size()) nextTwoDigits = parts.whole[i];
    else if(
      i>=parts.whole.size()
      && parts.decimal.size() != 0
      && i-parts.whole.size()<parts.decimal.size()
    ) nextTwoDigits = parts.decimal[i-parts.whole.size()];
    else nextTwoDigits = 0;
    nextColumnNumber = number * 100 + nextTwoDigits;
    nextDPrediction = nextDigit(number, nextColumnNumber);
    number *= 10;
    number += nextDPrediction;

    if(i == parts.whole.size()) outFile << ".";
    outFile << nextDPrediction;
    std::cout << "\r ---- Digits written " << i+1 << "/" << digits << " ----";
  }

  std::cout << std::endl;
  return 0;
}
