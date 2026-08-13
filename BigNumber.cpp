#include "./BigNumber.h"
#include <cstdint>

BigNumber::BigNumber(): digits(0) {}

BigNumber& BigNumber::operator=(uint64_t integer) {
  if(integer == 0) {
    digits = {};
    return *this;
  }

  digits = {};
  while(integer > 0) {
    digits.push_back(integer%BASE);
    integer /= BASE;
  }
  return *this;
}

void BigNumber::trim() {
  while(digits.size() > 1 && digits.back() == 0) {
    digits.pop_back();
  }
}

// ----
// Comparsions with integers
// ----

bool BigNumber::operator>(uint64_t integer) const {
  BigNumber integerToNative;
  integerToNative = integer;
  integerToNative.trim();

  if(digits.size() > integerToNative.digits.size()) return true;
  else if(digits.size() < integerToNative.digits.size()) return false;

  for (size_t i=digits.size(); i>0; --i) {
    if(integerToNative.digits[i-1] > digits[i-1]) return false;
  }

  return false;
}

bool BigNumber::operator<(uint64_t integer) const {
  BigNumber integerToNative;
  integerToNative = integer;
  return !(*this > integerToNative) && *this != integerToNative;
}

bool BigNumber::operator==(uint64_t integer) const {
  BigNumber integerToNative;
  integerToNative = integer;
  integerToNative.trim();
  return integerToNative == *this;
}

bool BigNumber::operator!=(uint64_t integer) const {
  return !(*this == integer);
}

bool BigNumber::operator>=(uint64_t integer) const {
  return (*this > integer) || (*this == integer);
}

bool BigNumber::operator<=(uint64_t integer) const {
  return (*this < integer) || (*this == integer);
}

// ----
// Comparsions with other BigNumber's
// ----

bool BigNumber::operator>(const BigNumber& other) const {
  if(digits.size() > other.digits.size()) return true;
  if(digits.size() < other.digits.size()) return false;

  for(size_t i=digits.size(); i>0; --i) {
    if(digits[i-1] > other.digits[i-1]) return true;
  }
  return false;
}

bool BigNumber::operator==(const BigNumber& other) const {
  return digits == other.digits;
}


bool BigNumber::operator!=(const BigNumber& other) const {
  return !(*this == other);
}

bool BigNumber::operator<(const BigNumber& other) const {
  return !(*this > other) && *this != other;
}

bool BigNumber::operator>=(const BigNumber& other) const {
  return (*this > other) || (*this == other);
}

bool BigNumber::operator<=(const BigNumber& other) const {
  return (*this < other) || (*this == other);
}

// ----
// Addition
// ----

BigNumber& BigNumber::operator+=(const BigNumber& other) {
  if(other == 0) return *this;

  uint64_t carry = 0;
  size_t length = 0;
  if(digits.size() >= other.digits.size()) length = digits.size();
  else length = other.digits.size();
  for (size_t i=0; i<length; i++) {
    if(i >= digits.size()) digits.push_back(carry+other.digits[i]);
    else if(i >= other.digits.size()) {
      digits[i] += carry;
      digits[i] = digits[i] % BASE;
      carry = digits[i]/BASE;
    }
    else {
      uint64_t sum = digits[i] + other.digits[i] + carry;
      digits[i] = sum % BASE;
      carry = sum/BASE;
    }
  }

  trim();
  return *this;
}

BigNumber& BigNumber::operator+=(uint64_t integer) {
  if(integer == 0) return *this;
  BigNumber integerToNative;
  integerToNative = integer;
  *this -= integerToNative;
  return *this;
}

BigNumber BigNumber::operator+(uint64_t integer) {
  BigNumber result = *this;
  result += integer;
  return result;
}

BigNumber BigNumber::operator+(const BigNumber& other) {
  BigNumber result = *this;
  result += other;
  return result;
}

// ----
// Substraction
// ----

BigNumber& BigNumber::operator-=(uint64_t integer) {
  BigNumber integerToNative;
  integerToNative = integer;
  *this -= integerToNative;
  return *this;
}

BigNumber& BigNumber::operator-=(const BigNumber& other) {
  trim();
  if(other == 0) return *this;
  if(*this < other) throw "The number you want to subtract is bigger.";
  if(*this == other) {
    digits = {0};
    return *this;
  }

  bool isBorrowedByBefore = false;
  
  for(size_t i=0; i<digits.size(); i++) {
    if(isBorrowedByBefore) {
      if(digits[i] == 0) {
        // Here we don't cancel out the number borrowing chain.
        // Because if it is zero, it'll be borrowing from the
        // number bfore it and add up the BASE, and at the same
        // time getting substracted by one because it's already
        // borrowed from.
        digits[i] = BASE - 1;
      }
      else {
        // While here we don't need to borrow from the
        // next number because it is already above 0.
        isBorrowedByBefore = false;
        digits[i] -= 1;
      }
    }

    if(i >= other.digits.size()) {
      if(!isBorrowedByBefore) break;
    }
    else if(digits[i] >= other.digits[i]) digits[i] -= other.digits[i];
    else if(digits[i] < other.digits[i]) {
      digits[i] += BASE;
      isBorrowedByBefore = true;
      digits[i] -= other.digits[i];
    }
  }

  trim();

  return *this;
}

BigNumber BigNumber::operator-(uint64_t integer) {
  BigNumber result = *this;
  result -= integer;
  return result;
}

BigNumber BigNumber::operator-(const BigNumber& other) {
  BigNumber result = *this;
  result -= other;
  return result;
}

// ----
// Output function for debugging
// ----

std::ostream& operator<<(std::ostream& os, const BigNumber& number) {
  os << "<";
  for (size_t i=0; i<number.digits.size(); i++) {
    os << number.digits[i];
    if(i != number.digits.size() - 1) os << ", ";
  }
  os << ">";

  return os;
}

// ----
// Multiplication
// ----

BigNumber& BigNumber::operator*=(unsigned int integer) {
  if(integer == 0) {
    digits = {0};
    return *this;
  } else if(integer == 1) return *this;
  
  uint64_t carry = 0;
  for(size_t i=0; i<digits.size(); ++i) {
    uint64_t mul = integer * digits[i];
    uint64_t remainder = (mul + carry) % BASE;
    digits[i] = remainder;
    carry = (mul + carry)/BASE;
  }

  if(carry != 0) {
    digits.push_back(carry);
    carry = 0;
  }

  trim();
  return *this;
}

BigNumber BigNumber::operator*(unsigned int integer) {
  BigNumber number = *this;
  number *= integer;
  return number;
}
