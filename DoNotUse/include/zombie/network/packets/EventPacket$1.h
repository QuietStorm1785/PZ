#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/packets/EventPacket/EventType.h"

namespace zombie {
namespace network {
namespace packets {


// $VF: synthetic class
class EventPacket {
public:
   static {
      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.EventSetActivatedPrimary.ordinal()] = 1;
      } catch (NoSuchFieldError var22) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.EventSetActivatedSecondary.ordinal()] = 2;
      } catch (NoSuchFieldError var21) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.EventFallClimb.ordinal()] = 3;
      } catch (NoSuchFieldError var20) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.collideWithWall.ordinal()] = 4;
      } catch (NoSuchFieldError var19) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.EventFishing.ordinal()] = 5;
      } catch (NoSuchFieldError var18) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.EventFitness.ordinal()] = 6;
      } catch (NoSuchFieldError var17) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.EventUpdateFitness.ordinal()] = 7;
      } catch (NoSuchFieldError var16) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.EventEmote.ordinal()] = 8;
      } catch (NoSuchFieldError var15) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.EventSitOnGround.ordinal()] = 9;
      } catch (NoSuchFieldError var14) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.EventClimbRope.ordinal()] = 10;
      } catch (NoSuchFieldError var13) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.EventClimbDownRope.ordinal()] = 11;
      } catch (NoSuchFieldError var12) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.EventClimbFence.ordinal()] = 12;
      } catch (NoSuchFieldError var11) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.EventClimbWall.ordinal()] = 13;
      } catch (NoSuchFieldError var10) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.EventClimbWindow.ordinal()] = 14;
      } catch (NoSuchFieldError var9) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.EventOpenWindow.ordinal()] = 15;
      } catch (NoSuchFieldError var8) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.EventCloseWindow.ordinal()] = 16;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.EventSmashWindow.ordinal()] = 17;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.wasBumped.ordinal()] = 18;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.EventOverrideItem.ordinal()] = 19;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.ChargeSpearConnect.ordinal()] = 20;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.Update.ordinal()] = 21;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$network$packets$EventPacket$EventType[EventType.Unknown.ordinal()] = 22;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
