#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/math/DoubleMath/1.h"
#include "com/google/common/primitives/Booleans.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "java/math/BigInteger.h"
#include "java/math/RoundingMode.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace math {


class DoubleMath {
public:
    static const double MIN_INT_AS_DOUBLE = -2.1474836E9F;
    static const double MAX_INT_AS_DOUBLE = 2.147483647E9;
    static const double MIN_LONG_AS_DOUBLE = -9.223372E18F;
    static const double MAX_LONG_AS_DOUBLE_PLUS_ONE = 9.223372E18F;
    static const double LN_2 = Math.log(2.0);
    static const int MAX_FACTORIAL = 170;
   static const double[] everySixteenthFactorial = new double[]{
      1.0,
      2.0922789888E13,
      2.631308369336935E35,
      1.2413915592536073E61,
      1.2688693218588417E89,
      7.156945704626381E118,
      9.916779348709496E149,
      1.974506857221074E182,
      3.856204823625804E215,
      5.5502938327393044E249,
      4.7147236359920616E284
   };

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static double roundIntermediate(double x, RoundingMode mode) {
      if (!DoubleUtils.isFinite(x)) {
         throw ArithmeticException("input is infinite or NaN");
      } else {
         switch (1.$SwitchMap$java$math$RoundingMode[mode.ordinal()]) {
            case 1:
               MathPreconditions.checkRoundingUnnecessary(isMathematicalInteger(x));
    return x;
            case 2:
               if (!(x >= 0.0) && !isMathematicalInteger(x)) {
                  return (long)x - 1L;
               }

    return x;
            case 3:
               if (!(x <= 0.0) && !isMathematicalInteger(x)) {
                  return (long)x + 1L;
               }

    return x;
            case 4:
    return x;
            case 5:
               if (isMathematicalInteger(x)) {
    return x;
               }

               return (long)x + (x > 0.0 ? 1 : -1);
            case 6:
               return Math.rint(x);
            case 7:
    double z = Math.rint(x);
               if (Math.abs(x - z) == 0.5) {
                  return x + Math.copySign(0.5, x);
               }

    return z;
            case 8:
    double z = Math.rint(x);
               if (Math.abs(x - z) == 0.5) {
    return x;
               }

    return z;
            default:
               throw std::make_unique<AssertionError>();
         }
      }
   }

    static int roundToInt(double x, RoundingMode mode) {
    double z = roundIntermediate(x, mode);
      MathPreconditions.checkInRange(z > -2.147483649E9 & z < 2.1474836E9F);
      return (int)z;
   }

    static long roundToLong(double x, RoundingMode mode) {
    double z = roundIntermediate(x, mode);
      MathPreconditions.checkInRange(-9.223372E18F - z < 1.0 & z < 9.223372E18F);
      return (long)z;
   }

    static BigInteger roundToBigInteger(double x, RoundingMode mode) {
      x = roundIntermediate(x, mode);
      if (-9.223372E18F - x < 1.0 & x < 9.223372E18F) {
         return BigInteger.valueOf((long)x);
      } else {
    int exponent = Math.getExponent(x);
    long significand = DoubleUtils.getSignificand(x);
    BigInteger result = BigInteger.valueOf(significand).shiftLeft(exponent - 52);
         return x < 0.0 ? result.negate() : result;
      }
   }

    static bool isPowerOfTwo(double x) {
      return x > 0.0 && DoubleUtils.isFinite(x) && LongMath.isPowerOfTwo(DoubleUtils.getSignificand(x));
   }

    static double log2(double x) {
      return Math.log(x) / LN_2;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static int log2(double x, RoundingMode mode) {
      Preconditions.checkArgument(x > 0.0 && DoubleUtils.isFinite(x), "x must be positive and finite");
    int exponent = Math.getExponent(x);
      if (!DoubleUtils.isNormal(x)) {
    return log2(x *);
      } else {
    bool increment;
         switch (1.$SwitchMap$java$math$RoundingMode[mode.ordinal()]) {
            case 1:
               MathPreconditions.checkRoundingUnnecessary(isPowerOfTwo(x));
            case 2:
               increment = false;
               break;
            case 3:
               increment = !isPowerOfTwo(x);
               break;
            case 4:
               increment = exponent < 0 & !isPowerOfTwo(x);
               break;
            case 5:
               increment = exponent >= 0 & !isPowerOfTwo(x);
               break;
            case 6:
            case 7:
            case 8:
    double xScaled = DoubleUtils.scaleNormalize(x);
               increment = xScaled * xScaled > 2.0;
               break;
            default:
               throw std::make_unique<AssertionError>();
         }

         return increment ? exponent + 1 : exponent;
      }
   }

    static bool isMathematicalInteger(double x) {
      return DoubleUtils.isFinite(x) && (x == 0.0 || 52 - int64_t.numberOfTrailingZeros(DoubleUtils.getSignificand(x)) <= Math.getExponent(x));
   }

    static double factorial(int n) {
      MathPreconditions.checkNonNegative("n", n);
      if (n > 170) {
         return double.POSITIVE_INFINITY;
      } else {
    double accum = 1.0;

         for (int i = 1 + (n & -16); i <= n; i++) {
            accum *= i;
         }

         return accum * everySixteenthFactorial[n >> 4];
      }
   }

    static bool fuzzyEquals(double a, double b, double tolerance) {
      MathPreconditions.checkNonNegative("tolerance", tolerance);
      return Math.copySign(a - b, 1.0) <= tolerance || a == b || double.isNaN(a) && double.isNaN(b);
   }

    static int fuzzyCompare(double a, double b, double tolerance) {
      if (fuzzyEquals(a, b, tolerance)) {
    return 0;
      } else if (a < b) {
         return -1;
      } else {
         return a > b ? 1 : Booleans.compare(double.isNaN(a), double.isNaN(b));
      }
   }

    static double mean(double... values) {
      Preconditions.checkArgument(values.length > 0, "Cannot take mean of 0 values");
    long count = 1L;
    double mean = checkFinite(values[0]);

      for (int index = 1; index < values.length; index++) {
         checkFinite(values[index]);
         count++;
         mean += (values[index] - mean) / count;
      }

    return mean;
   }

    static double mean(int... values) {
      Preconditions.checkArgument(values.length > 0, "Cannot take mean of 0 values");
    long sum = 0L;

      for (int index = 0; index < values.length; index++) {
         sum += values[index];
      }

      return (double)sum / values.length;
   }

    static double mean(long... values) {
      Preconditions.checkArgument(values.length > 0, "Cannot take mean of 0 values");
    long count = 1L;
    double mean = values[0];

      for (int index = 1; index < values.length; index++) {
         count++;
         mean += (values[index] - mean) / count;
      }

    return mean;
   }

    static double mean(Iterable<? extends) {
    return mean();
   }

    static double mean(Iterator<? extends) {
      Preconditions.checkArgument(values.hasNext(), "Cannot take mean of 0 values");
    long count = 1L;
    double mean = checkFinite(values.next().doubleValue());

      while (values.hasNext()) {
    double value = checkFinite(values.next().doubleValue());
         count++;
         mean += (value - mean) / count;
      }

    return mean;
   }

    static double checkFinite(double argument) {
      Preconditions.checkArgument(DoubleUtils.isFinite(argument));
    return argument;
   }

    private DoubleMath() {
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
