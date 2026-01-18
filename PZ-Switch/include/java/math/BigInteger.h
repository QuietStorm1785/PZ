#pragma once
#include <string>
#include <cstdint>

namespace java {
namespace math {
class BigInteger {
public:
 BigInteger() = default;
 explicit BigInteger(long long v) : value_(std::to_string(v) {}
 explicit BigInteger(const std::string& s) : value_(s) {}

 std::string toString() const { return value_; }

private:
 std::string value_{"0"};
};
} // namespace math
} // namespace java
