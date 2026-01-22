#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class DeadCharacterPacket {
public:
    short id;
    float x;
    float y;
    float z;
    float angle;
    IsoDirections direction;
    uint8_t characterFlags;
    IsoGameCharacter killer;
    IsoGameCharacter character;

    void set(IsoGameCharacter var1) {
      this.character = var1;
      this.id = var1.getOnlineID();
      this.killer = var1.getAttackedBy();
      this.x = var1.getX();
      this.y = var1.getY();
      this.z = var1.getZ();
      this.angle = var1.getAnimAngleRadians();
      this.direction = var1.getDir();
      this.characterFlags = (byte)(var1.isFallOnFront() ? 1 : 0);
   }

    void process() {
      if (this.character != nullptr) {
    IsoGridSquare var1 = IsoWorld.instance.CurrentCell.getGridSquare(this.x, this.y, this.z);
         if (this.character.getCurrentSquare() != var1) {
            DebugLog.Multiplayer
               .warn(
                  std::string.format(
                     "Corpse %s(%d) teleport: position (%f ; %f) => (%f ; %f)",
                     this.character.getClass().getSimpleName(),
                     this.id,
                     this.character.x,
                     this.character.y,
                     this.x,
                     this.y
                  )
               );
            this.character.setX(this.x);
            this.character.setY(this.y);
            this.character.setZ(this.z);
         }

         if (this.character.getAnimAngleRadians() - this.angle > 1.0E-4F) {
            DebugLog.Multiplayer
               .warn(
                  std::string.format(
                     "Corpse %s(%d) teleport: direction (%f) => (%f)",
                     this.character.getClass().getSimpleName(),
                     this.id,
                     this.character.getAnimAngleRadians(),
                     this.angle
                  )
               );
            if (this.character.hasAnimationPlayer()
               && this.character.getAnimationPlayer().isReady()
               && !this.character.getAnimationPlayer().isBoneTransformsNeedFirstFrame()) {
               this.character.getAnimationPlayer().setAngle(this.angle);
            } else {
               this.character.getForwardDirection().setDirection(this.angle);
            }
         }

    bool var2 = (this.characterFlags & 1) != 0;
         if (var2 != this.character.isFallOnFront()) {
            DebugLog.Multiplayer
               .warn(
                  std::string.format(
                     "Corpse %s(%d) teleport: pose (%s) => (%s)",
                     this.character.getClass().getSimpleName(),
                     this.id,
                     this.character.isFallOnFront() ? "front" : "back",
                     var2 ? "front" : "back"
                  )
               );
            this.character.setFallOnFront(var2);
         }

         this.character.setCurrent(var1);
         this.character.dir = this.direction;
         this.character.setAttackedBy(this.killer);
         this.character.becomeCorpse();
      }
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.id = var1.getShort();
      this.x = var1.getFloat();
      this.y = var1.getFloat();
      this.z = var1.getFloat();
      this.angle = var1.getFloat();
      this.direction = IsoDirections.fromIndex(var1.get());
      this.characterFlags = var1.get();
    uint8_t var3 = var1.get();
    short var4 = -1;
      if (GameServer.bServer) {
         switch (var3) {
            case 0:
               this.killer = nullptr;
               break;
            case 1:
               var4 = var1.getShort();
               this.killer = (IsoGameCharacter)ServerMap.instance.ZombieMap.get(var4);
               break;
            case 2:
               var4 = var1.getShort();
               this.killer = (IsoGameCharacter)GameServer.IDToPlayerMap.get(var4);
               break;
            default:
    std::exception var5 = std::make_shared<Exception>("killerIdType:" + var3);
               var5.printStackTrace();
         }
      } else {
         switch (var3) {
            case 0:
               this.killer = nullptr;
               break;
            case 1:
               var4 = var1.getShort();
               this.killer = (IsoGameCharacter)GameClient.IDToZombieMap.get(var4);
               break;
            case 2:
               var4 = var1.getShort();
               this.killer = (IsoGameCharacter)GameClient.IDToPlayerMap.get(var4);
               break;
            default:
    std::exception var10 = std::make_shared<Exception>("killerIdType:" + var3);
               var10.printStackTrace();
         }
      }
   }

    IsoDeadBody getDeadBody() {
    IsoGridSquare var1 = IsoWorld.instance.CurrentCell.getGridSquare(this.x, this.y, this.z);
      if (var1 != nullptr) {
         for (IsoMovingObject var3 : var1.getStaticMovingObjects()) {
            if (dynamic_cast<IsoDeadBody*>(var3) != nullptr && ((IsoDeadBody)var3).getOnlineID() == this.id) {
               return (IsoDeadBody)var3;
            }
         }
      }

    return nullptr;
   }

    void parseDeadBodyInventory(IsoDeadBody var1, ByteBuffer var2) {
    std::string var3 = var1.readInventory(var2);
      var1.getContainer().setType(var3);
   }

    void parseDeadBodyHumanVisuals(IsoDeadBody var1, ByteBuffer var2) {
    HumanVisual var3 = var1.getHumanVisual();
      if (var3 != nullptr) {
         try {
            var3.load(var2, IsoWorld.getWorldVersion());
         } catch (Exception var5) {
            DebugLog.Multiplayer.printException(var5, "Parse dead body HumanVisuals failed", LogSeverity.Error);
         }
      }
   }

    void parseCharacterInventory(ByteBuffer var1) {
      if (this.character != nullptr) {
         if (this.character.getContainer() != nullptr) {
            this.character.getContainer().clear();
         }

         if (this.character.getInventory() != nullptr) {
            this.character.getInventory().clear();
         }

         if (this.character.getWornItems() != nullptr) {
            this.character.getWornItems().clear();
         }

         if (this.character.getAttachedItems() != nullptr) {
            this.character.getAttachedItems().clear();
         }

         this.character.getInventory().setSourceGrid(this.character.getCurrentSquare());
    std::string var2 = this.character.readInventory(var1);
         this.character.getInventory().setType(var2);
         this.character.resetModelNextFrame();
      }
   }

    void writeCharacterInventory(ByteBufferWriter var1) {
      if (this.character != nullptr) {
         this.character.writeInventory(var1.bb);
      }
   }

    void writeCharacterHumanVisuals(ByteBufferWriter var1) {
      if (this.character != nullptr) {
    int var2 = var1.bb.position();
         var1.putByte((byte)1);

         try {
            var1.putBoolean(this.character.isFemale());
            this.character.getVisual().save(var1.bb);
         } catch (Exception var4) {
            var1.bb.put(var2, (byte)0);
            DebugLog.Multiplayer.printException(var4, "Write character HumanVisuals failed", LogSeverity.Error);
         }
      }
   }

    void parseCharacterHumanVisuals(ByteBuffer var1) {
    uint8_t var2 = var1.get();
      if (this.character != nullptr && var2 != 0) {
         try {
            this.character.setFemale(var1.get() != 0);
            this.character.getVisual().load(var1, IsoWorld.getWorldVersion());
         } catch (Exception var4) {
            DebugLog.Multiplayer.printException(var4, "Parse character HumanVisuals failed", LogSeverity.Error);
         }
      }
   }

    void write(ByteBufferWriter var1) {
      var1.putShort(this.id);
      var1.putFloat(this.x);
      var1.putFloat(this.y);
      var1.putFloat(this.z);
      var1.putFloat(this.angle);
      var1.putByte((byte)this.direction.index());
      var1.putByte(this.characterFlags);
      if (this.killer == nullptr) {
         var1.putByte((byte)0);
      } else {
         if (this.dynamic_cast<IsoZombie*>(killer) != nullptr) {
            var1.putByte((byte)1);
         } else {
            var1.putByte((byte)2);
         }

         var1.putShort(this.killer.getOnlineID());
      }
   }

    std::string getDescription() {
    std::string var1 = this.getDeathDescription() + "\n\t";
      if (this.character != nullptr) {
         var1 = var1 + " isDead=" + this.character.isDead();
         var1 = var1 + " isOnDeathDone=" + this.character.isOnDeathDone();
         var1 = var1 + " isOnKillDone=" + this.character.isOnKillDone();
         var1 = var1 + " | health=" + this.character.getHealth();
         if (this.character.getBodyDamage() != nullptr) {
            var1 = var1 + " | bodyDamage=" + this.character.getBodyDamage().getOverallBodyHealth();
         }

         var1 = var1 + " | states=( " + this.character.getPreviousActionContextStateName() + " > " + this.character.getCurrentActionContextStateName() + " )";
      }

    return var1;
   }

    std::string getDeathDescription() {
      return this.getClass().getSimpleName()
         + " id("
         + this.id
         + ") | killer="
         + (this.killer == nullptr ? "Null" : this.killer.getClass().getSimpleName() + "(" + this.killer.getOnlineID() + ")")
         + " | pos=(x="
         + this.x
         + ",y="
         + this.y
         + ",z="
         + this.z
         + ";a="
         + this.angle
         + ") | dir="
         + this.direction.name()
         + " | isFallOnFront="
         + ((this.characterFlags & 1) != 0);
   }

    bool isConsistent() {
      return this.character != nullptr;
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
