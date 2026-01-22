#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/packets/RequestDataPacket/RequestID.h"

namespace zombie {
namespace network {
namespace packets {


// $VF: synthetic class
class RequestDataPacket {
public:
   static {
      try {
         $SwitchMap$zombie$network$packets$RequestDataPacket$RequestID[RequestID.Descriptors.ordinal()] = 1;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$network$packets$RequestDataPacket$RequestID[RequestID.MetaGrid.ordinal()] = 2;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$network$packets$RequestDataPacket$RequestID[RequestID.MapZone.ordinal()] = 3;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$network$packets$RequestDataPacket$RequestID[RequestID.PlayerZombieDescriptors.ordinal()] = 4;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$network$packets$RequestDataPacket$RequestID[RequestID.RadioData.ordinal()] = 5;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
