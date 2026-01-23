#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameProfileRecording/Span.h"
#include "zombie/util/IPooledObject.h"

namespace zombie {


class GameProfileRecording {
public:
    long StartTime;
    long EndTime;
   const List<Span> Spans = std::make_unique<std::vector<>>();

    void reset() {
      IPooledObject.release(this.Spans);
   }
}
} // namespace zombie
