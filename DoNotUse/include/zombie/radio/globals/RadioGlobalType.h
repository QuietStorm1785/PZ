#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {
namespace globals {

enum class RadioGlobalType {
   std::string,
   int,
   bool,
   float,
   Invalid;
}
} // namespace globals
} // namespace radio
} // namespace zombie
