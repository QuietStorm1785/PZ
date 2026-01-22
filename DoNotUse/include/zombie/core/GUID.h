#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace core {


class GUID {
public:
    static std::string generateGUID() {
    UUID var0 = UUID.randomUUID();
      return var0;
   }
}
} // namespace core
} // namespace zombie
