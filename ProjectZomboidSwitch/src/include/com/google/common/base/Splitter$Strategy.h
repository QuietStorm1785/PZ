#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace base {


class Splitter {
public:
    virtual ~Splitter() = default;
   Iterator<std::string> iterator(Splitter var1, CharSequence var2);
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
