#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/Translator.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemSoundManager.h"
#include "zombie/inventory/ItemType.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoCompost.h"
#include "zombie/iso/objects/IsoFireManager.h"
#include "zombie/iso/objects/IsoFireplace.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Item/Type.h"
#include "zombie/ui/ObjectTooltip.h"
#include "zombie/ui/ObjectTooltip/Layout.h"
#include "zombie/ui/ObjectTooltip/LayoutItem.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/io/BitHeader.h"
#include "zombie/util/io/BitHeader/HeaderSize.h"
#include "zombie/util/io/BitHeaderRead.h"
#include "zombie/util/io/BitHeaderWrite.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {
namespace types {


class Food : public InventoryItem {
public:
    bool bBadCold = false;
    bool bGoodHot = false;
    static const float MIN_HEAT = 0.2F;
    static const float MAX_HEAT = 3.0F;
    float Heat = 1.0F;
    float endChange = 0.0F;
    float hungChange = 0.0F;
    std::string useOnConsume = nullptr;
    bool rotten = false;
    bool bDangerousUncooked = false;
    int LastCookMinute = 0;
    float thirstChange = 0.0F;
    bool Poison = false;
   private List<std::string> ReplaceOnCooked = nullptr;
    float baseHunger = 0.0F;
   public std::vector<std::string> spices = nullptr;
    bool isSpice = false;
    int poisonDetectionLevel = -1;
    int PoisonLevelForRecipe = 0;
    int UseForPoison = 0;
    int PoisonPower = 0;
    std::string FoodType = nullptr;
    std::string CustomEatSound = nullptr;
    bool RemoveNegativeEffectOnCooked = false;
    std::string Chef = nullptr;
    std::string OnCooked = nullptr;
    std::string WorldTextureCooked;
    std::string WorldTextureRotten;
    std::string WorldTextureOverdone;
    int fluReduction = 0;
    int ReduceFoodSickness = 0;
    float painReduction = 0.0F;
    std::string HerbalistType;
    float carbohydrates = 0.0F;
    float lipids = 0.0F;
    float proteins = 0.0F;
    float calories = 0.0F;
    bool packaged = false;
    float freezingTime = 0.0F;
    bool frozen = false;
    bool canBeFrozen = true;
    float LastFrozenUpdate = -1.0F;
    static const float FreezerAgeMultiplier = 0.02F;
    std::string replaceOnRotten = nullptr;
    bool forceFoodTypeAsName = false;
    float rottenTime = 0.0F;
    float compostTime = 0.0F;
    std::string onEat = nullptr;
    bool badInMicrowave = false;
    bool cookedInMicrowave = false;
    long m_cookingSound = 0L;
    int m_cookingParameter = -1;
    static const int COOKING_STATE_COOKING = 0;
    static const int COOKING_STATE_BURNING = 1;

    std::string getCategory() {
      return this.mainCategory != nullptr ? this.mainCategory : "Food";
   }

    public Food(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      super(var1, var2, var3, var4);
      Texture.WarnFailFindTexture = false;
      this.texturerotten = Texture.trygetTexture(var4 + "Rotten");
      this.textureCooked = Texture.trygetTexture(var4 + "Cooked");
      this.textureBurnt = Texture.trygetTexture(var4 + "Overdone");
    std::string var5 = "Overdone.png";
      if (this.textureBurnt == nullptr) {
         this.textureBurnt = Texture.trygetTexture(var4 + "Burnt");
         if (this.textureBurnt != nullptr) {
            var5 = "Burnt.png";
         }
      }

    std::string var6 = "Rotten.png";
      if (this.texturerotten == nullptr) {
         this.texturerotten = Texture.trygetTexture(var4 + "Spoiled");
         if (this.texturerotten != nullptr) {
            var6 = "Spoiled.png";
         }
      }

      Texture.WarnFailFindTexture = true;
      if (this.texturerotten == nullptr) {
         this.texturerotten = this.texture;
      }

      if (this.textureCooked == nullptr) {
         this.textureCooked = this.texture;
      }

      if (this.textureBurnt == nullptr) {
         this.textureBurnt = this.texture;
      }

      this.WorldTextureCooked = this.WorldTexture.replace(".png", "Cooked.png");
      this.WorldTextureOverdone = this.WorldTexture.replace(".png", var5);
      this.WorldTextureRotten = this.WorldTexture.replace(".png", var6);
      this.cat = ItemType.Food;
   }

    public Food(const std::string& var1, const std::string& var2, const std::string& var3, Item var4) {
      super(var1, var2, var3, var4);
    std::string var5 = var4.ItemName;
      Texture.WarnFailFindTexture = false;
      this.texture = var4.NormalTexture;
      if (var4.SpecialTextures.size() == 0) {
    bool var6 = false;
      }

      if (var4.SpecialTextures.size() > 0) {
         this.texturerotten = (Texture)var4.SpecialTextures.get(0);
      }

      if (var4.SpecialTextures.size() > 1) {
         this.textureCooked = (Texture)var4.SpecialTextures.get(1);
      }

      if (var4.SpecialTextures.size() > 2) {
         this.textureBurnt = (Texture)var4.SpecialTextures.get(2);
      }

      Texture.WarnFailFindTexture = true;
      if (this.texturerotten == nullptr) {
         this.texturerotten = this.texture;
      }

      if (this.textureCooked == nullptr) {
         this.textureCooked = this.texture;
      }

      if (this.textureBurnt == nullptr) {
         this.textureBurnt = this.texture;
      }

      if (var4.SpecialWorldTextureNames.size() > 0) {
         this.WorldTextureRotten = (std::string)var4.SpecialWorldTextureNames.get(0);
      }

      if (var4.SpecialWorldTextureNames.size() > 1) {
         this.WorldTextureCooked = (std::string)var4.SpecialWorldTextureNames.get(1);
      }

      if (var4.SpecialWorldTextureNames.size() > 2) {
         this.WorldTextureOverdone = (std::string)var4.SpecialWorldTextureNames.get(2);
      }

      this.cat = ItemType.Food;
   }

    bool IsFood() {
    return true;
   }

    int getSaveType() {
      return Type.Food.ordinal();
   }

    void update() {
      if (this.hasTag("AlreadyCooked")) {
         this.setCooked(true);
      }

      this.updateTemperature();
    ItemContainer var1 = this.getOutermostContainer();
      if (var1 != nullptr) {
         if (this.IsCookable && !this.isFrozen()) {
            if (this.Heat > 1.6F) {
    int var6 = GameTime.getInstance().getMinutes();
               if (var6 != this.LastCookMinute) {
                  this.LastCookMinute = var6;
    float var7 = this.Heat / 1.5F;
                  if (var1.getTemprature() <= 1.6F) {
                     var7 *= 0.05F;
                  }

                  this.CookingTime += var7;
                  if (this.shouldPlayCookingSound()) {
                     ItemSoundManager.addItem(this);
                  }

                  if (this.isTaintedWater() && this.CookingTime > Math.min(this.MinutesToCook, 10.0F)) {
                     this.setTaintedWater(false);
                  }

                  if (!this.isCooked() && !this.Burnt && this.CookingTime > this.MinutesToCook) {
                     if (this.getReplaceOnCooked() != nullptr && !this.isRotten()) {
                        if (GameClient.bClient) {
                           GameClient.instance.sendReplaceOnCooked(this);
                           this.container.Remove(this);
                           IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this);
                           return;
                        }

                        for (int var9 = 0; var9 < this.getReplaceOnCooked().size(); var9++) {
    InventoryItem var10 = this.container.AddItem(this.getReplaceOnCooked().get(var9));
                           if (var10 != nullptr) {
                              var10.copyConditionModData(this);
                              if (dynamic_cast<Food*>(var10) != nullptr && dynamic_cast<Food*>(this) != nullptr) {
                              }

                              if (dynamic_cast<Food*>(var10) != nullptr && ((Food)var10).isBadInMicrowave() && this.container.isMicrowave()) {
                                 var10.setUnhappyChange(5.0F);
                                 var10.setBoredomChange(5.0F);
                                 ((Food)var10).cookedInMicrowave = true;
                              }
                           }
                        }

                        this.container.Remove(this);
                        IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this);
                        return;
                     }

                     this.setCooked(true);
                     if (this.getScriptItem().RemoveUnhappinessWhenCooked) {
                        this.setUnhappyChange(0.0F);
                     }

                     if (this.type == "RicePot")
                        || this.type == "PastaPot")
                        || this.type == "RicePan")
                        || this.type == "PastaPan")
                        || this.type == "WaterPotRice")
                        || this.type == "WaterPotPasta")
                        || this.type == "WaterSaucepanRice")
                        || this.type == "WaterSaucepanPasta")
                        || this.type == "RiceBowl")
                        || this.type == "PastaBowl")) {
                        this.setAge(0.0F);
                        this.setOffAge(1);
                        this.setOffAgeMax(2);
                     }

                     if (this.isRemoveNegativeEffectOnCooked()) {
                        if (this.thirstChange > 0.0F) {
                           this.setThirstChange(0.0F);
                        }

                        if (this.unhappyChange > 0.0F) {
                           this.setUnhappyChange(0.0F);
                        }

                        if (this.boredomChange > 0.0F) {
                           this.setBoredomChange(0.0F);
                        }
                     }

                     if (this.getOnCooked() != nullptr) {
                        LuaManager.caller.protectedCall(LuaManager.thread, LuaManager.env.rawget(this.getOnCooked()), new Object[]{this});
                     }

                     if (this.isBadInMicrowave() && this.container.isMicrowave()) {
                        this.setUnhappyChange(5.0F);
                        this.setBoredomChange(5.0F);
                        this.cookedInMicrowave = true;
                     }

                     if (this.Chef != nullptr && !this.Chef.empty()) {
                        for (int var4 = 0; var4 < IsoPlayer.numPlayers; var4++) {
    IsoPlayer var5 = IsoPlayer.players[var4];
                           if (var5 != nullptr && !var5.isDead() && this.Chef == var5.getFullName())) {
                              var5.getXp().AddXP(Perks.Cooking, 10.0F);
                              break;
                           }
                        }
                     }
                  }

                  if (this.CookingTime > this.MinutesToBurn) {
                     this.Burnt = true;
                     this.setCooked(false);
                  }

                  if (IsoWorld.instance.isHydroPowerOn()
                     && this.Burnt
                     && this.CookingTime >= 50.0F
                     && this.CookingTime >= this.MinutesToCook * 2.0F + this.MinutesToBurn / 2.0F
                     && Rand.Next(Rand.AdjustForFramerate(200)) == 0) {
                     boolean var8 = this.container != nullptr
                        && this.container.getParent() != nullptr
                        && this.container.getParent().getName() != nullptr
                        && this.container.getParent().getName() == "Campfire");
                     if (!var8 && this.container != nullptr && this.container.getParent() != nullptr && this.container.getParent() instanceof IsoFireplace) {
                        var8 = true;
                     }

                     if (this.container != nullptr && this.container.SourceGrid != nullptr && !var8) {
                        IsoFireManager.StartFire(this.container.SourceGrid.getCell(), this.container.SourceGrid, true, 500000);
                        this.IsCookable = false;
                     }
                  }
               }
            }
         } else if (this.isTaintedWater() && this.Heat > 1.6F && !this.isFrozen()) {
    int var2 = GameTime.getInstance().getMinutes();
            if (var2 != this.LastCookMinute) {
               this.LastCookMinute = var2;
    float var3 = 1.0F;
               if (var1.getTemprature() <= 1.6F) {
                  var3 = (float)(var3 * 0.2);
               }

               this.CookingTime += var3;
               if (this.CookingTime > 10.0F) {
                  this.setTaintedWater(false);
               }
            }
         }
      }

      this.updateRotting(var1);
   }

    void updateSound(BaseSoundEmitter var1) {
      if (this.shouldPlayCookingSound()) {
         if (var1.isPlaying(this.m_cookingSound)) {
            this.setCookingParameter(var1);
            return;
         }

    ItemContainer var2 = this.getOutermostContainer();
    IsoGridSquare var3 = var2.getParent().getSquare();
         var1.setPos(var3.getX() + 0.5F, var3.getY() + 0.5F, var3.getZ());
         this.m_cookingSound = var1.playSoundImpl(this.getCookingSound(), (IsoObject)nullptr);
         this.setCookingParameter(var1);
      } else {
         var1.stopOrTriggerSound(this.m_cookingSound);
         this.m_cookingSound = 0L;
         this.m_cookingParameter = -1;
         ItemSoundManager.removeItem(this);
      }
   }

    bool shouldPlayCookingSound() {
      if (GameServer.bServer) {
    return false;
      } else if (StringUtils.isNullOrWhitespace(this.getCookingSound())) {
    return false;
      } else {
    ItemContainer var1 = this.getOutermostContainer();
         return var1 != nullptr && var1.getParent() != nullptr && var1.getParent().getObjectIndex() != -1 && !(var1.getTemprature() <= 1.6F)
            ? this.isCookable() && !this.isFrozen() && this.getHeat() > 1.6F
            : false;
      }
   }

    void setCookingParameter(BaseSoundEmitter var1) {
    bool var2 = this.CookingTime > this.MinutesToCook;
    int var3 = var2 ? 1 : 0;
      if (var3 != this.m_cookingParameter) {
         this.m_cookingParameter = var3;

         // OpenAL equivalent: Use alSourcef or alSourcei to set source parameters (e.g., AL_GAIN, AL_PITCH) as needed.
      }
   }

    void updateTemperature() {
    ItemContainer var1 = this.getOutermostContainer();
    float var2 = var1 == nullptr ? 1.0F : var1.getTemprature();
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
   }

    void updateRotting(ItemContainer var1) {
      if (this.OffAgeMax != 1.0E9) {
         if (!GameClient.bClient || this.isInLocalPlayerInventory()) {
            if (!GameServer.bServer || this.container == nullptr || this.getOutermostContainer() == this.container) {
               if (this.replaceOnRotten != nullptr && !this.replaceOnRotten.empty()) {
                  this.updateAge();
                  if (this.isRotten()) {
    InventoryItem var2 = InventoryItemFactory.CreateItem(this.getModule() + "." + this.replaceOnRotten, this);
                     if (var2 == nullptr) {
                        DebugLog.General.warn("ReplaceOnRotten = " + this.replaceOnRotten + " doesn't exist for " + this.getFullType());
                        this.destroyThisItem();
                        return;
                     }

                     var2.setAge(this.getAge());
    IsoWorldInventoryObject var3 = this.getWorldItem();
                     if (var3 != nullptr && var3.getSquare() != nullptr) {
    IsoGridSquare var4 = var3.getSquare();
                        if (!GameServer.bServer) {
                           var3.item = var2;
                           var2.setWorldItem(var3);
                           var3.updateSprite();
                           IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this);
                           LuaEventManager.triggerEvent("OnContainerUpdate");
                           return;
                        }

                        var4.AddWorldInventoryItem(var2, var3.xoff, var3.yoff, var3.zoff, true);
                     } else if (this.container != nullptr) {
                        this.container.AddItem(var2);
                        if (GameServer.bServer) {
                           GameServer.sendAddItemToContainer(this.container, var2);
                        }
                     }

                     this.destroyThisItem();
                     return;
                  }
               }

               if (SandboxOptions.instance.DaysForRottenFoodRemoval.getValue() >= 0) {
                  if (var1 != nullptr && var1.dynamic_cast<IsoCompost*>(parent) != nullptr) {
                     return;
                  }

                  this.updateAge();
                  if (this.getAge() > this.getOffAgeMax() + SandboxOptions.instance.DaysForRottenFoodRemoval.getValue()) {
                     this.destroyThisItem();
                     return;
                  }
               }
            }
         }
      }
   }

    void updateAge() {
    ItemContainer var1 = this.getOutermostContainer();
      this.updateFreezing(var1);
    bool var2 = false;
      if (var1 != nullptr && var1.getSourceGrid() != nullptr && var1.getSourceGrid().haveElectricity()) {
         var2 = true;
      }

    float var3 = (float)GameTime.getInstance().getWorldAgeHours();
    float var4 = 0.2F;
      if (SandboxOptions.instance.FridgeFactor.getValue() == 1) {
         var4 = 0.4F;
      } else if (SandboxOptions.instance.FridgeFactor.getValue() == 2) {
         var4 = 0.3F;
      } else if (SandboxOptions.instance.FridgeFactor.getValue() == 4) {
         var4 = 0.1F;
      } else if (SandboxOptions.instance.FridgeFactor.getValue() == 5) {
         var4 = 0.03F;
      }

      if (this.LastAged < 0.0F) {
         this.LastAged = var3;
      } else if (this.LastAged > var3) {
         this.LastAged = var3;
      }

      if (var3 > this.LastAged) {
    double var5 = var3 - this.LastAged;
         if (var1 != nullptr && this.Heat != var1.getTemprature()) {
            if (var5 < 0.33333334F) {
               if (!IsoWorld.instance.getCell().getProcessItems().contains(this)) {
                  this.Heat = GameTime.instance.Lerp(this.Heat, var1.getTemprature(), (float)var5 / 0.33333334F);
                  IsoWorld.instance.getCell().addToProcessItems(this);
               }
            } else {
               this.Heat = var1.getTemprature();
            }
         }

         if (this.isFrozen()) {
            var5 *= 0.02F;
         } else if (var1 != nullptr && (var1.getType() == "fridge") || var1.getType() == "freezer"))) {
            if (var2) {
               var5 *= var4;
            } else if (SandboxOptions.instance.getElecShutModifier() > -1 && this.LastAged < SandboxOptions.instance.getElecShutModifier() * 24) {
    float var7 = Math.min((float)(SandboxOptions.instance.getElecShutModifier() * 24), var3);
               var5 = (var7 - this.LastAged) * var4;
               if (var3 > SandboxOptions.instance.getElecShutModifier() * 24) {
                  var5 += var3 - SandboxOptions.instance.getElecShutModifier() * 24;
               }
            }
         }

    float var12 = 1.0F;
         if (SandboxOptions.instance.FoodRotSpeed.getValue() == 1) {
            var12 = 1.7F;
         } else if (SandboxOptions.instance.FoodRotSpeed.getValue() == 2) {
            var12 = 1.4F;
         } else if (SandboxOptions.instance.FoodRotSpeed.getValue() == 4) {
            var12 = 0.7F;
         } else if (SandboxOptions.instance.FoodRotSpeed.getValue() == 5) {
            var12 = 0.4F;
         }

    bool var8 = !this.Burnt && this.OffAge < 1000000000 && this.Age < this.OffAge;
    bool var9 = !this.Burnt && this.OffAgeMax < 1000000000 && this.Age >= this.OffAgeMax;
         this.Age = (float)(this.Age + var5 * var12 / 24.0);
         this.LastAged = var3;
    bool var10 = !this.Burnt && this.OffAge < 1000000000 && this.Age < this.OffAge;
    bool var11 = !this.Burnt && this.OffAgeMax < 1000000000 && this.Age >= this.OffAgeMax;
         if (!GameServer.bServer && (var8 != var10 || var9 != var11)) {
            LuaEventManager.triggerEvent("OnContainerUpdate", this);
         }
      }
   }

    void setAutoAge() {
    ItemContainer var1 = this.getOutermostContainer();
    float var2 = (float)GameTime.getInstance().getWorldAgeHours() / 24.0F;
      var2 += (SandboxOptions.instance.TimeSinceApo.getValue() - 1) * 30;
    float var3 = var2;
    bool var4 = false;
      if (var1 != nullptr && var1.getParent() != nullptr && var1.getParent().getSprite() != nullptr) {
         var4 = var1.getParent().getSprite().getProperties().Is("IsFridge");
      }

      if (var1 != nullptr && (var4 || var1.getType() == "fridge") || var1.getType() == "freezer"))) {
    int var5 = SandboxOptions.instance.ElecShutModifier.getValue();
         if (var5 > -1) {
    float var6 = Math.min((float)var5, var2);
    int var7 = SandboxOptions.instance.FridgeFactor.getValue();
    float var8 = 0.2F;
            if (var7 == 1) {
               var8 = 0.4F;
            } else if (var7 == 2) {
               var8 = 0.3F;
            } else if (var7 == 4) {
               var8 = 0.1F;
            } else if (var7 == 5) {
               var8 = 0.03F;
            }

            if (!var1.getType() == "fridge") && this.canBeFrozen() && !var4) {
    float var9 = var6;
    float var10 = 100.0F;
               if (var2 > var6) {
    float var11 = (var2 - var6) * 24.0F;
    float var12 = 1440.0F / GameTime.getInstance().getMinutesPerDay() * 60.0F * 5.0F;
    float var13 = 0.0095999995F;
                  var10 -= var13 * var12 * var11;
                  if (var10 > 0.0F) {
                     var9 = var6 + var11 / 24.0F;
                  } else {
    float var14 = 100.0F / (var13 * var12);
                     var9 = var6 + var14 / 24.0F;
                     var10 = 0.0F;
                  }
               }

               var3 = var2 - var9;
               var3 += var9 * 0.02F;
               this.setFreezingTime(var10);
            } else {
               var3 = var2 - var6;
               var3 += var6 * var8;
            }
         }
      }

    int var18 = SandboxOptions.instance.FoodRotSpeed.getValue();
    float var19 = 1.0F;
      if (var18 == 1) {
         var19 = 1.7F;
      } else if (var18 == 2) {
         var19 = 1.4F;
      } else if (var18 == 4) {
         var19 = 0.7F;
      } else if (var18 == 5) {
         var19 = 0.4F;
      }

      this.Age = var3 * var19;
      this.LastAged = (float)GameTime.getInstance().getWorldAgeHours();
      this.LastFrozenUpdate = this.LastAged;
      if (var1 != nullptr) {
         this.setHeat(var1.getTemprature());
      }
   }

    void updateFreezing(ItemContainer var1) {
    float var2 = (float)GameTime.getInstance().getWorldAgeHours();
      if (this.LastFrozenUpdate < 0.0F) {
         this.LastFrozenUpdate = var2;
      } else if (this.LastFrozenUpdate > var2) {
         this.LastFrozenUpdate = var2;
      }

      if (var2 > this.LastFrozenUpdate) {
    float var3 = var2 - this.LastFrozenUpdate;
    float var4 = 4.0F;
    float var5 = 1.5F;
         if (this.isFreezing()) {
            this.setFreezingTime(this.getFreezingTime() + var3 / var4 * 100.0F);
         }

         if (this.isThawing()) {
    float var6 = var5;
            if (var1 != nullptr && "fridge" == var1.getType()) && var1.isPowered()) {
               var6 = var5 * 2.0F;
            }

            if (var1 != nullptr && var1.getTemprature() > 1.0F) {
               var6 /= 6.0F;
            }

            this.setFreezingTime(this.getFreezingTime() - var3 / var6 * 100.0F);
         }

         this.LastFrozenUpdate = var2;
      }
   }

    float getActualWeight() {
      if (this.haveExtraItems()) {
    float var8 = this.getHungChange();
    float var9 = this.getBaseHunger();
    float var10 = var9 == 0.0F ? 0.0F : var8 / var9;
    float var4 = 0.0F;
         if (this.getReplaceOnUse() != nullptr) {
    std::string var5 = this.getReplaceOnUseFullType();
    Item var6 = ScriptManager.instance.getItem(var5);
            if (var6 != nullptr) {
               var4 = var6.getActualWeight();
            }
         }

    float var11 = super.getActualWeight() + this.getExtraItemsWeight();
         return (var11 - var4) * var10 + var4;
      } else {
         if (this.getReplaceOnUse() != nullptr && !this.isCustomWeight()) {
    std::string var7 = this.getReplaceOnUseFullType();
    Item var2 = ScriptManager.instance.getItem(var7);
            if (var2 != nullptr) {
    float var3 = 1.0F;
               if (this.getScriptItem().getHungerChange() < 0.0F) {
                  var3 = this.getHungChange() * 100.0F / this.getScriptItem().getHungerChange();
               } else if (this.getScriptItem().getThirstChange() < 0.0F) {
                  var3 = this.getThirstChange() * 100.0F / this.getScriptItem().getThirstChange();
               }

               return (this.getScriptItem().getActualWeight() - var2.getActualWeight()) * var3 + var2.getActualWeight();
            }
         } else if (!this.isCustomWeight()) {
    float var1 = 1.0F;
            if (this.getScriptItem().getHungerChange() < 0.0F) {
               var1 = this.getHungChange() * 100.0F / this.getScriptItem().getHungerChange();
            } else if (this.getScriptItem().getThirstChange() < 0.0F) {
               var1 = this.getThirstChange() * 100.0F / this.getScriptItem().getThirstChange();
            }

            return this.getScriptItem().getActualWeight() * var1;
         }

         return super.getActualWeight();
      }
   }

    float getWeight() {
      return this.getReplaceOnUse() != nullptr ? this.getActualWeight() : super.getWeight();
   }

    bool CanStack(InventoryItem var1) {
    return false;
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.putFloat(this.Age);
      var1.putFloat(this.LastAged);
    BitHeaderWrite var3 = BitHeader.allocWrite(HeaderSize.uint8_t, var1);
      if (this.calories != 0.0F || this.proteins != 0.0F || this.lipids != 0.0F || this.carbohydrates != 0.0F) {
         var3.addFlags(1);
         var1.putFloat(this.calories);
         var1.putFloat(this.proteins);
         var1.putFloat(this.lipids);
         var1.putFloat(this.carbohydrates);
      }

      if (this.hungChange != 0.0F) {
         var3.addFlags(2);
         var1.putFloat(this.hungChange);
      }

      if (this.baseHunger != 0.0F) {
         var3.addFlags(4);
         var1.putFloat(this.baseHunger);
      }

      if (this.unhappyChange != 0.0F) {
         var3.addFlags(8);
         var1.putFloat(this.unhappyChange);
      }

      if (this.boredomChange != 0.0F) {
         var3.addFlags(16);
         var1.putFloat(this.boredomChange);
      }

      if (this.thirstChange != 0.0F) {
         var3.addFlags(32);
         var1.putFloat(this.thirstChange);
      }

    BitHeaderWrite var4 = BitHeader.allocWrite(HeaderSize.int, var1);
      if (this.Heat != 1.0F) {
         var4.addFlags(1);
         var1.putFloat(this.Heat);
      }

      if (this.LastCookMinute != 0) {
         var4.addFlags(2);
         var1.putInt(this.LastCookMinute);
      }

      if (this.CookingTime != 0.0F) {
         var4.addFlags(4);
         var1.putFloat(this.CookingTime);
      }

      if (this.Cooked) {
         var4.addFlags(8);
      }

      if (this.Burnt) {
         var4.addFlags(16);
      }

      if (this.IsCookable) {
         var4.addFlags(32);
      }

      if (this.bDangerousUncooked) {
         var4.addFlags(64);
      }

      if (this.poisonDetectionLevel != -1) {
         var4.addFlags(128);
         var1.put((byte)this.poisonDetectionLevel);
      }

      if (this.spices != nullptr) {
         var4.addFlags(256);
         var1.put((byte)this.spices.size());

         for (std::string var6 : this.spices) {
            GameWindow.WriteString(var1, var6);
         }
      }

      if (this.PoisonPower != 0) {
         var4.addFlags(512);
         var1.put((byte)this.PoisonPower);
      }

      if (this.Chef != nullptr) {
         var4.addFlags(1024);
         GameWindow.WriteString(var1, this.Chef);
      }

      if (this.OffAge != 1.0E9) {
         var4.addFlags(2048);
         var1.putInt(this.OffAge);
      }

      if (this.OffAgeMax != 1.0E9) {
         var4.addFlags(4096);
         var1.putInt(this.OffAgeMax);
      }

      if (this.painReduction != 0.0F) {
         var4.addFlags(8192);
         var1.putFloat(this.painReduction);
      }

      if (this.fluReduction != 0) {
         var4.addFlags(16384);
         var1.putInt(this.fluReduction);
      }

      if (this.ReduceFoodSickness != 0) {
         var4.addFlags(32768);
         var1.putInt(this.ReduceFoodSickness);
      }

      if (this.Poison) {
         var4.addFlags(65536);
      }

      if (this.UseForPoison != 0) {
         var4.addFlags(131072);
         var1.putShort((short)this.UseForPoison);
      }

      if (this.freezingTime != 0.0F) {
         var4.addFlags(262144);
         var1.putFloat(this.freezingTime);
      }

      if (this.isFrozen()) {
         var4.addFlags(524288);
      }

      if (this.LastFrozenUpdate != 0.0F) {
         var4.addFlags(1048576);
         var1.putFloat(this.LastFrozenUpdate);
      }

      if (this.rottenTime != 0.0F) {
         var4.addFlags(2097152);
         var1.putFloat(this.rottenTime);
      }

      if (this.compostTime != 0.0F) {
         var4.addFlags(4194304);
         var1.putFloat(this.compostTime);
      }

      if (this.cookedInMicrowave) {
         var4.addFlags(8388608);
      }

      if (this.fatigueChange != 0.0F) {
         var4.addFlags(16777216);
         var1.putFloat(this.fatigueChange);
      }

      if (this.endChange != 0.0F) {
         var4.addFlags(33554432);
         var1.putFloat(this.endChange);
      }

      if (!var4 == 0)) {
         var3.addFlags(64);
         var4.write();
      } else {
         var1.position(var4.getStartPosition());
      }

      var3.write();
      var3.release();
      var4.release();
   }

    void load(ByteBuffer var1, int var2) {
      super.load(var1, var2);
      this.calories = 0.0F;
      this.proteins = 0.0F;
      this.lipids = 0.0F;
      this.carbohydrates = 0.0F;
      this.hungChange = 0.0F;
      this.baseHunger = 0.0F;
      this.unhappyChange = 0.0F;
      this.boredomChange = 0.0F;
      this.thirstChange = 0.0F;
      this.Heat = 1.0F;
      this.LastCookMinute = 0;
      this.CookingTime = 0.0F;
      this.Cooked = false;
      this.Burnt = false;
      this.IsCookable = false;
      this.bDangerousUncooked = false;
      this.poisonDetectionLevel = -1;
      this.spices = nullptr;
      this.PoisonPower = 0;
      this.Chef = nullptr;
      this.OffAge = 1000000000;
      this.OffAgeMax = 1000000000;
      this.painReduction = 0.0F;
      this.fluReduction = 0;
      this.ReduceFoodSickness = 0;
      this.Poison = false;
      this.UseForPoison = 0;
      this.freezingTime = 0.0F;
      this.frozen = false;
      this.LastFrozenUpdate = 0.0F;
      this.rottenTime = 0.0F;
      this.compostTime = 0.0F;
      this.cookedInMicrowave = false;
      this.fatigueChange = 0.0F;
      this.endChange = 0.0F;
      this.Age = var1.getFloat();
      this.LastAged = var1.getFloat();
    BitHeaderRead var3 = BitHeader.allocRead(HeaderSize.uint8_t, var1);
      if (!var3 == 0)) {
         if (var3.hasFlags(1)) {
            this.calories = var1.getFloat();
            this.proteins = var1.getFloat();
            this.lipids = var1.getFloat();
            this.carbohydrates = var1.getFloat();
         }

         if (var3.hasFlags(2)) {
            this.hungChange = var1.getFloat();
         }

         if (var3.hasFlags(4)) {
            this.baseHunger = var1.getFloat();
         }

         if (var3.hasFlags(8)) {
            this.unhappyChange = var1.getFloat();
         }

         if (var3.hasFlags(16)) {
            this.boredomChange = var1.getFloat();
         }

         if (var3.hasFlags(32)) {
            this.thirstChange = var1.getFloat();
         }

         if (var3.hasFlags(64)) {
    BitHeaderRead var4 = BitHeader.allocRead(HeaderSize.int, var1);
            if (var4.hasFlags(1)) {
               this.Heat = var1.getFloat();
            }

            if (var4.hasFlags(2)) {
               this.LastCookMinute = var1.getInt();
            }

            if (var4.hasFlags(4)) {
               this.CookingTime = var1.getFloat();
            }

            this.Cooked = var4.hasFlags(8);
            this.Burnt = var4.hasFlags(16);
            this.IsCookable = var4.hasFlags(32);
            this.bDangerousUncooked = var4.hasFlags(64);
            if (var4.hasFlags(128)) {
               this.poisonDetectionLevel = var1.get();
            }

            if (var4.hasFlags(256)) {
               this.spices = std::make_unique<std::vector<>>();
    uint8_t var5 = var1.get();

               for (int var6 = 0; var6 < var5; var6++) {
    std::string var7 = GameWindow.ReadString(var1);
                  this.spices.push_back(var7);
               }
            }

            if (var4.hasFlags(512)) {
               this.PoisonPower = var1.get();
            }

            if (var4.hasFlags(1024)) {
               this.Chef = GameWindow.ReadString(var1);
            }

            if (var4.hasFlags(2048)) {
               this.OffAge = var1.getInt();
            }

            if (var4.hasFlags(4096)) {
               this.OffAgeMax = var1.getInt();
            }

            if (var4.hasFlags(8192)) {
               this.painReduction = var1.getFloat();
            }

            if (var4.hasFlags(16384)) {
               this.fluReduction = var1.getInt();
            }

            if (var4.hasFlags(32768)) {
               this.ReduceFoodSickness = var1.getInt();
            }

            this.Poison = var4.hasFlags(65536);
            if (var4.hasFlags(131072)) {
               this.UseForPoison = var1.getShort();
            }

            if (var4.hasFlags(262144)) {
               this.freezingTime = var1.getFloat();
            }

            this.setFrozen(var4.hasFlags(524288));
            if (var4.hasFlags(1048576)) {
               this.LastFrozenUpdate = var1.getFloat();
            }

            if (var4.hasFlags(2097152)) {
               this.rottenTime = var1.getFloat();
            }

            if (var4.hasFlags(4194304)) {
               this.compostTime = var1.getFloat();
            }

            this.cookedInMicrowave = var4.hasFlags(8388608);
            if (var4.hasFlags(16777216)) {
               this.fatigueChange = var1.getFloat();
            }

            if (var4.hasFlags(33554432)) {
               this.endChange = var1.getFloat();
            }

            var4.release();
         }
      }

      var3.release();
      if (GameServer.bServer && this.LastAged == -1.0F) {
         this.LastAged = (float)GameTime.getInstance().getWorldAgeHours();
      }
   }

    bool finishupdate() {
      if (this.container != nullptr || this.getWorldItem() != nullptr && this.getWorldItem().getSquare() != nullptr) {
         if (this.IsCookable) {
    return false;
         } else if (this.container == nullptr || this.Heat == this.container.getTemprature() && !this.container.isTemperatureChanging()) {
            if (this.isTaintedWater() && this.container != nullptr && this.container.getTemprature() > 1.0F) {
    return false;
            } else {
               if ((!GameClient.bClient || this.isInLocalPlayerInventory()) && this.OffAgeMax != 1.0E9) {
                  if (this.replaceOnRotten != nullptr && !this.replaceOnRotten.empty()) {
    return false;
                  }

                  if (SandboxOptions.instance.DaysForRottenFoodRemoval.getValue() != -1) {
    return false;
                  }
               }

    return true;
            }
         } else {
    return false;
         }
      } else {
    return true;
      }
   }

    bool shouldUpdateInWorld() {
      if (!GameClient.bClient && this.OffAgeMax != 1.0E9) {
         if (this.replaceOnRotten != nullptr && !this.replaceOnRotten.empty()) {
    return true;
         }

         if (SandboxOptions.instance.DaysForRottenFoodRemoval.getValue() != -1) {
    return true;
         }
      }

      return this.getHeat() != 1.0F;
   }

    std::string getName() {
    std::string var1 = "";
      if (this.Burnt) {
         var1 = var1 + this.BurntString + " ";
      } else if (this.OffAge < 1000000000 && this.Age < this.OffAge) {
         var1 = var1 + this.FreshString + " ";
      } else if (this.OffAgeMax < 1000000000 && this.Age >= this.OffAgeMax) {
         var1 = var1 + this.OffString + " ";
      } else if (this.OffAgeMax < 1000000000 && this.Age >= this.OffAge) {
         var1 = var1 + this.StaleString + " ";
      }

      if (this.isCooked() && !this.Burnt && !this.hasTag("HideCooked")) {
         var1 = var1 + this.CookedString + " ";
      } else if (this.IsCookable && !this.Burnt && !this.hasTag("HideCooked")) {
         var1 = var1 + this.UnCookedString + " ";
      }

      if (this.isFrozen()) {
         var1 = var1 + this.FrozenString + " ";
      }

      var1 = var1.trim();
      return var1.empty() ? this.name : Translator.getText("IGUI_FoodNaming", var1, this.name);
   }

    void DoTooltip(ObjectTooltip var1, Layout var2) {
      if (this.getHungerChange() != 0.0F) {
    LayoutItem var3 = var2.addItem();
         var3.setLabel(Translator.getText("Tooltip_food_Hunger") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
    int var4 = (int)(this.getHungerChange() * 100.0F);
         var3.setValueRight(var4, false);
      }

      if (this.getThirstChange() != 0.0F) {
    LayoutItem var17 = var2.addItem();
         var17.setLabel(Translator.getText("Tooltip_food_Thirst") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
    int var39 = (int)(this.getThirstChange() * 100.0F);
         var17.setValueRight(var39, false);
      }

      if (this.getEnduranceChange() != 0.0F) {
    LayoutItem var18 = var2.addItem();
    int var40 = (int)(this.getEnduranceChange() * 100.0F);
         var18.setLabel(Translator.getText("Tooltip_food_Endurance") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var18.setValueRight(var40, true);
      }

      if (this.getStressChange() != 0.0F) {
    LayoutItem var19 = var2.addItem();
    int var41 = (int)(this.getStressChange() * 100.0F);
         var19.setLabel(Translator.getText("Tooltip_food_Stress") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var19.setValueRight(var41, false);
      }

      if (this.getBoredomChange() != 0.0F) {
    LayoutItem var20 = var2.addItem();
    int var42 = (int)this.getBoredomChange();
         var20.setLabel(Translator.getText("Tooltip_food_Boredom") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var20.setValueRight(var42, false);
      }

      if (this.getUnhappyChange() != 0.0F) {
    LayoutItem var21 = var2.addItem();
    int var43 = (int)this.getUnhappyChange();
         var21.setLabel(Translator.getText("Tooltip_food_Unhappiness") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValueRight(var43, false);
      }

      if (this.isIsCookable() && !this.isFrozen() && !this.Burnt && this.getHeat() > 1.6) {
    float var44 = this.getCookingTime();
    float var5 = this.getMinutesToCook();
    float var6 = this.getMinutesToBurn();
    float var7 = var44 / var5;
    ColorInfo var8 = Core.getInstance().getGoodHighlitedColor();
    float var9 = var8.getR();
    float var10 = var8.getG();
    float var11 = var8.getB();
    float var12 = 1.0F;
    float var13 = var8.getR();
    float var14 = var8.getG();
    float var15 = var8.getB();
    std::string var16 = Translator.getText("IGUI_invpanel_Cooking");
         if (var44 > var5) {
            var8 = Core.getInstance().getBadHighlitedColor();
            var16 = Translator.getText("IGUI_invpanel_Burning");
            var13 = var8.getR();
            var14 = var8.getG();
            var15 = var8.getB();
            var7 = (var44 - var5) / (var6 - var5);
            var9 = var8.getR();
            var10 = var8.getG();
            var11 = var8.getB();
         }

    LayoutItem var22 = var2.addItem();
         var22.setLabel(var16 + ": ", var13, var14, var15, 1.0F);
         var22.setProgress(var7, var9, var10, var11, var12);
      }

      if (this.getFreezingTime() < 100.0F && this.getFreezingTime() > 0.0F) {
    float var45 = this.getFreezingTime() / 100.0F;
    float var46 = 0.0F;
    float var47 = 0.6F;
    float var48 = 0.0F;
    float var50 = 0.7F;
    float var51 = 1.0F;
    float var52 = 1.0F;
    float var53 = 0.8F;
    LayoutItem var23 = var2.addItem();
         var23.setLabel(Translator.getText("IGUI_invpanel_FreezingTime") + ": ", var51, var52, var53, 1.0F);
         var23.setProgress(var45, var46, var47, var48, var50);
      }

      if (Core.bDebug && DebugOptions.instance.TooltipInfo.getValue()
         || this.isPackaged()
         || var1.getCharacter() != nullptr && (var1.getCharacter().Traits.Nutritionist.isSet() || var1.getCharacter().Traits.Nutritionist2.isSet())) {
    LayoutItem var24 = var2.addItem();
         var24.setLabel(Translator.getText("Tooltip_food_Calories") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var24.setValueRightNoPlus(this.getCalories());
         var24 = var2.addItem();
         var24.setLabel(Translator.getText("Tooltip_food_Carbs") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var24.setValueRightNoPlus(this.getCarbohydrates());
         var24 = var2.addItem();
         var24.setLabel(Translator.getText("Tooltip_food_Prots") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var24.setValueRightNoPlus(this.getProteins());
         var24 = var2.addItem();
         var24.setLabel(Translator.getText("Tooltip_food_Fat") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var24.setValueRightNoPlus(this.getLipids());
      }

      if (this.isbDangerousUncooked() && !this.isCooked() && !this.isBurnt()) {
    LayoutItem var28 = var2.addItem();
         var28.setLabel(
            Translator.getText("Tooltip_food_Dangerous_uncooked"),
            Core.getInstance().getBadHighlitedColor().getR(),
            Core.getInstance().getBadHighlitedColor().getG(),
            Core.getInstance().getBadHighlitedColor().getB(),
            1.0F
         );
         if (this.hasTag("Egg")) {
            var28.setLabel(Translator.getText("Tooltip_food_SlightDanger_uncooked"), 1.0F, 0.0F, 0.0F, 1.0F);
         }
      }

      if (this.getScriptItem().RemoveUnhappinessWhenCooked && !this.isCooked()) {
    LayoutItem var29 = var2.addItem();
         var29.setLabel(
            Translator.getText("Tooltip_food_CookToRemoveUnhappiness"),
            Core.getInstance().getBadHighlitedColor().getR(),
            Core.getInstance().getBadHighlitedColor().getG(),
            Core.getInstance().getBadHighlitedColor().getB(),
            1.0F
         );
      }

      if ((this.isGoodHot() || this.isBadCold()) && this.Heat < 1.3F) {
    LayoutItem var30 = var2.addItem();
         var30.setLabel(Translator.getText("Tooltip_food_BetterHot"), 1.0F, 0.9F, 0.9F, 1.0F);
      }

      if (this.cookedInMicrowave) {
    LayoutItem var31 = var2.addItem();
         var31.setLabel(Translator.getText("Tooltip_food_CookedInMicrowave"), 1.0F, 0.9F, 0.9F, 1.0F);
      }

      if (Core.bDebug && DebugOptions.instance.TooltipInfo.getValue()) {
    LayoutItem var32 = var2.addItem();
         var32.setLabel("DBG: BaseHunger", 0.0F, 1.0F, 0.0F, 1.0F);
         var32.setValueRight((int)(this.getBaseHunger() * 100.0F), false);
         var32 = var2.addItem();
         var32.setLabel("DBG: Age", 0.0F, 1.0F, 0.0F, 1.0F);
         var32.setValueRightNoPlus(this.getAge() * 24.0F);
         if (this.getOffAgeMax() != 1.0E9) {
            var32 = var2.addItem();
            var32.setLabel("DBG: Age Fresh", 0.0F, 1.0F, 0.0F, 1.0F);
            var32.setValueRightNoPlus(this.getOffAge() * 24.0F);
            var32 = var2.addItem();
            var32.setLabel("DBG: Age Rotten", 0.0F, 1.0F, 0.0F, 1.0F);
            var32.setValueRightNoPlus(this.getOffAgeMax() * 24);
         }

         var32 = var2.addItem();
         var32.setLabel("DBG: Heat", 0.0F, 1.0F, 0.0F, 1.0F);
         var32.setValueRightNoPlus(this.getHeat());
         var32 = var2.addItem();
         var32.setLabel("DBG: Freeze Time", 0.0F, 1.0F, 0.0F, 1.0F);
         var32.setValueRightNoPlus(this.getFreezingTime());
         var32 = var2.addItem();
         var32.setLabel("DBG: Compost Time", 0.0F, 1.0F, 0.0F, 1.0F);
         var32.setValueRightNoPlus(this.getCompostTime());
      }
   }

    float getEnduranceChange() {
      if (this.Burnt) {
         return this.endChange / 3.0F;
      } else if (this.Age >= this.OffAge && this.Age < this.OffAgeMax) {
         return this.endChange / 2.0F;
      } else {
         return this.isCooked() ? this.endChange * 2.0F : this.endChange;
      }
   }

    void setEnduranceChange(float var1) {
      this.endChange = var1;
   }

    float getUnhappyChange() {
    float var1 = this.unhappyChange;
    bool var2 = "Icecream" == this.getType()) || this.hasTag("GoodFrozen");
      if (this.isFrozen() && !var2) {
         var1 += 30.0F;
      }

      if (this.Burnt) {
         var1 += 20.0F;
      }

      if (this.Age >= this.OffAge && this.Age < this.OffAgeMax) {
         var1 += 10.0F;
      }

      if (this.Age >= this.OffAgeMax) {
         var1 += 20.0F;
      }

      if (this.isBadCold() && this.IsCookable && this.isCooked() && this.Heat < 1.3F) {
         var1 += 2.0F;
      }

      if (this.isGoodHot() && this.IsCookable && this.isCooked() && this.Heat > 1.3F) {
         var1 -= 2.0F;
      }

    return var1;
   }

    float getBoredomChange() {
    float var1 = this.boredomChange;
    bool var2 = "Icecream" == this.getType()) || this.hasTag("GoodFrozen");
      if (this.isFrozen() && !var2) {
         var1 += 30.0F;
      }

      if (this.Burnt) {
         var1 += 20.0F;
      }

      if (this.Age >= this.OffAge && this.Age < this.OffAgeMax) {
         var1 += 10.0F;
      }

      if (this.Age >= this.OffAgeMax) {
         var1 += 20.0F;
      }

    return var1;
   }

    float getHungerChange() {
    float var1 = this.hungChange;
      if (this.Burnt) {
         return var1 / 3.0F;
      } else if (this.Age >= this.OffAge && this.Age < this.OffAgeMax) {
         return var1 / 1.3F;
      } else if (this.Age >= this.OffAgeMax) {
         return var1 / 2.2F;
      } else {
         return this.isCooked() ? var1 * 1.3F : var1;
      }
   }

    float getStressChange() {
      if (this.Burnt) {
         return this.stressChange / 4.0F;
      } else if (this.Age >= this.OffAge && this.Age < this.OffAgeMax) {
         return this.stressChange / 1.3F;
      } else if (this.Age >= this.OffAgeMax) {
         return this.stressChange / 2.0F;
      } else {
         return this.isCooked() ? this.stressChange * 1.3F : this.stressChange;
      }
   }

    float getBoredomChangeUnmodified() {
      return this.boredomChange;
   }

    float getEnduranceChangeUnmodified() {
      return this.endChange;
   }

    float getStressChangeUnmodified() {
      return this.stressChange;
   }

    float getThirstChangeUnmodified() {
      return this.thirstChange;
   }

    float getUnhappyChangeUnmodified() {
      return this.unhappyChange;
   }

    float getScore(SurvivorDesc var1) {
    float var2 = 0.0F;
      return var2 - this.getHungerChange() * 100.0F;
   }

    bool isBadCold() {
      return this.bBadCold;
   }

    void setBadCold(bool var1) {
      this.bBadCold = var1;
   }

    bool isGoodHot() {
      return this.bGoodHot;
   }

    void setGoodHot(bool var1) {
      this.bGoodHot = var1;
   }

    bool isCookedInMicrowave() {
      return this.cookedInMicrowave;
   }

    void setCookedInMicrowave(bool var1) {
      this.cookedInMicrowave = var1;
   }

    float getHeat() {
      return this.Heat;
   }

    float getInvHeat() {
      return this.Heat > 1.0F ? (this.Heat - 1.0F) / 2.0F : 1.0F - (this.Heat - 0.2F) / 0.8F;
   }

    void setHeat(float var1) {
      this.Heat = var1;
   }

    float getEndChange() {
      return this.endChange;
   }

    void setEndChange(float var1) {
      this.endChange = var1;
   }

    float getBaseHungChange() {
      return this.getHungChange();
   }

    float getHungChange() {
      return this.hungChange;
   }

    void setHungChange(float var1) {
      this.hungChange = var1;
   }

    std::string getUseOnConsume() {
      return this.useOnConsume;
   }

    void setUseOnConsume(const std::string& var1) {
      this.useOnConsume = var1;
   }

    bool isRotten() {
      return this.Age >= this.OffAgeMax;
   }

    bool isFresh() {
      return this.Age < this.OffAge;
   }

    void setRotten(bool var1) {
      this.rotten = var1;
   }

    bool isbDangerousUncooked() {
      return this.bDangerousUncooked;
   }

    void setbDangerousUncooked(bool var1) {
      this.bDangerousUncooked = var1;
   }

    int getLastCookMinute() {
      return this.LastCookMinute;
   }

    void setLastCookMinute(int var1) {
      this.LastCookMinute = var1;
   }

    float getThirstChange() {
    float var1 = this.thirstChange;
      if (this.Burnt) {
         return var1 / 5.0F;
      } else {
         return this.isCooked() ? var1 / 2.0F : var1;
      }
   }

    void setThirstChange(float var1) {
      this.thirstChange = var1;
   }

    void setReplaceOnCooked(List<std::string> var1) {
      this.ReplaceOnCooked = var1;
   }

   public List<std::string> getReplaceOnCooked() {
      return this.ReplaceOnCooked;
   }

    float getBaseHunger() {
      return this.baseHunger;
   }

    void setBaseHunger(float var1) {
      this.baseHunger = var1;
   }

    bool isSpice() {
      return this.isSpice;
   }

    void setSpice(bool var1) {
      this.isSpice = var1;
   }

    bool isPoison() {
      return this.Poison;
   }

    int getPoisonDetectionLevel() {
      return this.poisonDetectionLevel;
   }

    void setPoisonDetectionLevel(int var1) {
      this.poisonDetectionLevel = var1;
   }

    int getPoisonLevelForRecipe() {
      return this.PoisonLevelForRecipe;
   }

    void setPoisonLevelForRecipe(int var1) {
      this.PoisonLevelForRecipe = var1;
   }

    int getUseForPoison() {
      return this.UseForPoison;
   }

    void setUseForPoison(int var1) {
      this.UseForPoison = var1;
   }

    int getPoisonPower() {
      return this.PoisonPower;
   }

    void setPoisonPower(int var1) {
      this.PoisonPower = var1;
   }

    std::string getFoodType() {
      return this.FoodType;
   }

    void setFoodType(const std::string& var1) {
      this.FoodType = var1;
   }

    bool isRemoveNegativeEffectOnCooked() {
      return this.RemoveNegativeEffectOnCooked;
   }

    void setRemoveNegativeEffectOnCooked(bool var1) {
      this.RemoveNegativeEffectOnCooked = var1;
   }

    std::string getCookingSound() {
      return this.getScriptItem().getCookingSound();
   }

    std::string getCustomEatSound() {
      return this.CustomEatSound;
   }

    void setCustomEatSound(const std::string& var1) {
      this.CustomEatSound = var1;
   }

    std::string getChef() {
      return this.Chef;
   }

    void setChef(const std::string& var1) {
      this.Chef = var1;
   }

    std::string getOnCooked() {
      return this.OnCooked;
   }

    void setOnCooked(const std::string& var1) {
      this.OnCooked = var1;
   }

    std::string getHerbalistType() {
      return this.HerbalistType;
   }

    void setHerbalistType(const std::string& var1) {
      this.HerbalistType = var1;
   }

   public std::vector<std::string> getSpices() {
      return this.spices;
   }

    void setSpices(std::vector<std::string> var1) {
      if (var1 != nullptr && !var1.empty()) {
         if (this.spices == nullptr) {
            this.spices = new std::vector<>(var1);
         } else {
            this.spices.clear();
            this.spices.addAll(var1);
         }
      } else {
         if (this.spices != nullptr) {
            this.spices.clear();
         }
      }
   }

    Texture getTex() {
      if (this.Burnt) {
         return this.textureBurnt;
      } else if (this.Age >= this.OffAgeMax) {
         return this.texturerotten;
      } else {
         return this.isCooked() ? this.textureCooked : super.getTex();
      }
   }

    std::string getWorldTexture() {
      if (this.Burnt) {
         return this.WorldTextureOverdone;
      } else if (this.Age >= this.OffAgeMax) {
         return this.WorldTextureRotten;
      } else {
         return this.isCooked() ? this.WorldTextureCooked : this.WorldTexture;
      }
   }

    int getReduceFoodSickness() {
      return this.ReduceFoodSickness;
   }

    void setReduceFoodSickness(int var1) {
      this.ReduceFoodSickness = var1;
   }

    int getFluReduction() {
      return this.fluReduction;
   }

    void setFluReduction(int var1) {
      this.fluReduction = var1;
   }

    float getPainReduction() {
      return this.painReduction;
   }

    void setPainReduction(float var1) {
      this.painReduction = var1;
   }

    float getCarbohydrates() {
      return this.carbohydrates;
   }

    void setCarbohydrates(float var1) {
      this.carbohydrates = var1;
   }

    float getLipids() {
      return this.lipids;
   }

    void setLipids(float var1) {
      this.lipids = var1;
   }

    float getProteins() {
      return this.proteins;
   }

    void setProteins(float var1) {
      this.proteins = var1;
   }

    float getCalories() {
      return this.calories;
   }

    void setCalories(float var1) {
      this.calories = var1;
   }

    bool isPackaged() {
      return this.packaged;
   }

    void setPackaged(bool var1) {
      this.packaged = var1;
   }

    float getFreezingTime() {
      return this.freezingTime;
   }

    void setFreezingTime(float var1) {
      if (var1 >= 100.0F) {
         this.setFrozen(true);
         var1 = 100.0F;
      } else if (var1 <= 0.0F) {
         var1 = 0.0F;
         this.setFrozen(false);
      }

      this.freezingTime = var1;
   }

    void freeze() {
      this.setFreezingTime(100.0F);
   }

    bool isFrozen() {
      return this.frozen;
   }

    void setFrozen(bool var1) {
      this.frozen = var1;
   }

    bool canBeFrozen() {
      return this.canBeFrozen;
   }

    void setCanBeFrozen(bool var1) {
      this.canBeFrozen = var1;
   }

    bool isFreezing() {
      return this.canBeFrozen()
            && !(this.getFreezingTime() >= 100.0F)
            && this.getOutermostContainer() != nullptr
            && "freezer" == this.getOutermostContainer().getType())
         ? this.getOutermostContainer().isPowered()
         : false;
   }

    bool isThawing() {
      if (!this.canBeFrozen() || this.getFreezingTime() <= 0.0F) {
    return false;
      } else {
         return this.getOutermostContainer() != nullptr && "freezer" == this.getOutermostContainer().getType())
            ? !this.getOutermostContainer().isPowered()
            : true;
      }
   }

    std::string getReplaceOnRotten() {
      return this.replaceOnRotten;
   }

    void setReplaceOnRotten(const std::string& var1) {
      this.replaceOnRotten = var1;
   }

    void multiplyFoodValues(float var1) {
      this.setBoredomChange(this.getBoredomChangeUnmodified() * var1);
      this.setUnhappyChange(this.getUnhappyChangeUnmodified() * var1);
      this.setHungChange(this.getHungChange() * var1);
      this.setFluReduction((int)(this.getFluReduction() * var1));
      this.setThirstChange(this.getThirstChangeUnmodified() * var1);
      this.setPainReduction(this.getPainReduction() * var1);
      this.setReduceFoodSickness((int)(this.getReduceFoodSickness() * var1));
      this.setEndChange(this.getEnduranceChangeUnmodified() * var1);
      this.setStressChange(this.getStressChangeUnmodified() * var1);
      this.setFatigueChange(this.getFatigueChange() * var1);
      this.setCalories(this.getCalories() * var1);
      this.setCarbohydrates(this.getCarbohydrates() * var1);
      this.setProteins(this.getProteins() * var1);
      this.setLipids(this.getLipids() * var1);
   }

    float getRottenTime() {
      return this.rottenTime;
   }

    void setRottenTime(float var1) {
      this.rottenTime = var1;
   }

    float getCompostTime() {
      return this.compostTime;
   }

    void setCompostTime(float var1) {
      this.compostTime = var1;
   }

    std::string getOnEat() {
      return this.onEat;
   }

    void setOnEat(const std::string& var1) {
      this.onEat = var1;
   }

    bool isBadInMicrowave() {
      return this.badInMicrowave;
   }

    void setBadInMicrowave(bool var1) {
      this.badInMicrowave = var1;
   }

    void destroyThisItem() {
    IsoWorldInventoryObject var1 = this.getWorldItem();
      if (var1 != nullptr && var1.getSquare() != nullptr) {
         if (GameServer.bServer) {
            GameServer.RemoveItemFromMap(var1);
         } else {
            var1.removeFromWorld();
            var1.removeFromSquare();
         }

         this.setWorldItem(nullptr);
      } else if (this.container != nullptr) {
    IsoObject var2 = this.container.getParent();
         if (GameServer.bServer) {
            if (!this.isInPlayerInventory()) {
               GameServer.sendRemoveItemFromContainer(this.container, this);
            }

            this.container.Remove(this);
         } else {
            this.container.Remove(this);
         }

         IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this);
         LuaManager.updateOverlaySprite(var2);
      }

      if (!GameServer.bServer) {
         LuaEventManager.triggerEvent("OnContainerUpdate");
      }
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie
