#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/PacketTypes/PacketType.h"

namespace zombie {
namespace spnetwork {


// $VF: synthetic class
class SinglePlayerServer {
public:
   static {
      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.ClientCommand.ordinal()] = 1;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.GlobalObjects.ordinal()] = 2;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace spnetwork
} // namespace zombie
