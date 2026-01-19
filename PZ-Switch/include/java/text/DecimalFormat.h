#pragma once

#include <string>
#include <string_view>

namespace java {
namespace text {

class DecimalFormat {
public:
 DecimalFormat(std::string_view pattern);
 virtual ~DecimalFormat() = default;

 std::string format(double value) const;
 std::string format(int value) const;
 double parse(std::string_view source) const;

private:
 std::string pattern_;
};

} // namespace text
} // namespace java
