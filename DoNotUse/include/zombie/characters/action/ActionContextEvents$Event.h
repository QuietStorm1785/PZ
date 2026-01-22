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

class ActionContextEvents {
public:
    int layer;
    std::string name;
   ActionContextEvents$Event next;

   private ActionContextEvents$Event() {
   }
}
} // namespace action
} // namespace characters
} // namespace zombie
