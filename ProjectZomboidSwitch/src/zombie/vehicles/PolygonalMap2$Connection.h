#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/PolygonalMap2/Node.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    Node node1;
    Node node2;
    int flags;
   static const ArrayDeque<PolygonalMap2$Connection> pool = std::make_unique<ArrayDeque<>>();

   private PolygonalMap2$Connection() {
   }

   PolygonalMap2$Connection init(Node var1, Node var2, int var3) {
      this.node1 = var1;
      this.node2 = var2;
      this.flags = var3;
    return this;
   }

    Node otherNode(Node var1) {
      if (!$assertionsDisabled && var1 != this.node1 && var1 != this.node2) {
         throw std::make_unique<AssertionError>();
      } else {
    return var1 = = this.node1 ? this.node2 : this.node1;
      }
   }

    bool has(int var1) {
      return (this.flags & var1) != 0;
   }

   static PolygonalMap2$Connection alloc() {
      if (pool.empty()) {
    bool var0 = false;
      } else {
    bool var1 = false;
      }

      return pool.empty() ? new PolygonalMap2$Connection() : pool.pop();
   }

    void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw std::make_unique<AssertionError>();
      } else {
         pool.push(this);
      }
   }
}
} // namespace vehicles
} // namespace zombie
