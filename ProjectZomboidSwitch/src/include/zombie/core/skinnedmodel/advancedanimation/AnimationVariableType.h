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

enum class AnimationVariableType {
   Void,
   std::string,
   float,
   bool;
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
