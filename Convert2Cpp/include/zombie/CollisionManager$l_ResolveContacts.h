#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoPushableObject.h"
#include "zombie/iso/Vector2.h"

namespace zombie {


class CollisionManager {
public:
    static auto vel = std::make_shared<Vector2>();
    static auto vel2 = std::make_shared<Vector2>();
   static final List<IsoPushableObject> pushables = std::make_unique<ArrayList<>>();
   static std::vector<IsoMovingObject> objectListInvoking = std::make_shared<std::array<IsoMovingObject, 1024>>();

   private CollisionManager$l_ResolveContacts() {
   }
}
} // namespace zombie
