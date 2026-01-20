#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "java/math/BigInteger.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace primitives {


class UnsignedInteger : public Number {
public:
    static const UnsignedInteger ZERO = fromIntBits(0);
    static const UnsignedInteger ONE = fromIntBits(1);
    static const UnsignedInteger MAX_VALUE = fromIntBits(-1);
    const int value;

    private UnsignedInteger(int value) {
      this.value = value & -1;
   }

    static UnsignedInteger fromIntBits(int bits) {
      return std::make_shared<UnsignedInteger>(bits);
   }

    static UnsignedInteger valueOf(long value) {
      Preconditions.checkArgument((value & 4294967295L) == value, "value (%s) is outside the range for an unsigned integer value", value);
    return fromIntBits();
   }

    static UnsignedInteger valueOf(BigInteger value) {
      Preconditions.checkNotNull(value);
      Preconditions.checkArgument(value.signum() >= 0 && value.bitLength() <= 32, "value (%s) is outside the range for an unsigned integer value", value);
    return fromIntBits();
   }

    static UnsignedInteger valueOf(const std::string& string) {
    return valueOf();
   }

    static UnsignedInteger valueOf(const std::string& string, int radix) {
    return fromIntBits();
   }

    UnsignedInteger plus(UnsignedInteger val) {
    return fromIntBits(this.value +);
   }

    UnsignedInteger minus(UnsignedInteger val) {
    return fromIntBits(this.value -);
   }

    UnsignedInteger times(UnsignedInteger val) {
    return fromIntBits(this.value *);
   }

    UnsignedInteger dividedBy(UnsignedInteger val) {
    return fromIntBits();
   }

    UnsignedInteger mod(UnsignedInteger val) {
    return fromIntBits();
   }

    int intValue() {
      return this.value;
   }

    long longValue() {
      return UnsignedInts.toLong(this.value);
   }

    float floatValue() {
      return (float)this.longValue();
   }

    double doubleValue() {
      return this.longValue();
   }

    BigInteger bigIntegerValue() {
      return BigInteger.valueOf(this.longValue());
   }

    int compareTo(UnsignedInteger other) {
      Preconditions.checkNotNull(other);
      return UnsignedInts.compare(this.value, other.value);
   }

    int hashCode() {
      return this.value;
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<UnsignedInteger*>(obj) != nullptr) {
    UnsignedInteger other = (UnsignedInteger)obj;
         return this.value == other.value;
      } else {
    return false;
      }
   }

    std::string toString() {
      return this.toString(10);
   }

    std::string toString(int radix) {
      return UnsignedInts.toString(this.value, radix);
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
