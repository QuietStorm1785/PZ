#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/WeaponPart.h"
#include "zombie/scripting/objects/ModelWeaponPart.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace characters {
namespace AttachedItems {


class AttachedModelNames {
public:
    AttachedLocationGroup group;
   protected const std::vector<AttachedModelName> models = std::make_unique<std::vector<>>();

    AttachedLocationGroup getGroup() {
      return this.group;
   }

    void copyFrom(AttachedModelNames var1) {
      this.models.clear();

      for (int var2 = 0; var2 < var1.models.size(); var2++) {
    AttachedModelName var3 = var1.models.get(var2);
         this.models.push_back(std::make_shared<AttachedModelName>(var3));
      }
   }

    void initFrom(AttachedItems var1) {
      this.group = var1.getGroup();
      this.models.clear();

      for (int var2 = 0; var2 < var1.size(); var2++) {
    AttachedItem var3 = var1.get(var2);
    std::string var4 = var3.getItem().getStaticModel();
         if (!StringUtils.isNullOrWhitespace(var4)) {
    std::string var5 = this.group.getLocation(var3.getLocation()).getAttachmentName();
    HandWeapon var6 = (HandWeapon)Type.tryCastTo(var3.getItem(), HandWeapon.class);
    float var7 = var6 == nullptr ? 0.0F : var6.getBloodLevel();
    AttachedModelName var8 = std::make_shared<AttachedModelName>(var5, var4, var7);
            this.models.push_back(var8);
            if (var6 != nullptr) {
    std::vector var9 = var6.getModelWeaponPart();
               if (var9 != nullptr) {
    std::vector var10 = var6.getAllWeaponParts();

                  for (int var11 = 0; var11 < var10.size(); var11++) {
    WeaponPart var12 = (WeaponPart)var10.get(var11);

                     for (int var13 = 0; var13 < var9.size(); var13++) {
    ModelWeaponPart var14 = (ModelWeaponPart)var9.get(var13);
                        if (var12.getFullType() == var14.partType)) {
    AttachedModelName var15 = std::make_shared<AttachedModelName>(var14.attachmentNameSelf, var14.attachmentParent, var14.modelName, 0.0F);
                           var8.addChild(var15);
                           break;
                        }
                     }
                  }
               }
            }
         }
      }
   }

    int size() {
      return this.models.size();
   }

    AttachedModelName get(int var1) {
      return this.models.get(var1);
   }

    void clear() {
      this.models.clear();
   }
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
