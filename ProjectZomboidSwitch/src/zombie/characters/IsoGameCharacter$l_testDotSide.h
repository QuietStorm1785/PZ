#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace characters {


class IsoGameCharacter {
public:
    static const Vector2 v1 = std::make_shared<Vector2>();
    static const Vector2 v2 = std::make_shared<Vector2>();
    static const Vector2 v3 = std::make_shared<Vector2>();

   protected IsoGameCharacter$l_testDotSide() {
   }
}
} // namespace characters
} // namespace zombie
