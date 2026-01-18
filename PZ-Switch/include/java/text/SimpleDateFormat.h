#pragma once

#include <string>

namespace java {
namespace text {

class SimpleDateFormat {
public:
 SimpleDateFormat(const std::string& pattern);
 virtual ~SimpleDateFormat() = default;

 std::string format(long time) const;
 long parse(const std::string& dateStr) const;

private:
 std::string pattern_;
};

} // namespace text
} // namespace java
