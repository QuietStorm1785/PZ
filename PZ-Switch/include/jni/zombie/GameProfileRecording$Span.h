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


class GameProfileRecording {
:
    int key;
    int Depth;
    long StartTime;
    long EndTime;
   List<GameProfileRecording$Span> Children = std::make_unique<ArrayList<>>();
   private static Pool<GameProfileRecording$Span> s_pool = new Pool(GameProfileRecording$Span::new);

    void onReleased() {
      super.onReleased();
      IPooledObject.release(this.Children);
   }

    static GameProfileRecording$Span alloc() {
      return (GameProfileRecording$Span)s_pool.alloc();
   }
}
} // namespace zombie
