#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Translator.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemType.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Item/Type.h"
#include "zombie/ui/ObjectTooltip.h"
#include "zombie/ui/ObjectTooltip/Layout.h"
#include "zombie/ui/ObjectTooltip/LayoutItem.h"

namespace zombie {
namespace inventory {
namespace types {


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
   private const std::vector<std::string> mountOn = std::make_unique<std::vector<>>();
   private const std::vector<std::string> mountOnDisplayName = std::make_unique<std::vector<>>();
    std::string partType = nullptr;

    public WeaponPart(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      super(var1, var2, var3, var4);
      this.cat = ItemType.Weapon;
   }

    int getSaveType() {
      return Type.WeaponPart.ordinal();
   }

    std::string getCategory() {
      return this.mainCategory != nullptr ? this.mainCategory : "WeaponPart";
   }

    void DoTooltip(ObjectTooltip var1, Layout var2) {
    LayoutItem var3 = var2.addItem();
      var3.setLabel(Translator.getText("Tooltip_weapon_Type") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
      var3.setValue(Translator.getText("Tooltip_weapon_" + this.partType), 1.0F, 1.0F, 0.8F, 1.0F);
      var3 = var2.addItem();
    std::string var4 = Translator.getText("Tooltip_weapon_CanBeMountOn") + this.mountOnDisplayName.replaceAll("\\[", "").replaceAll("\\]", "");
      var3.setLabel(var4, 1.0F, 1.0F, 0.8F, 1.0F);
   }

    float getMinRangeRanged() {
      return this.minRangeRanged;
   }

    void setMinRangeRanged(float var1) {
      this.minRangeRanged = var1;
   }

    float getMaxRange() {
      return this.maxRange;
   }

    void setMaxRange(float var1) {
      this.maxRange = var1;
   }

    float getRecoilDelay() {
      return this.recoilDelay;
   }

    void setRecoilDelay(float var1) {
      this.recoilDelay = var1;
   }

    int getClipSize() {
      return this.clipSize;
   }

    void setClipSize(int var1) {
      this.clipSize = var1;
   }

    float getDamage() {
      return this.damage;
   }

    void setDamage(float var1) {
      this.damage = var1;
   }

   public std::vector<std::string> getMountOn() {
      return this.mountOn;
   }

    void setMountOn(std::vector<std::string> var1) {
      this.mountOn.clear();
      this.mountOnDisplayName.clear();

      for (int var2 = 0; var2 < var1.size(); var2++) {
    std::string var3 = (std::string)var1.get(var2);
         if (!var3.contains(".")) {
            var3 = this.getModule() + "." + var3;
         }

    Item var4 = ScriptManager.instance.getItem(var3);
         if (var4 != nullptr) {
            this.mountOn.push_back(var4.getFullName());
            this.mountOnDisplayName.push_back(var4.getDisplayName());
         }
      }
   }

    std::string getPartType() {
      return this.partType;
   }

    void setPartType(const std::string& var1) {
      this.partType = var1;
   }

    int getReloadTime() {
      return this.reloadTime;
   }

    void setReloadTime(int var1) {
      this.reloadTime = var1;
   }

    int getAimingTime() {
      return this.aimingTime;
   }

    void setAimingTime(int var1) {
      this.aimingTime = var1;
   }

    int getHitChance() {
      return this.hitChance;
   }

    void setHitChance(int var1) {
      this.hitChance = var1;
   }

    float getAngle() {
      return this.angle;
   }

    void setAngle(float var1) {
      this.angle = var1;
   }

    float getWeightModifier() {
      return this.weightModifier;
   }

    void setWeightModifier(float var1) {
      this.weightModifier = var1;
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie
