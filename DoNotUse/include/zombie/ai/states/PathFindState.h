#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/vehicles/PathFindState2.h"

namespace zombie {
namespace ai {
namespace states {


class PathFindState : public State {
public:
    static const PathFindState2 _instance = std::make_shared<PathFindState2>();

    static PathFindState2 instance() {
    return _instance;
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
