#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/core/Color.h"
#include "zombie/core/Rand.h"
#include "zombie/core/Translator.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemType.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteGrid.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Item/Type.h"
#include "zombie/util/StringUtils.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {
namespace types {


class Moveable : public InventoryItem {
public:
    std::string worldSprite = "";
    bool isLight = false;
    bool lightUseBattery = false;
    bool lightHasBattery = false;
    std::string lightBulbItem = "Base.LightBulb";
    float lightPower = 0.0F;
    float lightDelta = 2.5E-4F;
    float lightR = 1.0F;
    float lightG = 1.0F;
    float lightB = 1.0F;
    bool isMultiGridAnchor = false;
    IsoSpriteGrid spriteGrid;
    std::string customNameFull = "Moveable Object";
    std::string movableFullName = "Moveable Object";
    bool canBeDroppedOnFloor = false;
    bool hasReadWorldSprite = false;
    std::string customItem = nullptr;

    public Moveable(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      super(var1, var2, var3, var4);
      this.cat = ItemType.Moveable;
   }

    public Moveable(const std::string& var1, const std::string& var2, const std::string& var3, Item var4) {
      super(var1, var2, var3, var4);
      this.cat = ItemType.Moveable;
   }

    std::string getName() {
      if ("Moveable Object" == this.movableFullName)) {
         return this.name;
      } else {
         return this.movableFullName == this.name)
            ? Translator.getMoveableDisplayName(this.customNameFull)
            : Translator.getMoveableDisplayName(this.movableFullName) + this.customNameFull.substr(this.movableFullName.length());
      }
   }

    std::string getDisplayName() {
      return this.getName();
   }

    bool CanBeDroppedOnFloor() {
      if (this.worldSprite != nullptr && this.spriteGrid != nullptr) {
    IsoSprite var1 = IsoSpriteManager.instance.getSprite(this.worldSprite);
    PropertyContainer var2 = var1.getProperties();
         return this.canBeDroppedOnFloor || !var2.Is("ForceSingleItem");
      } else {
         return this.canBeDroppedOnFloor;
      }
   }

    std::string getMovableFullName() {
      return this.movableFullName;
   }

    std::string getCustomNameFull() {
      return this.customNameFull;
   }

    bool isMultiGridAnchor() {
      return this.isMultiGridAnchor;
   }

    IsoSpriteGrid getSpriteGrid() {
      return this.spriteGrid;
   }

    std::string getWorldSprite() {
      return this.worldSprite;
   }

    bool ReadFromWorldSprite(const std::string& var1) {
      if (var1 == nullptr) {
    return false;
      } else if (this.hasReadWorldSprite && this.worldSprite != nullptr && this.worldSprite.equalsIgnoreCase(var1)) {
    return true;
      } else {
         this.customItem = nullptr;

         try {
    IsoSprite var2 = (IsoSprite)IsoSpriteManager.instance.NamedMap.get(var1);
            if (var2 != nullptr) {
    PropertyContainer var3 = var2.getProperties();
               if (var3.Is("IsMoveAble")) {
                  if (var3.Is("CustomItem")) {
                     this.customItem = var3.Val("CustomItem");
    Item var11 = ScriptManager.instance.FindItem(this.customItem);
                     if (var11 != nullptr) {
                        this.Weight = this.ActualWeight = var11.ActualWeight;
                     }

                     this.worldSprite = var1;
                     if (var2.getSpriteGrid() != nullptr) {
                        this.spriteGrid = var2.getSpriteGrid();
    int var12 = var2.getSpriteGrid().getSpriteIndex(var2);
                        this.isMultiGridAnchor = var12 == 0;
                     }

    return true;
                  }

                  this.isLight = var3.Is("lightR");
                  this.worldSprite = var1;
    float var4 = 1.0F;
                  if (var3.Is("PickUpWeight")) {
                     var4 = float.parseFloat(var3.Val("PickUpWeight")) / 10.0F;
                  }

                  this.Weight = var4;
                  this.ActualWeight = var4;
                  this.setCustomWeight(true);
    std::string var5 = "Moveable Object";
                  if (var3.Is("CustomName")) {
                     if (var3.Is("GroupName")) {
                        var5 = var3.Val("GroupName") + " " + var3.Val("CustomName");
                     } else {
                        var5 = var3.Val("CustomName");
                     }
                  }

                  this.movableFullName = var5;
                  this.name = var5;
                  this.customNameFull = var5;
                  if (var2.getSpriteGrid() != nullptr) {
                     this.spriteGrid = var2.getSpriteGrid();
    int var13 = var2.getSpriteGrid().getSpriteIndex(var2);
    int var15 = var2.getSpriteGrid().getSpriteCount();
                     this.isMultiGridAnchor = var13 == 0;
                     if (!var3.Is("ForceSingleItem")) {
                        this.name = this.name + " (" + (var13 + 1) + "/" + var15 + ")";
                     } else {
                        this.name = this.name + " (1/1)";
                     }

                     this.customNameFull = this.name;
    Texture var8 = nullptr;
    std::string var9 = "Item_Flatpack";
                     if (var9 != nullptr) {
                        var8 = Texture.getSharedTexture(var9);
                        this.setColor(std::make_shared<Color>(Rand.Next(0.7F, 1.0F), Rand.Next(0.7F, 1.0F), Rand.Next(0.7F, 1.0F)));
                     }

                     if (var8 == nullptr) {
                        var8 = Texture.getSharedTexture("media/inventory/Question_On.png");
                     }

                     this.setTexture(var8);
                     this.getModData().rawset("Flatpack", "true");
                  } else if (this.texture == nullptr
                     || this.texture.getName() == nullptr
                     || this.texture.getName() == "Item_Moveable_object")
                     || this.texture.getName() == "Question_On")) {
    Texture var6 = nullptr;
    void* var7 = nullptr;
                     var7 = var1;
                     if (var1 != nullptr) {
                        var6 = Texture.getSharedTexture(var1);
                        if (var6 != nullptr) {
                           var6 = var6.splitIcon();
                        }
                     }

                     if (var6 == nullptr) {
                        if (!var3.Is("MoveType")) {
                           var7 = "Item_Moveable_object";
                        } else if (var3.Val("MoveType") == "WallObject")) {
                           var7 = "Item_Moveable_wallobject";
                        } else if (var3.Val("MoveType") == "WindowObject")) {
                           var7 = "Item_Moveable_windowobject";
                        } else if (var3.Val("MoveType") == "Window")) {
                           var7 = "Item_Moveable_window";
                        } else if (var3.Val("MoveType") == "FloorTile")) {
                           var7 = "Item_Moveable_floortile";
                        } else if (var3.Val("MoveType") == "FloorRug")) {
                           var7 = "Item_Moveable_floorrug";
                        } else if (var3.Val("MoveType") == "Vegitation")) {
                           var7 = "Item_Moveable_vegitation";
                        }

                        if (var7 != nullptr) {
                           var6 = Texture.getSharedTexture((std::string)var7);
                        }
                     }

                     if (var6 == nullptr) {
                        var6 = Texture.getSharedTexture("media/inventory/Question_On.png");
                     }

                     this.setTexture(var6);
                  }

                  this.hasReadWorldSprite = true;
    return true;
               }
            }
         } catch (Exception var10) {
            System.out.println("Error in Moveable item: " + var10.getMessage());
         }

         System.out.println("Warning: Moveable not valid");
    return false;
      }
   }

    bool isLight() {
      return this.isLight;
   }

    void setLight(bool var1) {
      this.isLight = var1;
   }

    bool isLightUseBattery() {
      return this.lightUseBattery;
   }

    void setLightUseBattery(bool var1) {
      this.lightUseBattery = var1;
   }

    bool isLightHasBattery() {
      return this.lightHasBattery;
   }

    void setLightHasBattery(bool var1) {
      this.lightHasBattery = var1;
   }

    std::string getLightBulbItem() {
      return this.lightBulbItem;
   }

    void setLightBulbItem(const std::string& var1) {
      this.lightBulbItem = var1;
   }

    float getLightPower() {
      return this.lightPower;
   }

    void setLightPower(float var1) {
      this.lightPower = var1;
   }

    float getLightDelta() {
      return this.lightDelta;
   }

    void setLightDelta(float var1) {
      this.lightDelta = var1;
   }

    float getLightR() {
      return this.lightR;
   }

    void setLightR(float var1) {
      this.lightR = var1;
   }

    float getLightG() {
      return this.lightG;
   }

    void setLightG(float var1) {
      this.lightG = var1;
   }

    float getLightB() {
      return this.lightB;
   }

    void setLightB(float var1) {
      this.lightB = var1;
   }

    int getSaveType() {
      return Type.Moveable.ordinal();
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      GameWindow.WriteString(var1, this.worldSprite);
      var1.put((byte)(this.isLight ? 1 : 0));
      if (this.isLight) {
         var1.put((byte)(this.lightUseBattery ? 1 : 0));
         var1.put((byte)(this.lightHasBattery ? 1 : 0));
         var1.put((byte)(this.lightBulbItem != nullptr ? 1 : 0));
         if (this.lightBulbItem != nullptr) {
            GameWindow.WriteString(var1, this.lightBulbItem);
         }

         var1.putFloat(this.lightPower);
         var1.putFloat(this.lightDelta);
         var1.putFloat(this.lightR);
         var1.putFloat(this.lightG);
         var1.putFloat(this.lightB);
      }
   }

    void load(ByteBuffer var1, int var2) {
      super.load(var1, var2);
      this.worldSprite = GameWindow.ReadString(var1);
      if (!this.ReadFromWorldSprite(this.worldSprite)
         && dynamic_cast<Radio*>(this) != nullptr
         && this.getScriptItem() != nullptr
         && !StringUtils.isNullOrWhitespace(this.getScriptItem().worldObjectSprite)) {
         DebugLog.log("Moveable.load -> Radio item = " + (this.fullType != nullptr ? this.fullType : "unknown"));
      }

      if (this.customItem == nullptr && !StringUtils.isNullOrWhitespace(this.worldSprite) && !this.type.equalsIgnoreCase(this.worldSprite)) {
         this.type = this.worldSprite;
         this.fullType = this.module + "." + this.worldSprite;
      }

      this.isLight = var1.get() == 1;
      if (this.isLight) {
         this.lightUseBattery = var1.get() == 1;
         this.lightHasBattery = var1.get() == 1;
         if (var1.get() == 1) {
            this.lightBulbItem = GameWindow.ReadString(var1);
         }

         this.lightPower = var1.getFloat();
         this.lightDelta = var1.getFloat();
         this.lightR = var1.getFloat();
         this.lightG = var1.getFloat();
         this.lightB = var1.getFloat();
      }
   }

    void setWorldSprite(const std::string& var1) {
      this.worldSprite = var1;
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie
