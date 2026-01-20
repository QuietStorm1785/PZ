#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "zombie/characters/NetworkCharacter.h"
#include "zombie/characters/NetworkCharacter/Transform.h"
#include "zombie/core/Color.h"
#include "zombie/core/Colors.h"
#include "zombie/core/raknet/VoiceManager.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/FakeClientManager/1.h"
#include "zombie/network/FakeClientManager/Client.h"
#include "zombie/network/FakeClientManager/Movement.h"
#include "zombie/network/FakeClientManager/Movement/Motion.h"
#include "zombie/network/FakeClientManager/Network.h"
#include "zombie/network/FakeClientManager/Player/Clothes.h"
#include "zombie/network/FakeClientManager/PlayerManager.h"
#include "zombie/network/FakeClientManager/PlayerManager/RemotePlayer.h"
#include "zombie/network/FakeClientManager/Zombie.h"
#include "zombie/network/FakeClientManager/ZombieSimulator.h"

namespace zombie {
namespace network {


class FakeClientManager {
public:
    static const int cellSize = 50;
    static const int spawnMinX = 3550;
    static const int spawnMaxX = 14450;
    static const int spawnMinY = 5050;
    static const int spawnMaxY = 12950;
    static const int ChunkGridWidth = 13;
    static const int ChunksPerWidth = 10;
    static int fps = 60;
    static int predictInterval = 1000;
    static float damage = 1.0F;
    static bool isVOIPEnabled = false;
    const NetworkCharacter networkCharacter;
    const UpdateLimit updateLimiter;
    const UpdateLimit predictLimiter;
    const UpdateLimit timeSyncLimiter;
    const Client client;
    const Movement movement;
   private const std::vector<Clothes> clothes;
    const std::string username;
    const int isFemale;
    const Color tagColor;
    const Color speakColor;
    UpdateLimit teleportLimiter;
    short OnlineID;
    float x;
    float y;
    const float z;
    Vector2 direction;
    int WorldX;
    int WorldY;
    float angle;
    ZombieSimulator simulator;
    PlayerManager playerManager;
    bool weapon_isBareHeads = false;
    int weapon_id = 837602032;
    short registry_id = 1202;
    static float distance = 0.0F;
    int lastPlayerForHello = -1;

   private FakeClientManager$Player(Movement var1, Network var2, int var3, int var4) {
      this.username = std::string.format("Client%d", var1.id);
      this.tagColor = Colors.SkyBlue;
      this.speakColor = Colors.GetRandomColor();
      this.isFemale = (int)Math.round(Math.random());
      this.OnlineID = -1;
      this.clothes = std::make_unique<std::vector<>>();
      this.clothes.push_back(std::make_shared<Clothes>((byte)11, (byte)0, "Shirt_FormalWhite"));
      this.clothes.push_back(std::make_shared<Clothes>((byte)13, (byte)3, "Tie_Full"));
      this.clothes.push_back(std::make_shared<Clothes>((byte)11, (byte)0, "Socks_Ankle"));
      this.clothes.push_back(std::make_shared<Clothes>((byte)13, (byte)0, "Trousers_Suit"));
      this.clothes.push_back(std::make_shared<Clothes>((byte)13, (byte)0, "Suit_Jacket"));
      this.clothes.push_back(std::make_shared<Clothes>((byte)11, (byte)0, "Shoes_Black"));
      this.clothes.push_back(std::make_shared<Clothes>((byte)11, (byte)0, "Glasses_Sun"));
      this.WorldX = (int)this.x / 10;
      this.WorldY = (int)this.y / 10;
      this.movement = var1;
      this.z = 0.0F;
      this.angle = 0.0F;
      this.x = var1.spawn.x;
      this.y = var1.spawn.y;
      this.direction = var1.direction.ToVector();
      this.networkCharacter = std::make_unique<NetworkCharacter>();
      this.simulator = std::make_shared<ZombieSimulator>(this);
      this.playerManager = std::make_shared<PlayerManager>(this);
      this.client = std::make_shared<Client>(this, var2, var3, var4);
      var2.createdClients.put(var3, this.client);
      this.updateLimiter = std::make_shared<UpdateLimit>(1000 / fps);
      this.predictLimiter = std::make_shared<UpdateLimit>((long)(predictInterval * 0.6F));
      this.timeSyncLimiter = std::make_shared<UpdateLimit>(10000L);
   }

    float getDistance(float var1) {
      return var1 / 3.6F / fps;
   }

    void teleportMovement() {
    float var1 = this.movement.destination.x;
    float var2 = this.movement.destination.y;
      FakeClientManager.info(
         this.movement.id,
         std::string.format(
            "Player %3d teleport (%9.3f,%9.3f) => (%9.3f,%9.3f) / %9.3f, next in %.3fs",
            this.OnlineID,
            this.x,
            this.y,
            var1,
            var2,
            Math.sqrt(Math.pow(var1 - this.x, 2.0) + Math.pow(var2 - this.y, 2.0)),
            (float)this.movement.teleportDelay / 1000.0F
         )
      );
      this.x = var1;
      this.y = var2;
      this.angle = 0.0F;
      this.teleportLimiter.Reset(this.movement.teleportDelay);
   }

    void lineMovement() {
      distance = this.getDistance(this.movement.speed);
      this.direction.set(this.movement.destination.x - this.x, this.movement.destination.y - this.y);
      this.direction.normalize();
    float var1 = this.x + distance * this.direction.x;
    float var2 = this.y + distance * this.direction.y;
      if (this.x < this.movement.destination.x && var1 > this.movement.destination.x
         || this.x > this.movement.destination.x && var1 < this.movement.destination.x
         || this.y < this.movement.destination.y && var2 > this.movement.destination.y
         || this.y > this.movement.destination.y && var2 < this.movement.destination.y) {
         var1 = this.movement.destination.x;
         var2 = this.movement.destination.y;
      }

      this.x = var1;
      this.y = var2;
   }

    void circleMovement() {
      this.angle = (this.angle + (float)(2.0 * Math.asin(this.getDistance(this.movement.speed) / 2.0F / this.movement.radius))) % 360.0F;
    float var1 = this.movement.spawn.x + (float)(this.movement.radius * Math.sin(this.angle));
    float var2 = this.movement.spawn.y + (float)(this.movement.radius * Math.cos(this.angle));
      this.x = var1;
      this.y = var2;
   }

    Zombie getNearestZombie() {
    Zombie var1 = nullptr;
    float var2 = float.POSITIVE_INFINITY;

      for (Zombie var4 : this.simulator.zombies.values()) {
    float var5 = IsoUtils.DistanceToSquared(this.x, this.y, var4.x, var4.y);
         if (var5 < var2) {
            var1 = var4;
            var2 = var5;
         }
      }

    return var1;
   }

    Zombie getNearestZombie(RemotePlayer var1) {
    Zombie var2 = nullptr;
    float var3 = float.POSITIVE_INFINITY;

      for (Zombie var5 : this.simulator.zombies.values()) {
    float var6 = IsoUtils.DistanceToSquared(var1.x, var1.y, var5.x, var5.y);
         if (var6 < var3) {
            var2 = var5;
            var3 = var6;
         }
      }

    return var2;
   }

    RemotePlayer getNearestPlayer() {
    RemotePlayer var1 = nullptr;
    float var2 = float.POSITIVE_INFINITY;
      /* synchronized - TODO: add std::mutex */ (this.playerManager.players) {
         for (RemotePlayer var5 : this.playerManager.players.values()) {
    float var6 = IsoUtils.DistanceToSquared(this.x, this.y, var5.x, var5.y);
            if (var6 < var2) {
               var1 = var5;
               var2 = var6;
            }
         }

    return var1;
      }
   }

    void aiAttackZombiesMovement() {
    Zombie var1 = this.getNearestZombie();
    float var2 = this.getDistance(this.movement.speed);
      if (var1 != nullptr) {
         this.direction.set(var1.x - this.x, var1.y - this.y);
         this.direction.normalize();
      }

    float var3 = this.x + var2 * this.direction.x;
    float var4 = this.y + var2 * this.direction.y;
      this.x = var3;
      this.y = var4;
   }

    void aiRunAwayFromZombiesMovement() {
    Zombie var1 = this.getNearestZombie();
    float var2 = this.getDistance(this.movement.speed);
      if (var1 != nullptr) {
         this.direction.set(this.x - var1.x, this.y - var1.y);
         this.direction.normalize();
      }

    float var3 = this.x + var2 * this.direction.x;
    float var4 = this.y + var2 * this.direction.y;
      this.x = var3;
      this.y = var4;
   }

    void aiRunToAnotherPlayersMovement() {
    RemotePlayer var1 = this.getNearestPlayer();
    float var2 = this.getDistance(this.movement.speed);
    float var3 = this.x + var2 * this.direction.x;
    float var4 = this.y + var2 * this.direction.y;
      if (var1 != nullptr) {
         this.direction.set(var1.x - this.x, var1.y - this.y);
    float var5 = this.direction.normalize();
         if (var5 > 2.0F) {
            this.x = var3;
            this.y = var4;
         } else if (this.lastPlayerForHello != var1.OnlineID) {
            this.lastPlayerForHello = var1.OnlineID;
         }
      }
   }

    void aiNormalMovement() {
    float var1 = this.getDistance(this.movement.speed);
    RemotePlayer var2 = this.getNearestPlayer();
      if (var2 == nullptr) {
         this.aiRunAwayFromZombiesMovement();
      } else {
    float var3 = IsoUtils.DistanceToSquared(this.x, this.y, var2.x, var2.y);
         if (var3 > 36.0F) {
            this.movement.speed = 13.0F;
            this.movement.motion = Motion.Run;
         } else {
            this.movement.speed = 4.0F;
            this.movement.motion = Motion.Walk;
         }

    Zombie var4 = this.getNearestZombie();
    float var5 = float.POSITIVE_INFINITY;
         if (var4 != nullptr) {
            var5 = IsoUtils.DistanceToSquared(this.x, this.y, var4.x, var4.y);
         }

    Zombie var6 = this.getNearestZombie(var2);
    float var7 = float.POSITIVE_INFINITY;
         if (var6 != nullptr) {
            var7 = IsoUtils.DistanceToSquared(var2.x, var2.y, var6.x, var6.y);
         }

         if (var7 < 25.0F) {
            var4 = var6;
            var5 = var7;
         }

         if (var3 > 25.0F || var4 == nullptr) {
            this.direction.set(var2.x - this.x, var2.y - this.y);
    float var8 = this.direction.normalize();
            if (var8 > 4.0F) {
    float var9 = this.x + var1 * this.direction.x;
    float var10 = this.y + var1 * this.direction.y;
               this.x = var9;
               this.y = var10;
            } else if (this.lastPlayerForHello != var2.OnlineID) {
               this.lastPlayerForHello = var2.OnlineID;
            }
         } else if (var5 < 25.0F) {
            this.direction.set(var4.x - this.x, var4.y - this.y);
            this.direction.normalize();
            this.x = this.x + var1 * this.direction.x;
            this.y = this.y + var1 * this.direction.y;
         }
      }
   }

    void checkRequestChunks() {
    int var1 = (int)this.x / 10;
    int var2 = (int)this.y / 10;
      if (Math.abs(var1 - this.WorldX) < 13 && Math.abs(var2 - this.WorldY) < 13) {
         if (var1 != this.WorldX) {
            if (var1 < this.WorldX) {
               for (int var9 = -6; var9 <= 6; var9++) {
                  this.client.addChunkRequest(this.WorldX - 6, this.WorldY + var9, 0, var9 + 6);
               }
            } else {
               for (int var10 = -6; var10 <= 6; var10++) {
                  this.client.addChunkRequest(this.WorldX + 6, this.WorldY + var10, 12, var10 + 6);
               }
            }
         } else if (var2 != this.WorldY) {
            if (var2 < this.WorldY) {
               for (int var11 = -6; var11 <= 6; var11++) {
                  this.client.addChunkRequest(this.WorldX + var11, this.WorldY - 6, var11 + 6, 0);
               }
            } else {
               for (int var12 = -6; var12 <= 6; var12++) {
                  this.client.addChunkRequest(this.WorldX + var12, this.WorldY + 6, var12 + 6, 12);
               }
            }
         }
      } else {
    int var3 = this.WorldX - 6;
    int var4 = this.WorldY - 6;
    int var5 = this.WorldX + 6;
    int var6 = this.WorldY + 6;

         for (int var7 = var3; var7 <= var5; var7++) {
            for (int var8 = var4; var8 <= var6; var8++) {
               this.client.addChunkRequest(var7, var8, var7 - var3, var8 - var4);
            }
         }
      }

      this.client.requestChunks();
      this.WorldX = var1;
      this.WorldY = var2;
   }

    void hit() {
      FakeClientManager.info(this.movement.id, std::string.format("Player %3d hit", this.OnlineID));
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void run() {
      this.simulator.update();
      if (this.updateLimiter.Check()) {
         if (isVOIPEnabled) {
            FMODManager.instance.tick();
            VoiceManager.instance.update();
         }

         if (this.movement.doTeleport() && this.teleportLimiter.Check()) {
            this.teleportMovement();
         }

         switch (1.$SwitchMap$zombie$network$FakeClientManager$Movement$Type[this.movement.type.ordinal()]) {
            case 1:
               this.circleMovement();
               break;
            case 2:
               this.lineMovement();
               break;
            case 3:
               this.aiAttackZombiesMovement();
               break;
            case 4:
               this.aiRunAwayFromZombiesMovement();
               break;
            case 5:
               this.aiRunToAnotherPlayersMovement();
               break;
            case 6:
               this.aiNormalMovement();
         }

         this.checkRequestChunks();
         if (this.predictLimiter.Check()) {
    int var1 = (int)(this.client.getServerTime() / 1000000L);
            this.networkCharacter.checkResetPlayer(var1);
    Transform var2 = this.networkCharacter.predict(predictInterval, var1, this.x, this.y, this.direction.x, this.direction.y);
            this.client.sendPlayer(var2, var1, this.direction);
         }

         if (this.timeSyncLimiter.Check()) {
            this.client.sendTimeSync();
            this.client.sendSyncRadioData();
         }

         if (this.movement.hordeCreator != nullptr && this.movement.hordeCreator.hordeCreatorLimiter.Check()) {
            this.client.sendCommand(this.movement.hordeCreator.getCommand((int)this.x, (int)this.y, (int)this.z));
         }

         if (this.movement.soundMaker != nullptr && this.movement.soundMaker.soundMakerLimiter.Check()) {
            this.client.sendWorldSound4Player((int)this.x, (int)this.y, (int)this.z, this.movement.soundMaker.radius, this.movement.soundMaker.radius);
            this.client.sendChatMessage(this.movement.soundMaker.message);
            this.client.sendEventPacket(this.OnlineID, (int)this.x, (int)this.y, (int)this.z, (byte)4, "shout");
         }
      }
   }
}
} // namespace network
} // namespace zombie
