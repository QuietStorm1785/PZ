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
    static const Vector2 vel = std::make_shared<Vector2>();
    static const Vector2 vel2 = std::make_shared<Vector2>();
   static const List<IsoPushableObject> pushables = std::make_unique<std::vector<>>();
   static IsoMovingObject[] objectListInvoking = new IsoMovingObject[1024];

   private CollisionManager$l_ResolveContacts() {
   }
}
} // namespace zombie
