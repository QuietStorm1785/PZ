#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace audio {
namespace parameters {

enum class ParameterRoomType {
   Generic(0),
   Barn(1),
   Mall(2),
   Warehouse(3),
   Prison(4),
   Church(5),
   Office(6),
   Factory(7);

    const int label;

   private ParameterRoomType$RoomType(int var3) {
      this.label = var3;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
