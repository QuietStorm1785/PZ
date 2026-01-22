#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/IPooledObject.h"
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"

namespace zombie {


class GameProfiler {
public:
    std::string Key;
    long StartTime;
    long EndTime;
    long Total;
    int Depth;
    float r = 1.0F;
    float g = 1.0F;
    float b = 1.0F;
   public const List<GameProfiler$ProfileArea> Children = std::make_unique<std::vector<>>();
   private static const Pool<GameProfiler$ProfileArea> s_pool = std::make_shared<Pool>(GameProfiler$ProfileArea::new);

    void onReleased() {
      super.onReleased();
      this.clear();
   }

    void clear() {
      this.StartTime = 0L;
      this.EndTime = 0L;
      this.Total = 0L;
      this.Depth = 0;
      IPooledObject.release(this.Children);
   }

   public static GameProfiler$ProfileArea alloc() {
      return (GameProfiler$ProfileArea)s_pool.alloc();
   }
}
} // namespace zombie
