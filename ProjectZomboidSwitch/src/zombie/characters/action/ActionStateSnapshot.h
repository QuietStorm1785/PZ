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

class ActionStateSnapshot {
public:
    std::string stateName;
   public std::string[] childStateNames;
}
} // namespace action
} // namespace characters
} // namespace zombie
