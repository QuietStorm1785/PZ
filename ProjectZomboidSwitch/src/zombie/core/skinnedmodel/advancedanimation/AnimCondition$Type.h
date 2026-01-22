#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {

enum class AnimCondition {
   STRING,
   STRNEQ,
   BOOL,
   EQU,
   NEQ,
   LESS,
   GTR,
   OR;
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
