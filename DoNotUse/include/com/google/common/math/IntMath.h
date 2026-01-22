#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/math/IntMath/1.h"
#include "com/google/common/primitives/Ints.h"
#include "java/math/RoundingMode.h"

namespace com {
namespace google {
namespace common {
namespace math {


class IntMath {
public:
    static const int MAX_SIGNED_POWER_OF_TWO = 1073741824;
    static const int MAX_POWER_OF_SQRT2_UNSIGNED = -1257966797;
   static const byte[] maxLog10ForLeadingZeros = new byte[]{9, 9, 9, 8, 8, 8, 7, 7, 7, 6, 6, 6, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 0, 0, 0, 0};
   static const int[] powersOf10 = new int[]{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
   static const int[] halfPowersOf10 = new int[]{3, 31, 316, 3162, 31622, 316227, 3162277, 31622776, 316227766, int.MAX_VALUE};
    static const int FLOOR_SQRT_MAX_INT = 46340;
   private static const int[] factorials = new int[]{1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};
   static int[] biggestBinomials = new int[]{int.MAX_VALUE, int.MAX_VALUE, 65536, 2345, 477, 193, 110, 75, 58, 49, 43, 39, 37, 35, 34, 34, 33};

    static int ceilingPowerOfTwo(int x) {
      MathPreconditions.checkPositive("x", x);
      if (x > 1073741824) {
         throw ArithmeticException("ceilingPowerOfTwo(" + x + ") not representable as an int");
      } else {
         return 1 << -int.numberOfLeadingZeros(x - 1);
      }
   }

    static int floorPowerOfTwo(int x) {
      MathPreconditions.checkPositive("x", x);
      return int.highestOneBit(x);
   }

    static bool isPowerOfTwo(int x) {
      return x > 0 & (x & x - 1) == 0;
   }

    static int lessThanBranchFree(int x, int y) {
      return ~(~(x - y)) >>> 31;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static int log2(int x, RoundingMode mode) {
      MathPreconditions.checkPositive("x", x);
      switch (1.$SwitchMap$java$math$RoundingMode[mode.ordinal()]) {
         case 1:
            MathPreconditions.checkRoundingUnnecessary(isPowerOfTwo(x));
         case 2:
         case 3:
            return 31 - int.numberOfLeadingZeros(x);
         case 4:
         case 5:
            return 32 - int.numberOfLeadingZeros(x - 1);
         case 6:
         case 7:
         case 8:
    int leadingZeros = int.numberOfLeadingZeros(x);
    int cmp = -1257966797 >>> leadingZeros;
    int logFloor = 31 - leadingZeros;
            return logFloor + lessThanBranchFree(cmp, x);
         default:
            throw std::make_unique<AssertionError>();
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static int log10(int x, RoundingMode mode) {
      MathPreconditions.checkPositive("x", x);
    int logFloor = log10Floor(x);
    int floorPow = powersOf10[logFloor];
      switch (1.$SwitchMap$java$math$RoundingMode[mode.ordinal()]) {
         case 1:
            MathPreconditions.checkRoundingUnnecessary(x == floorPow);
         case 2:
         case 3:
    return logFloor;
         case 4:
         case 5:
            return logFloor + lessThanBranchFree(floorPow, x);
         case 6:
         case 7:
         case 8:
            return logFloor + lessThanBranchFree(halfPowersOf10[logFloor], x);
         default:
            throw std::make_unique<AssertionError>();
      }
   }

    static int log10Floor(int x) {
    int y = maxLog10ForLeadingZeros[int.numberOfLeadingZeros(x)];
      return y - lessThanBranchFree(x, powersOf10[y]);
   }

    static int pow(int b, int k) {
      MathPreconditions.checkNonNegative("exponent", k);
      switch (b) {
         case -2:
            if (k < 32) {
               return (k & 1) == 0 ? 1 << k : -(1 << k);
            }

    return 0;
         case -1:
            return (k & 1) == 0 ? 1 : -1;
         case 0:
    return k = = 0 ? 1 : 0;
         case 1:
    return 1;
         case 2:
            return k < 32 ? 1 << k : 0;
         default:
    int accum = 1;

            while (true) {
               switch (k) {
                  case 0:
    return accum;
                  case 1:
                     return b * accum;
               }

               accum *= (k & 1) == 0 ? 1 : b;
               b *= b;
               k >>= 1;
            }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static int sqrt(int x, RoundingMode mode) {
      MathPreconditions.checkNonNegative("x", x);
    int sqrtFloor = sqrtFloor(x);
      switch (1.$SwitchMap$java$math$RoundingMode[mode.ordinal()]) {
         case 1:
            MathPreconditions.checkRoundingUnnecessary(sqrtFloor * sqrtFloor == x);
         case 2:
         case 3:
    return sqrtFloor;
         case 4:
         case 5:
            return sqrtFloor + lessThanBranchFree(sqrtFloor * sqrtFloor, x);
         case 6:
         case 7:
         case 8:
    int halfSquare = sqrtFloor * sqrtFloor + sqrtFloor;
            return sqrtFloor + lessThanBranchFree(halfSquare, x);
         default:
            throw std::make_unique<AssertionError>();
      }
   }

    static int sqrtFloor(int x) {
      return (int)Math.sqrt(x);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static int divide(int p, int q, RoundingMode mode) {
      Preconditions.checkNotNull(mode);
      if (q == 0) {
         throw ArithmeticException("/ by zero");
      } else {
    int div = p / q;
    int rem = p - q * div;
         if (rem == 0) {
    return div;
         } else {
    int signum = 1 | (p ^ q) >> 31;
    bool increment;
            switch (1.$SwitchMap$java$math$RoundingMode[mode.ordinal()]) {
               case 1:
                  MathPreconditions.checkRoundingUnnecessary(rem == 0);
               case 2:
                  increment = false;
                  break;
               case 3:
                  increment = signum < 0;
                  break;
               case 4:
                  increment = true;
                  break;
               case 5:
                  increment = signum > 0;
                  break;
               case 6:
               case 7:
               case 8:
    int absRem = Math.abs(rem);
    int cmpRemToHalfDivisor = absRem - (Math.abs(q) - absRem);
                  if (cmpRemToHalfDivisor == 0) {
                     increment = mode == RoundingMode.HALF_UP || mode == RoundingMode.HALF_EVEN & (div & 1) != 0;
                  } else {
                     increment = cmpRemToHalfDivisor > 0;
                  }
                  break;
               default:
                  throw std::make_unique<AssertionError>();
            }

            return increment ? div + signum : div;
         }
      }
   }

    static int mod(int x, int m) {
      if (m <= 0) {
         throw ArithmeticException("Modulus " + m + " must be > 0");
      } else {
    int result = x % m;
         return result >= 0 ? result : result + m;
      }
   }

    static int gcd(int a, int b) {
      MathPreconditions.checkNonNegative("a", a);
      MathPreconditions.checkNonNegative("b", b);
      if (a == 0) {
    return b;
      } else if (b == 0) {
    return a;
      } else {
    int aTwos = int.numberOfTrailingZeros(a);
         a >>= aTwos;
    int bTwos = int.numberOfTrailingZeros(b);
         b >>= bTwos;

         while (a != b) {
    int delta = a - b;
    int minDeltaOrZero = delta & delta >> 31;
            a = delta - minDeltaOrZero - minDeltaOrZero;
            b += minDeltaOrZero;
            a >>= int.numberOfTrailingZeros(a);
         }

         return a << Math.min(aTwos, bTwos);
      }
   }

    static int checkedAdd(int a, int b) {
    long result = (long)a + b;
      MathPreconditions.checkNoOverflow(result == (int)result);
      return (int)result;
   }

    static int checkedSubtract(int a, int b) {
    long result = (long)a - b;
      MathPreconditions.checkNoOverflow(result == (int)result);
      return (int)result;
   }

    static int checkedMultiply(int a, int b) {
    long result = (long)a * b;
      MathPreconditions.checkNoOverflow(result == (int)result);
      return (int)result;
   }

    static int checkedPow(int b, int k) {
      MathPreconditions.checkNonNegative("exponent", k);
      switch (b) {
         case -2:
            MathPreconditions.checkNoOverflow(k < 32);
            return (k & 1) == 0 ? 1 << k : -1 << k;
         case -1:
            return (k & 1) == 0 ? 1 : -1;
         case 0:
    return k = = 0 ? 1 : 0;
         case 1:
    return 1;
         case 2:
            MathPreconditions.checkNoOverflow(k < 31);
            return 1 << k;
         default:
    int accum = 1;

            while (true) {
               switch (k) {
                  case 0:
    return accum;
                  case 1:
    return checkedMultiply();
               }

               if ((k & 1) != 0) {
                  accum = checkedMultiply(accum, b);
               }

               k >>= 1;
               if (k > 0) {
                  MathPreconditions.checkNoOverflow(-46340 <= b & b <= 46340);
                  b *= b;
               }
            }
      }
   }

    static int saturatedAdd(int a, int b) {
      return Ints.saturatedCast((long)a + b);
   }

    static int saturatedSubtract(int a, int b) {
      return Ints.saturatedCast((long)a - b);
   }

    static int saturatedMultiply(int a, int b) {
      return Ints.saturatedCast((long)a * b);
   }

    static int saturatedPow(int b, int k) {
      MathPreconditions.checkNonNegative("exponent", k);
      switch (b) {
         case -2:
            if (k >= 32) {
               return int.MAX_VALUE + (k & 1);
            }

            return (k & 1) == 0 ? 1 << k : -1 << k;
         case -1:
            return (k & 1) == 0 ? 1 : -1;
         case 0:
    return k = = 0 ? 1 : 0;
         case 1:
    return 1;
         case 2:
            if (k >= 31) {
               return int.MAX_VALUE;
            }

            return 1 << k;
         default:
    int accum = 1;
    int limit = int.MAX_VALUE + (b >>> 31 & k & 1);

            while (true) {
               switch (k) {
                  case 0:
    return accum;
                  case 1:
    return saturatedMultiply();
               }

               if ((k & 1) != 0) {
                  accum = saturatedMultiply(accum, b);
               }

               k >>= 1;
               if (k > 0) {
                  if (-46340 > b | b > 46340) {
    return limit;
                  }

                  b *= b;
               }
            }
      }
   }

    static int factorial(int n) {
      MathPreconditions.checkNonNegative("n", n);
      return n < factorials.length ? factorials[n] : int.MAX_VALUE;
   }

    static int binomial(int n, int k) {
      MathPreconditions.checkNonNegative("n", n);
      MathPreconditions.checkNonNegative("k", k);
      Preconditions.checkArgument(k <= n, "k (%s) > n (%s)", k, n);
      if (k > n >> 1) {
         k = n - k;
      }

      if (k < biggestBinomials.length && n <= biggestBinomials[k]) {
         switch (k) {
            case 0:
    return 1;
            case 1:
    return n;
            default:
    long result = 1L;

               for (int i = 0; i < k; i++) {
                  result *= n - i;
                  result /= i + 1;
               }

               return (int)result;
         }
      } else {
         return int.MAX_VALUE;
      }
   }

    static int mean(int x, int y) {
      return (x & y) + ((x ^ y) >> 1);
   }

    static bool isPrime(int n) {
      return LongMath.isPrime(n);
   }

    private IntMath() {
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
