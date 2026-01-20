#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "java/math/BigInteger.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace math {


class MathPreconditions {
public:
    static int checkPositive(@Nullable std::string, int x) {
      if (x <= 0) {
         throw IllegalArgumentException(role + " (" + x + ") must be > 0");
      } else {
    return x;
      }
   }

    static long checkPositive(@Nullable std::string, long x) {
      if (x <= 0L) {
         throw IllegalArgumentException(role + " (" + x + ") must be > 0");
      } else {
    return x;
      }
   }

    static BigInteger checkPositive(@Nullable std::string, BigInteger x) {
      if (x.signum() <= 0) {
         throw IllegalArgumentException(role + " (" + x + ") must be > 0");
      } else {
    return x;
      }
   }

    static int checkNonNegative(@Nullable std::string, int x) {
      if (x < 0) {
         throw IllegalArgumentException(role + " (" + x + ") must be >= 0");
      } else {
    return x;
      }
   }

    static long checkNonNegative(@Nullable std::string, long x) {
      if (x < 0L) {
         throw IllegalArgumentException(role + " (" + x + ") must be >= 0");
      } else {
    return x;
      }
   }

    static BigInteger checkNonNegative(@Nullable std::string, BigInteger x) {
      if (x.signum() < 0) {
         throw IllegalArgumentException(role + " (" + x + ") must be >= 0");
      } else {
    return x;
      }
   }

    static double checkNonNegative(@Nullable std::string, double x) {
      if (!(x >= 0.0)) {
         throw IllegalArgumentException(role + " (" + x + ") must be >= 0");
      } else {
    return x;
      }
   }

    static void checkRoundingUnnecessary(bool condition) {
      if (!condition) {
         throw ArithmeticException("mode was UNNECESSARY, but rounding was necessary");
      }
   }

    static void checkInRange(bool condition) {
      if (!condition) {
         throw ArithmeticException("not in range");
      }
   }

    static void checkNoOverflow(bool condition) {
      if (!condition) {
         throw ArithmeticException("overflow");
      }
   }

    private MathPreconditions() {
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
