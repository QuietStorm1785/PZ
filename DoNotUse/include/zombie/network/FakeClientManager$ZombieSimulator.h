#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Sets.h"
#include "com/google/common/collect/Sets/SetView.h"
#include "com/google/common/collect/UnmodifiableIterator.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/FakeClientManager/Player.h"
#include "zombie/network/FakeClientManager/PlayerManager/RemotePlayer.h"
#include "zombie/network/FakeClientManager/Zombie.h"
#include "zombie/network/FakeClientManager/ZombieSimulator/Behaviour.h"
#include "zombie/network/NetworkVariables/PredictionTypes.h"
#include "zombie/network/NetworkVariables/WalkType.h"
#include "zombie/network/NetworkVariables/ZombieState.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/packets/ZombiePacket.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace network {


class FakeClientManager {
public:
    static Behaviour behaviour = Behaviour.Stay;
    static int deleteZombieDistanceSquared = 10000;
    static int forgotZombieDistanceSquared = 225;
    static int canSeeZombieDistanceSquared = 100;
    static int seeZombieDistanceSquared = 25;
    static bool canChangeTarget = true;
    static int updatePeriod = 100;
    static int attackPeriod = 1000;
    static int maxZombiesPerUpdate = 300;
    const ByteBuffer bb = ByteBuffer.allocate(1000000);
    UpdateLimit updateLimiter = std::make_shared<UpdateLimit>(updatePeriod);
    UpdateLimit attackLimiter = std::make_shared<UpdateLimit>(attackPeriod);
    Player player = nullptr;
    const ZombiePacket zombiePacket = std::make_shared<ZombiePacket>();
   private std::unordered_set<int16_t> authoriseZombiesCurrent = std::make_unique<std::unordered_set<>>();
   private std::unordered_set<int16_t> authoriseZombiesLast = std::make_unique<std::unordered_set<>>();
   private const std::vector<int16_t> unknownZombies = std::make_unique<std::vector<>>();
   private const std::unordered_map<int, Zombie> zombies = std::make_unique<std::unordered_map<>>();
   private const ArrayDeque<Zombie> zombies4Add = std::make_unique<ArrayDeque<>>();
   private const ArrayDeque<Zombie> zombies4Delete = std::make_unique<ArrayDeque<>>();
   private const std::unordered_set<int16_t> authoriseZombies = std::make_unique<std::unordered_set<>>();
   private const ArrayDeque<Zombie> SendQueue = std::make_unique<ArrayDeque<>>();
    static Vector2 tmpDir = std::make_shared<Vector2>();

   public FakeClientManager$ZombieSimulator(Player var1) {
      this.player = var1;
   }

    void becomeLocal(Zombie var1) {
      var1.localOwnership = true;
   }

    void becomeRemote(Zombie var1) {
      var1.localOwnership = false;
   }

    void clear() {
    std::unordered_set var1 = this.authoriseZombiesCurrent;
      this.authoriseZombiesCurrent = this.authoriseZombiesLast;
      this.authoriseZombiesLast = var1;
      this.authoriseZombiesLast.removeIf(var1x -> this.zombies.get(int.valueOf(var1x)) == nullptr);
      this.authoriseZombiesCurrent.clear();
   }

    void add(short var1) {
      this.authoriseZombiesCurrent.push_back(var1);
   }

    void receivePacket(ByteBuffer var1) {
    short var2 = var1.getShort();

      for (short var3 = 0; var3 < var2; var3++) {
         this.parseZombie(var1);
      }
   }

    void parseZombie(ByteBuffer var1) {
    ZombiePacket var2 = this.zombiePacket;
      var2.parse(var1, nullptr);
    Zombie var3 = this.zombies.get(int.valueOf(var2.id));
      if (!this.authoriseZombies.contains(var2.id) || var3 == nullptr) {
         if (var3 == nullptr) {
            var3 = std::make_shared<Zombie>(var2.id);
            this.zombies4Add.push_back(var3);
            FakeClientManager.trace(this.player.movement.id, std::string.format("New zombie %s", var3.OnlineID));
         }

         var3.lastUpdate = System.currentTimeMillis();
         var3.zombiePacket.copy(var2);
         var3.x = var2.realX;
         var3.y = var2.realY;
         var3.z = var2.realZ;
      }
   }

    void process() {
    SetView var1 = Sets.difference(this.authoriseZombiesCurrent, this.authoriseZombiesLast);
    UnmodifiableIterator var2 = var1.iterator();

      while (var2.hasNext()) {
    short var3 = (int16_t)var2.next();
    Zombie var4 = this.zombies.get(int.valueOf(var3));
         if (var4 != nullptr) {
            this.becomeLocal(var4);
         } else if (!this.unknownZombies.contains(var3)) {
            this.unknownZombies.push_back(var3);
         }
      }

    SetView var8 = Sets.difference(this.authoriseZombiesLast, this.authoriseZombiesCurrent);
    UnmodifiableIterator var9 = var8.iterator();

      while (var9.hasNext()) {
    short var11 = (int16_t)var9.next();
    Zombie var5 = this.zombies.get(int.valueOf(var11));
         if (var5 != nullptr) {
            this.becomeRemote(var5);
         }
      }

      /* synchronized - TODO: add std::mutex */ (this.authoriseZombies) {
         this.authoriseZombies.clear();
         this.authoriseZombies.addAll(this.authoriseZombiesCurrent);
      }
   }

    void send() {
      if (this.authoriseZombies.size() != 0 || this.unknownZombies.size() != 0) {
         if (this.SendQueue.empty()) {
            /* synchronized - TODO: add std::mutex */ (this.authoriseZombies) {
               for (int16_t var3 : this.authoriseZombies) {
    Zombie var4 = this.zombies.get(int.valueOf(var3));
                  if (var4 != nullptr && var4.OnlineID != -1) {
                     this.SendQueue.push_back(var4);
                  }
               }
            }
         }

         this.bb.clear();
         this.bb.putShort((short)0);
    int var7 = this.unknownZombies.size();
         this.bb.putShort((short)var7);

         for (int var8 = 0; var8 < this.unknownZombies.size(); var8++) {
            if (this.unknownZombies.get(var8) == nullptr) {
               return;
            }

            this.bb.putShort(this.unknownZombies.get(var8));
         }

         this.unknownZombies.clear();
    int var9 = this.bb.position();
         this.bb.putShort((short)maxZombiesPerUpdate);
    int var10 = 0;

         while (!this.SendQueue.empty()) {
    Zombie var11 = this.SendQueue.poll();
            if (var11.OnlineID != -1) {
               var11.zombiePacket.write(this.bb);
               if (++var10 >= maxZombiesPerUpdate) {
                  break;
               }
            }
         }

         if (var10 < maxZombiesPerUpdate) {
    int var12 = this.bb.position();
            this.bb.position(var9);
            this.bb.putShort((short)var10);
            this.bb.position(var12);
         }

         if (var10 > 0 || var7 > 0) {
    ByteBuffer var13 = this.player.client.network.startPacket();
            this.player.client.doPacket(PacketType.ZombieSimulation.getId(), var13);
            var13.put(this.bb.array(), 0, this.bb.position());
            this.player.client.network.endPacketSuperHighUnreliable(this.player.client.connectionGUID);
         }
      }
   }

    void simulate(int var1, Zombie var2) {
    float var3 = IsoUtils.DistanceToSquared(this.player.x, this.player.y, var2.x, var2.y);
      if (!(var3 > deleteZombieDistanceSquared) && (var2.localOwnership || var2.lastUpdate + 5000L >= System.currentTimeMillis())) {
         tmpDir.set(-var2.x + this.player.x, -var2.y + this.player.y);
         if (var2.isMoving) {
    float var4 = 0.2F;
            var2.x = PZMath.lerp(var2.x, var2.zombiePacket.x, var4);
            var2.y = PZMath.lerp(var2.y, var2.zombiePacket.y, var4);
            var2.z = 0.0F;
            var2.dir = IsoDirections.fromAngle(tmpDir);
         }

         if (canChangeTarget) {
            /* synchronized - TODO: add std::mutex */ (this.player.playerManager.players) {
               for (RemotePlayer var6 : this.player.playerManager.players.values()) {
    float var7 = IsoUtils.DistanceToSquared(var6.x, var6.y, var2.x, var2.y);
                  if (var7 < seeZombieDistanceSquared) {
                     var2.zombiePacket.target = var6.OnlineID;
                     break;
                  }
               }
            }
         } else {
            var2.zombiePacket.target = this.player.OnlineID;
         }

         if (behaviour == Behaviour.Stay) {
            var2.isMoving = false;
         } else if (behaviour == Behaviour.Normal) {
            if (var3 > forgotZombieDistanceSquared) {
               var2.isMoving = false;
            }

            if (var3 < canSeeZombieDistanceSquared && (Rand.Next(100) < 1 || var2.dir == IsoDirections.fromAngle(tmpDir))) {
               var2.isMoving = true;
            }

            if (var3 < seeZombieDistanceSquared) {
               var2.isMoving = true;
            }
         } else {
            var2.isMoving = true;
         }

    float var11 = 0.0F;
         if (var2.isMoving) {
    Vector2 var13 = var2.dir.ToVector();
            var11 = 3.0F;
            if (var3 < 100.0F) {
               var11 = 6.0F;
            }

    long var14 = System.currentTimeMillis() - var2.lastUpdate;
            var2.zombiePacket.x = var2.x + var13.x * (float)var14 * 0.001F * var11;
            var2.zombiePacket.y = var2.y + var13.y * (float)var14 * 0.001F * var11;
            var2.zombiePacket.z = (byte)var2.z;
            var2.zombiePacket.moveType = PredictionTypes.Moving;
         } else {
            var2.zombiePacket.x = var2.x;
            var2.zombiePacket.y = var2.y;
            var2.zombiePacket.z = (byte)var2.z;
            var2.zombiePacket.moveType = PredictionTypes.Static;
         }

         var2.zombiePacket.booleanVariables = 0;
         if (var3 < 100.0F) {
            var2.zombiePacket.booleanVariables = (short)(var2.zombiePacket.booleanVariables | 2);
         }

         var2.zombiePacket.timeSinceSeenFlesh = var2.isMoving ? 0 : 100000;
         var2.zombiePacket.smParamTargetAngle = 0;
         var2.zombiePacket.speedMod = 1000;
         var2.zombiePacket.walkType = WalkType.values()[var2.walkType];
         var2.zombiePacket.realX = var2.x;
         var2.zombiePacket.realY = var2.y;
         var2.zombiePacket.realZ = (byte)var2.z;
         var2.zombiePacket.realHealth = (short)(var2.health * 1000.0F);
         var2.zombiePacket.realState = ZombieState.fromString("fakezombie-" + behaviour.toLowerCase());
         if (var2.isMoving) {
            var2.zombiePacket.pfbType = 1;
            var2.zombiePacket.pfbTarget = this.player.OnlineID;
         } else {
            var2.zombiePacket.pfbType = 0;
         }

         if (var3 < 2.0F && this.attackLimiter.Check()) {
            var2.health = var2.health - Player.damage;
            this.sendHitCharacter(var2, Player.damage);
            if (var2.health <= 0.0F) {
               this.player.client.sendChatMessage("DIE!!");
               this.zombies4Delete.push_back(var2);
            }
         }

         var2.lastUpdate = System.currentTimeMillis();
      } else {
         this.zombies4Delete.push_back(var2);
      }
   }

    void writeHitInfoToZombie(ByteBuffer var1, short var2, float var3, float var4, float var5) {
      var1.put((byte)2);
      var1.putShort(var2);
      var1.put((byte)0);
      var1.putFloat(var3);
      var1.putFloat(var4);
      var1.putFloat(0.0F);
      var1.putFloat(var5);
      var1.putFloat(1.0F);
      var1.putInt(100);
   }

    void sendHitCharacter(Zombie var1, float var2) {
    bool var3 = false;
    ByteBuffer var4 = this.player.client.network.startPacket();
      this.player.client.doPacket(PacketType.HitCharacter.getId(), var4);
      var4.put((byte)3);
      var4.putShort(this.player.OnlineID);
      var4.putShort((short)0);
      var4.putFloat(this.player.x);
      var4.putFloat(this.player.y);
      var4.putFloat(this.player.z);
      var4.putFloat(this.player.direction.x);
      var4.putFloat(this.player.direction.y);
      FakeClientManager.WriteStringUTF(var4, "");
      FakeClientManager.WriteStringUTF(var4, "");
      FakeClientManager.WriteStringUTF(var4, "");
      var4.putShort((short)((this.player.weapon_isBareHeads ? 2 : 0) + (var3 ? 8 : 0)));
      var4.putFloat(1.0F);
      var4.putFloat(1.0F);
      var4.putFloat(1.0F);
      FakeClientManager.WriteStringUTF(var4, "default");
    uint8_t var5 = 0;
      var5 = (byte)(var5 | (byte)(this.player.weapon_isBareHeads ? 9 : 0));
      var4.put(var5);
      var4.put((byte)0);
      var4.putShort((short)0);
      var4.putFloat(1.0F);
      var4.putInt(0);
    uint8_t var6 = 1;
      var4.put(var6);

      for (int var7 = 0; var7 < var6; var7++) {
         this.writeHitInfoToZombie(var4, var1.OnlineID, var1.x, var1.y, var2);
      }

      var6 = 0;
      var4.put(var6);
      var6 = 1;
      var4.put(var6);

      for (int var11 = 0; var11 < var6; var11++) {
         this.writeHitInfoToZombie(var4, var1.OnlineID, var1.x, var1.y, var2);
      }

      if (!this.player.weapon_isBareHeads) {
         var4.put((byte)0);
      } else {
         var4.put((byte)1);
         var4.putShort(this.player.registry_id);
         var4.put((byte)1);
         var4.putInt(this.player.weapon_id);
         var4.put((byte)0);
         var4.putInt(0);
         var4.putInt(0);
      }

      var4.putShort(var1.OnlineID);
      var4.putShort((short)(var2 >= var1.health ? 3 : 0));
      var4.putFloat(var1.x);
      var4.putFloat(var1.y);
      var4.putFloat(var1.z);
      var4.putFloat(var1.dir.ToVector().x);
      var4.putFloat(var1.dir.ToVector().y);
      FakeClientManager.WriteStringUTF(var4, "");
      FakeClientManager.WriteStringUTF(var4, "");
      FakeClientManager.WriteStringUTF(var4, "");
      var4.putShort((short)0);
      FakeClientManager.WriteStringUTF(var4, "");
      FakeClientManager.WriteStringUTF(var4, "FRONT");
      var4.put((byte)0);
      var4.putFloat(var2);
      var4.putFloat(1.0F);
      var4.putFloat(this.player.direction.x);
      var4.putFloat(this.player.direction.y);
      var4.putFloat(1.0F);
      var4.put((byte)0);
      if (tmpDir.getLength() > 0.0F) {
         var1.dropPositionX = var1.x + tmpDir.x / tmpDir.getLength();
         var1.dropPositionY = var1.y + tmpDir.y / tmpDir.getLength();
      } else {
         var1.dropPositionX = var1.x;
         var1.dropPositionY = var1.y;
      }

      var4.putFloat(var1.dropPositionX);
      var4.putFloat(var1.dropPositionY);
      var4.put((byte)var1.z);
      var4.putFloat(var1.dir.toAngle());
      this.player.client.network.endPacketImmediate(this.player.client.connectionGUID);
   }

    void sendSendDeadZombie(Zombie var1) {
    ByteBuffer var2 = this.player.client.network.startPacket();
      this.player.client.doPacket(PacketType.ZombieDeath.getId(), var2);
      var2.putShort(var1.OnlineID);
      var2.putFloat(var1.x);
      var2.putFloat(var1.y);
      var2.putFloat(var1.z);
      var2.putFloat(var1.dir.toAngle());
      var2.put((byte)var1.dir.index());
      var2.put((byte)0);
      var2.put((byte)0);
      var2.put((byte)0);
      this.player.client.network.endPacketImmediate(this.player.client.connectionGUID);
   }

    void simulateAll() {
      while (!this.zombies4Add.empty()) {
    Zombie var1 = this.zombies4Add.poll();
         this.zombies.put(int.valueOf(var1.OnlineID), var1);
      }

      this.zombies.forEach(this::simulate);

      while (!this.zombies4Delete.empty()) {
    Zombie var2 = this.zombies4Delete.poll();
         this.zombies.remove(int.valueOf(var2.OnlineID));
      }
   }

    void update() {
      if (this.updateLimiter.Check()) {
         this.simulateAll();
         this.send();
      }
   }
}
} // namespace network
} // namespace zombie
