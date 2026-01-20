#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/FakeClientManager/HordeCreator.h"
#include "zombie/network/FakeClientManager/Movement/Motion.h"
#include "zombie/network/FakeClientManager/Movement/Type.h"
#include "zombie/network/FakeClientManager/SoundMaker.h"

namespace zombie {
namespace network {


class FakeClientManager {
public:
    static std::string version;
    static int defaultRadius = 150;
    static int aimSpeed = 4;
    static int sneakSpeed = 6;
    static int walkSpeed = 7;
    static int sneakRunSpeed = 10;
    static int runSpeed = 13;
    static int sprintSpeed = 19;
    static int pedestrianSpeedMin = 5;
    static int pedestrianSpeedMax = 20;
    static int vehicleSpeedMin = 40;
    static int vehicleSpeedMax = 80;
    static const float zombieLungeDistanceSquared = 100.0F;
    static const float zombieWalkSpeed = 3.0F;
    static const float zombieLungeSpeed = 6.0F;
    const int id;
    const std::string description;
    const Vector2 spawn;
    Motion motion;
    float speed;
    const Type type;
    const int radius;
    const IsoDirections direction;
    const Vector2 destination;
    const bool ghost;
    const long connectDelay;
    const long disconnectDelay;
    const long reconnectDelay;
    const long teleportDelay;
    const HordeCreator hordeCreator;
    SoundMaker soundMaker;
    long timestamp;

   public FakeClientManager$Movement(
      int var1,
      std::string var2,
      int var3,
      int var4,
      Motion var5,
      int var6,
      Type var7,
      int var8,
      int var9,
      int var10,
      IsoDirections var11,
      boolean var12,
      long var13,
      long var15,
      long var17,
      long var19,
      HordeCreator var21,
      SoundMaker var22
   ) {
      this.id = var1;
      this.description = var2;
      this.spawn = std::make_shared<Vector2>(var3, var4);
      this.motion = var5;
      this.speed = var6;
      this.type = var7;
      this.radius = var8;
      this.direction = var11;
      this.destination = std::make_shared<Vector2>(var9, var10);
      this.ghost = var12;
      this.connectDelay = var13;
      this.disconnectDelay = var15;
      this.reconnectDelay = var17;
      this.teleportDelay = var19;
      this.hordeCreator = var21;
      this.soundMaker = var22;
   }

    void connect(int var1) {
    long var2 = System.currentTimeMillis();
      if (this.disconnectDelay != 0L) {
         FakeClientManager.info(
            this.id,
            std::string.format(
               "Player %3d connect in %.3fs, disconnect in %.3fs", var1, (float)(var2 - this.timestamp) / 1000.0F, (float)this.disconnectDelay / 1000.0F
            )
         );
      } else {
         FakeClientManager.info(this.id, std::string.format("Player %3d connect in %.3fs", var1, (float)(var2 - this.timestamp) / 1000.0F));
      }

      this.timestamp = var2;
   }

    void disconnect(int var1) {
    long var2 = System.currentTimeMillis();
      if (this.reconnectDelay != 0L) {
         FakeClientManager.info(
            this.id,
            std::string.format(
               "Player %3d disconnect in %.3fs, reconnect in %.3fs", var1, (float)(var2 - this.timestamp) / 1000.0F, (float)this.reconnectDelay / 1000.0F
            )
         );
      } else {
         FakeClientManager.info(this.id, std::string.format("Player %3d disconnect in %.3fs", var1, (float)(var2 - this.timestamp) / 1000.0F));
      }

      this.timestamp = var2;
   }

    bool doTeleport() {
      return this.teleportDelay != 0L;
   }

    bool doDisconnect() {
      return this.disconnectDelay != 0L;
   }

    bool checkDisconnect() {
      return System.currentTimeMillis() - this.timestamp > this.disconnectDelay;
   }

    bool doReconnect() {
      return this.reconnectDelay != 0L;
   }

    bool checkReconnect() {
      return System.currentTimeMillis() - this.timestamp > this.reconnectDelay;
   }
}
} // namespace network
} // namespace zombie
