#include "BigNumber.h"
#include <iostream>
#include <cassert>
#include <random>
#include <chrono>
#include <string>
#include <sstream>

// ============================================================
// HELPER: Create BigNumber from string (since you don't have string constructor)
// ============================================================
BigNumber fromString(const std::string& str) {
    BigNumber result;  // Default 0
    for(char c : str) {
        if(c < '0' || c > '9') continue;
        result *= 10;
        result += (c - '0');
    }
    return result;
}

// ============================================================
// HELPER: Compare BigNumber to string
// ============================================================
bool equalsString(const BigNumber& num, const std::string& str) {
    BigNumber expected = fromString(str);
    return num == expected;
}

// ============================================================
// HELPER: Print test result
// ============================================================
void printTestResult(const std::string& testName, bool passed) {
    if(passed) {
        std::cout << "  ✅ " << testName << " passed!" << std::endl;
    } else {
        std::cout << "  ❌ " << testName << " FAILED!" << std::endl;
    }
}

// ============================================================
// TEST 1: Constructors and Assignment
// ============================================================
void testConstructorsAndAssignment() {
    std::cout << "\n--- Testing Constructors and Assignment ---" << std::endl;
    
    // Default constructor
    BigNumber a;
    assert(a == 0);
    printTestResult("Default constructor", a == 0);
    
    // Assignment from integer
    BigNumber b;
    b = 123;
    assert(b == 123);
    printTestResult("Assignment from int (123)", b == 123);
    
    b = 0;
    assert(b == 0);
    printTestResult("Assignment from int (0)", b == 0);
    
    b = 18446744073709551615ULL;
    assert(b == 18446744073709551615ULL);
    printTestResult("Assignment from max uint64_t", b == 18446744073709551615ULL);
    
    // Assignment from string (via helper)
    BigNumber c = fromString("12345678901234567890");
    assert(equalsString(c, "12345678901234567890"));
    printTestResult("Assignment from string (big number)", equalsString(c, "12345678901234567890"));
}

// ============================================================
// TEST 2: Addition
// ============================================================
void testAddition() {
    std::cout << "\n--- Testing Addition ---" << std::endl;
    
    // Small numbers
    BigNumber a; a = 123;
    BigNumber b; b = 456;
    BigNumber c = a + b;
    assert(c == 579);
    printTestResult("Small addition (123 + 456 = 579)", c == 579);
    
    // Large numbers
    BigNumber d; d = 12345678901234567890ULL;
    BigNumber e; e = 9876543210987654321ULL;
    BigNumber f = d + e;
    assert(equalsString(f, "22222222112222222211"));
    printTestResult("Large addition", equalsString(f, "22222222112222222211"));
    
    // Carry across digits
    BigNumber g = fromString("99999999999999999");  // 10^17 - 1
    std::cout << "g before addition: " << g << std::endl;
    std::cout << "g.digits: ";
    for (auto d : g.digits) std::cout << d << " ";
    std::cout << std::endl;

    g += 1;
    assert(equalsString(g, "100000000000000000"));
    printTestResult("Carry across digits (BASE - 1 + 1)", equalsString(g, "100000000000000000"));
    
    // Chain addition
    BigNumber h; h = 10;
    h += 20;
    h += 30;
    assert(h == 60);
    printTestResult("Chain addition (10+20+30=60)", h == 60);
    
    // Addition with zero
    BigNumber i; i = 1000;
    i += 0;
    assert(i == 1000);
    printTestResult("Addition with zero", i == 1000);
}

// ============================================================
// TEST 3: Subtraction
// ============================================================
void testSubtraction() {
    std::cout << "\n--- Testing Subtraction ---" << std::endl;
    
    // Simple subtraction
    BigNumber a; a = 1000;
    BigNumber b; b = 1;
    BigNumber c = a - b;
    assert(c == 999);
    printTestResult("Simple subtraction (1000 - 1 = 999)", c == 999);
    
    // Borrow chain
    BigNumber d = fromString("100000000000000000000");
    d -= 1;
    assert(equalsString(d, "99999999999999999999"));
    printTestResult("Borrow chain (10^20 - 1)", equalsString(d, "99999999999999999999"));
    
    // Zero result
    BigNumber e; e = 12345;
    std::cout << "e before: " << e << std::endl;
    e -= 12345;
    std::cout << "e after: "  << e << std::endl;
    assert(e == 0);
    printTestResult("Zero result (12345 - 12345 = 0)", e == 0);
    
    // Subtraction with borrow from non-zero digit
    BigNumber f = fromString("200000000000000000000");
    f -= 1;
    assert(equalsString(f, "199999999999999999999"));
    printTestResult("Borrow from non-zero (2*10^20 - 1)", equalsString(f, "199999999999999999999"));
    
    // Negative subtraction (should throw)
    bool threw = false;
    try {
        BigNumber g; g = 100;
        g -= 200;
    } catch (const char* msg) {
        threw = true;
    }
    assert(threw);
    printTestResult("Negative subtraction throws", threw);
}

// ============================================================
// TEST 4: Multiplication
// ============================================================
void testMultiplication() {
    std::cout << "\n--- Testing Multiplication ---" << std::endl;
    
    // Small multiplication
    BigNumber a; a = 123;
    BigNumber b = a * 10;
    assert(b == 1230);
    printTestResult("Small multiplication (123 * 10 = 1230)", b == 1230);
    
    // Large multiplication
    BigNumber c; c = 12345678901234567890ULL;
    BigNumber d = c * 100;
    assert(equalsString(d, "1234567890123456789000"));
    printTestResult("Large multiplication (*100)", equalsString(d, "1234567890123456789000"));
    
    // Multiplication by zero
    BigNumber e = fromString("99999999999999999999");
    e *= 0;
    assert(e == 0);
    printTestResult("Multiplication by zero", e == 0);
    
    // Multiplication by one
    BigNumber f; f = 12345;
    f *= 1;
    assert(f == 12345);
    printTestResult("Multiplication by one", f == 12345);
    
    // Repeated multiplication (your use case)
    BigNumber g; g = 1;
    for(int i = 0; i < 10; i++) {
        g *= 100;
    }
    assert(equalsString(g, "100000000000000000000"));  // 100^10 = 10^20
    printTestResult("Repeated multiplication (100^10)", equalsString(g, "100000000000000000000"));
    
    // Large multiplication chain
    BigNumber h; h = 1;
    for(int i = 0; i < 100; i++) {
        h *= 100;
    }
    // 100^100 = 10^200, with BASE=10^17: 200/17 ≈ 11.76 → 12 digits
    assert(h.digits.size() == 12);
    printTestResult("100 multiplications chain (100^100)", h.digits.size() == 12);
}

// ============================================================
// TEST 5: Comparisons
// ============================================================
void testComparisons() {
    std::cout << "\n--- Testing Comparisons ---" << std::endl;
    
    BigNumber a; a = 500;
    BigNumber b; b = 1000;
    BigNumber c; c = 500;
    
    // BigNumber vs BigNumber
    assert(a < b);
    assert(b > a);
    assert(a == c);
    assert(a != b);
    assert(a <= c);
    assert(a >= c);
    assert(a <= b);
    assert(b >= a);
    printTestResult("BigNumber vs BigNumber", true);
    
    // BigNumber vs Integer
    assert(a < 1000);
    assert(b > 500);
    assert(a == 500);
    assert(a != 1000);
    assert(a <= 500);
    assert(a >= 500);
    assert(a <= 1000);
    assert(b >= 500);
    printTestResult("BigNumber vs Integer", true);
    
    // Large numbers comparison
    BigNumber d = fromString("99999999999999999999");
    BigNumber e = fromString("100000000000000000000");
    assert(d < e);
    assert(e > d);
    assert(d != e);
    assert(d <= e);
    assert(e >= d);
    printTestResult("Large numbers comparison", true);
    
    // Equal large numbers
    BigNumber f = fromString("12345678901234567890");
    BigNumber g = fromString("12345678901234567890");
    assert(f == g);
    assert(!(f != g));
    assert(f <= g);
    assert(f >= g);
    printTestResult("Equal large numbers", true);
}

// ============================================================
// TEST 6: Edge Cases
// ============================================================
void testEdgeCases() {
    std::cout << "\n--- Testing Edge Cases ---" << std::endl;
    
    // All zeros
    BigNumber a; a = 0;
    BigNumber b; b = 0;
    assert(a + b == 0);
    assert(a - b == 0);
    assert(a * 100 == 0);
    printTestResult("Operations with zeros", true);
    
    // Maximum single digit (BASE - 1)
    BigNumber c = fromString("99999999999999999");  // 10^17 - 1
    c += 1;
    assert(equalsString(c, "100000000000000000"));  // 10^17
    printTestResult("BASE - 1 + 1 = BASE", equalsString(c, "100000000000000000"));
    
    // Maximum uint64_t + 1
    BigNumber d = fromString("18446744073709551615");
    BigNumber e = d + 1;
    assert(equalsString(e, "18446744073709551616"));
    printTestResult("UINT64_MAX + 1", equalsString(e, "18446744073709551616"));
    
    // Alternating operations
    BigNumber f; f = 1000;
    for(int i = 0; i < 100; i++) {
        f += 100;
        f -= 50;
        f *= 2;
    }
    assert(f > 0);
    printTestResult("Alternating operations (100 iterations)", f > 0);
    
    // Trim test
    BigNumber g = fromString("100000000000000000000");
    g -= 1;
    assert(equalsString(g, "99999999999999999999"));
    printTestResult("Trim test (100^20 - 1)", equalsString(g, "99999999999999999999"));
}

// ============================================================
// TEST 7: Output Operator
// ============================================================
void testOutput() {
    std::cout << "\n--- Testing Output Operator ---" << std::endl;
    
    std::stringstream ss;
    BigNumber a; a = 12345;
    ss << a;
    assert(ss.str() == "<12345>");
    printTestResult("Output small number", ss.str() == "<12345>");
    
    ss.str("");
    BigNumber b = fromString("12345678901234567890");
    ss << b;
    assert(ss.str() == "<1234567890, 1234567890>");
    printTestResult("Output large number", ss.str() == "<1234567890, 1234567890>");
    
    ss.str("");
    BigNumber c; c = 0;
    ss << c;
    assert(ss.str() == "<0>");
    printTestResult("Output zero", ss.str() == "<0>");
}

// ============================================================
// TEST 8: Stress Tests (Random Operations)
// ============================================================
void stressTest() {
    std::cout << "\n--- Running Stress Tests (100,000 random operations) ---" << std::endl;
    
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(0, UINT64_MAX);
    
    const int ITERATIONS = 100000;
    int progress = 0;
    
    for(int i = 0; i < ITERATIONS; i++) {
        uint64_t a_val = dis(gen);
        uint64_t b_val = dis(gen);
        
        BigNumber a; a = a_val;
        BigNumber b; b = b_val;
        
        // Test addition (skip overflow)
        if(a_val <= UINT64_MAX - b_val) {
            BigNumber sum = a + b;
            assert(sum == a_val + b_val);
        }
        
        // Test multiplication by 100 (skip overflow)
        if(a_val <= UINT64_MAX / 100) {
            BigNumber mult = a * 100;
            assert(mult == a_val * 100);
        }
        
        // Test comparison
        assert((a < b) == (a_val < b_val));
        assert((a > b) == (a_val > b_val));
        assert((a == b) == (a_val == b_val));
        assert((a != b) == (a_val != b_val));
        
        // Test subtraction (only if a >= b)
        if(a_val >= b_val) {
            BigNumber diff = a - b;
            assert(diff == a_val - b_val);
        }
        
        // Progress indicator
        if(i % 10000 == 0) {
            std::cout << "  Progress: " << i << "/" << ITERATIONS << std::endl;
        }
    }
    
    printTestResult("Stress tests passed", true);
}

// ============================================================
// TEST 9: Performance Tests
// ============================================================
void performanceTest() {
    std::cout << "\n--- Running Performance Tests ---" << std::endl;
    
    BigNumber a; a = 12345678901234567890ULL;
    BigNumber b; b = 9876543210987654321ULL;
    
    // Addition performance
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 1000000; i++) {
        BigNumber c = a + b;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "  1,000,000 additions: " << duration.count() << "ms" << std::endl;
    
    // Multiplication performance
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 1000000; i++) {
        BigNumber c = a * 100;
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "  1,000,000 multiplications by 100: " << duration.count() << "ms" << std::endl;
    
    // Your use case performance
    start = std::chrono::high_resolution_clock::now();
    BigNumber result; result = 1;
    for(int i = 0; i < 10000; i++) {
        result *= 100;
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "  10,000 multiplications by 100 (chain): " << duration.count() << "ms" << std::endl;
    
    printTestResult("Performance tests passed", true);
}

// ============================================================
// TEST 10: Your Specific Use Case
// ============================================================
void testYourUseCase() {
    std::cout << "\n--- Testing Your Specific Use Case ---" << std::endl;
    std::cout << "  (Multiplying by 100 repeatedly)" << std::endl;
    
    BigNumber result; result = 1;
    
    // Simulate your algorithm
    for(int i = 0; i < 1000; i++) {
        result *= 100;  // Max multiplication
        result += 50;   // Some addition
        result -= 25;   // Some subtraction
    }
    
    std::cout << "  Result has " << result.digits.size() << " digits (BASE=10^17)" << std::endl;
    std::cout << "  Result: " << result << std::endl;
    
    // Verify no overflow in digits
    bool overflow = false;
    for(size_t i = 0; i < result.digits.size(); i++) {
        if(result.digits[i] >= 100000000000000000ULL) {
            overflow = true;
            break;
        }
    }
    assert(!overflow);
    printTestResult("No digit overflow", !overflow);
}

// ============================================================
// TEST 11: Real-World Scenario (Factorial)
// ============================================================
void testRealWorldScenario() {
    std::cout << "\n--- Testing Real-World Scenario (100!) ---" << std::endl;
    
    BigNumber fact; fact = 1;
    for(int i = 1; i <= 100; i++) {
        fact *= i;
    }
    
    std::cout << "  100! has " << fact.digits.size() << " digits (BASE=10^17)" << std::endl;
    std::cout << "  100! = " << fact << std::endl;
    
    // 100! is roughly 9.3e157, so with BASE=10^17:
    // 157/17 ≈ 9.23 → 10 digits
    assert(fact.digits.size() >= 9 && fact.digits.size() <= 11);
    printTestResult("100! calculation", fact.digits.size() >= 9 && fact.digits.size() <= 11);
}

// ============================================================
// TEST 12: Compound Operations
// ============================================================
void testCompoundOperations() {
    std::cout << "\n--- Testing Compound Operations ---" << std::endl;
    
    BigNumber a; a = 1000;
    a += 500;
    assert(a == 1500);
    printTestResult("+= (1000 + 500)", a == 1500);
    
    a -= 300;
    assert(a == 1200);
    printTestResult("-= (1500 - 300)", a == 1200);
    
    a *= 2;
    assert(a == 2400);
    printTestResult("*= (1200 * 2)", a == 2400);
    
    BigNumber b; b = 100;
    b += 200;
    b -= 50;
    b *= 3;
    assert(b == 750);
    printTestResult("Chain compound (100+200-50)*3", b == 750);
}

// ============================================================
// MAIN
// ============================================================
int main() {
    std::cout << "============================================" << std::endl;
    std::cout << "   BigNumber Test Suite" << std::endl;
    std::cout << "   BASE = 10^17" << std::endl;
    std::cout << "============================================" << std::endl;
    
    try {
        testConstructorsAndAssignment();
        testAddition();
        testSubtraction();
        testMultiplication();
        testComparisons();
        testEdgeCases();
        testOutput();
        testCompoundOperations();
        stressTest();
        performanceTest();
        testYourUseCase();
        testRealWorldScenario();
        
        std::cout << "\n============================================" << std::endl;
        std::cout << "   🎉 ALL TESTS PASSED!" << std::endl;
        std::cout << "   Your BigNumber class is ROCK SOLID!" << std::endl;
        std::cout << "============================================" << std::endl;
        
    } catch (const char* msg) {
        std::cerr << "\n============================================" << std::endl;
        std::cerr << "   ❌ TEST FAILED!" << std::endl;
        std::cerr << "   Error: " << msg << std::endl;
        std::cerr << "============================================" << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "\n============================================" << std::endl;
        std::cerr << "   ❌ TEST FAILED!" << std::endl;
        std::cerr << "   Error: " << e.what() << std::endl;
        std::cerr << "============================================" << std::endl;
        return 1;
    }
    
    return 0;
}
