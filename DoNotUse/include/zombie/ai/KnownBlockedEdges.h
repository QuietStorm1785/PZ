#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/network/GameServer.h"
#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace ai {


class KnownBlockedEdges {
public:
    int x;
    int y;
    int z;
    bool w;
    bool n;
   static const ObjectPool<KnownBlockedEdges> pool = std::make_shared<ObjectPool>(KnownBlockedEdges::new);

    KnownBlockedEdges init(KnownBlockedEdges var1) {
      return this.init(var1.x, var1.y, var1.z, var1.w, var1.n);
   }

    KnownBlockedEdges init(int var1, int var2, int var3) {
      return this.init(var1, var2, var3, false, false);
   }

    KnownBlockedEdges init(int var1, int var2, int var3, bool var4, bool var5) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.w = var4;
      this.n = var5;
    return this;
   }

    bool isBlocked(int var1, int var2) {
      return this.x > var1 && this.w ? true : this.y > var2 && this.n;
   }

    static KnownBlockedEdges alloc() {
      assert GameServer.bServer || Thread.currentThread() == GameWindow.GameThread;

      return (KnownBlockedEdges)pool.alloc();
   }

    static void releaseAll(std::vector<KnownBlockedEdges> var0) {
      assert GameServer.bServer || Thread.currentThread() == GameWindow.GameThread;

      pool.release(var0);
   }

    void release() {
      assert GameServer.bServer || Thread.currentThread() == GameWindow.GameThread;

      pool.release(this);
   }
}
} // namespace ai
} // namespace zombie
