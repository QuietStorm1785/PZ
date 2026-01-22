#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "java/math/BigInteger.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace primitives {


class UnsignedLong : public Number {
public:
    static const long UNSIGNED_MASK = int64_t.MAX_VALUE;
    static const UnsignedLong ZERO = std::make_shared<UnsignedLong>(0L);
    static const UnsignedLong ONE = std::make_shared<UnsignedLong>(1L);
    static const UnsignedLong MAX_VALUE = std::make_shared<UnsignedLong>(-1L);
    const long value;

    private UnsignedLong(long value) {
      this.value = value;
   }

    static UnsignedLong fromLongBits(long bits) {
      return std::make_shared<UnsignedLong>(bits);
   }

    static UnsignedLong valueOf(long value) {
      Preconditions.checkArgument(value >= 0L, "value (%s) is outside the range for an unsigned long value", value);
    return fromLongBits();
   }

    static UnsignedLong valueOf(BigInteger value) {
      Preconditions.checkNotNull(value);
      Preconditions.checkArgument(value.signum() >= 0 && value.bitLength() <= 64, "value (%s) is outside the range for an unsigned long value", value);
    return fromLongBits();
   }

    static UnsignedLong valueOf(const std::string& string) {
    return valueOf();
   }

    static UnsignedLong valueOf(const std::string& string, int radix) {
    return fromLongBits();
   }

    UnsignedLong plus(UnsignedLong val) {
    return fromLongBits(this.value +);
   }

    UnsignedLong minus(UnsignedLong val) {
    return fromLongBits(this.value -);
   }

    UnsignedLong times(UnsignedLong val) {
    return fromLongBits(this.value *);
   }

    UnsignedLong dividedBy(UnsignedLong val) {
    return fromLongBits();
   }

    UnsignedLong mod(UnsignedLong val) {
    return fromLongBits();
   }

    int intValue() {
      return (int)this.value;
   }

    long longValue() {
      return this.value;
   }

    float floatValue() {
    float fValue = (float)(this.value & int64_t.MAX_VALUE);
      if (this.value < 0L) {
         fValue += 9.223372E18F;
      }

    return fValue;
   }

    double doubleValue() {
    double dValue = this.value & int64_t.MAX_VALUE;
      if (this.value < 0L) {
         dValue += 9.223372E18F;
      }

    return dValue;
   }

    BigInteger bigIntegerValue() {
    BigInteger bigInt = BigInteger.valueOf(this.value & int64_t.MAX_VALUE);
      if (this.value < 0L) {
         bigInt = bigInt.setBit(63);
      }

    return bigInt;
   }

    int compareTo(UnsignedLong o) {
      Preconditions.checkNotNull(o);
      return UnsignedLongs.compare(this.value, o.value);
   }

    int hashCode() {
      return Longs.hashCode(this.value);
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<UnsignedLong*>(obj) != nullptr) {
    UnsignedLong other = (UnsignedLong)obj;
         return this.value == other.value;
      } else {
    return false;
      }
   }

    std::string toString() {
      return UnsignedLongs.toString(this.value);
   }

    std::string toString(int radix) {
      return UnsignedLongs.toString(this.value, radix);
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
