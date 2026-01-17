#pragma once
#include "fmod/fmod/FMODManager.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/characters/skills/PerkFactory.h"
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
#include "zombie/ui/ObjectTooltip.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/io/BitHeader.h"
#include "zombie/util/io/BitHeaderRead.h"
#include "zombie/util/io/BitHeaderWrite.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace inventory {
namespace types {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Food : public InventoryItem {
public:
  bool bBadCold = false;
  bool bGoodHot = false;
  static const float MIN_HEAT = 0.2F;
  static const float MAX_HEAT = 3.0F;
  float Heat = 1.0F;
  float endChange = 0.0F;
  float hungChange = 0.0F;
  std::string useOnConsume = null;
  bool rotten = false;
  bool bDangerousUncooked = false;
  int LastCookMinute = 0;
  float thirstChange = 0.0F;
  bool Poison = false;
private
  List<String> ReplaceOnCooked = nullptr;
  float baseHunger = 0.0F;
public
  ArrayList<String> spices = nullptr;
  bool isSpice = false;
  int poisonDetectionLevel = -1;
  int PoisonLevelForRecipe = 0;
  int UseForPoison = 0;
  int PoisonPower = 0;
  std::string FoodType = null;
  std::string CustomEatSound = null;
  bool RemoveNegativeEffectOnCooked = false;
  std::string Chef = null;
  std::string OnCooked = null;
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
  std::string replaceOnRotten = null;
  bool forceFoodTypeAsName = false;
  float rottenTime = 0.0F;
  float compostTime = 0.0F;
  std::string onEat = null;
  bool badInMicrowave = false;
  bool cookedInMicrowave = false;
  long m_cookingSound = 0L;
  int m_cookingParameter = -1;
  static const int COOKING_STATE_COOKING = 0;
  static const int COOKING_STATE_BURNING = 1;

  std::string getCategory() {
    return this.mainCategory != nullptr ? this.mainCategory : "Food";
  }

public
  Food(const std::string &module, const std::string &name,
       const std::string &itemType, const std::string &texName) {
    super(module, name, itemType, texName);
    Texture.WarnFailFindTexture = false;
    this.texturerotten = Texture.trygetTexture(texName + "Rotten");
    this.textureCooked = Texture.trygetTexture(texName + "Cooked");
    this.textureBurnt = Texture.trygetTexture(texName + "Overdone");
    std::string string0 = "Overdone.png";
    if (this.textureBurnt == nullptr) {
      this.textureBurnt = Texture.trygetTexture(texName + "Burnt");
      if (this.textureBurnt != nullptr) {
        string0 = "Burnt.png";
      }
    }

    std::string string1 = "Rotten.png";
    if (this.texturerotten == nullptr) {
      this.texturerotten = Texture.trygetTexture(texName + "Spoiled");
      if (this.texturerotten != nullptr) {
        string1 = "Spoiled.png";
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
    this.WorldTextureOverdone = this.WorldTexture.replace(".png", string0);
    this.WorldTextureRotten = this.WorldTexture.replace(".png", string1);
    this.cat = ItemType.Food;
  }

public
  Food(const std::string &module, const std::string &name,
       const std::string &itemType, Item item) {
    super(module, name, itemType, item);
    std::string string = item.ItemName;
    Texture.WarnFailFindTexture = false;
    this.texture = item.NormalTexture;
    if (item.SpecialTextures.size() == 0) {
      bool boolean0 = false;
    }

    if (item.SpecialTextures.size() > 0) {
      this.texturerotten = item.SpecialTextures.get(0);
    }

    if (item.SpecialTextures.size() > 1) {
      this.textureCooked = item.SpecialTextures.get(1);
    }

    if (item.SpecialTextures.size() > 2) {
      this.textureBurnt = item.SpecialTextures.get(2);
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

    if (item.SpecialWorldTextureNames.size() > 0) {
      this.WorldTextureRotten = item.SpecialWorldTextureNames.get(0);
    }

    if (item.SpecialWorldTextureNames.size() > 1) {
      this.WorldTextureCooked = item.SpecialWorldTextureNames.get(1);
    }

    if (item.SpecialWorldTextureNames.size() > 2) {
      this.WorldTextureOverdone = item.SpecialWorldTextureNames.get(2);
    }

    this.cat = ItemType.Food;
  }

  bool IsFood() { return true; }

  int getSaveType() { return Item.Type.Food.ordinal(); }

  void update() {
    if (this.hasTag("AlreadyCooked")) {
      this.setCooked(true);
    }

    this.updateTemperature();
    ItemContainer container = this.getOutermostContainer();
    if (container != nullptr) {
      if (this.IsCookable && !this.isFrozen()) {
        if (this.Heat > 1.6F) {
          int int0 = GameTime.getInstance().getMinutes();
          if (int0 != this.LastCookMinute) {
            this.LastCookMinute = int0;
            float float0 = this.Heat / 1.5F;
            if (container.getTemprature() <= 1.6F) {
              float0 *= 0.05F;
            }

            this.CookingTime += float0;
            if (this.shouldPlayCookingSound()) {
              ItemSoundManager.addItem(this);
            }

            if (this.isTaintedWater() &&
                this.CookingTime > Math.min(this.MinutesToCook, 10.0F)) {
              this.setTaintedWater(false);
            }

            if (!this.isCooked() && !this.Burnt &&
                this.CookingTime > this.MinutesToCook) {
              if (this.getReplaceOnCooked() != nullptr && !this.isRotten()) {
                if (GameClient.bClient) {
                  GameClient.instance.sendReplaceOnCooked(this);
                  this.container.Remove(this);
                  IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this);
                  return;
                }

                for (int int1 = 0; int1 < this.getReplaceOnCooked().size();
                     int1++) {
                  InventoryItem item = this.container.AddItem(
                      this.getReplaceOnCooked().get(int1));
                  if (item != nullptr) {
                    item.copyConditionModData(this);
                    if (item instanceof Food && this instanceof Food) {
                    }

                    if (item instanceof Food &&
                                            ((Food)item).isBadInMicrowave() &&
                                            this.container.isMicrowave()) {
                      item.setUnhappyChange(5.0F);
                      item.setBoredomChange(5.0F);
                      ((Food)item).cookedInMicrowave = true;
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
                LuaManager.caller.protectedCall(
                    LuaManager.thread,
                    LuaManager.env.rawget(this.getOnCooked()), this);
              }

              if (this.isBadInMicrowave() && this.container.isMicrowave()) {
                this.setUnhappyChange(5.0F);
                this.setBoredomChange(5.0F);
                this.cookedInMicrowave = true;
              }

              if (this.Chef != nullptr && !this.Chef.isEmpty()) {
                for (int int2 = 0; int2 < IsoPlayer.numPlayers; int2++) {
                  IsoPlayer player = IsoPlayer.players[int2];
                  if (player != nullptr && !player.isDead() &&
                      this.Chef == player.getFullName())) {
                      player.getXp().AddXP(PerkFactory.Perks.Cooking, 10.0F);
                      break;
                    }
                }
              }
            }

            if (this.CookingTime > this.MinutesToBurn) {
              this.Burnt = true;
              this.setCooked(false);
            }

            if (IsoWorld.instance.isHydroPowerOn() && this.Burnt &&
                this.CookingTime >= 50.0F &&
                this.CookingTime >=
                    this.MinutesToCook * 2.0F + this.MinutesToBurn / 2.0F &&
                Rand.Next(Rand.AdjustForFramerate(200)) == 0) {
                            boolean boolean0 = this.container != nullptr
                                && this.container.getParent() != nullptr
                                && this.container.getParent().getName() != nullptr
                                && this.container.getParent().getName() == "Campfire");
                            if (!boolean0 && this.container != nullptr &&
                                    this.container.getParent() != nullptr &&
                                    this.container.getParent()
                                    instanceof IsoFireplace) {
                              boolean0 = true;
                            }

                            if (this.container != nullptr &&
                                this.container.SourceGrid != nullptr &&
                                !boolean0) {
                              IsoFireManager.StartFire(
                                  this.container.SourceGrid.getCell(),
                                  this.container.SourceGrid, true, 500000);
                              this.IsCookable = false;
                            }
            }
          }
        }
      } else if (this.isTaintedWater() && this.Heat > 1.6F &&
                 !this.isFrozen()) {
        int int3 = GameTime.getInstance().getMinutes();
        if (int3 != this.LastCookMinute) {
          this.LastCookMinute = int3;
          float float1 = 1.0F;
          if (container.getTemprature() <= 1.6F) {
            float1 = (float)(float1 * 0.2);
          }

          this.CookingTime += float1;
          if (this.CookingTime > 10.0F) {
            this.setTaintedWater(false);
          }
        }
      }
    }

    this.updateRotting(container);
  }

  void updateSound(BaseSoundEmitter emitter) {
    if (this.shouldPlayCookingSound()) {
      if (emitter.isPlaying(this.m_cookingSound)) {
        this.setCookingParameter(emitter);
        return;
      }

      ItemContainer container = this.getOutermostContainer();
      IsoGridSquare square = container.getParent().getSquare();
      emitter.setPos(square.getX() + 0.5F, square.getY() + 0.5F, square.getZ());
      this.m_cookingSound =
          emitter.playSoundImpl(this.getCookingSound(), (IsoObject) nullptr);
      this.setCookingParameter(emitter);
    } else {
      emitter.stopOrTriggerSound(this.m_cookingSound);
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
      ItemContainer container = this.getOutermostContainer();
      return container != nullptr && container.getParent() != nullptr &&
                     container.getParent().getObjectIndex() != -1 &&
                     !(container.getTemprature() <= 1.6F)
                 ? this.isCookable() && !this.isFrozen() &&
                       this.getHeat() > 1.6F
                 : false;
    }
  }

  void setCookingParameter(BaseSoundEmitter baseSoundEmitter) {
    bool boolean0 = this.CookingTime > this.MinutesToCook;
    int int0 = boolean0 ? 1 : 0;
    if (int0 != this.m_cookingParameter) {
      this.m_cookingParameter = int0;
      baseSoundEmitter.setParameterValue(
          this.m_cookingSound,
          FMODManager.instance.getParameterDescription("CookingState"),
          this.m_cookingParameter);
    }
  }

  void updateTemperature() {
    ItemContainer container = this.getOutermostContainer();
    float float0 = container == null ? 1.0F : container.getTemprature();
    if (this.Heat > float0) {
      this.Heat = this.Heat - 0.001F * GameTime.instance.getMultiplier();
      if (this.Heat < Math.max(0.2F, float0)) {
        this.Heat = Math.max(0.2F, float0);
      }
    }

    if (this.Heat < float0) {
      this.Heat =
          this.Heat + float0 / 1000.0F * GameTime.instance.getMultiplier();
      if (this.Heat > Math.min(3.0F, float0)) {
        this.Heat = Math.min(3.0F, float0);
      }
    }
  }

  void updateRotting(ItemContainer container) {
    if (this.OffAgeMax != 1.0E9) {
      if (!GameClient.bClient || this.isInLocalPlayerInventory()) {
        if (!GameServer.bServer || this.container == nullptr ||
            this.getOutermostContainer() == this.container) {
          if (this.replaceOnRotten != nullptr &&
              !this.replaceOnRotten.isEmpty()) {
            this.updateAge();
            if (this.isRotten()) {
              InventoryItem item = InventoryItemFactory.CreateItem(
                  this.getModule() + "." + this.replaceOnRotten, this);
              if (item == nullptr) {
                DebugLog.General.warn(
                    "ReplaceOnRotten = " + this.replaceOnRotten +
                    " doesn't exist for " + this.getFullType());
                this.destroyThisItem();
                return;
              }

              item.setAge(this.getAge());
              IsoWorldInventoryObject worldInventoryObject =
                  this.getWorldItem();
              if (worldInventoryObject != nullptr &&
                  worldInventoryObject.getSquare() != nullptr) {
                IsoGridSquare square = worldInventoryObject.getSquare();
                if (!GameServer.bServer) {
                  worldInventoryObject.item = item;
                  item.setWorldItem(worldInventoryObject);
                  worldInventoryObject.updateSprite();
                  IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this);
                  LuaEventManager.triggerEvent("OnContainerUpdate");
                  return;
                }

                square.AddWorldInventoryItem(item, worldInventoryObject.xoff,
                                             worldInventoryObject.yoff,
                                             worldInventoryObject.zoff, true);
              } else if (this.container != nullptr) {
                this.container.AddItem(item);
                if (GameServer.bServer) {
                  GameServer.sendAddItemToContainer(this.container, item);
                }
              }

              this.destroyThisItem();
              return;
            }
          }

          if (SandboxOptions.instance.DaysForRottenFoodRemoval.getValue() >=
              0) {
            if (container != nullptr && container.parent instanceof
                IsoCompost) {
              return;
            }

            this.updateAge();
            if (this.getAge() > this.getOffAgeMax() +
                                    SandboxOptions.instance
                                        .DaysForRottenFoodRemoval.getValue()) {
              this.destroyThisItem();
              return;
            }
          }
        }
      }
    }
  }

  void updateAge() {
    ItemContainer container = this.getOutermostContainer();
    this.updateFreezing(container);
    bool boolean0 = false;
    if (container != nullptr && container.getSourceGrid() != nullptr &&
        container.getSourceGrid().haveElectricity()) {
      boolean0 = true;
    }

    float float0 = (float)GameTime.getInstance().getWorldAgeHours();
    float float1 = 0.2F;
    if (SandboxOptions.instance.FridgeFactor.getValue() == 1) {
      float1 = 0.4F;
    } else if (SandboxOptions.instance.FridgeFactor.getValue() == 2) {
      float1 = 0.3F;
    } else if (SandboxOptions.instance.FridgeFactor.getValue() == 4) {
      float1 = 0.1F;
    } else if (SandboxOptions.instance.FridgeFactor.getValue() == 5) {
      float1 = 0.03F;
    }

    if (this.LastAged < 0.0F) {
      this.LastAged = float0;
    } else if (this.LastAged > float0) {
      this.LastAged = float0;
    }

    if (float0 > this.LastAged) {
      double double0 = float0 - this.LastAged;
      if (container != nullptr && this.Heat != container.getTemprature()) {
        if (double0 < 0.33333334F) {
          if (!IsoWorld.instance.getCell().getProcessItems().contains(this)) {
            this.Heat =
                GameTime.instance.Lerp(this.Heat, container.getTemprature(),
                                       (float)double0 / 0.33333334F);
            IsoWorld.instance.getCell().addToProcessItems(this);
          }
        } else {
          this.Heat = container.getTemprature();
        }
      }

      if (this.isFrozen()) {
        double0 *= 0.02F;
      } else if (container != nullptr && (container.getType() == "fridge") ||
                 container.getType() == "freezer"))) {
          if (boolean0) {
            double0 *= float1;
          } else if (SandboxOptions.instance.getElecShutModifier() > -1 &&
                     this.LastAged <
                         SandboxOptions.instance.getElecShutModifier() * 24) {
            float float2 = Math.min(
                (float)(SandboxOptions.instance.getElecShutModifier() * 24),
                float0);
            double0 = (float2 - this.LastAged) * float1;
            if (float0 > SandboxOptions.instance.getElecShutModifier() * 24) {
              double0 +=
                  float0 - SandboxOptions.instance.getElecShutModifier() * 24;
            }
          }
        }

      float float3 = 1.0F;
      if (SandboxOptions.instance.FoodRotSpeed.getValue() == 1) {
        float3 = 1.7F;
      } else if (SandboxOptions.instance.FoodRotSpeed.getValue() == 2) {
        float3 = 1.4F;
      } else if (SandboxOptions.instance.FoodRotSpeed.getValue() == 4) {
        float3 = 0.7F;
      } else if (SandboxOptions.instance.FoodRotSpeed.getValue() == 5) {
        float3 = 0.4F;
      }

      bool boolean1 =
          !this.Burnt && this.OffAge < 1000000000 && this.Age < this.OffAge;
      bool boolean2 = !this.Burnt && this.OffAgeMax < 1000000000 &&
                      this.Age >= this.OffAgeMax;
      this.Age = (float)(this.Age + double0 * float3 / 24.0);
      this.LastAged = float0;
      bool boolean3 =
          !this.Burnt && this.OffAge < 1000000000 && this.Age < this.OffAge;
      bool boolean4 = !this.Burnt && this.OffAgeMax < 1000000000 &&
                      this.Age >= this.OffAgeMax;
      if (!GameServer.bServer &&
          (boolean1 != boolean3 || boolean2 != boolean4)) {
        LuaEventManager.triggerEvent("OnContainerUpdate", this);
      }
    }
  }

  void setAutoAge() {
    ItemContainer container = this.getOutermostContainer();
    float float0 = (float)GameTime.getInstance().getWorldAgeHours() / 24.0F;
    float0 += (SandboxOptions.instance.TimeSinceApo.getValue() - 1) * 30;
    float float1 = float0;
    bool boolean0 = false;
    if (container != nullptr && container.getParent() != nullptr &&
        container.getParent().getSprite() != nullptr) {
      boolean0 =
          container.getParent().getSprite().getProperties().Is("IsFridge");
    }

    if (container != nullptr && (boolean0 || container.getType() == "fridge") ||
        container.getType() == "freezer"))) {
        int int0 = SandboxOptions.instance.ElecShutModifier.getValue();
        if (int0 > -1) {
          float float2 = Math.min((float)int0, float0);
          int int1 = SandboxOptions.instance.FridgeFactor.getValue();
          float float3 = 0.2F;
          if (int1 == 1) {
            float3 = 0.4F;
          } else if (int1 == 2) {
            float3 = 0.3F;
          } else if (int1 == 4) {
            float3 = 0.1F;
          } else if (int1 == 5) {
            float3 = 0.03F;
          }

          if (!container.getType() == "fridge") && this.canBeFrozen() && !boolean0) {
              float float4 = float2;
              float float5 = 100.0F;
              if (float0 > float2) {
                float float6 = (float0 - float2) * 24.0F;
                float float7 = 1440.0F /
                               GameTime.getInstance().getMinutesPerDay() *
                               60.0F * 5.0F;
                float float8 = 0.0095999995F;
                float5 -= float8 * float7 * float6;
                if (float5 > 0.0F) {
                  float4 = float2 + float6 / 24.0F;
                } else {
                  float float9 = 100.0F / (float8 * float7);
                  float4 = float2 + float9 / 24.0F;
                  float5 = 0.0F;
                }
              }

              float1 = float0 - float4;
              float1 += float4 * 0.02F;
              this.setFreezingTime(float5);
            }
          else {
            float1 = float0 - float2;
            float1 += float2 * float3;
          }
        }
      }

    int int2 = SandboxOptions.instance.FoodRotSpeed.getValue();
    float float10 = 1.0F;
    if (int2 == 1) {
      float10 = 1.7F;
    } else if (int2 == 2) {
      float10 = 1.4F;
    } else if (int2 == 4) {
      float10 = 0.7F;
    } else if (int2 == 5) {
      float10 = 0.4F;
    }

    this.Age = float1 * float10;
    this.LastAged = (float)GameTime.getInstance().getWorldAgeHours();
    this.LastFrozenUpdate = this.LastAged;
    if (container != nullptr) {
      this.setHeat(container.getTemprature());
    }
  }

  void updateFreezing(ItemContainer outermostContainer) {
    float float0 = (float)GameTime.getInstance().getWorldAgeHours();
    if (this.LastFrozenUpdate < 0.0F) {
      this.LastFrozenUpdate = float0;
    } else if (this.LastFrozenUpdate > float0) {
      this.LastFrozenUpdate = float0;
    }

    if (float0 > this.LastFrozenUpdate) {
      float float1 = float0 - this.LastFrozenUpdate;
      float float2 = 4.0F;
      float float3 = 1.5F;
      if (this.isFreezing()) {
        this.setFreezingTime(this.getFreezingTime() + float1 / float2 * 100.0F);
      }

      if (this.isThawing()) {
        float float4 = float3;
        if (outermostContainer != nullptr &&
            "fridge" == outermostContainer.getType()) && outermostContainer.isPowered()) {
                    float4 = float3 * 2.0F;
                }

        if (outermostContainer != nullptr &&
            outermostContainer.getTemprature() > 1.0F) {
          float4 /= 6.0F;
        }

        this.setFreezingTime(this.getFreezingTime() - float1 / float4 * 100.0F);
      }

      this.LastFrozenUpdate = float0;
    }
  }

  /**
   * @return the ActualWeight
   */
  float getActualWeight() {
    if (this.haveExtraItems()) {
      float float0 = this.getHungChange();
      float float1 = this.getBaseHunger();
      float float2 = float1 == 0.0F ? 0.0F : float0 / float1;
      float float3 = 0.0F;
      if (this.getReplaceOnUse() != nullptr) {
        std::string string0 = this.getReplaceOnUseFullType();
        Item item0 = ScriptManager.instance.getItem(string0);
        if (item0 != nullptr) {
          float3 = item0.getActualWeight();
        }
      }

      float float4 = super.getActualWeight() + this.getExtraItemsWeight();
      return (float4 - float3) * float2 + float3;
    } else {
      if (this.getReplaceOnUse() != nullptr && !this.isCustomWeight()) {
        std::string string1 = this.getReplaceOnUseFullType();
        Item item1 = ScriptManager.instance.getItem(string1);
        if (item1 != nullptr) {
          float float5 = 1.0F;
          if (this.getScriptItem().getHungerChange() < 0.0F) {
            float5 = this.getHungChange() * 100.0F /
                     this.getScriptItem().getHungerChange();
          } else if (this.getScriptItem().getThirstChange() < 0.0F) {
            float5 = this.getThirstChange() * 100.0F /
                     this.getScriptItem().getThirstChange();
          }

          return (this.getScriptItem().getActualWeight() -
                  item1.getActualWeight()) *
                     float5 +
                 item1.getActualWeight();
        }
      } else if (!this.isCustomWeight()) {
        float float6 = 1.0F;
        if (this.getScriptItem().getHungerChange() < 0.0F) {
          float6 = this.getHungChange() * 100.0F /
                   this.getScriptItem().getHungerChange();
        } else if (this.getScriptItem().getThirstChange() < 0.0F) {
          float6 = this.getThirstChange() * 100.0F /
                   this.getScriptItem().getThirstChange();
        }

        return this.getScriptItem().getActualWeight() * float6;
      }

      return super.getActualWeight();
    }
  }

  /**
   * @return the Weight
   */
  float getWeight() {
    return this.getReplaceOnUse() != nullptr ? this.getActualWeight()
                                             : super.getWeight();
  }

  bool CanStack(InventoryItem item) { return false; }

  void save(ByteBuffer output, bool net) {
    super.save(output, net);
    output.putFloat(this.Age);
    output.putFloat(this.LastAged);
    BitHeaderWrite bitHeaderWrite0 =
        BitHeader.allocWrite(BitHeader.HeaderSize.Byte, output);
    if (this.calories != 0.0F || this.proteins != 0.0F || this.lipids != 0.0F ||
        this.carbohydrates != 0.0F) {
      bitHeaderWrite0.addFlags(1);
      output.putFloat(this.calories);
      output.putFloat(this.proteins);
      output.putFloat(this.lipids);
      output.putFloat(this.carbohydrates);
    }

    if (this.hungChange != 0.0F) {
      bitHeaderWrite0.addFlags(2);
      output.putFloat(this.hungChange);
    }

    if (this.baseHunger != 0.0F) {
      bitHeaderWrite0.addFlags(4);
      output.putFloat(this.baseHunger);
    }

    if (this.unhappyChange != 0.0F) {
      bitHeaderWrite0.addFlags(8);
      output.putFloat(this.unhappyChange);
    }

    if (this.boredomChange != 0.0F) {
      bitHeaderWrite0.addFlags(16);
      output.putFloat(this.boredomChange);
    }

    if (this.thirstChange != 0.0F) {
      bitHeaderWrite0.addFlags(32);
      output.putFloat(this.thirstChange);
    }

    BitHeaderWrite bitHeaderWrite1 =
        BitHeader.allocWrite(BitHeader.HeaderSize.Integer, output);
    if (this.Heat != 1.0F) {
      bitHeaderWrite1.addFlags(1);
      output.putFloat(this.Heat);
    }

    if (this.LastCookMinute != 0) {
      bitHeaderWrite1.addFlags(2);
      output.putInt(this.LastCookMinute);
    }

    if (this.CookingTime != 0.0F) {
      bitHeaderWrite1.addFlags(4);
      output.putFloat(this.CookingTime);
    }

    if (this.Cooked) {
      bitHeaderWrite1.addFlags(8);
    }

    if (this.Burnt) {
      bitHeaderWrite1.addFlags(16);
    }

    if (this.IsCookable) {
      bitHeaderWrite1.addFlags(32);
    }

    if (this.bDangerousUncooked) {
      bitHeaderWrite1.addFlags(64);
    }

    if (this.poisonDetectionLevel != -1) {
      bitHeaderWrite1.addFlags(128);
      output.put((byte)this.poisonDetectionLevel);
    }

    if (this.spices != nullptr) {
      bitHeaderWrite1.addFlags(256);
      output.put((byte)this.spices.size());

      for (String string : this.spices) {
        GameWindow.WriteString(output, string);
      }
    }

    if (this.PoisonPower != 0) {
      bitHeaderWrite1.addFlags(512);
      output.put((byte)this.PoisonPower);
    }

    if (this.Chef != nullptr) {
      bitHeaderWrite1.addFlags(1024);
      GameWindow.WriteString(output, this.Chef);
    }

    if (this.OffAge != 1.0E9) {
      bitHeaderWrite1.addFlags(2048);
      output.putInt(this.OffAge);
    }

    if (this.OffAgeMax != 1.0E9) {
      bitHeaderWrite1.addFlags(4096);
      output.putInt(this.OffAgeMax);
    }

    if (this.painReduction != 0.0F) {
      bitHeaderWrite1.addFlags(8192);
      output.putFloat(this.painReduction);
    }

    if (this.fluReduction != 0) {
      bitHeaderWrite1.addFlags(16384);
      output.putInt(this.fluReduction);
    }

    if (this.ReduceFoodSickness != 0) {
      bitHeaderWrite1.addFlags(32768);
      output.putInt(this.ReduceFoodSickness);
    }

    if (this.Poison) {
      bitHeaderWrite1.addFlags(65536);
    }

    if (this.UseForPoison != 0) {
      bitHeaderWrite1.addFlags(131072);
      output.putShort((short)this.UseForPoison);
    }

    if (this.freezingTime != 0.0F) {
      bitHeaderWrite1.addFlags(262144);
      output.putFloat(this.freezingTime);
    }

    if (this.isFrozen()) {
      bitHeaderWrite1.addFlags(524288);
    }

    if (this.LastFrozenUpdate != 0.0F) {
      bitHeaderWrite1.addFlags(1048576);
      output.putFloat(this.LastFrozenUpdate);
    }

    if (this.rottenTime != 0.0F) {
      bitHeaderWrite1.addFlags(2097152);
      output.putFloat(this.rottenTime);
    }

    if (this.compostTime != 0.0F) {
      bitHeaderWrite1.addFlags(4194304);
      output.putFloat(this.compostTime);
    }

    if (this.cookedInMicrowave) {
      bitHeaderWrite1.addFlags(8388608);
    }

    if (this.fatigueChange != 0.0F) {
      bitHeaderWrite1.addFlags(16777216);
      output.putFloat(this.fatigueChange);
    }

    if (this.endChange != 0.0F) {
      bitHeaderWrite1.addFlags(33554432);
      output.putFloat(this.endChange);
    }

    if (!bitHeaderWrite1 == 0)) {
        bitHeaderWrite0.addFlags(64);
        bitHeaderWrite1.write();
      }
    else {
      output.position(bitHeaderWrite1.getStartPosition());
    }

    bitHeaderWrite0.write();
    bitHeaderWrite0.release();
    bitHeaderWrite1.release();
  }

  void load(ByteBuffer input, int WorldVersion) {
    super.load(input, WorldVersion);
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
    this.Age = input.getFloat();
    this.LastAged = input.getFloat();
    BitHeaderRead bitHeaderRead0 =
        BitHeader.allocRead(BitHeader.HeaderSize.Byte, input);
    if (!bitHeaderRead0 == 0)) {
        if (bitHeaderRead0.hasFlags(1)) {
          this.calories = input.getFloat();
          this.proteins = input.getFloat();
          this.lipids = input.getFloat();
          this.carbohydrates = input.getFloat();
        }

        if (bitHeaderRead0.hasFlags(2)) {
          this.hungChange = input.getFloat();
        }

        if (bitHeaderRead0.hasFlags(4)) {
          this.baseHunger = input.getFloat();
        }

        if (bitHeaderRead0.hasFlags(8)) {
          this.unhappyChange = input.getFloat();
        }

        if (bitHeaderRead0.hasFlags(16)) {
          this.boredomChange = input.getFloat();
        }

        if (bitHeaderRead0.hasFlags(32)) {
          this.thirstChange = input.getFloat();
        }

        if (bitHeaderRead0.hasFlags(64)) {
          BitHeaderRead bitHeaderRead1 =
              BitHeader.allocRead(BitHeader.HeaderSize.Integer, input);
          if (bitHeaderRead1.hasFlags(1)) {
            this.Heat = input.getFloat();
          }

          if (bitHeaderRead1.hasFlags(2)) {
            this.LastCookMinute = input.getInt();
          }

          if (bitHeaderRead1.hasFlags(4)) {
            this.CookingTime = input.getFloat();
          }

          this.Cooked = bitHeaderRead1.hasFlags(8);
          this.Burnt = bitHeaderRead1.hasFlags(16);
          this.IsCookable = bitHeaderRead1.hasFlags(32);
          this.bDangerousUncooked = bitHeaderRead1.hasFlags(64);
          if (bitHeaderRead1.hasFlags(128)) {
            this.poisonDetectionLevel = input.get();
          }

          if (bitHeaderRead1.hasFlags(256)) {
            this.spices = std::make_unique<ArrayList<>>();
            uint8_t byte0 = input.get();

            for (int int0 = 0; int0 < byte0; int0++) {
              std::string string = GameWindow.ReadString(input);
              this.spices.add(string);
            }
          }

          if (bitHeaderRead1.hasFlags(512)) {
            this.PoisonPower = input.get();
          }

          if (bitHeaderRead1.hasFlags(1024)) {
            this.Chef = GameWindow.ReadString(input);
          }

          if (bitHeaderRead1.hasFlags(2048)) {
            this.OffAge = input.getInt();
          }

          if (bitHeaderRead1.hasFlags(4096)) {
            this.OffAgeMax = input.getInt();
          }

          if (bitHeaderRead1.hasFlags(8192)) {
            this.painReduction = input.getFloat();
          }

          if (bitHeaderRead1.hasFlags(16384)) {
            this.fluReduction = input.getInt();
          }

          if (bitHeaderRead1.hasFlags(32768)) {
            this.ReduceFoodSickness = input.getInt();
          }

          this.Poison = bitHeaderRead1.hasFlags(65536);
          if (bitHeaderRead1.hasFlags(131072)) {
            this.UseForPoison = input.getShort();
          }

          if (bitHeaderRead1.hasFlags(262144)) {
            this.freezingTime = input.getFloat();
          }

          this.setFrozen(bitHeaderRead1.hasFlags(524288));
          if (bitHeaderRead1.hasFlags(1048576)) {
            this.LastFrozenUpdate = input.getFloat();
          }

          if (bitHeaderRead1.hasFlags(2097152)) {
            this.rottenTime = input.getFloat();
          }

          if (bitHeaderRead1.hasFlags(4194304)) {
            this.compostTime = input.getFloat();
          }

          this.cookedInMicrowave = bitHeaderRead1.hasFlags(8388608);
          if (bitHeaderRead1.hasFlags(16777216)) {
            this.fatigueChange = input.getFloat();
          }

          if (bitHeaderRead1.hasFlags(33554432)) {
            this.endChange = input.getFloat();
          }

          bitHeaderRead1.release();
        }
      }

    bitHeaderRead0.release();
    if (GameServer.bServer && this.LastAged == -1.0F) {
      this.LastAged = (float)GameTime.getInstance().getWorldAgeHours();
    }
  }

  bool finishupdate() {
    if (this.container != nullptr ||
        this.getWorldItem() != nullptr &&
            this.getWorldItem().getSquare() != nullptr) {
      if (this.IsCookable) {
        return false;
      } else if (this.container == nullptr ||
                 this.Heat == this.container.getTemprature() &&
                     !this.container.isTemperatureChanging()) {
        if (this.isTaintedWater() && this.container != nullptr &&
            this.container.getTemprature() > 1.0F) {
          return false;
        } else {
          if ((!GameClient.bClient || this.isInLocalPlayerInventory()) &&
              this.OffAgeMax != 1.0E9) {
            if (this.replaceOnRotten != nullptr &&
                !this.replaceOnRotten.isEmpty()) {
              return false;
            }

            if (SandboxOptions.instance.DaysForRottenFoodRemoval.getValue() !=
                -1) {
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
      if (this.replaceOnRotten != nullptr && !this.replaceOnRotten.isEmpty()) {
        return true;
      }

      if (SandboxOptions.instance.DaysForRottenFoodRemoval.getValue() != -1) {
        return true;
      }
    }

    return this.getHeat() != 1.0F;
  }

  /**
   * @return the name
   */
  std::string getName() {
    std::string string = "";
    if (this.Burnt) {
      string = string + this.BurntString + " ";
    } else if (this.OffAge < 1000000000 && this.Age < this.OffAge) {
      string = string + this.FreshString + " ";
    } else if (this.OffAgeMax < 1000000000 && this.Age >= this.OffAgeMax) {
      string = string + this.OffString + " ";
    } else if (this.OffAgeMax < 1000000000 && this.Age >= this.OffAge) {
      string = string + this.StaleString + " ";
    }

    if (this.isCooked() && !this.Burnt && !this.hasTag("HideCooked")) {
      string = string + this.CookedString + " ";
    } else if (this.IsCookable && !this.Burnt && !this.hasTag("HideCooked")) {
      string = string + this.UnCookedString + " ";
    }

    if (this.isFrozen()) {
      string = string + this.FrozenString + " ";
    }

    string = string.trim();
    return string.isEmpty()
               ? this.name
               : Translator.getText("IGUI_FoodNaming", string, this.name);
  }

  void DoTooltip(ObjectTooltip tooltipUI, ObjectTooltip.Layout layout) {
    if (this.getHungerChange() != 0.0F) {
      ObjectTooltip.LayoutItem layoutItem0 = layout.addItem();
      layoutItem0.setLabel(Translator.getText("Tooltip_food_Hunger") + ":",
                           1.0F, 1.0F, 0.8F, 1.0F);
      int int0 = (int)(this.getHungerChange() * 100.0F);
      layoutItem0.setValueRight(int0, false);
    }

    if (this.getThirstChange() != 0.0F) {
      ObjectTooltip.LayoutItem layoutItem1 = layout.addItem();
      layoutItem1.setLabel(Translator.getText("Tooltip_food_Thirst") + ":",
                           1.0F, 1.0F, 0.8F, 1.0F);
      int int1 = (int)(this.getThirstChange() * 100.0F);
      layoutItem1.setValueRight(int1, false);
    }

    if (this.getEnduranceChange() != 0.0F) {
      ObjectTooltip.LayoutItem layoutItem2 = layout.addItem();
      int int2 = (int)(this.getEnduranceChange() * 100.0F);
      layoutItem2.setLabel(Translator.getText("Tooltip_food_Endurance") + ":",
                           1.0F, 1.0F, 0.8F, 1.0F);
      layoutItem2.setValueRight(int2, true);
    }

    if (this.getStressChange() != 0.0F) {
      ObjectTooltip.LayoutItem layoutItem3 = layout.addItem();
      int int3 = (int)(this.getStressChange() * 100.0F);
      layoutItem3.setLabel(Translator.getText("Tooltip_food_Stress") + ":",
                           1.0F, 1.0F, 0.8F, 1.0F);
      layoutItem3.setValueRight(int3, false);
    }

    if (this.getBoredomChange() != 0.0F) {
      ObjectTooltip.LayoutItem layoutItem4 = layout.addItem();
      int int4 = (int)this.getBoredomChange();
      layoutItem4.setLabel(Translator.getText("Tooltip_food_Boredom") + ":",
                           1.0F, 1.0F, 0.8F, 1.0F);
      layoutItem4.setValueRight(int4, false);
    }

    if (this.getUnhappyChange() != 0.0F) {
      ObjectTooltip.LayoutItem layoutItem5 = layout.addItem();
      int int5 = (int)this.getUnhappyChange();
      layoutItem5.setLabel(Translator.getText("Tooltip_food_Unhappiness") + ":",
                           1.0F, 1.0F, 0.8F, 1.0F);
      layoutItem5.setValueRight(int5, false);
    }

    if (this.isIsCookable() && !this.isFrozen() && !this.Burnt &&
        this.getHeat() > 1.6) {
      float float0 = this.getCookingTime();
      float float1 = this.getMinutesToCook();
      float float2 = this.getMinutesToBurn();
      float float3 = float0 / float1;
      ColorInfo colorInfo = Core.getInstance().getGoodHighlitedColor();
      float float4 = colorInfo.getR();
      float float5 = colorInfo.getG();
      float float6 = colorInfo.getB();
      float float7 = 1.0F;
      float float8 = colorInfo.getR();
      float float9 = colorInfo.getG();
      float float10 = colorInfo.getB();
      std::string string = Translator.getText("IGUI_invpanel_Cooking");
      if (float0 > float1) {
        colorInfo = Core.getInstance().getBadHighlitedColor();
        string = Translator.getText("IGUI_invpanel_Burning");
        float8 = colorInfo.getR();
        float9 = colorInfo.getG();
        float10 = colorInfo.getB();
        float3 = (float0 - float1) / (float2 - float1);
        float4 = colorInfo.getR();
        float5 = colorInfo.getG();
        float6 = colorInfo.getB();
      }

      ObjectTooltip.LayoutItem layoutItem6 = layout.addItem();
      layoutItem6.setLabel(string + ": ", float8, float9, float10, 1.0F);
      layoutItem6.setProgress(float3, float4, float5, float6, float7);
    }

    if (this.getFreezingTime() < 100.0F && this.getFreezingTime() > 0.0F) {
      float float11 = this.getFreezingTime() / 100.0F;
      float float12 = 0.0F;
      float float13 = 0.6F;
      float float14 = 0.0F;
      float float15 = 0.7F;
      float float16 = 1.0F;
      float float17 = 1.0F;
      float float18 = 0.8F;
      ObjectTooltip.LayoutItem layoutItem7 = layout.addItem();
      layoutItem7.setLabel(Translator.getText("IGUI_invpanel_FreezingTime") +
                               ": ",
                           float16, float17, float18, 1.0F);
      layoutItem7.setProgress(float11, float12, float13, float14, float15);
    }

    if (Core.bDebug && DebugOptions.instance.TooltipInfo.getValue() ||
        this.isPackaged() ||
        tooltipUI.getCharacter() != nullptr &&
            (tooltipUI.getCharacter().Traits.Nutritionist.isSet() ||
             tooltipUI.getCharacter().Traits.Nutritionist2.isSet())) {
      ObjectTooltip.LayoutItem layoutItem8 = layout.addItem();
      layoutItem8.setLabel(Translator.getText("Tooltip_food_Calories") + ":",
                           1.0F, 1.0F, 0.8F, 1.0F);
      layoutItem8.setValueRightNoPlus(this.getCalories());
      layoutItem8 = layout.addItem();
      layoutItem8.setLabel(Translator.getText("Tooltip_food_Carbs") + ":", 1.0F,
                           1.0F, 0.8F, 1.0F);
      layoutItem8.setValueRightNoPlus(this.getCarbohydrates());
      layoutItem8 = layout.addItem();
      layoutItem8.setLabel(Translator.getText("Tooltip_food_Prots") + ":", 1.0F,
                           1.0F, 0.8F, 1.0F);
      layoutItem8.setValueRightNoPlus(this.getProteins());
      layoutItem8 = layout.addItem();
      layoutItem8.setLabel(Translator.getText("Tooltip_food_Fat") + ":", 1.0F,
                           1.0F, 0.8F, 1.0F);
      layoutItem8.setValueRightNoPlus(this.getLipids());
    }

    if (this.isbDangerousUncooked() && !this.isCooked() && !this.isBurnt()) {
      ObjectTooltip.LayoutItem layoutItem9 = layout.addItem();
      layoutItem9.setLabel(
          Translator.getText("Tooltip_food_Dangerous_uncooked"),
          Core.getInstance().getBadHighlitedColor().getR(),
          Core.getInstance().getBadHighlitedColor().getG(),
          Core.getInstance().getBadHighlitedColor().getB(), 1.0F);
      if (this.hasTag("Egg")) {
        layoutItem9.setLabel(
            Translator.getText("Tooltip_food_SlightDanger_uncooked"), 1.0F,
            0.0F, 0.0F, 1.0F);
      }
    }

    if (this.getScriptItem().RemoveUnhappinessWhenCooked && !this.isCooked()) {
      ObjectTooltip.LayoutItem layoutItem10 = layout.addItem();
      layoutItem10.setLabel(
          Translator.getText("Tooltip_food_CookToRemoveUnhappiness"),
          Core.getInstance().getBadHighlitedColor().getR(),
          Core.getInstance().getBadHighlitedColor().getG(),
          Core.getInstance().getBadHighlitedColor().getB(), 1.0F);
    }

    if ((this.isGoodHot() || this.isBadCold()) && this.Heat < 1.3F) {
      ObjectTooltip.LayoutItem layoutItem11 = layout.addItem();
      layoutItem11.setLabel(Translator.getText("Tooltip_food_BetterHot"), 1.0F,
                            0.9F, 0.9F, 1.0F);
    }

    if (this.cookedInMicrowave) {
      ObjectTooltip.LayoutItem layoutItem12 = layout.addItem();
      layoutItem12.setLabel(
          Translator.getText("Tooltip_food_CookedInMicrowave"), 1.0F, 0.9F,
          0.9F, 1.0F);
    }

    if (Core.bDebug && DebugOptions.instance.TooltipInfo.getValue()) {
      ObjectTooltip.LayoutItem layoutItem13 = layout.addItem();
      layoutItem13.setLabel("DBG: BaseHunger", 0.0F, 1.0F, 0.0F, 1.0F);
      layoutItem13.setValueRight((int)(this.getBaseHunger() * 100.0F), false);
      layoutItem13 = layout.addItem();
      layoutItem13.setLabel("DBG: Age", 0.0F, 1.0F, 0.0F, 1.0F);
      layoutItem13.setValueRightNoPlus(this.getAge() * 24.0F);
      if (this.getOffAgeMax() != 1.0E9) {
        layoutItem13 = layout.addItem();
        layoutItem13.setLabel("DBG: Age Fresh", 0.0F, 1.0F, 0.0F, 1.0F);
        layoutItem13.setValueRightNoPlus(this.getOffAge() * 24.0F);
        layoutItem13 = layout.addItem();
        layoutItem13.setLabel("DBG: Age Rotten", 0.0F, 1.0F, 0.0F, 1.0F);
        layoutItem13.setValueRightNoPlus(this.getOffAgeMax() * 24);
      }

      layoutItem13 = layout.addItem();
      layoutItem13.setLabel("DBG: Heat", 0.0F, 1.0F, 0.0F, 1.0F);
      layoutItem13.setValueRightNoPlus(this.getHeat());
      layoutItem13 = layout.addItem();
      layoutItem13.setLabel("DBG: Freeze Time", 0.0F, 1.0F, 0.0F, 1.0F);
      layoutItem13.setValueRightNoPlus(this.getFreezingTime());
      layoutItem13 = layout.addItem();
      layoutItem13.setLabel("DBG: Compost Time", 0.0F, 1.0F, 0.0F, 1.0F);
      layoutItem13.setValueRightNoPlus(this.getCompostTime());
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

  void setEnduranceChange(float _endChange) { this.endChange = _endChange; }

  /**
   * @return the unhappyChange
   */
  float getUnhappyChange() {
    float float0 = this.unhappyChange;
    bool boolean0 =
        "Icecream".equals(this.getType()) || this.hasTag("GoodFrozen");
    if (this.isFrozen() && !boolean0) {
      float0 += 30.0F;
    }

    if (this.Burnt) {
      float0 += 20.0F;
    }

    if (this.Age >= this.OffAge && this.Age < this.OffAgeMax) {
      float0 += 10.0F;
    }

    if (this.Age >= this.OffAgeMax) {
      float0 += 20.0F;
    }

    if (this.isBadCold() && this.IsCookable && this.isCooked() &&
        this.Heat < 1.3F) {
      float0 += 2.0F;
    }

    if (this.isGoodHot() && this.IsCookable && this.isCooked() &&
        this.Heat > 1.3F) {
      float0 -= 2.0F;
    }

    return float0;
  }

  /**
   * @return the boredomChange
   */
  float getBoredomChange() {
    float float0 = this.boredomChange;
    bool boolean0 =
        "Icecream".equals(this.getType()) || this.hasTag("GoodFrozen");
    if (this.isFrozen() && !boolean0) {
      float0 += 30.0F;
    }

    if (this.Burnt) {
      float0 += 20.0F;
    }

    if (this.Age >= this.OffAge && this.Age < this.OffAgeMax) {
      float0 += 10.0F;
    }

    if (this.Age >= this.OffAgeMax) {
      float0 += 20.0F;
    }

    return float0;
  }

  float getHungerChange() {
    float float0 = this.hungChange;
    if (this.Burnt) {
      return float0 / 3.0F;
    } else if (this.Age >= this.OffAge && this.Age < this.OffAgeMax) {
      return float0 / 1.3F;
    } else if (this.Age >= this.OffAgeMax) {
      return float0 / 2.2F;
    } else {
      return this.isCooked() ? float0 * 1.3F : float0;
    }
  }

  /**
   * @return the stressChange
   */
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

  float getBoredomChangeUnmodified() { return this.boredomChange; }

  float getEnduranceChangeUnmodified() { return this.endChange; }

  float getStressChangeUnmodified() { return this.stressChange; }

  float getThirstChangeUnmodified() { return this.thirstChange; }

  float getUnhappyChangeUnmodified() { return this.unhappyChange; }

  float getScore(SurvivorDesc desc) {
    float float0 = 0.0F;
    return float0 - this.getHungerChange() * 100.0F;
  }

  bool isBadCold() { return this.bBadCold; }

  void setBadCold(bool _bBadCold) { this.bBadCold = _bBadCold; }

  bool isGoodHot() { return this.bGoodHot; }

  void setGoodHot(bool _bGoodHot) { this.bGoodHot = _bGoodHot; }

  bool isCookedInMicrowave() { return this.cookedInMicrowave; }

  void setCookedInMicrowave(bool b) { this.cookedInMicrowave = b; }

  float getHeat() { return this.Heat; }

  float getInvHeat() {
    return this.Heat > 1.0F ? (this.Heat - 1.0F) / 2.0F
                            : 1.0F - (this.Heat - 0.2F) / 0.8F;
  }

  void setHeat(float _Heat) { this.Heat = _Heat; }

  float getEndChange() { return this.endChange; }

  void setEndChange(float _endChange) { this.endChange = _endChange; }

  float getBaseHungChange() { return this.getHungChange(); }

  float getHungChange() { return this.hungChange; }

  void setHungChange(float _hungChange) { this.hungChange = _hungChange; }

  std::string getUseOnConsume() { return this.useOnConsume; }

  void setUseOnConsume(const std::string &_useOnConsume) {
    this.useOnConsume = _useOnConsume;
  }

  bool isRotten() { return this.Age >= this.OffAgeMax; }

  bool isFresh() { return this.Age < this.OffAge; }

  void setRotten(bool _rotten) { this.rotten = _rotten; }

  bool isbDangerousUncooked() { return this.bDangerousUncooked; }

  void setbDangerousUncooked(bool _bDangerousUncooked) {
    this.bDangerousUncooked = _bDangerousUncooked;
  }

  int getLastCookMinute() { return this.LastCookMinute; }

  void setLastCookMinute(int _LastCookMinute) {
    this.LastCookMinute = _LastCookMinute;
  }

  float getThirstChange() {
    float float0 = this.thirstChange;
    if (this.Burnt) {
      return float0 / 5.0F;
    } else {
      return this.isCooked() ? float0 / 2.0F : float0;
    }
  }

  void setThirstChange(float _thirstChange) {
    this.thirstChange = _thirstChange;
  }

  void setReplaceOnCooked(List<String> replaceOnCooked) {
    this.ReplaceOnCooked = replaceOnCooked;
  }

public
  List<String> getReplaceOnCooked() { return this.ReplaceOnCooked; }

  float getBaseHunger() { return this.baseHunger; }

  void setBaseHunger(float _baseHunger) { this.baseHunger = _baseHunger; }

  bool isSpice() { return this.isSpice; }

  void setSpice(bool _isSpice) { this.isSpice = _isSpice; }

  bool isPoison() { return this.Poison; }

  int getPoisonDetectionLevel() { return this.poisonDetectionLevel; }

  void setPoisonDetectionLevel(int _poisonDetectionLevel) {
    this.poisonDetectionLevel = _poisonDetectionLevel;
  }

  int getPoisonLevelForRecipe() { return this.PoisonLevelForRecipe; }

  void setPoisonLevelForRecipe(int poisonLevelForRecipe) {
    this.PoisonLevelForRecipe = poisonLevelForRecipe;
  }

  int getUseForPoison() { return this.UseForPoison; }

  void setUseForPoison(int useForPoison) { this.UseForPoison = useForPoison; }

  int getPoisonPower() { return this.PoisonPower; }

  void setPoisonPower(int poisonPower) { this.PoisonPower = poisonPower; }

  std::string getFoodType() { return this.FoodType; }

  void setFoodType(const std::string &foodType) { this.FoodType = foodType; }

  bool isRemoveNegativeEffectOnCooked() {
    return this.RemoveNegativeEffectOnCooked;
  }

  void setRemoveNegativeEffectOnCooked(bool removeNegativeEffectOnCooked) {
    this.RemoveNegativeEffectOnCooked = removeNegativeEffectOnCooked;
  }

  std::string getCookingSound() {
    return this.getScriptItem().getCookingSound();
  }

  std::string getCustomEatSound() { return this.CustomEatSound; }

  void setCustomEatSound(const std::string &customEatSound) {
    this.CustomEatSound = customEatSound;
  }

  std::string getChef() { return this.Chef; }

  void setChef(const std::string &chef) { this.Chef = chef; }

  std::string getOnCooked() { return this.OnCooked; }

  void setOnCooked(const std::string &onCooked) { this.OnCooked = onCooked; }

  std::string getHerbalistType() { return this.HerbalistType; }

  void setHerbalistType(const std::string &type) { this.HerbalistType = type; }

public
  ArrayList<String> getSpices() { return this.spices; }

  void setSpices(ArrayList<String> _spices) {
    if (_spices != nullptr && !_spices.isEmpty()) {
      if (this.spices == nullptr) {
        this.spices = new ArrayList<>(_spices);
      } else {
        this.spices.clear();
        this.spices.addAll(_spices);
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

  /**
   * @return the WorldTexture
   */
  std::string getWorldTexture() {
    if (this.Burnt) {
      return this.WorldTextureOverdone;
    } else if (this.Age >= this.OffAgeMax) {
      return this.WorldTextureRotten;
    } else {
      return this.isCooked() ? this.WorldTextureCooked : this.WorldTexture;
    }
  }

  int getReduceFoodSickness() { return this.ReduceFoodSickness; }

  void setReduceFoodSickness(int _ReduceFoodSickness) {
    this.ReduceFoodSickness = _ReduceFoodSickness;
  }

  int getFluReduction() { return this.fluReduction; }

  void setFluReduction(int _fluReduction) { this.fluReduction = _fluReduction; }

  float getPainReduction() { return this.painReduction; }

  void setPainReduction(float _painReduction) {
    this.painReduction = _painReduction;
  }

  float getCarbohydrates() { return this.carbohydrates; }

  void setCarbohydrates(float _carbohydrates) {
    this.carbohydrates = _carbohydrates;
  }

  float getLipids() { return this.lipids; }

  void setLipids(float _lipids) { this.lipids = _lipids; }

  float getProteins() { return this.proteins; }

  void setProteins(float _proteins) { this.proteins = _proteins; }

  float getCalories() { return this.calories; }

  void setCalories(float _calories) { this.calories = _calories; }

  bool isPackaged() { return this.packaged; }

  void setPackaged(bool _packaged) { this.packaged = _packaged; }

  float getFreezingTime() { return this.freezingTime; }

  void setFreezingTime(float _freezingTime) {
    if (_freezingTime >= 100.0F) {
      this.setFrozen(true);
      _freezingTime = 100.0F;
    } else if (_freezingTime <= 0.0F) {
      _freezingTime = 0.0F;
      this.setFrozen(false);
    }

    this.freezingTime = _freezingTime;
  }

  void freeze() { this.setFreezingTime(100.0F); }

  bool isFrozen() { return this.frozen; }

  void setFrozen(bool _frozen) { this.frozen = _frozen; }

  bool canBeFrozen() { return this.canBeFrozen; }

  void setCanBeFrozen(bool _canBeFrozen) { this.canBeFrozen = _canBeFrozen; }

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

  std::string getReplaceOnRotten() { return this.replaceOnRotten; }

  void setReplaceOnRotten(const std::string &_replaceOnRotten) {
    this.replaceOnRotten = _replaceOnRotten;
  }

  void multiplyFoodValues(float percentage) {
    this.setBoredomChange(this.getBoredomChangeUnmodified() * percentage);
    this.setUnhappyChange(this.getUnhappyChangeUnmodified() * percentage);
    this.setHungChange(this.getHungChange() * percentage);
    this.setFluReduction((int)(this.getFluReduction() * percentage));
    this.setThirstChange(this.getThirstChangeUnmodified() * percentage);
    this.setPainReduction(this.getPainReduction() * percentage);
    this.setReduceFoodSickness(
        (int)(this.getReduceFoodSickness() * percentage));
    this.setEndChange(this.getEnduranceChangeUnmodified() * percentage);
    this.setStressChange(this.getStressChangeUnmodified() * percentage);
    this.setFatigueChange(this.getFatigueChange() * percentage);
    this.setCalories(this.getCalories() * percentage);
    this.setCarbohydrates(this.getCarbohydrates() * percentage);
    this.setProteins(this.getProteins() * percentage);
    this.setLipids(this.getLipids() * percentage);
  }

  float getRottenTime() { return this.rottenTime; }

  void setRottenTime(float time) { this.rottenTime = time; }

  float getCompostTime() { return this.compostTime; }

  void setCompostTime(float _compostTime) { this.compostTime = _compostTime; }

  std::string getOnEat() { return this.onEat; }

  void setOnEat(const std::string &_onEat) { this.onEat = _onEat; }

  bool isBadInMicrowave() { return this.badInMicrowave; }

  void setBadInMicrowave(bool _badInMicrowave) {
    this.badInMicrowave = _badInMicrowave;
  }

  void destroyThisItem() {
    IsoWorldInventoryObject worldInventoryObject = this.getWorldItem();
    if (worldInventoryObject != nullptr &&
        worldInventoryObject.getSquare() != nullptr) {
      if (GameServer.bServer) {
        GameServer.RemoveItemFromMap(worldInventoryObject);
      } else {
        worldInventoryObject.removeFromWorld();
        worldInventoryObject.removeFromSquare();
      }

      this.setWorldItem(nullptr);
    } else if (this.container != nullptr) {
      IsoObject object = this.container.getParent();
      if (GameServer.bServer) {
        if (!this.isInPlayerInventory()) {
          GameServer.sendRemoveItemFromContainer(this.container, this);
        }

        this.container.Remove(this);
      } else {
        this.container.Remove(this);
      }

      IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this);
      LuaManager.updateOverlaySprite(object);
    }

    if (!GameServer.bServer) {
      LuaEventManager.triggerEvent("OnContainerUpdate");
    }
  }
}
} // namespace types
} // namespace inventory
} // namespace zombie
