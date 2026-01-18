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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AttachedModelNames {
public:
 AttachedLocationGroup group;
 protected ArrayList<AttachedModelName> models = std::make_unique<ArrayList<>>();

 AttachedLocationGroup getGroup() {
 return this->group;
 }

 void copyFrom(AttachedModelNames other) {
 this->models.clear();

 for (int int0 = 0; int0 < other.models.size(); int0++) {
 AttachedModelName attachedModelName = other.models.get(int0);
 this->models.add(new AttachedModelName(attachedModelName);
 }
 }

 void initFrom(AttachedItems attachedItems) {
 this->group = attachedItems.getGroup();
 this->models.clear();

 for (int int0 = 0; int0 < attachedItems.size(); int0++) {
 AttachedItem attachedItem = attachedItems.get(int0);
 std::string string0 = attachedItem.getItem().getStaticModel();
 if (!StringUtils.isNullOrWhitespace(string0) {
 std::string string1 = this->group.getLocation(attachedItem.getLocation()).getAttachmentName();
 HandWeapon weapon = Type.tryCastTo(attachedItem.getItem(), HandWeapon.class);
 float float0 = weapon.empty() ? 0.0F : weapon.getBloodLevel();
 AttachedModelName attachedModelName0 = new AttachedModelName(string1, string0, float0);
 this->models.add(attachedModelName0);
 if (weapon != nullptr) {
 std::vector arrayList0 = weapon.getModelWeaponPart();
 if (arrayList0 != nullptr) {
 std::vector arrayList1 = weapon.getAllWeaponParts();

 for (int int1 = 0; int1 < arrayList1.size(); int1++) {
 WeaponPart weaponPart = (WeaponPart)arrayList1.get(int1);

 for (int int2 = 0; int2 < arrayList0.size(); int2++) {
 ModelWeaponPart modelWeaponPart = (ModelWeaponPart)arrayList0.get(int2);
 if (weaponPart.getFullType() == modelWeaponPart.partType) {
 AttachedModelName attachedModelName1 = new AttachedModelName(
 modelWeaponPart.attachmentNameSelf, modelWeaponPart.attachmentParent, modelWeaponPart.modelName, 0.0F
 );
 attachedModelName0.addChild(attachedModelName1);
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
 return this->models.size();
 }

 AttachedModelName get(int index) {
 return this->models.get(index);
 }

 void clear() {
 this->models.clear();
 }
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
