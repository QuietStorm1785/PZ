#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoMovingObject.h"

namespace zombie {


class CollisionManager {
:
    IsoMovingObject a;
    IsoMovingObject b;

    CollisionManager$Contact(CollisionManager var1, IsoMovingObject var2, IsoMovingObject var3) {
      this.this$0 = var1;
      this.a = var2;
      this.b = var3;
   }
}
} // namespace zombie
