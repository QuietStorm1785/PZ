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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PathFindState : public State {
public:
 static const PathFindState2 _instance = new PathFindState2();

 static PathFindState2 instance() {
 return _instance;
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
