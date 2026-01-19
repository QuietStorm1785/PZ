#pragma once

#include <string>
#include <string_view>

namespace java {
namespace text {

class SimpleDateFormat {
public:
 SimpleDateFormat(std::string_view pattern);
 virtual ~SimpleDateFormat() = default;

 std::string format(long time) const;
 long parse(std::string_view dateStr) const;

private:
 std::string pattern_;
};

} // namespace text
} // namespace java
