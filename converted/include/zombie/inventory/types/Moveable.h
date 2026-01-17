#pragma once
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
#include "zombie/util/StringUtils.h"
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

/**
 * Turbo.
 */
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
  std::string customItem = null;

public
  Moveable(const std::string &module, const std::string &name,
           const std::string &type, const std::string &tex) {
    super(module, name, type, tex);
    this.cat = ItemType.Moveable;
  }

public
  Moveable(const std::string &module, const std::string &name,
           const std::string &type, Item item) {
    super(module, name, type, item);
    this.cat = ItemType.Moveable;
  }

  /**
   * @return the name
   */
  std::string getName() {
    if ("Moveable Object" == this.movableFullName)) {
            return this.name;
        }
    else {
            return this.movableFullName == this.name)
                ? Translator.getMoveableDisplayName(this.customNameFull)
                : Translator.getMoveableDisplayName(this.movableFullName) + this.customNameFull.substring(this.movableFullName.length());
    }
  }

  std::string getDisplayName() { return this.getName(); }

  bool CanBeDroppedOnFloor() {
    if (this.worldSprite != nullptr && this.spriteGrid != nullptr) {
      IsoSprite sprite = IsoSpriteManager.instance.getSprite(this.worldSprite);
      PropertyContainer propertyContainer = sprite.getProperties();
      return this.canBeDroppedOnFloor ||
             !propertyContainer.Is("ForceSingleItem");
    } else {
      return this.canBeDroppedOnFloor;
    }
  }

  std::string getMovableFullName() { return this.movableFullName; }

  std::string getCustomNameFull() { return this.customNameFull; }

  bool isMultiGridAnchor() { return this.isMultiGridAnchor; }

  IsoSpriteGrid getSpriteGrid() { return this.spriteGrid; }

  std::string getWorldSprite() { return this.worldSprite; }

  bool ReadFromWorldSprite(const std::string &sprite) {
    if (sprite == nullptr) {
      return false;
    } else if (this.hasReadWorldSprite && this.worldSprite != nullptr &&
               this.worldSprite.equalsIgnoreCase(sprite)) {
      return true;
    } else {
      this.customItem = nullptr;

      try {
        IsoSprite _sprite = IsoSpriteManager.instance.NamedMap.get(sprite);
        if (_sprite != nullptr) {
          PropertyContainer propertyContainer = _sprite.getProperties();
          if (propertyContainer.Is("IsMoveAble")) {
            if (propertyContainer.Is("CustomItem")) {
              this.customItem = propertyContainer.Val("CustomItem");
              Item item = ScriptManager.instance.FindItem(this.customItem);
              if (item != nullptr) {
                this.Weight = this.ActualWeight = item.ActualWeight;
              }

              this.worldSprite = sprite;
              if (_sprite.getSpriteGrid() != nullptr) {
                this.spriteGrid = _sprite.getSpriteGrid();
                int int0 = _sprite.getSpriteGrid().getSpriteIndex(_sprite);
                this.isMultiGridAnchor = int0 == 0;
              }

              return true;
            }

            this.isLight = propertyContainer.Is("lightR");
            this.worldSprite = sprite;
            float float0 = 1.0F;
            if (propertyContainer.Is("PickUpWeight")) {
              float0 = Float.parseFloat(propertyContainer.Val("PickUpWeight")) /
                       10.0F;
            }

            this.Weight = float0;
            this.ActualWeight = float0;
            this.setCustomWeight(true);
            std::string string0 = "Moveable Object";
            if (propertyContainer.Is("CustomName")) {
              if (propertyContainer.Is("GroupName")) {
                string0 = propertyContainer.Val("GroupName") + " " +
                          propertyContainer.Val("CustomName");
              } else {
                string0 = propertyContainer.Val("CustomName");
              }
            }

            this.movableFullName = string0;
            this.name = string0;
            this.customNameFull = string0;
            if (_sprite.getSpriteGrid() != nullptr) {
              this.spriteGrid = _sprite.getSpriteGrid();
              int int1 = _sprite.getSpriteGrid().getSpriteIndex(_sprite);
              int int2 = _sprite.getSpriteGrid().getSpriteCount();
              this.isMultiGridAnchor = int1 == 0;
              if (!propertyContainer.Is("ForceSingleItem")) {
                this.name = this.name + " (" + (int1 + 1) + "/" + int2 + ")";
              } else {
                this.name = this.name + " (1/1)";
              }

              this.customNameFull = this.name;
              Texture texture0 = null;
              std::string string1 = "Item_Flatpack";
              if (string1 != nullptr) {
                texture0 = Texture.getSharedTexture(string1);
                this.setColor(new Color(Rand.Next(0.7F, 1.0F),
                                        Rand.Next(0.7F, 1.0F),
                                        Rand.Next(0.7F, 1.0F)));
              }

              if (texture0 == nullptr) {
                texture0 =
                    Texture.getSharedTexture("media/inventory/Question_On.png");
              }

              this.setTexture(texture0);
              this.getModData().rawset("Flatpack", "true");
            } else if (this.texture == nullptr ||
                       this.texture.getName() == nullptr ||
                       this.texture.getName() == "Item_Moveable_object")
                            || this.texture.getName() == "Question_On")) {
                              Texture texture1 = null;
                              void *object = null;
                              object = sprite;
                              if (sprite != nullptr) {
                                texture1 = Texture.getSharedTexture(sprite);
                                if (texture1 != nullptr) {
                                  texture1 = texture1.splitIcon();
                                }
                              }

                              if (texture1 == nullptr) {
                                if (!propertyContainer.Is("MoveType")) {
                                  object = "Item_Moveable_object";
                                } else if (propertyContainer.Val("MoveType") ==
                                           "WallObject")) {
                                    object = "Item_Moveable_wallobject";
                                }
                                else if (propertyContainer.Val("MoveType") ==
                                         "WindowObject")) {
                                    object = "Item_Moveable_windowobject";
                                }
                                else if (propertyContainer.Val("MoveType") ==
                                         "Window")) {
                                    object = "Item_Moveable_window";
                                }
                                else if (propertyContainer.Val("MoveType") ==
                                         "FloorTile")) {
                                    object = "Item_Moveable_floortile";
                                }
                                else if (propertyContainer.Val("MoveType") ==
                                         "FloorRug")) {
                                    object = "Item_Moveable_floorrug";
                                }
                                else if (propertyContainer.Val("MoveType") ==
                                         "Vegitation")) {
                                    object = "Item_Moveable_vegitation";
                                }

                                if (object != nullptr) {
                                  texture1 =
                                      Texture.getSharedTexture((String)object);
                                }
                              }

                              if (texture1 == nullptr) {
                                texture1 = Texture.getSharedTexture(
                                    "media/inventory/Question_On.png");
                              }

                              this.setTexture(texture1);
                            }

            this.hasReadWorldSprite = true;
            return true;
          }
        }
      } catch (Exception exception) {
        System.out.println("Error in Moveable item: " + exception.getMessage());
      }

      System.out.println("Warning: Moveable not valid");
      return false;
    }
  }

  bool isLight() { return this.isLight; }

  void setLight(bool _isLight) { this.isLight = _isLight; }

  bool isLightUseBattery() { return this.lightUseBattery; }

  void setLightUseBattery(bool _lightUseBattery) {
    this.lightUseBattery = _lightUseBattery;
  }

  bool isLightHasBattery() { return this.lightHasBattery; }

  void setLightHasBattery(bool _lightHasBattery) {
    this.lightHasBattery = _lightHasBattery;
  }

  std::string getLightBulbItem() { return this.lightBulbItem; }

  void setLightBulbItem(const std::string &_lightBulbItem) {
    this.lightBulbItem = _lightBulbItem;
  }

  float getLightPower() { return this.lightPower; }

  void setLightPower(float _lightPower) { this.lightPower = _lightPower; }

  float getLightDelta() { return this.lightDelta; }

  void setLightDelta(float _lightDelta) { this.lightDelta = _lightDelta; }

  float getLightR() { return this.lightR; }

  void setLightR(float _lightR) { this.lightR = _lightR; }

  float getLightG() { return this.lightG; }

  void setLightG(float _lightG) { this.lightG = _lightG; }

  float getLightB() { return this.lightB; }

  void setLightB(float _lightB) { this.lightB = _lightB; }

  int getSaveType() { return Item.Type.Moveable.ordinal(); }

  void save(ByteBuffer output, bool net) {
    super.save(output, net);
    GameWindow.WriteString(output, this.worldSprite);
    output.put((byte)(this.isLight ? 1 : 0));
    if (this.isLight) {
      output.put((byte)(this.lightUseBattery ? 1 : 0));
      output.put((byte)(this.lightHasBattery ? 1 : 0));
      output.put((byte)(this.lightBulbItem != nullptr ? 1 : 0));
      if (this.lightBulbItem != nullptr) {
        GameWindow.WriteString(output, this.lightBulbItem);
      }

      output.putFloat(this.lightPower);
      output.putFloat(this.lightDelta);
      output.putFloat(this.lightR);
      output.putFloat(this.lightG);
      output.putFloat(this.lightB);
    }
  }

  void load(ByteBuffer input, int WorldVersion) {
    super.load(input, WorldVersion);
    this.worldSprite = GameWindow.ReadString(input);
    if (!this.ReadFromWorldSprite(this.worldSprite) && this instanceof
        Radio && this.getScriptItem() != nullptr &&
            !StringUtils.isNullOrWhitespace(
                this.getScriptItem().worldObjectSprite)) {
      DebugLog.log("Moveable.load -> Radio item = " +
                   (this.fullType != nullptr ? this.fullType : "unknown"));
    }

    if (this.customItem == nullptr &&
        !StringUtils.isNullOrWhitespace(this.worldSprite) &&
        !this.type.equalsIgnoreCase(this.worldSprite)) {
      this.type = this.worldSprite;
      this.fullType = this.module + "." + this.worldSprite;
    }

    this.isLight = input.get() == 1;
    if (this.isLight) {
      this.lightUseBattery = input.get() == 1;
      this.lightHasBattery = input.get() == 1;
      if (input.get() == 1) {
        this.lightBulbItem = GameWindow.ReadString(input);
      }

      this.lightPower = input.getFloat();
      this.lightDelta = input.getFloat();
      this.lightR = input.getFloat();
      this.lightG = input.getFloat();
      this.lightB = input.getFloat();
    }
  }

  void setWorldSprite(const std::string &WorldSprite) {
    this.worldSprite = WorldSprite;
  }
}
} // namespace types
} // namespace inventory
} // namespace zombie
