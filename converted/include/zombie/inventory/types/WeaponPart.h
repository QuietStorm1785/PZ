#pragma once
#include "zombie/core/Translator.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemType.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/ui/ObjectTooltip.h"
#include <cstdint>
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

class WeaponPart : public InventoryItem {
public:
  static const std::string TYPE_CANON = "Canon";
  static const std::string TYPE_CLIP = "Clip";
  static const std::string TYPE_RECOILPAD = "RecoilPad";
  static const std::string TYPE_SCOPE = "Scope";
  static const std::string TYPE_SLING = "Sling";
  static const std::string TYPE_STOCK = "Stock";
  float maxRange = 0.0F;
  float minRangeRanged = 0.0F;
  float damage = 0.0F;
  float recoilDelay = 0.0F;
  int clipSize = 0;
  int reloadTime = 0;
  int aimingTime = 0;
  int hitChance = 0;
  float angle = 0.0F;
  float weightModifier = 0.0F;
private
  final ArrayList<String> mountOn = std::make_unique<ArrayList<>>();
private
  final ArrayList<String> mountOnDisplayName = std::make_unique<ArrayList<>>();
  std::string partType = null;

public
  WeaponPart(const std::string &module, const std::string &name,
             const std::string &itemType, const std::string &texName) {
    super(module, name, itemType, texName);
    this.cat = ItemType.Weapon;
  }

  int getSaveType() { return Item.Type.WeaponPart.ordinal(); }

  std::string getCategory() {
    return this.mainCategory != nullptr ? this.mainCategory : "WeaponPart";
  }

  void DoTooltip(ObjectTooltip tooltipUI, ObjectTooltip.Layout layout) {
    ObjectTooltip.LayoutItem layoutItem = layout.addItem();
    layoutItem.setLabel(Translator.getText("Tooltip_weapon_Type") + ":", 1.0F,
                        1.0F, 0.8F, 1.0F);
    layoutItem.setValue(Translator.getText("Tooltip_weapon_" + this.partType),
                        1.0F, 1.0F, 0.8F, 1.0F);
    layoutItem = layout.addItem();
    std::string string =
        Translator.getText("Tooltip_weapon_CanBeMountOn") +
        this.mountOnDisplayName.toString().replaceAll("\\[", "").replaceAll(
            "\\]", "");
    layoutItem.setLabel(string, 1.0F, 1.0F, 0.8F, 1.0F);
  }

  float getMinRangeRanged() { return this.minRangeRanged; }

  void setMinRangeRanged(float _minRangeRanged) {
    this.minRangeRanged = _minRangeRanged;
  }

  float getMaxRange() { return this.maxRange; }

  void setMaxRange(float _maxRange) { this.maxRange = _maxRange; }

  float getRecoilDelay() { return this.recoilDelay; }

  void setRecoilDelay(float _recoilDelay) { this.recoilDelay = _recoilDelay; }

  int getClipSize() { return this.clipSize; }

  void setClipSize(int _clipSize) { this.clipSize = _clipSize; }

  float getDamage() { return this.damage; }

  void setDamage(float _damage) { this.damage = _damage; }

public
  ArrayList<String> getMountOn() { return this.mountOn; }

  void setMountOn(ArrayList<String> _mountOn) {
    this.mountOn.clear();
    this.mountOnDisplayName.clear();

    for (int int0 = 0; int0 < _mountOn.size(); int0++) {
      std::string string = (String)_mountOn.get(int0);
      if (!string.contains(".")) {
        string = this.getModule() + "." + string;
      }

      Item item = ScriptManager.instance.getItem(string);
      if (item != nullptr) {
        this.mountOn.add(item.getFullName());
        this.mountOnDisplayName.add(item.getDisplayName());
      }
    }
  }

  std::string getPartType() { return this.partType; }

  void setPartType(const std::string &_partType) { this.partType = _partType; }

  int getReloadTime() { return this.reloadTime; }

  void setReloadTime(int _reloadTime) { this.reloadTime = _reloadTime; }

  int getAimingTime() { return this.aimingTime; }

  void setAimingTime(int _aimingTime) { this.aimingTime = _aimingTime; }

  int getHitChance() { return this.hitChance; }

  void setHitChance(int _hitChance) { this.hitChance = _hitChance; }

  float getAngle() { return this.angle; }

  void setAngle(float _angle) { this.angle = _angle; }

  float getWeightModifier() { return this.weightModifier; }

  void setWeightModifier(float _weightModifier) {
    this.weightModifier = _weightModifier;
  }
}
} // namespace types
} // namespace inventory
} // namespace zombie
