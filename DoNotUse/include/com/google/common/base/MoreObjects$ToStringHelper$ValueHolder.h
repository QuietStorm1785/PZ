#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace base {

class MoreObjects {
public:
    std::string name;
    void* value;
   MoreObjects$ToStringHelper$ValueHolder next;

   private MoreObjects$ToStringHelper$ValueHolder() {
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
