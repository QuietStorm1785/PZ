#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class RBKateAndBaldspot : public RandomizedBuildingBase {
public:
 public RBKateAndBaldspot() {
 this->name = "K&B story";
 this->setChance(0);
 this->setUnique(true);
 }

 void randomizeBuilding(BuildingDef def) {
 def.bAlarmed = false;
 def.setHasBeenVisited(true);
 def.setAllExplored(true);
 std::vector arrayList = this->addZombiesOnSquare(1, "Kate", 100, this->getSq(10746, 9412, 1);
 if (arrayList != nullptr && !arrayList.empty()) {
 IsoZombie zombie0 = (IsoZombie)arrayList.get(0);
 HumanVisual humanVisual = (HumanVisual)zombie0.getVisual();
 humanVisual.setHairModel("Rachel");
 humanVisual.setHairColor(new ImmutableColor(0.83F, 0.67F, 0.27F);

 for (int int0 = 0; int0 < zombie0.getItemVisuals().size(); int0++) {
 ItemVisual itemVisual0 = zombie0.getItemVisuals().get(int0);
 if (itemVisual0.getClothingItemName() == "Skirt_Knees")) {
 itemVisual0.setTint(new ImmutableColor(0.54F, 0.54F, 0.54F);
 }
 }

 zombie0.getHumanVisual().setSkinTextureIndex(1);
 zombie0.addBlood(BloodBodyPartType.LowerLeg_L, true, true, true);
 zombie0.addBlood(BloodBodyPartType.LowerLeg_L, true, true, true);
 zombie0.addBlood(BloodBodyPartType.UpperLeg_L, true, true, true);
 zombie0.addBlood(BloodBodyPartType.UpperLeg_L, true, true, true);
 zombie0.setCrawler(true);
 zombie0.setCanWalk(false);
 zombie0.setCrawlerType(1);
 zombie0.resetModelNextFrame();
 arrayList = this->addZombiesOnSquare(1, "Bob", 0, this->getSq(10747, 9412, 1);
 if (arrayList != nullptr && !arrayList.empty()) {
 IsoZombie zombie1 = (IsoZombie)arrayList.get(0);
 humanVisual = (HumanVisual)zombie1.getVisual();
 humanVisual.setHairModel("Baldspot");
 humanVisual.setHairColor(new ImmutableColor(0.337F, 0.173F, 0.082F);
 humanVisual.setBeardModel("");

 for (int int1 = 0; int1 < zombie1.getItemVisuals().size(); int1++) {
 ItemVisual itemVisual1 = zombie1.getItemVisuals().get(int1);
 if (itemVisual1.getClothingItemName() == "Trousers_DefaultTEXTURE_TINT")) {
 itemVisual1.setTint(new ImmutableColor(0.54F, 0.54F, 0.54F);
 }

 if (itemVisual1.getClothingItemName() == "Shirt_FormalTINT")) {
 itemVisual1.setTint(new ImmutableColor(0.63F, 0.71F, 0.82F);
 }
 }

 zombie1.getHumanVisual().setSkinTextureIndex(1);
 zombie1.resetModelNextFrame();
 zombie1.addItemToSpawnAtDeath(InventoryItemFactory.CreateItem("KatePic"));
 zombie1.addItemToSpawnAtDeath(InventoryItemFactory.CreateItem("RippedSheets"));
 zombie1.addItemToSpawnAtDeath(InventoryItemFactory.CreateItem("Pills"));
 InventoryItem item0 = InventoryItemFactory.CreateItem("Hammer");
 item0.setCondition(1);
 zombie1.addItemToSpawnAtDeath(item0);
 zombie1.addItemToSpawnAtDeath(InventoryItemFactory.CreateItem("Nails"));
 zombie1.addItemToSpawnAtDeath(InventoryItemFactory.CreateItem("Plank"));
 arrayList = this->addZombiesOnSquare(1, "Raider", 0, this->getSq(10745, 9411, 0);
 if (arrayList != nullptr && !arrayList.empty()) {
 IsoZombie zombie2 = (IsoZombie)arrayList.get(0);
 humanVisual = (HumanVisual)zombie2.getVisual();
 humanVisual.setHairModel("Crewcut");
 humanVisual.setHairColor(new ImmutableColor(0.37F, 0.27F, 0.23F);
 humanVisual.setBeardModel("Goatee");

 for (int int2 = 0; int2 < zombie2.getItemVisuals().size(); int2++) {
 ItemVisual itemVisual2 = zombie2.getItemVisuals().get(int2);
 if (itemVisual2.getClothingItemName() == "Trousers_DefaultTEXTURE_TINT")) {
 itemVisual2.setTint(new ImmutableColor(0.54F, 0.54F, 0.54F);
 }

 if (itemVisual2.getClothingItemName() == "Vest_DefaultTEXTURE_TINT")) {
 itemVisual2.setTint(new ImmutableColor(0.22F, 0.25F, 0.27F);
 }
 }

 zombie2.getHumanVisual().setSkinTextureIndex(1);
 InventoryItem item1 = InventoryItemFactory.CreateItem("Shotgun");
 item1.setCondition(0);
 zombie2.setAttachedItem("Rifle On Back", item1);
 InventoryItem item2 = InventoryItemFactory.CreateItem("BaseballBat");
 item2.setCondition(1);
 zombie2.addItemToSpawnAtDeath(item2);
 zombie2.addItemToSpawnAtDeath(InventoryItemFactory.CreateItem("ShotgunShells"));
 zombie2.resetModelNextFrame();
 this->addItemOnGround(this->getSq(10747, 9412, 1), InventoryItemFactory.CreateItem("Pillow"));
 IsoGridSquare square0 = this->getSq(10745, 9410, 0);
 square0.Burn();
 square0 = this->getSq(10745, 9411, 0);
 square0.Burn();
 square0 = this->getSq(10746, 9411, 0);
 square0.Burn();
 square0 = this->getSq(10745, 9410, 0);
 square0.Burn();
 square0 = this->getSq(10745, 9412, 0);
 square0.Burn();
 square0 = this->getSq(10747, 9410, 0);
 square0.Burn();
 square0 = this->getSq(10746, 9409, 0);
 square0.Burn();
 square0 = this->getSq(10745, 9409, 0);
 square0.Burn();
 square0 = this->getSq(10744, 9410, 0);
 square0.Burn();
 square0 = this->getSq(10747, 9411, 0);
 square0.Burn();
 square0 = this->getSq(10746, 9412, 0);
 square0.Burn();
 IsoGridSquare square1 = this->getSq(10746, 9410, 0);

 for (int int3 = 0; int3 < square1.getObjects().size(); int3++) {
 IsoObject object = square1.getObjects().get(int3);
 if (object.getContainer() != nullptr) {
 InventoryItem item3 = InventoryItemFactory.CreateItem("PotOfSoup");
 item3.setCooked(true);
 item3.setBurnt(true);
 object.getContainer().AddItem(item3);
 break;
 }
 }

 this->addBarricade(this->getSq(10747, 9417, 0), 3);
 this->addBarricade(this->getSq(10745, 9417, 0), 3);
 this->addBarricade(this->getSq(10744, 9413, 0), 3);
 this->addBarricade(this->getSq(10744, 9412, 0), 3);
 this->addBarricade(this->getSq(10752, 9413, 0), 3);
 }
 }
 }
 }

 /**
 * Description copied from class: RandomizedBuildingBase
 */
 bool isValid(BuildingDef def, bool force) {
 this->debugLine = "";
 if (def.x == 10744 && def.y == 9409) {
 return true;
 } else {
 this->debugLine = "Need to be the K&B house";
 return false;
 }
 }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
