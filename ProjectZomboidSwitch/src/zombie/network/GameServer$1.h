#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/PacketTypes/PacketType.h"

namespace zombie {
namespace network {


// $VF: synthetic class
class GameServer {
public:
   static {
      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.Login.ordinal()] = 1;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.Ping.ordinal()] = 2;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.ScoreboardUpdate.ordinal()] = 3;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace network
} // namespace zombie
