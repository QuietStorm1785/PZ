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

enum class EditGlobalOps {
   set,
   add,
   sub;
}
} // namespace globals
} // namespace radio
} // namespace zombie
