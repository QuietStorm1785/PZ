#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/LosUtil/TestResults.h"

namespace zombie {
namespace ai {
namespace states {


class SwipeStatePlayer {
public:
    virtual ~SwipeStatePlayer() = default;
    bool visit(IsoGridSquare var1, IsoGridSquare var2);

    TestResults getResult();
}
} // namespace states
} // namespace ai
} // namespace zombie
