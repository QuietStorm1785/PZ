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
#include "zombie/SandboxOptions.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characterTextures/BloodClothingType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/WornItems/WornItem.h"
#include "zombie/characters/WornItems/WornItems.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/Translator.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/Clothing/1.h"
#include "zombie/inventory/types/Clothing/ClothingPatch.h"
#include "zombie/inventory/types/Clothing/ClothingPatchFabricType.h"
#include "zombie/inventory/types/Clothing/WetDryState.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoClothingDryer.h"
#include "zombie/iso/objects/IsoClothingWasher.h"
#include "zombie/iso/objects/IsoCombinationWasherDryer.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameClient.h"
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
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehiclePart.h"
#include "zombie/vehicles/VehicleWindow.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {
namespace types {


class Clothing : public InventoryItem {
public:
    float temperature;
    float insulation = 0.0F;
    float windresistance = 0.0F;
    float waterResistance = 0.0F;
   std::unordered_map<int, ClothingPatch> patches;
    std::string SpriteName = nullptr;
    std::string palette;
    float bloodLevel = 0.0F;
    float dirtyness = 0.0F;
    float wetness = 0.0F;
    float WeightWet = 0.0F;
    float lastWetnessUpdate = -1.0F;
    const std::string dirtyString = Translator.getText("IGUI_ClothingName_Dirty");
    const std::string bloodyString = Translator.getText("IGUI_ClothingName_Bloody");
    const std::string wetString = Translator.getText("IGUI_ClothingName_Wet");
    const std::string soakedString = Translator.getText("IGUI_ClothingName_Soaked");
    const std::string wornString = Translator.getText("IGUI_ClothingName_Worn");
    int ConditionLowerChance = 10000;
    float stompPower = 1.0F;
    float runSpeedModifier = 1.0F;
    float combatSpeedModifier = 1.0F;
    bool removeOnBroken = false;
    bool canHaveHoles = true;
    float biteDefense = 0.0F;
    float scratchDefense = 0.0F;
    float bulletDefense = 0.0F;
    static const int CONDITION_PER_HOLES = 3;
    float neckProtectionModifier = 1.0F;
    int chanceToFall = 0;

    std::string getCategory() {
      return this.mainCategory != nullptr ? this.mainCategory : "Clothing";
   }

    public Clothing(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4, const std::string& var5, const std::string& var6) {
      super(var1, var2, var3, var4);
      this.SpriteName = var6;
      this.col = std::make_shared<Color>(Rand.Next(255), Rand.Next(255), Rand.Next(255));
      this.palette = var5;
   }

    public Clothing(const std::string& var1, const std::string& var2, const std::string& var3, Item var4, const std::string& var5, const std::string& var6) {
      super(var1, var2, var3, var4);
      this.SpriteName = var6;
      this.col = std::make_shared<Color>(Rand.Next(255), Rand.Next(255), Rand.Next(255));
      this.palette = var5;
   }

    bool IsClothing() {
    return true;
   }

    int getSaveType() {
      return Type.Clothing.ordinal();
   }

    void Unwear() {
      if (this.container != nullptr && this.container.dynamic_cast<IsoGameCharacter*>(parent) != nullptr var1) {
         var1.removeWornItem(this);
         if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
            LuaEventManager.triggerEvent("OnClothingUpdated", var1);
         }

         IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this);
      }
   }

    void DoTooltip(ObjectTooltip var1, Layout var2) {
    float var4 = 1.0F;
    float var5 = 1.0F;
    float var6 = 0.8F;
    float var7 = 1.0F;
    float var8 = 0.0F;
    float var9 = 0.6F;
    float var10 = 0.0F;
    float var11 = 0.7F;
      if (!this.isCosmetic()) {
    LayoutItem var3 = var2.addItem();
         var3.setLabel(Translator.getText("Tooltip_weapon_Condition") + ":", var4, var5, var6, var7);
    float var12 = (float)this.Condition / this.ConditionMax;
         var3.setProgress(var12, var8, var9, var10, var11);
         var3 = var2.addItem();
         var3.setLabel(Translator.getText("Tooltip_item_Insulation") + ": ", 1.0F, 1.0F, 0.8F, 1.0F);
         var12 = this.getInsulation();
         if (var12 > 0.8F) {
            var3.setProgress(var12, 0.0F, 0.6F, 0.0F, 0.7F);
         } else if (var12 > 0.6F) {
            var3.setProgress(var12, 0.3F, 0.6F, 0.0F, 0.7F);
         } else if (var12 > 0.4F) {
            var3.setProgress(var12, 0.6F, 0.6F, 0.0F, 0.7F);
         } else if (var12 > 0.2F) {
            var3.setProgress(var12, 0.6F, 0.3F, 0.0F, 0.7F);
         } else {
            var3.setProgress(var12, 0.6F, 0.0F, 0.0F, 0.7F);
         }

         var12 = this.getWindresistance();
         if (var12 > 0.0F) {
            var3 = var2.addItem();
            var3.setLabel(Translator.getText("Tooltip_item_Windresist") + ": ", 1.0F, 1.0F, 0.8F, 1.0F);
            if (var12 > 0.8F) {
               var3.setProgress(var12, 0.0F, 0.6F, 0.0F, 0.7F);
            } else if (var12 > 0.6F) {
               var3.setProgress(var12, 0.3F, 0.6F, 0.0F, 0.7F);
            } else if (var12 > 0.4F) {
               var3.setProgress(var12, 0.6F, 0.6F, 0.0F, 0.7F);
            } else if (var12 > 0.2F) {
               var3.setProgress(var12, 0.6F, 0.3F, 0.0F, 0.7F);
            } else {
               var3.setProgress(var12, 0.6F, 0.0F, 0.0F, 0.7F);
            }
         }

         var12 = this.getWaterResistance();
         if (var12 > 0.0F) {
            var3 = var2.addItem();
            var3.setLabel(Translator.getText("Tooltip_item_Waterresist") + ": ", 1.0F, 1.0F, 0.8F, 1.0F);
            if (var12 > 0.8F) {
               var3.setProgress(var12, 0.0F, 0.6F, 0.0F, 0.7F);
            } else if (var12 > 0.6F) {
               var3.setProgress(var12, 0.3F, 0.6F, 0.0F, 0.7F);
            } else if (var12 > 0.4F) {
               var3.setProgress(var12, 0.6F, 0.6F, 0.0F, 0.7F);
            } else if (var12 > 0.2F) {
               var3.setProgress(var12, 0.6F, 0.3F, 0.0F, 0.7F);
            } else {
               var3.setProgress(var12, 0.6F, 0.0F, 0.0F, 0.7F);
            }
         }
      }

      if (this.bloodLevel != 0.0F) {
    LayoutItem var25 = var2.addItem();
         var25.setLabel(Translator.getText("Tooltip_clothing_bloody") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
    float var46 = this.bloodLevel / 100.0F;
         var25.setProgress(var46, var8, var9, var10, var11);
      }

      if (this.dirtyness >= 1.0F) {
    LayoutItem var26 = var2.addItem();
         var26.setLabel(Translator.getText("Tooltip_clothing_dirty") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
    float var47 = this.dirtyness / 100.0F;
         var26.setProgress(var47, var8, var9, var10, var11);
      }

      if (this.wetness != 0.0F) {
    LayoutItem var27 = var2.addItem();
         var27.setLabel(Translator.getText("Tooltip_clothing_wet") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
    float var48 = this.wetness / 100.0F;
         var27.setProgress(var48, var8, var9, var10, var11);
      }

    int var13 = 0;
    ItemVisual var14 = this.getVisual();

      for (int var15 = 0; var15 < BloodBodyPartType.MAX.index(); var15++) {
         if (var14.getHole(BloodBodyPartType.FromIndex(var15)) > 0.0F) {
            var13++;
         }
      }

      if (var13 > 0) {
    LayoutItem var28 = var2.addItem();
         var28.setLabel(Translator.getText("Tooltip_clothing_holes") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var28.setValueRightNoPlus(var13);
      }

      if (!this.isEquipped() && var1.getCharacter() != nullptr) {
    float var49 = 0.0F;
    float var16 = 0.0F;
    float var17 = 0.0F;
    WornItems var18 = var1.getCharacter().getWornItems();

         for (int var19 = 0; var19 < var18.size(); var19++) {
    WornItem var20 = var18.get(var19);
            if (this.getBodyLocation() == var20.getLocation()) || var18.getBodyLocationGroup().isExclusive(this.getBodyLocation(), var20.getLocation())) {
               var49 += ((Clothing)var20.getItem()).getBiteDefense();
               var16 += ((Clothing)var20.getItem()).getScratchDefense();
               var17 += ((Clothing)var20.getItem()).getBulletDefense();
            }
         }

    float var53 = this.getBiteDefense();
         if (var53 != var49) {
    LayoutItem var33 = var2.addItem();
            if (var53 > 0.0F || var49 > 0.0F) {
               var33.setLabel(Translator.getText("Tooltip_BiteDefense") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
               if (var53 > var49) {
                  var33.setValue((int)var53 + " (+" + (int)(var53 - var49) + ")", 0.0F, 1.0F, 0.0F, 1.0F);
               } else {
                  var33.setValue((int)var53 + " (-" + (int)(var49 - var53) + ")", 1.0F, 0.0F, 0.0F, 1.0F);
               }
            }
         } else if (this.getBiteDefense() != 0.0F) {
    LayoutItem var32 = var2.addItem();
            var32.setLabel(Translator.getText("Tooltip_BiteDefense") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
            var32.setValueRightNoPlus((int)this.getBiteDefense());
         }

    float var54 = this.getScratchDefense();
         if (var54 != var16) {
    LayoutItem var35 = var2.addItem();
            if (var54 > 0.0F || var16 > 0.0F) {
               var35.setLabel(Translator.getText("Tooltip_ScratchDefense") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
               if (var54 > var16) {
                  var35.setValue((int)var54 + " (+" + (int)(var54 - var16) + ")", 0.0F, 1.0F, 0.0F, 1.0F);
               } else {
                  var35.setValue((int)var54 + " (-" + (int)(var16 - var54) + ")", 1.0F, 0.0F, 0.0F, 1.0F);
               }
            }
         } else if (this.getScratchDefense() != 0.0F) {
    LayoutItem var34 = var2.addItem();
            var34.setLabel(Translator.getText("Tooltip_ScratchDefense") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
            var34.setValueRightNoPlus((int)this.getScratchDefense());
         }

    float var21 = this.getBulletDefense();
         if (var21 != var17) {
    LayoutItem var36 = var2.addItem();
            if (var21 > 0.0F || var17 > 0.0F) {
               var36.setLabel(Translator.getText("Tooltip_BulletDefense") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
               if (var21 > var17) {
                  var36.setValue((int)var21 + " (+" + (int)(var21 - var17) + ")", 0.0F, 1.0F, 0.0F, 1.0F);
               } else {
                  var36.setValue((int)var21 + " (-" + (int)(var17 - var21) + ")", 1.0F, 0.0F, 0.0F, 1.0F);
               }
            }
         } else if (this.getBulletDefense() != 0.0F) {
    LayoutItem var37 = var2.addItem();
            var37.setLabel(Translator.getText("Tooltip_BulletDefense") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
            var37.setValueRightNoPlus((int)this.getBulletDefense());
         }
      } else {
         if (this.getBiteDefense() != 0.0F) {
    LayoutItem var29 = var2.addItem();
            var29.setLabel(Translator.getText("Tooltip_BiteDefense") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
            var29.setValueRightNoPlus((int)this.getBiteDefense());
         }

         if (this.getScratchDefense() != 0.0F) {
    LayoutItem var30 = var2.addItem();
            var30.setLabel(Translator.getText("Tooltip_ScratchDefense") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
            var30.setValueRightNoPlus((int)this.getScratchDefense());
         }

         if (this.getBulletDefense() != 0.0F) {
    LayoutItem var31 = var2.addItem();
            var31.setLabel(Translator.getText("Tooltip_BulletDefense") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
            var31.setValueRightNoPlus((int)this.getBulletDefense());
         }
      }

      if (this.getRunSpeedModifier() != 1.0F) {
    LayoutItem var38 = var2.addItem();
         var38.setLabel(Translator.getText("Tooltip_RunSpeedModifier") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var38.setValueRightNoPlus(this.getRunSpeedModifier());
      }

      if (this.getCombatSpeedModifier() != 1.0F) {
    LayoutItem var39 = var2.addItem();
         var39.setLabel(Translator.getText("Tooltip_CombatSpeedModifier") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var39.setValueRightNoPlus(this.getCombatSpeedModifier());
      }

      if (Core.bDebug && DebugOptions.instance.TooltipInfo.getValue()) {
         if (this.bloodLevel != 0.0F) {
    LayoutItem var40 = var2.addItem();
            var40.setLabel("DBG: bloodLevel:", 1.0F, 1.0F, 0.8F, 1.0F);
    int var50 = (int)Math.ceil(this.bloodLevel);
            var40.setValueRight(var50, false);
         }

         if (this.dirtyness != 0.0F) {
    LayoutItem var41 = var2.addItem();
            var41.setLabel("DBG: dirtyness:", 1.0F, 1.0F, 0.8F, 1.0F);
    int var51 = (int)Math.ceil(this.dirtyness);
            var41.setValueRight(var51, false);
         }

         if (this.wetness != 0.0F) {
    LayoutItem var42 = var2.addItem();
            var42.setLabel("DBG: wetness:", 1.0F, 1.0F, 0.8F, 1.0F);
    int var52 = (int)Math.ceil(this.wetness);
            var42.setValueRight(var52, false);
         }
      }
   }

    bool isDirty() {
      return this.dirtyness > 15.0F;
   }

    bool isBloody() {
      return this.bloodLevel > 25.0F;
   }

    std::string getName() {
    std::string var1 = "";
      if (this.isDirty()) {
         var1 = var1 + this.dirtyString + ", ";
      }

      if (this.isBloody()) {
         var1 = var1 + this.bloodyString + ", ";
      }

      if (this.getWetness() >= 100.0F) {
         var1 = var1 + this.soakedString + ", ";
      } else if (this.getWetness() > 25.0F) {
         var1 = var1 + this.wetString + ", ";
      }

      if (this.getCondition() < this.getConditionMax() / 3) {
         var1 = var1 + this.wornString + ", ";
      }

      if (var1.length() > 2) {
         var1 = var1.substr(0, var1.length() - 2);
      }

      var1 = var1.trim();
      return var1.empty() ? this.name : Translator.getText("IGUI_ClothingNaming", var1, this.name);
   }

    void update() {
      if (this.container == nullptr || SandboxOptions.instance.ClothingDegradation.getValue() == 1) {
         ;
      }
   }

    void updateWetness() {
      this.updateWetness(false);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void updateWetness(bool var1) {
      if (var1 || !this.isEquipped()) {
         if (this.getBloodClothingType() == nullptr) {
            this.setWetness(0.0F);
         } else {
    float var2 = (float)GameTime.getInstance().getWorldAgeHours();
            if (this.lastWetnessUpdate < 0.0F) {
               this.lastWetnessUpdate = var2;
            } else if (this.lastWetnessUpdate > var2) {
               this.lastWetnessUpdate = var2;
            }

    float var3 = var2 - this.lastWetnessUpdate;
            if (!(var3 < 0.016666668F)) {
               this.lastWetnessUpdate = var2;
               switch (1.$SwitchMap$zombie$inventory$types$Clothing$WetDryState[this.getWetDryState().ordinal()]) {
                  case 1:
                  default:
                     break;
                  case 2:
                     if (this.getWetness() > 0.0F) {
    float var6 = var3 * 20.0F;
                        if (this.isEquipped()) {
                           var6 *= 2.0F;
                        }

                        this.setWetness(this.getWetness() - var6);
                     }
                     break;
                  case 3:
                     if (this.getWetness() < 100.0F) {
    float var4 = ClimateManager.getInstance().getRainIntensity();
                        if (var4 < 0.1F) {
                           var4 = 0.0F;
                        }

    float var5 = var4 * var3 * 100.0F;
                        this.setWetness(this.getWetness() + var5);
                     }
               }
            }
         }
      }
   }

    float getBulletDefense() {
      return this.bulletDefense;
   }

    void setBulletDefense(float var1) {
      this.bulletDefense = var1;
   }

    WetDryState getWetDryState() {
      if (this.getWorldItem() == nullptr) {
         if (this.container == nullptr) {
            return WetDryState.Invalid;
         } else if (this.container.dynamic_cast<IsoDeadBody*>(parent) != nullptr var6) {
            if (var6.getSquare() == nullptr) {
               return WetDryState.Invalid;
            } else if (var6.getSquare().isInARoom()) {
               return WetDryState.Dryer;
            } else {
               return ClimateManager.getInstance().isRaining() ? WetDryState.Wetter : WetDryState.Dryer;
            }
         } else if (this.container.dynamic_cast<IsoGameCharacter*>(parent) != nullptr var5) {
            if (var5.getCurrentSquare() == nullptr) {
               return WetDryState.Invalid;
            } else if (var5.getCurrentSquare().isInARoom() || var5.getCurrentSquare().haveRoof) {
               return WetDryState.Dryer;
            } else if (!ClimateManager.getInstance().isRaining()) {
               return WetDryState.Dryer;
            } else if (!this.isEquipped()) {
               return WetDryState.Dryer;
            } else if (var5.isAsleep() && var5.getBed() != nullptr && "Tent" == var5.getBed().getName())) {
               return WetDryState.Dryer;
            } else {
    BaseVehicle var2 = var5.getVehicle();
               if (var2 != nullptr && var2.hasRoof(var2.getSeat(var5))) {
    VehiclePart var3 = var2.getPartById("Windshield");
                  if (var3 != nullptr) {
    VehicleWindow var4 = var3.getWindow();
                     if (var4 != nullptr && var4.isHittable()) {
                        return WetDryState.Dryer;
                     }
                  }
               }

               return WetDryState.Wetter;
            }
         } else if (this.container.parent == nullptr) {
            return WetDryState.Dryer;
         } else if (this.container.dynamic_cast<IsoClothingDryer*>(parent) != nullptr && ((IsoClothingDryer)this.container.parent).isActivated()) {
            return WetDryState.Invalid;
         } else if (this.container.dynamic_cast<IsoClothingWasher*>(parent) != nullptr && ((IsoClothingWasher)this.container.parent).isActivated()) {
            return WetDryState.Invalid;
         } else {
    IsoCombinationWasherDryer var1 = (IsoCombinationWasherDryer)zombie.util.Type.tryCastTo(this.container.parent, IsoCombinationWasherDryer.class);
            return var1 != nullptr && var1.isActivated() ? WetDryState.Invalid : WetDryState.Dryer;
         }
      } else if (this.getWorldItem().getSquare() == nullptr) {
         return WetDryState.Invalid;
      } else if (this.getWorldItem().getSquare().isInARoom()) {
         return WetDryState.Dryer;
      } else {
         return ClimateManager.getInstance().isRaining() ? WetDryState.Wetter : WetDryState.Dryer;
      }
   }

    void flushWetness() {
      if (!(this.lastWetnessUpdate < 0.0F)) {
         this.updateWetness(true);
         this.lastWetnessUpdate = -1.0F;
      }
   }

    bool finishupdate() {
      return this.container != nullptr && this.container.dynamic_cast<IsoGameCharacter*>(parent) != nullptr ? !this.isEquipped() : true;
   }

    void Use(bool var1, bool var2) {
      if (this.uses <= 1) {
         this.Unwear();
      }

      super.Use(var1, var2);
   }

    bool CanStack(InventoryItem var1) {
      return this.ModDataMatches(var1) && this.palette == nullptr && ((Clothing)var1).palette == nullptr || this.palette == ((Clothing)var1).palette);
   }

    static Clothing CreateFromSprite(const std::string& var0) {
      try {
    void* var1 = nullptr;
         return (Clothing)InventoryItemFactory.CreateItem(var0, 1.0F);
      } catch (Exception var2) {
    return nullptr;
      }
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
    BitHeaderWrite var3 = BitHeader.allocWrite(HeaderSize.uint8_t, var1);
      if (this.getSpriteName() != nullptr) {
         var3.addFlags(1);
         GameWindow.WriteString(var1, this.getSpriteName());
      }

      if (this.dirtyness != 0.0F) {
         var3.addFlags(2);
         var1.putFloat(this.dirtyness);
      }

      if (this.bloodLevel != 0.0F) {
         var3.addFlags(4);
         var1.putFloat(this.bloodLevel);
      }

      if (this.wetness != 0.0F) {
         var3.addFlags(8);
         var1.putFloat(this.wetness);
      }

      if (this.lastWetnessUpdate != 0.0F) {
         var3.addFlags(16);
         var1.putFloat(this.lastWetnessUpdate);
      }

      if (this.patches != nullptr) {
         var3.addFlags(32);
         var1.put((byte)this.patches.size());

         for (int var5 : this.patches.keySet()) {
            var1.put((byte)var5);
            this.patches.get(var5).save(var1, false);
         }
      }

      var3.write();
      var3.release();
   }

    void load(ByteBuffer var1, int var2) {
      super.load(var1, var2);
    BitHeaderRead var3 = BitHeader.allocRead(HeaderSize.uint8_t, var1);
      if (!var3 == 0)) {
         if (var3.hasFlags(1)) {
            this.setSpriteName(GameWindow.ReadString(var1));
         }

         if (var3.hasFlags(2)) {
            this.dirtyness = var1.getFloat();
         }

         if (var3.hasFlags(4)) {
            this.bloodLevel = var1.getFloat();
         }

         if (var3.hasFlags(8)) {
            this.wetness = var1.getFloat();
         }

         if (var3.hasFlags(16)) {
            this.lastWetnessUpdate = var1.getFloat();
         }

         if (var3.hasFlags(32)) {
    uint8_t var4 = var1.get();

            for (int var5 = 0; var5 < var4; var5++) {
    uint8_t var6 = var1.get();
    ClothingPatch var7 = std::make_shared<ClothingPatch>(this);
               var7.load(var1, var2);
               if (this.patches == nullptr) {
                  this.patches = std::make_unique<std::unordered_map<>>();
               }

               this.patches.put(int.valueOf(var6), var7);
            }
         }
      }

      var3.release();
      this.synchWithVisual();
   }

    std::string getSpriteName() {
      return this.SpriteName;
   }

    void setSpriteName(const std::string& var1) {
      this.SpriteName = var1;
   }

    std::string getPalette() {
      return this.palette == nullptr ? "Trousers_White" : this.palette;
   }

    void setPalette(const std::string& var1) {
      this.palette = var1;
   }

    float getTemperature() {
      return this.temperature;
   }

    void setTemperature(float var1) {
      this.temperature = var1;
   }

    void setDirtyness(float var1) {
      this.dirtyness = PZMath.clamp(var1, 0.0F, 100.0F);
   }

    void setBloodLevel(float var1) {
      this.bloodLevel = PZMath.clamp(var1, 0.0F, 100.0F);
   }

    float getDirtyness() {
      return this.dirtyness;
   }

    float getBloodlevel() {
      return this.bloodLevel;
   }

    float getBloodlevelForPart(BloodBodyPartType var1) {
      return this.getVisual().getBlood(var1);
   }

    float getBloodLevel() {
      return this.bloodLevel;
   }

    float getBloodLevelForPart(BloodBodyPartType var1) {
      return this.getVisual().getBlood(var1);
   }

    float getWeight() {
    float var1 = this.getActualWeight();
    float var2 = this.getWeightWet();
      if (var2 <= 0.0F) {
         var2 = var1 * 1.25F;
      }

      return PZMath.lerp(var1, var2, this.getWetness() / 100.0F);
   }

    void setWetness(float var1) {
      this.wetness = PZMath.clamp(var1, 0.0F, 100.0F);
   }

    float getWetness() {
      return this.wetness;
   }

    float getWeightWet() {
      return this.WeightWet;
   }

    void setWeightWet(float var1) {
      this.WeightWet = var1;
   }

    int getConditionLowerChance() {
      return this.ConditionLowerChance;
   }

    void setConditionLowerChance(int var1) {
      this.ConditionLowerChance = var1;
   }

    void setCondition(int var1) {
      this.setCondition(var1, true);
      if (var1 <= 0) {
         this.Unwear();
         if (this.getContainer() != nullptr) {
            this.getContainer().setDrawDirty(true);
         }

         if (this.isRemoveOnBroken() && this.getContainer() != nullptr) {
            this.container.Remove(this);
         }
      }
   }

    float getClothingDirtynessIncreaseLevel() {
      if (SandboxOptions.instance.ClothingDegradation.getValue() == 2) {
         return 2.5E-4F;
      } else {
         return SandboxOptions.instance.ClothingDegradation.getValue() == 4 ? 0.025F : 0.0025F;
      }
   }

    float getInsulation() {
      return this.insulation;
   }

    void setInsulation(float var1) {
      this.insulation = var1;
   }

    float getStompPower() {
      return this.stompPower;
   }

    void setStompPower(float var1) {
      this.stompPower = var1;
   }

    float getRunSpeedModifier() {
      return this.runSpeedModifier;
   }

    void setRunSpeedModifier(float var1) {
      this.runSpeedModifier = var1;
   }

    float getCombatSpeedModifier() {
      return this.combatSpeedModifier;
   }

    void setCombatSpeedModifier(float var1) {
      this.combatSpeedModifier = var1;
   }

    bool isRemoveOnBroken() {
      return this.removeOnBroken;
   }

    void setRemoveOnBroken(bool var1) {
      this.removeOnBroken = var1;
   }

    bool getCanHaveHoles() {
      return this.canHaveHoles;
   }

    void setCanHaveHoles(bool var1) {
      this.canHaveHoles = var1;
   }

    bool isCosmetic() {
      return this.getScriptItem().isCosmetic();
   }

    std::string toString() {
      return this.getClass().getSimpleName() + "{ clothingItemName=\"" + this.getClothingItemName() + "\" }";
   }

    float getBiteDefense() {
      return this.getCondition() <= 0 ? 0.0F : this.biteDefense;
   }

    void setBiteDefense(float var1) {
      this.biteDefense = var1;
   }

    float getScratchDefense() {
      return this.getCondition() <= 0 ? 0.0F : this.scratchDefense;
   }

    void setScratchDefense(float var1) {
      this.scratchDefense = var1;
   }

    float getNeckProtectionModifier() {
      return this.neckProtectionModifier;
   }

    void setNeckProtectionModifier(float var1) {
      this.neckProtectionModifier = var1;
   }

    int getChanceToFall() {
      return this.chanceToFall;
   }

    void setChanceToFall(int var1) {
      this.chanceToFall = var1;
   }

    float getWindresistance() {
      return this.windresistance;
   }

    void setWindresistance(float var1) {
      this.windresistance = var1;
   }

    float getWaterResistance() {
      return this.waterResistance;
   }

    void setWaterResistance(float var1) {
      this.waterResistance = var1;
   }

    int getHolesNumber() {
      return this.getVisual() != nullptr ? this.getVisual().getHolesNumber() : 0;
   }

    int getPatchesNumber() {
      return this.patches.size();
   }

    float getDefForPart(BloodBodyPartType var1, bool var2, bool var3) {
      if (this.getVisual().getHole(var1) > 0.0F) {
         return 0.0F;
      } else {
    ClothingPatch var4 = this.getPatchType(var1);
    float var5 = this.getScratchDefense();
         if (var2) {
            var5 = this.getBiteDefense();
         }

         if (var3) {
            var5 = this.getBulletDefense();
         }

         if (var1 == BloodBodyPartType.Neck && this.getScriptItem().neckProtectionModifier < 1.0F) {
            var5 *= this.getScriptItem().neckProtectionModifier;
         }

         if (var4 != nullptr) {
    int var6 = var4.scratchDefense;
            if (var2) {
               var6 = var4.biteDefense;
            }

            if (var3) {
               var6 = var4.biteDefense;
            }

            if (!var4.hasHole) {
               var5 += var6;
            } else {
               var5 = var6;
            }
         }

    return var5;
      }
   }

    static int getBiteDefenseFromItem(IsoGameCharacter var0, InventoryItem var1) {
    int var2 = Math.max(1, var0.getPerkLevel(Perks.Tailoring));
    ClothingPatchFabricType var3 = ClothingPatchFabricType.fromType(var1.getFabricType());
      return var3.maxBiteDef > 0 ? (int)Math.max(1.0F, var3.maxBiteDef * (var2 / 10.0F)) : 0;
   }

    static int getScratchDefenseFromItem(IsoGameCharacter var0, InventoryItem var1) {
    int var2 = Math.max(1, var0.getPerkLevel(Perks.Tailoring));
    ClothingPatchFabricType var3 = ClothingPatchFabricType.fromType(var1.getFabricType());
      return (int)Math.max(1.0F, var3.maxScratchDef * (var2 / 10.0F));
   }

    ClothingPatch getPatchType(BloodBodyPartType var1) {
      return this.patches != nullptr ? this.patches.get(var1.index()) : nullptr;
   }

    void removePatch(BloodBodyPartType var1) {
      if (this.patches != nullptr) {
         this.getVisual().removePatch(var1.index());
    ClothingPatch var2 = this.patches.get(var1.index());
         if (var2 != nullptr && var2.hasHole) {
            this.getVisual().setHole(var1);
            this.setCondition(this.getCondition() - var2.conditionGain);
         }

         this.patches.remove(var1.index());
         if (GameClient.bClient && this.getContainer() != nullptr && this.getContainer().getParent() instanceof IsoPlayer) {
            GameClient.instance.sendClothing((IsoPlayer)this.getContainer().getParent(), "", nullptr);
         }
      }
   }

    bool canFullyRestore(IsoGameCharacter var1, BloodBodyPartType var2, InventoryItem var3) {
      return var1.getPerkLevel(Perks.Tailoring) > 7 && var3.getFabricType() == this.getFabricType()) && this.getVisual().getHole(var2) > 0.0F;
   }

    void addPatch(IsoGameCharacter var1, BloodBodyPartType var2, InventoryItem var3) {
    ClothingPatchFabricType var4 = ClothingPatchFabricType.fromType(var3.getFabricType());
      if (this.canFullyRestore(var1, var2, var3)) {
         this.getVisual().removeHole(var2.index());
         this.setCondition(this.getCondition() + this.getCondLossPerHole());
      } else {
         if (var4 == ClothingPatchFabricType.Cotton) {
            this.getVisual().setBasicPatch(var2);
         } else if (var4 == ClothingPatchFabricType.Denim) {
            this.getVisual().setDenimPatch(var2);
         } else {
            this.getVisual().setLeatherPatch(var2);
         }

         if (this.patches == nullptr) {
            this.patches = std::make_unique<std::unordered_map<>>();
         }

    int var5 = Math.max(1, var1.getPerkLevel(Perks.Tailoring));
    float var6 = this.getVisual().getHole(var2);
    int var7 = this.getCondLossPerHole();
         if (var5 < 3) {
            var7 -= 2;
         } else if (var5 < 6) {
            var7--;
         }

    ClothingPatch var8 = std::make_shared<ClothingPatch>(this, var5, var4.index, var6 > 0.0F);
         if (var6 > 0.0F) {
            var7 = Math.max(1, var7);
            this.setCondition(this.getCondition() + var7);
            var8.conditionGain = var7;
         }

         this.patches.put(var2.index(), var8);
         this.getVisual().removeHole(var2.index());
         if (GameClient.bClient && dynamic_cast<IsoPlayer*>(var1) != nullptr) {
            GameClient.instance.sendClothing((IsoPlayer)var1, "", nullptr);
         }
      }
   }

   public std::vector<BloodBodyPartType> getCoveredParts() {
    std::vector var1 = this.getScriptItem().getBloodClothingType();
      return BloodClothingType.getCoveredParts(var1);
   }

    int getNbrOfCoveredParts() {
    std::vector var1 = this.getScriptItem().getBloodClothingType();
      return BloodClothingType.getCoveredPartCount(var1);
   }

    int getCondLossPerHole() {
    int var2 = this.getNbrOfCoveredParts();
      return PZMath.max(1, this.getConditionMax() / var2);
   }

    void copyPatchesTo(Clothing var1) {
      var1.patches = this.patches;
   }

    std::string getClothingExtraSubmenu() {
      return this.ScriptItem.clothingExtraSubmenu;
   }

    bool canBe3DRender() {
      return !StringUtils.isNullOrEmpty(this.getWorldStaticItem())
         ? true
         : "Bip01_Head".equalsIgnoreCase(this.getClothingItem().m_AttachBone) && (!this.isCosmetic() || "Eyes" == this.getBodyLocation()));
   }

    bool isWorn() {
      return this.container.dynamic_cast<IsoGameCharacter*>(parent) != nullptr && ((IsoGameCharacter)this.container.parent).getWornItems().contains(this);
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie
