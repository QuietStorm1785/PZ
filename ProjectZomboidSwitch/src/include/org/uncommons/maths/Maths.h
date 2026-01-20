#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <boost/multiprecision/cpp_int.hpp>
#include <algorithm>
#include <cmath>
#include <mutex>

using BigInteger = boost::multiprecision::cpp_int;

namespace org {
namespace uncommons {
namespace maths {


class Maths {
public:
    static const int MAX_LONG_FACTORIAL = 20;
    static const int CACHE_SIZE = 256;
      // Cache for big factorials
      static std::unordered_map<int, BigInteger> BIG_FACTORIALS;
      static std::mutex BIG_FACTORIALS_MUTEX;

    private Maths() {
   }

    static long factorial(int n) {
      if (n >= 0 && n <= 20) {
    long factorial = 1L;

         for (int i = n; i > 1; i--) {
            factorial *= i;
         }

    return factorial;
      } else {
         throw IllegalArgumentException("Argument must be in the range 0 - 20.");
      }
   }

    static BigInteger bigFactorial(int n) {
      if (n < 0) {
         throw IllegalArgumentException("Argument must greater than or equal to zero.");
      } else {
            BigInteger factorial = 1;
            {
                std::lock_guard<std::mutex> lock(BIG_FACTORIALS_MUTEX);
                if (n < 256) {
                    auto it = BIG_FACTORIALS.find(n);
                    if (it != BIG_FACTORIALS.end()) return it->second;
                }
            }

            for (int i = n; i > 1; --i) {
                factorial *= i;
            }

            if (n < 256) {
                std::lock_guard<std::mutex> lock(BIG_FACTORIALS_MUTEX);
                BIG_FACTORIALS.emplace(n, factorial);
            }

            return factorial;
      }
   }

    static long raiseToPower(int value, int power) {
      if (power < 0) {
         throw IllegalArgumentException("This method does not support negative powers.");
      } else {
    long result = 1L;

         for (int i = 0; i < power; i++) {
            result *= value;
         }

    return result;
      }
   }

      static double log(double base, double arg) {
         return std::log(arg) / std::log(base);
    }

    static bool approxEquals(double value1, double value2, double tolerance) {
      if (!(tolerance < 0.0) && !(tolerance > 1.0)) {
         return std::abs(value1 - value2) <= value1 * tolerance;
      } else {
         throw std::invalid_argument("Tolerance must be between 0 and 1.");
      }
   }

      static int restrictRange(int value, int min, int max) {
         return std::min(std::max(value, min), max);
    }

      static long restrictRange(long value, long min, long max) {
         return std::min(std::max(value, min), max);
    }

      static double restrictRange(double value, double min, double max) {
         return std::min(std::max(value, min), max);
    }

      static long greatestCommonDivisor(long a, long b) {
         a = std::llabs(a);
         b = std::llabs(b);

      while (b != 0L) {
    long temp = b;
         b = a % b;
         a = temp;
      }

    return a;
   }
}
} // namespace maths
} // namespace uncommons
} // namespace org
