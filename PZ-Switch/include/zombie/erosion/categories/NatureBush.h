#pragma once
#include "zombie/erosion/ErosionData.h"
#include "zombie/erosion/obj/ErosionObj.h"
#include "zombie/erosion/obj/ErosionObjSprites.h"
#include "zombie/erosion/season/ErosionIceQueen.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace erosion {
namespace categories {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class NatureBush : public ErosionCategory {
public:
private
 int[][] soilRef =
 new int[][]{{11, 11, 12, 13},
 {5, 5, 7, 8, 11, 11, 12, 13, 11, 11, 12, 13},
 {5, 5, 7, 8, 5, 5, 7, 8, 11, 11, 12, 13},
 {1, 1, 4, 5},
 {5, 5, 7, 8, 1, 1, 4, 5, 1, 1, 4, 5},
 {5, 5, 7, 8, 5, 5, 7, 8, 1, 1, 4, 5},
 {9, 10, 14, 15},
 {5, 5, 7, 8, 9, 10, 14, 15, 9, 10, 14, 15},
 {5, 5, 7, 8, 5, 5, 7, 8, 9, 10, 14, 15},
 {2, 3, 16, 16},
 {5, 5, 7, 8, 2, 3, 16, 16, 2, 3, 16, 16},
 {5, 5, 7, 8, 5, 5, 7, 8, 2, 3, 16, 16}};
private
 ArrayList<ErosionObj> objs = std::make_unique<ArrayList<>>();
private
 int[] spawnChance = new int[100];
private
 NatureBush.BushInit[] bush = new NatureBush.BushInit[]{
 new NatureBush.BushInit("Spicebush", 0.05F, 0.35F, false),
 new NatureBush.BushInit("Ninebark", 0.65F, 0.75F, true),
 new NatureBush.BushInit("Ninebark", 0.65F, 0.75F, true),
 new NatureBush.BushInit("Blueberry", 0.4F, 0.5F, true),
 new NatureBush.BushInit("Blackberry", 0.4F, 0.5F, true),
 new NatureBush.BushInit("Piedmont azalea", 0.0F, 0.15F, true),
 new NatureBush.BushInit("Piedmont azalea", 0.0F, 0.15F, true),
 new NatureBush.BushInit("Arrowwood viburnum", 0.3F, 0.8F, true),
 new NatureBush.BushInit("Red chokeberry", 0.9F, 1.0F, true),
 new NatureBush.BushInit("Red chokeberry", 0.9F, 1.0F, true),
 new NatureBush.BushInit("Beautyberry", 0.7F, 0.85F, true),
 new NatureBush.BushInit("New jersey tea", 0.4F, 0.8F, true),
 new NatureBush.BushInit("New jersey tea", 0.4F, 0.8F, true),
 new NatureBush.BushInit("Wild hydrangea", 0.2F, 0.35F, true),
 new NatureBush.BushInit("Wild hydrangea", 0.2F, 0.35F, true),
 new NatureBush.BushInit("Shrubby St. John's wort", 0.35F, 0.75F, true)};

 bool replaceExistingObject(IsoGridSquare square0, ErosionData.Square square1,
 ErosionData.Chunk var3, bool var4, bool var5) {
 int int0 = square0.getObjects().size();
 bool boolean0 = false;

 for (int int1 = int0 - 1; int1 >= 1; int1--) {
 IsoObject object = square0.getObjects().get(int1);
 IsoSprite sprite = object.getSprite();
 if (sprite != nullptr && sprite.getName() != nullptr) {
 if (sprite.getName().startsWith("vegetation_foliage")) {
 int int2 = square1.soil;
 if (int2 < 0 || int2 >= this->soilRef.length) {
 int2 = square1.rand(square0.x, square0.y, this->soilRef.length);
 }

 int[] ints = this->soilRef[int2];
 int int3 = square1.noiseMainInt;
 NatureBush.CategoryData categoryData0 =
 (NatureBush.CategoryData)this->setCatModData(square1);
 categoryData0.gameObj =
 ints[square1.rand(square0.x, square0.y, ints.length)] - 1;
 categoryData0.maxStage = (int)Math.floor(int3 / 60.0F);
 categoryData0.stage = categoryData0.maxStage;
 categoryData0.spawnTime = 0;
 square0.RemoveTileObject(object);
 boolean0 = true;
 }

 if (sprite.getName().startsWith("f_bushes_1_")) {
 int int4 =
 Integer.parseInt(sprite.getName().replace("f_bushes_1_", ""));
 NatureBush.CategoryData categoryData1 =
 (NatureBush.CategoryData)this->setCatModData(square1);
 categoryData1.gameObj = int4 % 16;
 categoryData1.maxStage = 1;
 categoryData1.stage = categoryData1.maxStage;
 categoryData1.spawnTime = 0;
 square0.RemoveTileObject(object);
 boolean0 = true;
 }
 }
 }

 return boolean0;
 }

 bool validateSpawn(IsoGridSquare square0, ErosionData.Square square1,
 ErosionData.Chunk var3, bool var4, bool boolean0,
 bool var6) {
 if (square0.getObjects().size() > (boolean0 ? 2 : 1) {
 return false;
 } else if (square1.soil >= 0 && square1.soil < this->soilRef.length) {
 int[] ints = this->soilRef[square1.soil];
 int int0 = square1.noiseMainInt;
 int int1 = square1.rand(square0.x, square0.y, 101);
 if (int1 < this->spawnChance[int0]) {
 NatureBush.CategoryData categoryData =
 (NatureBush.CategoryData)this->setCatModData(square1);
 categoryData.gameObj =
 ints[square1.rand(square0.x, square0.y, ints.length)] - 1;
 categoryData.maxStage = (int)Math.floor(int0 / 60.0F);
 categoryData.stage = 0;
 categoryData.spawnTime = 100 - int0;
 return true;
 } else {
 return false;
 }
 } else {
 return false;
 }
 }

 void update(IsoGridSquare square1, ErosionData.Square square0,
 ErosionCategory.Data data, ErosionData.Chunk var4, int int0) {
 NatureBush.CategoryData categoryData = (NatureBush.CategoryData)data;
 if (int0 >= categoryData.spawnTime && !categoryData.doNothing) {
 if (categoryData.gameObj >= 0 &&
 categoryData.gameObj < this->objs.size()) {
 ErosionObj erosionObj = this->objs.get(categoryData.gameObj);
 int int1 = categoryData.maxStage;
 int int2 = (int)Math.floor((int0 - categoryData.spawnTime) /
 (erosionObj.cycleTime / (int1 + 1.0F));
 if (int2 < categoryData.stage) {
 int2 = categoryData.stage;
 }

 if (int2 > int1) {
 int2 = int1;
 }

 int int3 = this->currentSeason(square0.magicNum, erosionObj);
 bool boolean0 = this->currentBloom(square0.magicNum, erosionObj);
 bool boolean1 = false;
 this->updateObj(square0, data, square1, erosionObj, boolean1, int2, int3,
 boolean0);
 } else {
 categoryData.doNothing = true;
 }
 }
 }

 void init() {
 for (int int0 = 0; int0 < 100; int0++) {
 if (int0 >= 45 && int0 < 60) {
 this->spawnChance[int0] =
 (int)this->clerp((int0 - 45) / 15.0F, 0.0F, 20.0F);
 }

 if (int0 >= 60 && int0 < 90) {
 this->spawnChance[int0] =
 (int)this->clerp((int0 - 60) / 30.0F, 20.0F, 0.0F);
 }
 }

 this->seasonDisp[5].season1 = 0;
 this->seasonDisp[5].season2 = 0;
 this->seasonDisp[5].split = false;
 this->seasonDisp[1].season1 = 1;
 this->seasonDisp[1].season2 = 0;
 this->seasonDisp[1].split = false;
 this->seasonDisp[2].season1 = 2;
 this->seasonDisp[2].season2 = 2;
 this->seasonDisp[2].split = true;
 this->seasonDisp[4].season1 = 4;
 this->seasonDisp[4].season2 = 0;
 this->seasonDisp[4].split = true;
 ErosionIceQueen erosionIceQueen = ErosionIceQueen.instance;
 std::string string = "f_bushes_1_";

 for (int int1 = 1; int1 <= this->bush.length; int1++) {
 int int2 = int1 - 1;
 int int3 = int2 - (int)Math.floor(int2 / 8.0F) * 8;
 NatureBush.BushInit bushInit = this->bush[int2];
 ErosionObjSprites erosionObjSprites = new ErosionObjSprites(
 2, bushInit.name, true, bushInit.hasFlower, true);
 int int4 = 0 + int3;
 int int5 = int4 + 16;
 int int6 = int5 + 16;
 int int7 = int6 + 16;
 int int8 = 64 + int2;
 int int9 = int8 + 16;
 erosionObjSprites.setBase(0, string + int4, 0);
 erosionObjSprites.setBase(1, string + (int4 + 8), 0);
 erosionIceQueen.addSprite(string + int4, string + int5);
 erosionIceQueen.addSprite(string + (int4 + 8), string + (int5 + 8);
 erosionObjSprites.setChildSprite(0, string + int6, 1);
 erosionObjSprites.setChildSprite(1, string + (int6 + 8), 1);
 erosionObjSprites.setChildSprite(0, string + int7, 4);
 erosionObjSprites.setChildSprite(1, string + (int7 + 8), 4);
 erosionObjSprites.setChildSprite(0, string + int8, 2);
 erosionObjSprites.setChildSprite(1, string + (int8 + 32), 2);
 if (bushInit.hasFlower) {
 erosionObjSprites.setFlower(0, string + int9);
 erosionObjSprites.setFlower(1, string + (int9 + 32);
 }

 float float0 = bushInit.hasFlower ? bushInit.bloomstart : 0.0F;
 float float1 = bushInit.hasFlower ? bushInit.bloomend : 0.0F;
 ErosionObj erosionObj =
 new ErosionObj(erosionObjSprites, 60, float0, float1, true);
 this->objs.add(erosionObj);
 }
 }

protected
 ErosionCategory.Data allocData() { return new NatureBush.CategoryData(); }

 void getObjectNames(ArrayList<String> arrayList) {
 for (int int0 = 0; int0 < this->objs.size(); int0++) {
 if (this->objs.get(int0).name != nullptr &&
 !arrayList.contains(this->objs.get(int0).name) {
 arrayList.add(this->objs.get(int0).name);
 }
 }
 }

class BushInit {
 std::string name;
 float bloomstart;
 float bloomend;
 bool hasFlower;

 public
 BushInit(const std::string &string, float float0, float float1,
 bool boolean0) {
 this->name = string;
 this->bloomstart = float0;
 this->bloomend = float1;
 this->hasFlower = boolean0;
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
}
} // namespace categories
} // namespace erosion
} // namespace zombie
