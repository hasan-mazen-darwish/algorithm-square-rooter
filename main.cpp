#include <iostream>
#include <string>

bool isNumberValid(const std::string &str) {
  return std::all_of(str.begin(), str.end(), [](unsigned char c){
    return std::isdigit(c) || c == '.';
  });
}

int main() {
  return 1;
}
