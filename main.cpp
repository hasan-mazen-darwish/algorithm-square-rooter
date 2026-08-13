#include <iostream>
#include <string>
#include <vector>

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
  
  return 0;
}
