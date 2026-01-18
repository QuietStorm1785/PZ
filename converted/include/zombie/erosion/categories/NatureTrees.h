#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/ErosionData.h"
#include "zombie/erosion/obj/ErosionObj.h"
#include "zombie/erosion/obj/ErosionObjSprites.h"
#include "zombie/erosion/season/ErosionIceQueen.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include <filesystem>

namespace zombie {
namespace erosion {
namespace categories {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class NatureTrees : public ErosionCategory {
public:
 private int[][] soilRef = new int[][]{
 {2, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5},
 {1, 1, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5},
 {2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 3, 3, 4, 4, 4, 5},
 {1, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9},
 {2, 2, 1, 1, 1, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 9, 9, 9},
 {1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 7, 7, 7, 9},
 {1, 2, 8, 8, 8, 6, 6, 6, 6, 6, 6, 6, 6},
 {1, 1, 2, 2, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 6, 6, 6, 6, 6},
 {1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 8, 8, 8, 6},
 {3, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11},
 {1, 1, 3, 3, 3, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11},
 {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 10, 10, 10, 11}
 };
 private NatureTrees.TreeInit[] trees = new NatureTrees.TreeInit[]{
 new NatureTrees.TreeInit("American Holly", "e_americanholly_1", true),
 new NatureTrees.TreeInit("Canadian Hemlock", "e_canadianhemlock_1", true),
 new NatureTrees.TreeInit("Virginia Pine", "e_virginiapine_1", true),
 new NatureTrees.TreeInit("Riverbirch", "e_riverbirch_1", false),
 new NatureTrees.TreeInit("Cockspur Hawthorn", "e_cockspurhawthorn_1", false),
 new NatureTrees.TreeInit("Dogwood", "e_dogwood_1", false),
 new NatureTrees.TreeInit("Carolina Silverbell", "e_carolinasilverbell_1", false),
 new NatureTrees.TreeInit("Yellowwood", "e_yellowwood_1", false),
 new NatureTrees.TreeInit("Eastern Redbud", "e_easternredbud_1", false),
 new NatureTrees.TreeInit("Redmaple", "e_redmaple_1", false),
 new NatureTrees.TreeInit("American Linden", "e_americanlinden_1", false)
 };
 private int[] spawnChance = new int[100];
 private ArrayList<ErosionObj> objs = std::make_unique<ArrayList<>>();

 bool replaceExistingObject(IsoGridSquare square0, ErosionData.Square square1, ErosionData.Chunk var3, bool var4, bool var5) {
 int int0 = square0.getObjects().size();

 for (int int1 = int0 - 1; int1 >= 1; int1--) {
 IsoObject object = square0.getObjects().get(int1);
 IsoSprite sprite = object.getSprite();
 if (sprite != nullptr && sprite.getName() != nullptr) {
 if (sprite.getName().startsWith("jumbo_tree_01")) {
 int int2 = square1.soil;
 if (int2 < 0 || int2 >= this->soilRef.length) {
 int2 = square1.rand(square0.x, square0.y, this->soilRef.length);
 }

 int[] ints0 = this->soilRef[int2];
 int int3 = square1.noiseMainInt;
 NatureTrees.CategoryData categoryData0 = (NatureTrees.CategoryData)this->setCatModData(square1);
 categoryData0.gameObj = ints0[square1.rand(square0.x, square0.y, ints0.length)] - 1;
 categoryData0.maxStage = 5 + (int)Math.floor(int3 / 51.0F) - 1;
 categoryData0.stage = categoryData0.maxStage;
 categoryData0.spawnTime = 0;
 categoryData0.dispSeason = -1;
 ErosionObj erosionObj0 = this->objs.get(categoryData0.gameObj);
 object.setName(erosionObj0.name);
 categoryData0.hasSpawned = true;
 return true;
 }

 if (sprite.getName().startsWith("vegetation_trees")) {
 int int4 = square1.soil;
 if (int4 < 0 || int4 >= this->soilRef.length) {
 int4 = square1.rand(square0.x, square0.y, this->soilRef.length);
 }

 int[] ints1 = this->soilRef[int4];
 int int5 = square1.noiseMainInt;
 NatureTrees.CategoryData categoryData1 = (NatureTrees.CategoryData)this->setCatModData(square1);
 categoryData1.gameObj = ints1[square1.rand(square0.x, square0.y, ints1.length)] - 1;
 categoryData1.maxStage = 3 + (int)Math.floor(int5 / 51.0F) - 1;
 categoryData1.stage = categoryData1.maxStage;
 categoryData1.spawnTime = 0;
 categoryData1.dispSeason = -1;
 ErosionObj erosionObj1 = this->objs.get(categoryData1.gameObj);
 object.setName(erosionObj1.name);
 categoryData1.hasSpawned = true;
 return true;
 }

 for (int int6 = 0; int6 < this->trees.length; int6++) {
 if (sprite.getName().startsWith(this->trees[int6].tile) {
 NatureTrees.CategoryData categoryData2 = (NatureTrees.CategoryData)this->setCatModData(square1);
 categoryData2.gameObj = int6;
 categoryData2.maxStage = 3;
 categoryData2.stage = categoryData2.maxStage;
 categoryData2.spawnTime = 0;
 square0.RemoveTileObject(object);
 return true;
 }
 }
 }
 }

 return false;
 }

 bool validateSpawn(IsoGridSquare square0, ErosionData.Square square1, ErosionData.Chunk var3, bool var4, bool boolean0, bool var6) {
 if (square0.getObjects().size() > (boolean0 ? 2 : 1) {
 return false;
 } else if (square1.soil >= 0 && square1.soil < this->soilRef.length) {
 int[] ints = this->soilRef[square1.soil];
 int int0 = square1.noiseMainInt;
 int int1 = this->spawnChance[int0];
 if (int1 > 0 && square1.rand(square0.x, square0.y, 101) < int1) {
 NatureTrees.CategoryData categoryData = (NatureTrees.CategoryData)this->setCatModData(square1);
 categoryData.gameObj = ints[square1.rand(square0.x, square0.y, ints.length)] - 1;
 categoryData.maxStage = 2 + (int)Math.floor((int0 - 50) / 17) - 1;
 categoryData.stage = 0;
 categoryData.spawnTime = 30 + (100 - int0);
 return true;
 } else {
 return false;
 }
 } else {
 return false;
 }
 }

 void update(IsoGridSquare square1, ErosionData.Square square0, ErosionCategory.Data data, ErosionData.Chunk var4, int int0) {
 NatureTrees.CategoryData categoryData = (NatureTrees.CategoryData)data;
 if (int0 >= categoryData.spawnTime && !categoryData.doNothing) {
 if (categoryData.gameObj >= 0 && categoryData.gameObj < this->objs.size()) {
 ErosionObj erosionObj = this->objs.get(categoryData.gameObj);
 int int1 = categoryData.maxStage;
 int int2 = (int)Math.floor((int0 - categoryData.spawnTime) / (erosionObj.cycleTime / (int1 + 1.0F);
 if (int2 < data.stage) {
 int2 = data.stage;
 }

 if (int2 > int1) {
 int2 = int1;
 }

 bool boolean0 = true;
 int int3 = this->currentSeason(square0.magicNum, erosionObj);
 bool boolean1 = false;
 this->updateObj(square0, data, square1, erosionObj, boolean0, int2, int3, boolean1);
 } else {
 this->clearCatModData(square0);
 }
 }
 }

 void init() {
 for (int int0 = 0; int0 < 100; int0++) {
 this->spawnChance[int0] = int0 >= 50 ? (int)this->clerp((int0 - 50) / 50.0F, 0.0F, 90.0F) : 0;
 }

 int[] ints = new int[]{0, 5, 1, 2, 3, 4};
 this->seasonDisp[5].season1 = 0;
 this->seasonDisp[5].season2 = 0;
 this->seasonDisp[5].split = false;
 this->seasonDisp[1].season1 = 1;
 this->seasonDisp[1].season2 = 0;
 this->seasonDisp[1].split = false;
 this->seasonDisp[2].season1 = 2;
 this->seasonDisp[2].season2 = 3;
 this->seasonDisp[2].split = true;
 this->seasonDisp[4].season1 = 4;
 this->seasonDisp[4].season2 = 0;
 this->seasonDisp[4].split = true;
 std::string string0 = nullptr;
 ErosionIceQueen erosionIceQueen = ErosionIceQueen.instance;

 for (int int1 = 0; int1 < this->trees.length; int1++) {
 std::string string1 = this->trees[int1].name;
 std::string string2 = this->trees[int1].tile;
 bool boolean0 = !this->trees[int1].evergreen;
 ErosionObjSprites erosionObjSprites = new ErosionObjSprites(6, string1, true, false, boolean0);

 for (int int2 = 0; int2 < 6; int2++) {
 for (int int3 = 0; int3 < ints.length; int3++) {
 if (int2 > 3) {
 int int4 = 0 + int3 * 2 + (int2 - 4);
 if (int3 == 0) {
 string0 = string2.replace("_1", "JUMBO_1") + "_" + int4;
 erosionObjSprites.setBase(int2, string0, 0);
 } else if (int3 == 1) {
 erosionIceQueen.addSprite(string0, string2.replace("_1", "JUMBO_1") + "_" + int4);
 } else if (boolean0) {
 erosionObjSprites.setChildSprite(int2, string2.replace("_1", "JUMBO_1") + "_" + int4, ints[int3]);
 }
 } else {
 int int5 = 0 + int3 * 4 + int2;
 if (int3 == 0) {
 string0 = string2 + "_" + int5;
 erosionObjSprites.setBase(int2, string0, 0);
 } else if (int3 == 1) {
 erosionIceQueen.addSprite(string0, string2 + "_" + int5);
 } else if (boolean0) {
 erosionObjSprites.setChildSprite(int2, string2 + "_" + int5, ints[int3]);
 }
 }
 }
 }

 ErosionObj erosionObj = new ErosionObj(erosionObjSprites, 60, 0.0F, 0.0F, true);
 this->objs.add(erosionObj);
 }
 }

 protected ErosionCategory.Data allocData() {
 return new NatureTrees.CategoryData();
 }

 void getObjectNames(ArrayList<String> arrayList) {
 for (int int0 = 0; int0 < this->objs.size(); int0++) {
 if (this->objs.get(int0).name != nullptr && !arrayList.contains(this->objs.get(int0).name) {
 arrayList.add(this->objs.get(int0).name);
 }
 }
 }

 private static class CategoryData extends ErosionCategory.Data {
 int gameObj;
 int maxStage;
 int spawnTime;

 void save(ByteBuffer byteBuffer) {
 super.save(byteBuffer);
 byteBuffer.put((byte)this->gameObj);
 byteBuffer.put((byte)this->maxStage);
 byteBuffer.putShort((short)this->spawnTime);
 }

 void load(ByteBuffer byteBuffer, int int0) {
 super.load(byteBuffer, int0);
 this->gameObj = byteBuffer.get();
 this->maxStage = byteBuffer.get();
 this->spawnTime = byteBuffer.getShort();
 }
 }

 private class TreeInit {
 std::string name;
 std::string tile;
 bool evergreen;

 public TreeInit(const std::string& string0, const std::string& string1, bool boolean0) {
 this->name = string0;
 this->tile = string1;
 this->evergreen = boolean0;
 }
 }
}
} // namespace categories
} // namespace erosion
} // namespace zombie
