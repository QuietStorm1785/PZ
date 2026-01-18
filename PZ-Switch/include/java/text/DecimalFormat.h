#pragma once

#include <string>

namespace java {
namespace text {

class DecimalFormat {
public:
 DecimalFormat(const std::string& pattern);
 virtual ~DecimalFormat() = default;

 std::string format(double value) const;
 std::string format(int value) const;
 double parse(const std::string& source) const;

private:
 std::string pattern_;
};

} // namespace text
} // namespace java
