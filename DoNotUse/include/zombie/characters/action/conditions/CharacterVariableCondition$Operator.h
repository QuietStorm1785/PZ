#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {
namespace action {
namespace conditions {

enum class CharacterVariableCondition {
   Equal,
   NotEqual,
   Less,
   Greater,
   LessEqual,
   GreaterEqual;
}
} // namespace conditions
} // namespace action
} // namespace characters
} // namespace zombie
