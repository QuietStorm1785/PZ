#pragma once

#include <string>

namespace java {
namespace text {

class NumberFormat {
public:
 virtual ~NumberFormat() = default;

 virtual std::string format(double value) const = 0;
 virtual std::string format(int value) const = 0;
 virtual double parse(const std::string& source) const = 0;

 static NumberFormat* getInstance();
 static NumberFormat* getIntegerInstance();
 static NumberFormat* getNumberInstance();
};

} // namespace text
} // namespace java
