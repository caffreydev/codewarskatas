#include <iostream>

std::uint32_t lastFibDigit(const std::uint32_t n) {
    if (n < 3) return 1;

    std::uint32_t fib = 1;
    std::uint32_t prev = 1;
    std::uint32_t sum;
    for (std::uint32_t i = 3; i <= n; i++ ) {
        sum = (fib + prev) % 10;
        prev = fib;
        fib = sum;
    }


  return sum;
}

int main ()
{
    std::uint32_t n = 1,b = 1;
      std::cout << lastFibDigit(n) << " should equal: " << b <<  ".  It should work for n of: " << std::to_string(n) << "\n";
      n = 21,         b = 6;
      std::cout << lastFibDigit(n) << " should equal: " << b <<  ".  It should work for n of: " << std::to_string(n) << "\n";
      n = 302,        b = 1;
      std::cout << lastFibDigit(n) << " should equal: " << b <<  ".  It should work for n of: " << std::to_string(n) << "\n";
      n = 4003,       b = 7;
      std::cout << lastFibDigit(n) << " should equal: " << b <<  ".  It should work for n of: " << std::to_string(n) << "\n";
      n = 50004,      b = 8;
      std::cout << lastFibDigit(n) << " should equal: " << b <<  ".  It should work for n of: " << std::to_string(n) << "\n";
      n = 600005,     b = 5;
      std::cout << lastFibDigit(n) << " should equal: " << b <<  ".  It should work for n of: " << std::to_string(n) << "\n";
      n = 7000006,    b = 3;
      std::cout << lastFibDigit(n) << " should equal: " << b <<  ".  It should work for n of: " << std::to_string(n) << "\n";
      n = 80000007,   b = 8;
      std::cout << lastFibDigit(n) << " should equal: " << b <<  ".  It should work for n of: " << std::to_string(n) << "\n";
      n = 900000008,  b = 1;
      std::cout << lastFibDigit(n) << " should equal: " << b <<  ".  It should work for n of: " << std::to_string(n) << "\n";
      n = 1000000009, b = 9;
      std::cout << lastFibDigit(n) << " should equal: " << b <<  ".  It should work for n of: " << std::to_string(n) << "\n";
}