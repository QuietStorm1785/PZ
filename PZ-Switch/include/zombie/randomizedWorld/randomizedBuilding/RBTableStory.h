#pragma once
#include "zombie/core/Rand.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RBTableStory : public RandomizedBuildingBase {
public:
public
 static ArrayList<RBTableStory.StoryDef> allStories =
 std::make_unique<ArrayList<>>();
 float xOffset = 0.0F;
 float yOffset = 0.0F;
 IsoGridSquare currentSquare = nullptr;
public
 ArrayList<HashMap<String, Integer>> fullTableMap =
 std::make_unique<ArrayList<>>();
 IsoObject table1 = nullptr;
 IsoObject table2 = nullptr;

 void initStories() {
 if (allStories.empty()) {
 std::vector arrayList0 = new ArrayList();
 arrayList0.add("livingroom");
 arrayList0.add("kitchen");
 std::vector arrayList1 = new ArrayList();
 LinkedHashMap linkedHashMap = new LinkedHashMap();
 linkedHashMap.put("BakingPan", 50);
 linkedHashMap.put("CakePrep", 50);
 arrayList1.add(
 new RBTableStory.StorySpawnItem(linkedHashMap, nullptr, 100);
 arrayList1.add(
 new RBTableStory.StorySpawnItem(nullptr, "Chocolate", 100);
 arrayList1.add(new RBTableStory.StorySpawnItem(nullptr, "Butter", 70);
 arrayList1.add(new RBTableStory.StorySpawnItem(nullptr, "Flour", 70);
 arrayList1.add(new RBTableStory.StorySpawnItem(nullptr, "Spoon", 100);
 arrayList1.add(
 new RBTableStory.StorySpawnItem(nullptr, "EggCarton", 100);
 arrayList1.add(new RBTableStory.StorySpawnItem(nullptr, "Egg", 100);
 allStories.add(new RBTableStory.StoryDef(arrayList1, arrayList0);
 }
 }

 bool isValid(BuildingDef var1, bool var2) { return false; }

 void randomizeBuilding(BuildingDef var1) {
 this->initStories();
 if (this->table1 != nullptr && this->table2 != nullptr) {
 if (this->table1.getSquare() != nullptr &&
 this->table1.getSquare().getRoom() != nullptr) {
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < allStories.size(); int0++) {
 RBTableStory.StoryDef storyDef0 = allStories.get(int0);
 if (storyDef0.rooms.empty() ||
 storyDef0.rooms.contains(
 this->table1.getSquare().getRoom().getName())) {
 arrayList.add(storyDef0);
 }
 }

 if (!arrayList.empty()) {
 RBTableStory.StoryDef storyDef1 =
 (RBTableStory.StoryDef)arrayList.get(
 Rand.Next(0, arrayList.size()));
 if (storyDef1 != nullptr) {
 bool boolean0 = true;
 if ((int)this->table1.getY() != (int)this->table2.getY()) {
 boolean0 = false;
 }

 this->doSpawnTable(storyDef1.items, boolean0);
 if (storyDef1.addBlood) {
 int int1 = (int)this->table1.getX() - 1;
 int int2 = (int)this->table1.getX() + 1;
 int int3 = (int)this->table1.getY() - 1;
 int int4 = (int)this->table2.getY() + 1;
 if (boolean0) {
 int1 = (int)this->table1.getX() - 1;
 int2 = (int)this->table2.getX() + 1;
 int3 = (int)this->table1.getY() - 1;
 int4 = (int)this->table2.getY() + 1;
 }

 for (int int5 = int1; int5 < int2 + 1; int5++) {
 for (int int6 = int3; int6 < int4 + 1; int6++) {
 int int7 = Rand.Next(7, 15);

 for (int int8 = 0; int8 < int7; int8++) {
 this->currentSquare.getChunk().addBloodSplat(
 int5 + Rand.Next(-0.5F, 0.5F),
 int6 + Rand.Next(-0.5F, 0.5F), this->table1.getZ(),
 Rand.Next(8);
 }
 }
 }
 }
 }
 }
 }
 }
 }

 void doSpawnTable(ArrayList<RBTableStory.StorySpawnItem> arrayList,
 bool boolean0) {
 this->xOffset = 0.0F;
 this->yOffset = 0.0F;
 int int0 = 0;
 if (boolean0) {
 this->xOffset = 0.6F;
 this->yOffset = Rand.Next(0.5F, 1.1F);
 } else {
 this->yOffset = 0.6F;
 this->xOffset = Rand.Next(0.5F, 1.1F);
 }

 for (this->currentSquare = this->table1.getSquare(); int0 < arrayList.size();
 int0++) {
 RBTableStory.StorySpawnItem storySpawnItem =
 (RBTableStory.StorySpawnItem)arrayList.get(int0);
 std::string string = this->getItemFromSSI(storySpawnItem);
 if (string != nullptr) {
 InventoryItem item = this->currentSquare.AddWorldInventoryItem(
 string, this->xOffset, this->yOffset, 0.4F);
 if (item != nullptr) {
 this->increaseOffsets(boolean0, storySpawnItem);
 }
 }
 }
 }

 void increaseOffsets(bool boolean0,
 RBTableStory.StorySpawnItem storySpawnItem) {
 float float0 = 0.15F + storySpawnItem.forcedOffset;
 if (boolean0) {
 this->xOffset += float0;
 if (this->xOffset > 1.0F) {
 this->currentSquare = this->table2.getSquare();
 this->xOffset = 0.35F;
 }

 float float1 = this->yOffset;

 while (Math.abs(float1 - this->yOffset) < 0.11F) {
 this->yOffset = Rand.Next(0.5F, 1.1F);
 }
 } else {
 this->yOffset += float0;
 if (this->yOffset > 1.0F) {
 this->currentSquare = this->table2.getSquare();
 this->yOffset = 0.35F;
 }

 float float2 = this->xOffset;

 while (Math.abs(float2 - this->xOffset) < 0.11F) {
 this->xOffset = Rand.Next(0.5F, 1.1F);
 }
 }
 }

 std::string getItemFromSSI(RBTableStory.StorySpawnItem storySpawnItem) {
 if (Rand.Next(100) > storySpawnItem.chanceToSpawn) {
 return nullptr;
 } else if (storySpawnItem.eitherObject != nullptr &&
 !storySpawnItem.eitherObject.empty()) {
 int int0 = Rand.Next(100);
 int int1 = 0;

 for (String string : storySpawnItem.eitherObject.keySet()) {
 int int2 = storySpawnItem.eitherObject.get(string);
 int1 += int2;
 if (int1 >= int0) {
 return string;
 }
 }

 return nullptr;
 } else {
 return storySpawnItem.object;
 }
 }

class StoryDef {
 public
 ArrayList<RBTableStory.StorySpawnItem> items = nullptr;
 bool addBlood = false;
 public
 ArrayList<String> rooms = nullptr;

 public
 StoryDef(ArrayList<RBTableStory.StorySpawnItem> arrayList) {
 this->items = arrayList;
 }

 public
 StoryDef(ArrayList<RBTableStory.StorySpawnItem> arrayList0,
 ArrayList<String> arrayList1) {
 this->items = arrayList0;
 this->rooms = arrayList1;
 }
 }

 class StorySpawnItem {
 LinkedHashMap<String, Integer> eitherObject = nullptr;
 std::string object = nullptr;
 int chanceToSpawn = nullptr;
 float forcedOffset = 0.0F;

 public
 StorySpawnItem(Integer > linkedHashMap, const std::string &string,
 int integer) {
 this->eitherObject = linkedHashMap;
 this->object = string;
 this->chanceToSpawn = integer;
 }

 public
 StorySpawnItem(Integer > linkedHashMap, const std::string &string,
 int integer, float float0) {
 this->eitherObject = linkedHashMap;
 this->object = string;
 this->chanceToSpawn = integer;
 this->forcedOffset = float0;
 }
 }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
