#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/FakeClientManager/Client/State.h"
#include "zombie/network/FakeClientManager/Movement/Motion.h"
#include "zombie/network/FakeClientManager/Movement/Type.h"
#include "zombie/network/PacketTypes/PacketType.h"

namespace zombie {
namespace network {


// $VF: synthetic class
class FakeClientManager {
public:
   static {
      try {
         $SwitchMap$zombie$network$FakeClientManager$Movement$Motion[Motion.Aim.ordinal()] = 1;
      } catch (NoSuchFieldError var41) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Movement$Motion[Motion.Sneak.ordinal()] = 2;
      } catch (NoSuchFieldError var40) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Movement$Motion[Motion.SneakRun.ordinal()] = 3;
      } catch (NoSuchFieldError var39) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Movement$Motion[Motion.Run.ordinal()] = 4;
      } catch (NoSuchFieldError var38) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Movement$Motion[Motion.Sprint.ordinal()] = 5;
      } catch (NoSuchFieldError var37) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Movement$Motion[Motion.Walk.ordinal()] = 6;
      } catch (NoSuchFieldError var36) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Movement$Motion[Motion.Pedestrian.ordinal()] = 7;
      } catch (NoSuchFieldError var35) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Movement$Motion[Motion.Vehicle.ordinal()] = 8;
      } catch (NoSuchFieldError var34) {
      }

      $SwitchMap$zombie$network$PacketTypes$PacketType = new int[PacketType.values().length];

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.PlayerConnect.ordinal()] = 1;
      } catch (NoSuchFieldError var33) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.ExtraInfo.ordinal()] = 2;
      } catch (NoSuchFieldError var32) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.SentChunk.ordinal()] = 3;
      } catch (NoSuchFieldError var31) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.NotRequiredInZip.ordinal()] = 4;
      } catch (NoSuchFieldError var30) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.HitCharacter.ordinal()] = 5;
      } catch (NoSuchFieldError var29) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.StatisticRequest.ordinal()] = 6;
      } catch (NoSuchFieldError var28) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.TimeSync.ordinal()] = 7;
      } catch (NoSuchFieldError var27) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.SyncClock.ordinal()] = 8;
      } catch (NoSuchFieldError var26) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.ZombieSimulation.ordinal()] = 9;
      } catch (NoSuchFieldError var25) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.ZombieSimulationReliable.ordinal()] = 10;
      } catch (NoSuchFieldError var24) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.PlayerUpdate.ordinal()] = 11;
      } catch (NoSuchFieldError var23) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.PlayerUpdateReliable.ordinal()] = 12;
      } catch (NoSuchFieldError var22) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.PlayerTimeout.ordinal()] = 13;
      } catch (NoSuchFieldError var21) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.Kicked.ordinal()] = 14;
      } catch (NoSuchFieldError var20) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.Checksum.ordinal()] = 15;
      } catch (NoSuchFieldError var19) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.KillZombie.ordinal()] = 16;
      } catch (NoSuchFieldError var18) {
      }

      try {
         $SwitchMap$zombie$network$PacketTypes$PacketType[PacketType.Teleport.ordinal()] = 17;
      } catch (NoSuchFieldError var17) {
      }

      $SwitchMap$zombie$network$FakeClientManager$Client$State = new int[State.values().length];

      try {
         $SwitchMap$zombie$network$FakeClientManager$Client$State[State.CONNECT.ordinal()] = 1;
      } catch (NoSuchFieldError var16) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Client$State[State.LOGIN.ordinal()] = 2;
      } catch (NoSuchFieldError var15) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Client$State[State.PLAYER_CONNECT.ordinal()] = 3;
      } catch (NoSuchFieldError var14) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Client$State[State.CHECKSUM.ordinal()] = 4;
      } catch (NoSuchFieldError var13) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Client$State[State.PLAYER_EXTRA_INFO.ordinal()] = 5;
      } catch (NoSuchFieldError var12) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Client$State[State.LOAD.ordinal()] = 6;
      } catch (NoSuchFieldError var11) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Client$State[State.RUN.ordinal()] = 7;
      } catch (NoSuchFieldError var10) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Client$State[State.WAIT.ordinal()] = 8;
      } catch (NoSuchFieldError var9) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Client$State[State.DISCONNECT.ordinal()] = 9;
      } catch (NoSuchFieldError var8) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Client$State[State.QUIT.ordinal()] = 10;
      } catch (NoSuchFieldError var7) {
      }

      $SwitchMap$zombie$network$FakeClientManager$Movement$Type = new int[Type.values().length];

      try {
         $SwitchMap$zombie$network$FakeClientManager$Movement$Type[Type.Circle.ordinal()] = 1;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Movement$Type[Type.Line.ordinal()] = 2;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Movement$Type[Type.AIAttackZombies.ordinal()] = 3;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Movement$Type[Type.AIRunAwayFromZombies.ordinal()] = 4;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Movement$Type[Type.AIRunToAnotherPlayers.ordinal()] = 5;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$network$FakeClientManager$Movement$Type[Type.AINormal.ordinal()] = 6;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace network
} // namespace zombie
