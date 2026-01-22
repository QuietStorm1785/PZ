#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

enum class NetworkVariables {
   None,
   Moving,
   Static,
   Thump,
   Climb,
   Lunge,
   LungeHalf,
   Walk,
   WalkHalf,
   PathFind;

   public static NetworkVariables$PredictionTypes fromByte(byte var0) {
      for (NetworkVariables$PredictionTypes var4 : values()) {
         if (var4.ordinal() == var0) {
    return var4;
         }
      }

    return None;
   }
}
} // namespace network
} // namespace zombie
