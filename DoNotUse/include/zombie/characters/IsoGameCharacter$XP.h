#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/characters/IsoGameCharacter/PerkInfo.h"
#include "zombie/characters/IsoGameCharacter/XPMultiplier.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/characters/skills/PerkFactory/Perk.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/characters/traits/TraitFactory.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/Userlog/UserlogType.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace characters {


class IsoGameCharacter {
public:
    int level;
    int lastlevel;
    float TotalXP;
   public std::unordered_map<Perk, float> XPMap;
    float lastXPSumm;
    long lastXPTime;
    float lastXPGrowthRate;
    static const float MaxXPGrowthRate = 1000.0F;
   public std::unordered_map<Perk, XPMultiplier> XPMapMultiplier;
    IsoGameCharacter chr;

   public IsoGameCharacter$XP(IsoGameCharacter var1, IsoGameCharacter var2) {
      this.this$0 = var1;
      this.level = 0;
      this.lastlevel = 0;
      this.TotalXP = 0.0F;
      this.XPMap = std::make_unique<std::unordered_map<>>();
      this.lastXPSumm = 0.0F;
      this.lastXPTime = System.currentTimeMillis();
      this.lastXPGrowthRate = 0.0F;
      this.XPMapMultiplier = std::make_unique<std::unordered_map<>>();
      this.chr = nullptr;
      this.chr = var2;
   }

    void update() {
      if (GameServer.bServer && this.dynamic_cast<IsoPlayer*>(chr) != nullptr) {
         if (System.currentTimeMillis() - this.lastXPTime > 60000L) {
            this.lastXPTime = System.currentTimeMillis();
    float var1 = 0.0F;

            for (float var3 : this.XPMap.values()) {
               var1 += var3;
            }

            this.lastXPGrowthRate = var1 - this.lastXPSumm;
            this.lastXPSumm = var1;
            if (this.lastXPGrowthRate
               > 1000.0 * SandboxOptions.instance.XpMultiplier.getValue() * ServerOptions.instance.AntiCheatProtectionType9ThresholdMultiplier.getValue()) {
    UdpConnection var4 = GameServer.getConnectionFromPlayer((IsoPlayer)this.chr);
               if (ServerOptions.instance.AntiCheatProtectionType9.getValue() && PacketValidator.checkUser(var4)) {
                  PacketValidator.doKickUser(var4, this.getClass().getSimpleName(), "Type9", nullptr);
               } else if (this.lastXPGrowthRate
                  > 1000.0
                     * SandboxOptions.instance.XpMultiplier.getValue()
                     * ServerOptions.instance.AntiCheatProtectionType9ThresholdMultiplier.getValue()
                     / 2.0) {
                  PacketValidator.doLogUser(var4, UserlogType.SuspiciousActivity, this.getClass().getSimpleName(), "Type9");
               }
            }
         }
      }
   }

    void addXpMultiplier(Perk var1, float var2, int var3, int var4) {
    XPMultiplier var5 = this.XPMapMultiplier.get(var1);
      if (var5 == nullptr) {
         var5 = std::make_unique<XPMultiplier>();
      }

      var5.multiplier = var2;
      var5.minLevel = var3;
      var5.maxLevel = var4;
      this.XPMapMultiplier.put(var1, var5);
   }

   public std::unordered_map<Perk, XPMultiplier> getMultiplierMap() {
      return this.XPMapMultiplier;
   }

    float getMultiplier(Perk var1) {
    XPMultiplier var2 = this.XPMapMultiplier.get(var1);
    return var2 = = nullptr ? 0.0F : var2.multiplier;
   }

    int getPerkBoost(Perk var1) {
      return this.this$0.getDescriptor().getXPBoostMap().get(var1) != nullptr ? (int)this.this$0.getDescriptor().getXPBoostMap().get(var1) : 0;
   }

    void setPerkBoost(Perk var1, int var2) {
      if (var1 != nullptr && var1 != Perks.None && var1 != Perks.MAX) {
         var2 = PZMath.clamp(var2, 0, 10);
         if (var2 == 0) {
            this.this$0.getDescriptor().getXPBoostMap().remove(var1);
         } else {
            this.this$0.getDescriptor().getXPBoostMap().put(var1, var2);
         }
      }
   }

    int getLevel() {
      return this.level;
   }

    void setLevel(int var1) {
      this.level = var1;
   }

    float getTotalXp() {
      return this.TotalXP;
   }

    void AddXP(Perk var1, float var2) {
      if (this.dynamic_cast<IsoPlayer*>(chr) != nullptr && ((IsoPlayer)this.chr).isLocalPlayer()) {
         this.AddXP(var1, var2, true, true, false);
      }
   }

    void AddXPNoMultiplier(Perk var1, float var2) {
    XPMultiplier var3 = this.getMultiplierMap().remove(var1);

      try {
         this.AddXP(var1, var2);
      } finally {
         if (var3 != nullptr) {
            this.getMultiplierMap().put(var1, var3);
         }
      }
   }

    void AddXP(Perk var1, float var2, bool var3, bool var4, bool var5) {
      if (!var5 && GameClient.bClient && this.dynamic_cast<IsoPlayer*>(chr) != nullptr) {
         GameClient.instance.sendAddXp((IsoPlayer)this.chr, var1, (int)var2);
      }

    Perk var6 = nullptr;

      for (int var7 = 0; var7 < PerkFactory.PerkList.size(); var7++) {
    Perk var8 = (Perk)PerkFactory.PerkList.get(var7);
         if (var8.getType() == var1) {
            var6 = var8;
            break;
         }
      }

      if (var6.getType() != Perks.Fitness || !(this.dynamic_cast<IsoPlayer*>(chr) != nullptr) || ((IsoPlayer)this.chr).getNutrition().canAddFitnessXp()) {
         if (var6.getType() == Perks.Strength && this.dynamic_cast<IsoPlayer*>(chr) != nullptr) {
            if (((IsoPlayer)this.chr).getNutrition().getProteins() > 50.0F && ((IsoPlayer)this.chr).getNutrition().getProteins() < 300.0F) {
               var2 = (float)(var2 * 1.5);
            }

            if (((IsoPlayer)this.chr).getNutrition().getProteins() < -300.0F) {
               var2 = (float)(var2 * 0.7);
            }
         }

    float var15 = this.getXP(var1);
    float var16 = var6.getTotalXpForLevel(10);
         if (!(var2 >= 0.0F) || !(var15 >= var16)) {
    float var9 = 1.0F;
            if (var4) {
    bool var10 = false;

               for (Entry var12 : this.this$0.getDescriptor().getXPBoostMap().entrySet()) {
                  if (var12.getKey() == var6.getType()) {
                     var10 = true;
                     if ((int)var12.getValue() == 0 && !this.isSkillExcludedFromSpeedReduction((Perk)var12.getKey())) {
                        var9 *= 0.25F;
                     } else if ((int)var12.getValue() == 1 && var12.getKey() == Perks.Sprinting) {
                        var9 = (float)(var9 * 1.25);
                     } else if ((int)var12.getValue() == 1) {
                        var9 = (float)(var9 * 1.0);
                     } else if ((int)var12.getValue() == 2 && !this.isSkillExcludedFromSpeedIncrease((Perk)var12.getKey())) {
                        var9 = (float)(var9 * 1.33);
                     } else if ((int)var12.getValue() >= 3 && !this.isSkillExcludedFromSpeedIncrease((Perk)var12.getKey())) {
                        var9 = (float)(var9 * 1.66);
                     }
                  }
               }

               if (!var10 && !this.isSkillExcludedFromSpeedReduction(var6.getType())) {
                  var9 = 0.25F;
               }

               if (this.this$0.Traits.FastLearner.isSet() && !this.isSkillExcludedFromSpeedIncrease(var6.getType())) {
                  var9 *= 1.3F;
               }

               if (this.this$0.Traits.SlowLearner.isSet() && !this.isSkillExcludedFromSpeedReduction(var6.getType())) {
                  var9 *= 0.7F;
               }

               if (this.this$0.Traits.Pacifist.isSet()) {
                  if (var6.getType() == Perks.SmallBlade
                     || var6.getType() == Perks.LongBlade
                     || var6.getType() == Perks.SmallBlunt
                     || var6.getType() == Perks.Spear
                     || var6.getType() == Perks.Maintenance
                     || var6.getType() == Perks.Blunt
                     || var6.getType() == Perks.Axe) {
                     var9 *= 0.75F;
                  } else if (var6.getType() == Perks.Aiming) {
                     var9 *= 0.75F;
                  }
               }

               var2 *= var9;
    float var18 = this.getMultiplier(var1);
               if (var18 > 1.0F) {
                  var2 *= var18;
               }

               if (!var6.isPassiv()) {
                  var2 = (float)(var2 * SandboxOptions.instance.XpMultiplier.getValue());
               } else if (var6.isPassiv() && SandboxOptions.instance.XpMultiplierAffectsPassive.getValue()) {
                  var2 = (float)(var2 * SandboxOptions.instance.XpMultiplier.getValue());
               }
            }

    float var17 = var15 + var2;
            if (var17 < 0.0F) {
               var17 = 0.0F;
               var2 = -var15;
            }

            if (var17 > var16) {
               var17 = var16;
               var2 = var16 - var15;
            }

            this.XPMap.put(var1, var17);

            for (float var19 = var6.getTotalXpForLevel(this.chr.getPerkLevel(var6) + 1);
               var15 < var19 && var17 >= var19;
               var19 = var6.getTotalXpForLevel(this.chr.getPerkLevel(var6) + 1)
            ) {
               this.this$0.LevelPerk(var1);
               if (this.dynamic_cast<IsoPlayer*>(chr) != nullptr && ((IsoPlayer)this.chr).isLocalPlayer() && !this.chr.getEmitter().isPlaying("GainExperienceLevel")) {
                  this.chr.getEmitter().playSoundImpl("GainExperienceLevel", (IsoObject)nullptr);
               }

               if (this.chr.getPerkLevel(var6) >= 10) {
                  break;
               }
            }

    XPMultiplier var20 = this.getMultiplierMap().get(var6);
            if (var20 != nullptr) {
    float var13 = var6.getTotalXpForLevel(var20.minLevel - 1);
    float var14 = var6.getTotalXpForLevel(var20.maxLevel);
               if (var15 >= var13 && var17 < var13 || var15 < var14 && var17 >= var14) {
                  this.getMultiplierMap().remove(var6);
               }
            }

            if (var3) {
               LuaEventManager.triggerEventGarbage("AddXP", this.chr, var1, var2);
            }
         }
      }
   }

    bool isSkillExcludedFromSpeedReduction(Perk var1) {
      if (var1 == Perks.Sprinting) {
    return true;
      } else {
    return var1 = = Perks.Fitness ? true : var1 == Perks.Strength;
      }
   }

    bool isSkillExcludedFromSpeedIncrease(Perk var1) {
    return var1 = = Perks.Fitness ? true : var1 == Perks.Strength;
   }

    float getXP(Perk var1) {
      return this.XPMap.containsKey(var1) ? this.XPMap.get(var1) : 0.0F;
   }

    void AddXP(HandWeapon var1, int var2) {
   }

    void setTotalXP(float var1) {
      this.TotalXP = var1;
   }

    void savePerk(ByteBuffer var1, Perk var2) {
      GameWindow.WriteStringUTF(var1, var2 == nullptr ? "" : var2.getId());
   }

    Perk loadPerk(ByteBuffer var1, int var2) {
      if (var2 >= 152) {
    std::string var5 = GameWindow.ReadStringUTF(var1);
    Perk var6 = Perks.FromString(var5);
    return var6 = = Perks.MAX ? nullptr : var6;
      } else {
    int var3 = var1.getInt();
         if (var3 >= 0 && var3 < Perks.MAX.index()) {
    Perk var4 = Perks.fromIndex(var3);
    return var4 = = Perks.MAX ? nullptr : var4;
         } else {
    return nullptr;
         }
      }
   }

    void recalcSumm() {
    float var1 = 0.0F;

      for (float var3 : this.XPMap.values()) {
         var1 += var3;
      }

      this.lastXPSumm = var1;
      this.lastXPTime = System.currentTimeMillis();
      this.lastXPGrowthRate = 0.0F;
   }

    void load(ByteBuffer var1, int var2) {
    int var3 = var1.getInt();
      this.chr.Traits.clear();

      for (int var4 = 0; var4 < var3; var4++) {
    std::string var5 = GameWindow.ReadString(var1);
         if (TraitFactory.getTrait(var5) != nullptr) {
            if (!this.chr.Traits.contains(var5)) {
               this.chr.Traits.push_back(var5);
            }
         } else {
            DebugLog.General.error("unknown trait \"" + var5 + "\"");
         }
      }

      this.TotalXP = var1.getFloat();
      this.level = var1.getInt();
      this.lastlevel = var1.getInt();
      this.XPMap.clear();
    int var12 = var1.getInt();

      for (int var13 = 0; var13 < var12; var13++) {
    Perk var6 = this.loadPerk(var1, var2);
    float var7 = var1.getFloat();
         if (var6 != nullptr) {
            this.XPMap.put(var6, var7);
         }
      }

      if (var2 < 162) {
    int var14 = var1.getInt();

         for (int var16 = 0; var16 < var14; var16++) {
    Perk var19 = this.loadPerk(var1, var2);
         }
      }

      this.this$0.PerkList.clear();
    int var15 = var1.getInt();

      for (int var17 = 0; var17 < var15; var17++) {
    Perk var20 = this.loadPerk(var1, var2);
    int var8 = var1.getInt();
         if (var20 != nullptr) {
    PerkInfo var9 = std::make_shared<PerkInfo>(this.this$0);
            var9.perk = var20;
            var9.level = var8;
            this.this$0.PerkList.push_back(var9);
         }
      }

    int var18 = var1.getInt();

      for (int var21 = 0; var21 < var18; var21++) {
    Perk var22 = this.loadPerk(var1, var2);
    float var23 = var1.getFloat();
    uint8_t var10 = var1.get();
    uint8_t var11 = var1.get();
         if (var22 != nullptr) {
            this.addXpMultiplier(var22, var23, var10, var11);
         }
      }

      if (this.TotalXP > this.this$0.getXpForLevel(this.getLevel() + 1)) {
         this.setTotalXP(this.chr.getXpForLevel(this.getLevel()));
      }

      this.recalcSumm();
   }

    void save(ByteBuffer var1) {
      var1.putInt(this.chr.Traits.size());

      for (int var2 = 0; var2 < this.chr.Traits.size(); var2++) {
         GameWindow.WriteString(var1, this.chr.Traits.get(var2));
      }

      var1.putFloat(this.TotalXP);
      var1.putInt(this.level);
      var1.putInt(this.lastlevel);
      var1.putInt(this.XPMap.size());
    Iterator var5 = this.XPMap.entrySet().iterator();

      while (var5 != nullptr && var5.hasNext()) {
    Entry var3 = (Entry)var5.next();
         this.savePerk(var1, (Perk)var3.getKey());
         var1.putFloat((float)var3.getValue());
      }

      var1.putInt(this.this$0.PerkList.size());

      for (int var6 = 0; var6 < this.this$0.PerkList.size(); var6++) {
    PerkInfo var4 = (PerkInfo)this.this$0.PerkList.get(var6);
         this.savePerk(var1, var4.perk);
         var1.putInt(var4.level);
      }

      var1.putInt(this.XPMapMultiplier.size());
    Iterator var7 = this.XPMapMultiplier.entrySet().iterator();

      while (var7 != nullptr && var7.hasNext()) {
    Entry var8 = (Entry)var7.next();
         this.savePerk(var1, (Perk)var8.getKey());
         var1.putFloat(((XPMultiplier)var8.getValue()).multiplier);
         var1.put((byte)((XPMultiplier)var8.getValue()).minLevel);
         var1.put((byte)((XPMultiplier)var8.getValue()).maxLevel);
      }
   }

    void setXPToLevel(Perk var1, int var2) {
    Perk var3 = nullptr;

      for (int var4 = 0; var4 < PerkFactory.PerkList.size(); var4++) {
    Perk var5 = (Perk)PerkFactory.PerkList.get(var4);
         if (var5.getType() == var1) {
            var3 = var5;
            break;
         }
      }

      if (var3 != nullptr) {
         this.XPMap.put(var1, var3.getTotalXpForLevel(var2));
      }
   }
}
} // namespace characters
} // namespace zombie
