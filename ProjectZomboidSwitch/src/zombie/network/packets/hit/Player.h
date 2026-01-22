#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class Player : public char {
public:
    IsoPlayer player;
    short playerIndex;
    short playerFlags;
    float charge;
    float perkAiming;
    float combatSpeed;
    std::string attackType;
    AttackVars attackVars = std::make_shared<AttackVars>();
   std::vector<HitInfo> hitList = std::make_unique<std::vector<>>();

    void set(IsoPlayer var1, bool var2) {
      super.set(var1);
      this.playerIndex = var1.isLocal() ? (short)var1.getPlayerNum() : -1;
      this.player = var1;
      this.playerFlags = 0;
      this.playerFlags = (short)(this.playerFlags | (short)(var1.isAimAtFloor() ? 1 : 0));
      this.playerFlags = (short)(this.playerFlags | (short)(var1.isDoShove() ? 2 : 0));
      this.playerFlags = (short)(this.playerFlags | (short)(var1.isAttackFromBehind() ? 4 : 0));
      this.playerFlags |= (short)(var2 ? 8 : 0);
      this.charge = var1.useChargeDelta;
      this.perkAiming = var1.getPerkLevel(Perks.Aiming);
      this.combatSpeed = var1.getVariableFloat("CombatSpeed", 1.0F);
      this.attackType = var1.getAttackType();
      this.attackVars.copy(var1.attackVars);
      this.hitList.clear();
      this.hitList.addAll(var1.hitList);
   }

    void parsePlayer(UdpConnection var1) {
      if (GameServer.bServer) {
         if (var1 != nullptr && this.playerIndex != -1) {
            this.player = GameServer.getPlayerFromConnection(var1, this.playerIndex);
         } else {
            this.player = (IsoPlayer)GameServer.IDToPlayerMap.get(this.ID);
         }

         this.character = this.player;
      } else if (GameClient.bClient) {
         this.player = (IsoPlayer)GameClient.IDToPlayerMap.get(this.ID);
         if (this.player == nullptr) {
    IsoPlayer var2 = IsoPlayer.getInstance();
            if (var2 != nullptr) {
               this.player = std::make_shared<IsoPlayer>(var2.getCell(), std::make_unique<SurvivorDesc>(), (int)var2.x, (int)var2.y, (int)var2.z);
            }
         }

         this.character = this.player;
      }
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      super.parse(var1, var2);
      this.playerIndex = var1.getShort();
      this.playerFlags = var1.getShort();
      this.charge = var1.getFloat();
      this.perkAiming = var1.getFloat();
      this.combatSpeed = var1.getFloat();
      this.attackType = GameWindow.ReadString(var1);
      this.attackVars.parse(var1, var2);
    uint8_t var3 = var1.get();

      for (int var4 = 0; var4 < var3; var4++) {
    HitInfo var5 = std::make_shared<HitInfo>();
         var5.parse(var1, var2);
         this.hitList.push_back(var5);
      }
   }

    void write(ByteBufferWriter var1) {
      super.write(var1);
      var1.putShort(this.playerIndex);
      var1.putShort(this.playerFlags);
      var1.putFloat(this.charge);
      var1.putFloat(this.perkAiming);
      var1.putFloat(this.combatSpeed);
      var1.putUTF(this.attackType);
      this.attackVars.write(var1);
    uint8_t var2 = (byte)this.hitList.size();
      var1.putByte(var2);

      for (int var3 = 0; var3 < var2; var3++) {
         this.hitList.get(var3).write(var1);
      }
   }

    bool isConsistent() {
      return super.isConsistent() && this.player != nullptr;
   }

    std::string getDescription() {
    std::string var1 = "";
    uint8_t var2 = (byte)Math.min(100, this.hitList.size());

      for (int var3 = 0; var3 < var2; var3++) {
    HitInfo var4 = this.hitList.get(var3);
         var1 = var1 + var4.getDescription();
      }

      return super.getDescription()
         + "\n\tPlayer [ player "
         + (this.player == nullptr ? "?" : "\"" + this.player.getUsername() + "\"")
         + " | charge="
         + this.charge
         + " | perkAiming="
         + this.perkAiming
         + " | combatSpeed="
         + this.combatSpeed
         + " | attackType=\""
         + this.attackType
         + "\" | isAimAtFloor="
         + ((this.playerFlags & 1) != 0)
         + " | isDoShove="
         + ((this.playerFlags & 2) != 0)
         + " | isAttackFromBehind="
         + ((this.playerFlags & 4) != 0)
         + " | isCriticalHit="
         + ((this.playerFlags & 8) != 0)
         + " | _bodyDamage="
         + (this.player == nullptr ? "?" : this.player.getBodyDamage().getHealth())
         + this.attackVars.getDescription()
         + "\n\t hitList=["
         + var1
         + "](count="
         + this.hitList.size()
         + ") ]";
   }

    void process() {
      super.process();
      this.player.useChargeDelta = this.charge;
      this.player.setVariable("recoilVarX", this.perkAiming / 10.0F);
      this.player.setAttackType(this.attackType);
      this.player.setVariable("CombatSpeed", this.combatSpeed);
      this.player.setVariable("AimFloorAnim", (this.playerFlags & 1) != 0);
      this.player.setAimAtFloor((this.playerFlags & 1) != 0);
      this.player.setDoShove((this.playerFlags & 2) != 0);
      this.player.setAttackFromBehind((this.playerFlags & 4) != 0);
      this.player.setCriticalHit((this.playerFlags & 8) != 0);
   }

    void attack(HandWeapon var1, bool var2) {
      if (GameClient.bClient) {
         this.player.attackStarted = false;
         this.player.attackVars.copy(this.attackVars);
         this.player.hitList.clear();
         this.player.hitList.addAll(this.hitList);
         this.player.pressedAttack(false);
         if (this.player.isAttackStarted() && var1.isRanged() && !this.player.isDoShove()) {
            this.player.startMuzzleFlash();
         }

         if (var1.getPhysicsObject() != nullptr) {
            this.player.Throw(var1);
         }
      } else if (GameServer.bServer && var2 && !this.player.getSafety().isEnabled()) {
         this.player.getSafety().setCooldown(this.player.getSafety().getCooldown() + ServerOptions.getInstance().SafetyCooldownTimer.getValue());
         GameServer.sendChangeSafety(this.player.getSafety());
      }
   }

    IsoGameCharacter getCharacter() {
      return this.player;
   }

    IsoPlayer getPlayer() {
      return this.player;
   }

    bool isRelevant(UdpConnection var1) {
      return var1.RelevantTo(this.positionX, this.positionY);
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
