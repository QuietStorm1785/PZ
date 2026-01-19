#pragma once

#include <string>
#include <string_view>

namespace java {
namespace text {

class NumberFormat {
public:
 virtual ~NumberFormat() = default;

 virtual std::string format(double value) const = 0;
 virtual std::string format(int value) const = 0;
 virtual double parse(std::string_view source) const = 0;

 static NumberFormat* getInstance();
 static NumberFormat* getIntegerInstance();
 static NumberFormat* getNumberInstance();
};

} // namespace text
} // namespace java
