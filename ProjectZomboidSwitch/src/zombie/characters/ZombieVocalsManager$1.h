#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/ZombieVocalsManager/ObjectWithDistance.h"
#include <algorithm>

namespace zombie {
namespace characters {


class ZombieVocalsManager {
public:
   ZombieVocalsManager$1(ZombieVocalsManager var1) {
      this.this$0 = var1;
   }

    int compare(ObjectWithDistance var1, ObjectWithDistance var2) {
      return float.compare(var1.distSq, var2.distSq);
   }
}
} // namespace characters
} // namespace zombie
