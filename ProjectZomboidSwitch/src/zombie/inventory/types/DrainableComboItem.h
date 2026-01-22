#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/interfaces/IUpdater.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemUser.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/RainManager.h"
#include "zombie/network/GameServer.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Item/Type.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace inventory {
namespace types {


class DrainableComboItem : public InventoryItem {
public:
    bool bUseWhileEquiped = true;
    bool bUseWhileUnequiped = false;
    int ticksPerEquipUse = 30;
    float useDelta = 0.03125F;
    float delta = 1.0F;
    float ticks = 0.0F;
    std::string ReplaceOnDeplete = nullptr;
    std::string ReplaceOnDepleteFullType = nullptr;
   public List<std::string> ReplaceOnCooked = nullptr;
    std::string OnCooked = nullptr;
    float rainFactor = 0.0F;
    bool canConsolidate = true;
    float WeightEmpty = 0.0F;
    static const float MIN_HEAT = 0.2F;
    static const float MAX_HEAT = 3.0F;
    float Heat = 1.0F;
    int LastCookMinute = 0;

    public DrainableComboItem(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      super(var1, var2, var3, var4);
   }

    public DrainableComboItem(const std::string& var1, const std::string& var2, const std::string& var3, Item var4) {
      super(var1, var2, var3, var4);
   }

    bool IsDrainable() {
    return true;
   }

    int getSaveType() {
      return Type.Drainable.ordinal();
   }

    bool CanStack(InventoryItem var1) {
    return false;
   }

    float getUsedDelta() {
      return this.delta;
   }

    int getDrainableUsesInt() {
      return (int)Math.floor((this.getUsedDelta() + 1.0E-4) / this.getUseDelta());
   }

    float getDrainableUsesFloat() {
      return this.getUsedDelta() / this.getUseDelta();
   }

    void render() {
   }

    void renderlast() {
   }

    void setUsedDelta(float var1) {
      this.delta = PZMath.clamp(var1, 0.0F, 1.0F);
      this.updateWeight();
   }

    bool shouldUpdateInWorld() {
      if (!GameServer.bServer && this.Heat != 1.0F) {
    return true;
      } else if (this.canStoreWater() && this.isWaterSource() && this.getUsedDelta() < 1.0F) {
    IsoGridSquare var1 = this.getWorldItem().getSquare();
         return var1 != nullptr && var1.isOutside();
      } else {
    return false;
      }
   }

    void update() {
    ItemContainer var1 = this.getOutermostContainer();
      if (var1 != nullptr) {
    float var2 = var1.getTemprature();
         if (this.Heat > var2) {
            this.Heat = this.Heat - 0.001F * GameTime.instance.getMultiplier();
            if (this.Heat < Math.max(0.2F, var2)) {
               this.Heat = Math.max(0.2F, var2);
            }
         }

         if (this.Heat < var2) {
            this.Heat = this.Heat + var2 / 1000.0F * GameTime.instance.getMultiplier();
            if (this.Heat > Math.min(3.0F, var2)) {
               this.Heat = Math.min(3.0F, var2);
            }
         }

         if (this.IsCookable) {
            if (this.Heat > 1.6F) {
    int var3 = GameTime.getInstance().getMinutes();
               if (var3 != this.LastCookMinute) {
                  this.LastCookMinute = var3;
    float var4 = this.Heat / 1.5F;
                  if (var1.getTemprature() <= 1.6F) {
                     var4 *= 0.05F;
                  }

    float var5 = this.CookingTime;
                  if (var5 < 1.0F) {
                     var5 = 10.0F;
                  }

                  var5 += var4;
                  if (this.isTaintedWater() && var5 > Math.min(this.MinutesToCook, 10.0F)) {
                     this.setTaintedWater(false);
                  }

                  if (!this.isCooked() && var5 > this.MinutesToCook) {
                     this.setCooked(true);
                     if (this.getReplaceOnCooked() != nullptr) {
                        for (int var6 = 0; var6 < this.getReplaceOnCooked().size(); var6++) {
    InventoryItem var7 = this.container.AddItem(this.getReplaceOnCooked().get(var6));
                           if (var7 != nullptr) {
                              if (dynamic_cast<DrainableComboItem*>(var7) != nullptr) {
                                 ((DrainableComboItem)var7).setUsedDelta(this.getUsedDelta());
                              }

                              var7.copyConditionModData(this);
                           }
                        }

                        this.container.Remove(this);
                        IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this);
                        return;
                     }

                     if (this.getOnCooked() != nullptr) {
                        LuaManager.caller.protectedCall(LuaManager.thread, LuaManager.env.rawget(this.getOnCooked()), new Object[]{this});
                        return;
                     }
                  }

                  if (this.CookingTime > this.MinutesToBurn) {
                     this.Burnt = true;
                     this.setCooked(false);
                  }
               }
            }
         } else if (var1 != nullptr && var1.isMicrowave() && this.isTaintedWater() && this.Heat > 1.6F) {
    int var11 = GameTime.getInstance().getMinutes();
            if (var11 != this.LastCookMinute) {
               this.LastCookMinute = var11;
    float var13 = 1.0F;
               if (var1.getTemprature() <= 1.6F) {
                  var13 = (float)(var13 * 0.2);
               }

               this.CookingTime += var13;
               if (this.CookingTime > 10.0F) {
                  this.setTaintedWater(false);
               }
            }
         }
      }

      if (this.container == nullptr && this.Heat != 1.0F) {
    float var8 = 1.0F;
         if (this.Heat > var8) {
            this.Heat = this.Heat - 0.001F * GameTime.instance.getMultiplier();
            if (this.Heat < var8) {
               this.Heat = var8;
            }
         }

         if (this.Heat < var8) {
            this.Heat = this.Heat + var8 / 1000.0F * GameTime.instance.getMultiplier();
            if (this.Heat > var8) {
               this.Heat = var8;
            }
         }
      }

      if (this.bUseWhileEquiped && this.delta > 0.0F) {
    IsoPlayer var9 = nullptr;
         if (this.container != nullptr && this.container.dynamic_cast<IsoPlayer*>(parent) != nullptr) {
            for (int var12 = 0; var12 < IsoPlayer.numPlayers; var12++) {
               if (this.container.parent == IsoPlayer.players[var12]) {
                  var9 = IsoPlayer.players[var12];
               }
            }
         }

         if (var9 != nullptr && (this.canBeActivated() && this.isActivated() || !this.canBeActivated()) && (var9.isHandItem(this) || var9.isAttachedItem(this))) {
            this.ticks = this.ticks + GameTime.instance.getMultiplier();

            while (this.ticks >= this.ticksPerEquipUse) {
               this.ticks = this.ticks - this.ticksPerEquipUse;
               if (this.delta > 0.0F) {
                  this.Use();
               }
            }
         }
      }

      if (this.bUseWhileUnequiped && this.delta > 0.0F && (this.canBeActivated() && this.isActivated() || !this.canBeActivated())) {
         this.ticks = this.ticks + GameTime.instance.getMultiplier();

         while (this.ticks >= this.ticksPerEquipUse) {
            this.ticks = this.ticks - this.ticksPerEquipUse;
            if (this.delta > 0.0F) {
               this.Use();
            }
         }
      }

      if (this.getWorldItem() != nullptr && this.canStoreWater() && this.isWaterSource() && RainManager.isRaining() && this.getRainFactor() > 0.0F) {
    IsoGridSquare var10 = this.getWorldItem().getSquare();
         if (var10 != nullptr && var10.isOutside()) {
            this.setUsedDelta(this.getUsedDelta() + 0.001F * RainManager.getRainIntensity() * GameTime.instance.getMultiplier() * this.getRainFactor());
            if (this.getUsedDelta() > 1.0F) {
               this.setUsedDelta(1.0F);
            }

            this.setTaintedWater(true);
            this.updateWeight();
         }
      }
   }

    void Use() {
      if (this.getWorldItem() != nullptr) {
         ItemUser.UseItem(this);
      } else {
         this.delta = this.delta - this.useDelta;
         if (this.uses > 1) {
    int var1 = this.uses - 1;
            this.uses = 1;
    InventoryItem var2 = InventoryItemFactory.CreateItem(this.getFullType());
            var2.setUses(var1);
            this.container.AddItem(var2);
         }

         if (this.delta <= 1.0E-4F) {
            this.delta = 0.0F;
            if (this.getReplaceOnDeplete() != nullptr) {
    std::string var4 = this.getReplaceOnDepleteFullType();
               if (this.container != nullptr) {
    InventoryItem var5 = this.container.AddItem(var4);
                  if (this.container.dynamic_cast<IsoGameCharacter*>(parent) != nullptr var3) {
                     if (var3.getPrimaryHandItem() == this) {
                        var3.setPrimaryHandItem(var5);
                     }

                     if (var3.getSecondaryHandItem() == this) {
                        var3.setSecondaryHandItem(var5);
                     }
                  }

                  var5.setCondition(this.getCondition());
                  var5.setFavorite(this.isFavorite());
                  this.container.Remove(this);
               }
            } else {
               super.Use();
            }
         }

         this.updateWeight();
      }
   }

    void updateWeight() {
      if (this.getReplaceOnDeplete() != nullptr) {
         if (this.getUsedDelta() >= 1.0F) {
            this.setCustomWeight(true);
            this.setActualWeight(this.getScriptItem().getActualWeight());
            this.setWeight(this.getActualWeight());
            return;
         }

    Item var1 = ScriptManager.instance.getItem(this.ReplaceOnDepleteFullType);
         if (var1 != nullptr) {
            this.setCustomWeight(true);
            this.setActualWeight((this.getScriptItem().getActualWeight() - var1.getActualWeight()) * this.getUsedDelta() + var1.getActualWeight());
            this.setWeight(this.getActualWeight());
         }
      }

      if (this.getWeightEmpty() != 0.0F) {
         this.setCustomWeight(true);
         this.setActualWeight((this.getScriptItem().getActualWeight() - this.WeightEmpty) * this.getUsedDelta() + this.WeightEmpty);
      }
   }

    float getWeightEmpty() {
      return this.WeightEmpty;
   }

    void setWeightEmpty(float var1) {
      this.WeightEmpty = var1;
   }

    bool isUseWhileEquiped() {
      return this.bUseWhileEquiped;
   }

    void setUseWhileEquiped(bool var1) {
      this.bUseWhileEquiped = var1;
   }

    bool isUseWhileUnequiped() {
      return this.bUseWhileUnequiped;
   }

    void setUseWhileUnequiped(bool var1) {
      this.bUseWhileUnequiped = var1;
   }

    int getTicksPerEquipUse() {
      return this.ticksPerEquipUse;
   }

    void setTicksPerEquipUse(int var1) {
      this.ticksPerEquipUse = var1;
   }

    float getUseDelta() {
      return this.useDelta;
   }

    void setUseDelta(float var1) {
      this.useDelta = var1;
   }

    float getDelta() {
      return this.delta;
   }

    void setDelta(float var1) {
      this.delta = var1;
   }

    float getTicks() {
      return this.ticks;
   }

    void setTicks(float var1) {
      this.ticks = var1;
   }

    void setReplaceOnDeplete(const std::string& var1) {
      this.ReplaceOnDeplete = var1;
      this.ReplaceOnDepleteFullType = this.getReplaceOnDepleteFullType();
   }

    std::string getReplaceOnDeplete() {
      return this.ReplaceOnDeplete;
   }

    std::string getReplaceOnDepleteFullType() {
      return StringUtils.moduleDotType(this.getModule(), this.ReplaceOnDeplete);
   }

    void setHeat(float var1) {
      this.Heat = PZMath.clamp(var1, 0.0F, 3.0F);
   }

    float getHeat() {
      return this.Heat;
   }

    float getInvHeat() {
      return (1.0F - this.Heat) / 3.0F;
   }

    bool finishupdate() {
      if (this.canStoreWater() && this.isWaterSource() && this.getWorldItem() != nullptr && this.getWorldItem().getSquare() != nullptr) {
         return this.getUsedDelta() >= 1.0F;
      } else if (this.isTaintedWater()) {
    return false;
      } else {
         if (this.container != nullptr) {
            if (this.Heat != this.container.getTemprature() || this.container.isTemperatureChanging()) {
    return false;
            }

            if (this.container.type == "campfire") || this.container.type == "barbecue")) {
    return false;
            }
         }

    return true;
      }
   }

    int getRemainingUses() {
      return Math.round(this.getUsedDelta() / this.getUseDelta());
   }

    float getRainFactor() {
      return this.rainFactor;
   }

    void setRainFactor(float var1) {
      this.rainFactor = var1;
   }

    bool canConsolidate() {
      return this.canConsolidate;
   }

    void setCanConsolidate(bool var1) {
      this.canConsolidate = var1;
   }

   public List<std::string> getReplaceOnCooked() {
      return this.ReplaceOnCooked;
   }

    void setReplaceOnCooked(List<std::string> var1) {
      this.ReplaceOnCooked = var1;
   }

    std::string getOnCooked() {
      return this.OnCooked;
   }

    void setOnCooked(const std::string& var1) {
      this.OnCooked = var1;
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie
