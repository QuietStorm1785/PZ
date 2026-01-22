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
class SinglePlayerClient {
public:
   static {
      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.ClientCommand.ordinal()] = 1;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.GlobalObjects.ordinal()] = 2;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.ObjectChange.ordinal()] = 3;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace spnetwork
} // namespace zombie
