#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <cstdint>
#include <ostream>
#include <vector>
class BigNumber {
  private:
    static inline const uint64_t BASE = 100000000000000000ULL; //10^17

    void trim();

  public:
    std::vector<uint64_t> digits;
    BigNumber();

    // Assignment
    BigNumber& operator=(uint64_t integer);

    // Addition
    BigNumber  operator+(uint64_t integer);
    BigNumber  operator+(const BigNumber& other);
    BigNumber& operator+=(uint64_t integer);
    BigNumber& operator+=(const BigNumber& other);

    // Substraction
    BigNumber  operator-(uint64_t integer);
    BigNumber  operator-(const BigNumber& other);
    BigNumber& operator-=(uint64_t integer);
    BigNumber& operator-=(const BigNumber& other);

    // Multiplication
    BigNumber  operator*(unsigned int integer);
    BigNumber& operator*=(unsigned int integer);

    // Comparsion
    bool operator==(uint64_t integer) const;
    bool operator==(const BigNumber& other) const;
    bool operator!=(uint64_t integer) const;
    bool operator!=(const BigNumber& other) const;

    //Comparsion (bigger/smaller)
    bool operator>(uint64_t integer) const;
    bool operator<(uint64_t integer) const;
    bool operator>(const BigNumber& number) const;
    bool operator<(const BigNumber& number) const;
    
    bool operator>=(uint64_t integer) const;
    bool operator<=(uint64_t integer) const;
    bool operator>=(const BigNumber& number) const;
    bool operator<=(const BigNumber& number) const;
    // Output
    friend std::ostream& operator<<(std::ostream& os, const BigNumber& other);
};

#endif
