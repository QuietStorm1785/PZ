#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <nlohmann/json.hpp>
#include "org/uncommons/maths/Maths.h"

namespace org {
namespace uncommons {
namespace maths {
namespace number {


class Rational {
public:
    static Rational ZERO() { return Rational(0); }
    static Rational QUARTER() { return Rational(1,4); }
    static Rational THIRD() { return Rational(1,3); }
    static Rational HALF() { return Rational(1,2); }
    static Rational TWO_THIRDS() { return Rational(2,3); }
    static Rational THREE_QUARTERS() { return Rational(3,4); }
    static Rational ONE() { return Rational(1); }

    const int64_t numerator;
    const int64_t denominator;

    Rational(int64_t numerator, int64_t denominator) : numerator(0), denominator(1) {
        if (denominator == 0) throw std::invalid_argument("Denominator must be non-zero and positive.");
        int64_t gcd = Maths::greatestCommonDivisor(numerator, denominator);
        const_cast<int64_t&>(this->numerator) = numerator / gcd;
        const_cast<int64_t&>(this->denominator) = denominator / gcd;
    }

    Rational(int64_t value) : numerator(value), denominator(1) {}

    // Constructing from BigDecimal not yet implemented in C++ conversion
    Rational(const std::string& /*bigDecimalStr*/) : numerator(0), denominator(1) {
        // TODO: parse decimal string to rational representation
    }

    int64_t getNumerator() const { return numerator; }
    int64_t getDenominator() const { return denominator; }

    Rational add(Rational value) {
      return this.denominator == value.getDenominator()
         ? std::make_shared<Rational>(this.numerator + value.getNumerator(), this.denominator)
         : std::make_shared<Rational>(this.numerator * value.getDenominator() + value.getNumerator() * this.denominator, this.denominator * value.getDenominator());
   }

    Rational subtract(Rational value) {
      return this.denominator == value.getDenominator()
         ? std::make_shared<Rational>(this.numerator - value.getNumerator(), this.denominator)
         : std::make_shared<Rational>(this.numerator * value.getDenominator() - value.getNumerator() * this.denominator, this.denominator * value.getDenominator());
   }

    Rational multiply(Rational value) {
      return std::make_shared<Rational>(this.numerator * value.getNumerator(), this.denominator * value.getDenominator());
   }

    Rational divide(Rational value) {
      return std::make_shared<Rational>(this.numerator * value.getDenominator(), this.denominator * value.getNumerator());
   }

    int intValue() {
      return (int)this.longValue();
   }

    long longValue() {
      return (long)this.doubleValue();
   }

    float floatValue() {
      return (float)this.doubleValue();
   }

    double doubleValue() {
      return (double)this.numerator / this.denominator;
   }

    bool equals(void* other) {
      if (this == other) {
    return true;
      } else if (other != nullptr && this.getClass() == other.getClass()) {
    Rational rational = (Rational)other;
         return this.denominator == rational.getDenominator() && this.numerator == rational.getNumerator();
      } else {
    return false;
      }
   }

    int hashCode() {
    int result = (int)(this.numerator ^ this.numerator >>> 32);
      return 31 * result + (int)(this.denominator ^ this.denominator >>> 32);
   }

    std::string toString() {
    std::stringstream buffer = new std::stringstream();
      buffer.append(this.numerator);
      if (this.denominator != 1L) {
         buffer.append('/');
         buffer.append(this.denominator);
      }

      return buffer;
   }

    int compareTo(Rational other) {
      if (this.denominator == other.getDenominator()) {
         return int64_t.valueOf(this.numerator).compareTo(other.getNumerator());
      } else {
    long adjustedNumerator = this.numerator * other.getDenominator();
    long otherAdjustedNumerator = other.getNumerator() * this.denominator;
         return adjustedNumerator.compareTo(otherAdjustedNumerator);
      }
   }
}
} // namespace number
} // namespace maths
} // namespace uncommons
} // namespace org
