#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/randomizedWorld/randomizedBuilding/RandomizedBuildingBase.h"
#include <iterator>

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {
namespace TableStories {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class RBTableStoryBase : public RandomizedBuildingBase {
public:
 public static ArrayList<RBTableStoryBase> allStories = std::make_unique<ArrayList<>>();
 static int totalChance = 0;
 int chance = 0;
 protected ArrayList<String> rooms = std::make_unique<ArrayList<>>();
 bool need2Tables = false;
 bool ignoreAgainstWall = false;
 IsoObject table2 = nullptr;
 IsoObject table1 = nullptr;
 bool westTable = false;
 private static HashMap<RBTableStoryBase, Integer> rbtsmap = std::make_unique<HashMap<>>();
 private static ArrayList<IsoObject> tableObjects = std::make_unique<ArrayList<>>();
 public ArrayList<HashMap<String, Integer>> fullTableMap = std::make_unique<ArrayList<>>();

 static void initStories(IsoGridSquare square, IsoObject object) {
 if (allStories.empty()) {
 allStories.add(std::make_unique<RBTSBreakfast>());
 allStories.add(std::make_unique<RBTSDinner>());
 allStories.add(std::make_unique<RBTSSoup>());
 allStories.add(std::make_unique<RBTSSewing>());
 allStories.add(std::make_unique<RBTSElectronics>());
 allStories.add(std::make_unique<RBTSFoodPreparation>());
 allStories.add(std::make_unique<RBTSButcher>());
 allStories.add(std::make_unique<RBTSSandwich>());
 allStories.add(std::make_unique<RBTSDrink>());
 }

 totalChance = 0;
 rbtsmap.clear();

 for (int int0 = 0; int0 < allStories.size(); int0++) {
 RBTableStoryBase rBTableStoryBase = allStories.get(int0);
 if (rBTableStoryBase.isValid(square, object, false) && rBTableStoryBase.isTimeValid(false) {
 totalChance = totalChance + rBTableStoryBase.chance;
 rbtsmap.put(rBTableStoryBase, rBTableStoryBase.chance);
 }
 }
 }

 static RBTableStoryBase getRandomStory(IsoGridSquare square, IsoObject object) {
 initStories(square, object);
 int int0 = Rand.Next(totalChance);
 Iterator iterator = rbtsmap.keySet().iterator();
 int int1 = 0;

 while (iterator.hasNext()) {
 RBTableStoryBase rBTableStoryBase = (RBTableStoryBase)iterator.next();
 int1 += rbtsmap.get(rBTableStoryBase);
 if (int0 < int1) {
 rBTableStoryBase.table1 = object;
 return rBTableStoryBase;
 }
 }

 return nullptr;
 }

 bool isValid(IsoGridSquare square, IsoObject object, bool boolean0) {
 if (boolean0) {
 return true;
 } else if (this->rooms != nullptr && square.getRoom() != nullptr && !this->rooms.contains(square.getRoom().getName())) {
 return false;
 } else {
 if (this->need2Tables) {
 this->table2 = this->getSecondTable(object);
 if (this->table2.empty()) {
 return false;
 }
 }

 return !this->ignoreAgainstWall || !square.getWallFull();
 }
 }

 IsoObject getSecondTable(IsoObject object0) {
 this->westTable = true;
 IsoGridSquare square0 = object0.getSquare();
 if (this->ignoreAgainstWall && square0.getWallFull()) {
 return nullptr;
 } else {
 object0.getSpriteGridObjects(tableObjects);
 IsoGridSquare square1 = square0.getAdjacentSquare(IsoDirections.W);
 IsoObject object1 = this->checkForTable(square1, object0, tableObjects);
 if (object1.empty()) {
 square1 = square0.getAdjacentSquare(IsoDirections.E);
 object1 = this->checkForTable(square1, object0, tableObjects);
 }

 if (object1.empty()) {
 this->westTable = false;
 }

 if (object1.empty()) {
 square1 = square0.getAdjacentSquare(IsoDirections.N);
 object1 = this->checkForTable(square1, object0, tableObjects);
 }

 if (object1.empty()) {
 square1 = square0.getAdjacentSquare(IsoDirections.S);
 object1 = this->checkForTable(square1, object0, tableObjects);
 }

 return object1 != nullptr && this->ignoreAgainstWall && square1.getWallFull() ? nullptr : object1;
 }
 }

 IsoObject checkForTable(IsoGridSquare square, IsoObject object0, ArrayList<IsoObject> arrayList) {
 if (square.empty()) {
 return nullptr;
 } else if (square.isSomethingTo(object0.getSquare())) {
 return nullptr;
 } else {
 for (int int0 = 0; int0 < square.getObjects().size(); int0++) {
 IsoObject object1 = square.getObjects().get(int0);
 if ((arrayList.empty() || arrayList.contains(object1)
 && object1.getProperties().isTable()
 && object1.getContainer() == nullptr
 && object1 != object0) {
 return object1;
 }
 }

 return nullptr;
 }
 }
}
} // namespace TableStories
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
