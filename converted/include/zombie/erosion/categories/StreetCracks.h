#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/ErosionData.h"
#include "zombie/erosion/obj/ErosionObj.h"
#include "zombie/erosion/obj/ErosionObjOverlay.h"
#include "zombie/erosion/obj/ErosionObjOverlaySprites.h"
#include "zombie/erosion/obj/ErosionObjSprites.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include <filesystem>

namespace zombie {
namespace erosion {
namespace categories {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class StreetCracks : public ErosionCategory {
public:
 private ArrayList<ErosionObj> objs = std::make_unique<ArrayList<>>();
 private ArrayList<ErosionObjOverlay> crackObjs = std::make_unique<ArrayList<>>();
 private int[] spawnChance = new int[100];

 bool replaceExistingObject(IsoGridSquare var1, ErosionData.Square var2, ErosionData.Chunk var3, bool var4, bool var5) {
 return false;
 }

 bool validateSpawn(IsoGridSquare square1, ErosionData.Square square0, ErosionData.Chunk var3, bool var4, bool var5, bool var6) {
 int int0 = square0.noiseMainInt;
 int int1 = this->spawnChance[int0];
 if (int1 == 0) {
 return false;
 } else if (square0.rand(square1.x, square1.y, 101) >= int1) {
 return false;
 } else {
 StreetCracks.CategoryData categoryData = (StreetCracks.CategoryData)this->setCatModData(square0);
 categoryData.gameObj = square0.rand(square1.x, square1.y, this->crackObjs.size());
 categoryData.maxStage = int0 > 65 ? 2 : (int0 > 55 ? 1 : 0);
 categoryData.stage = 0;
 categoryData.spawnTime = 50 + (100 - int0);
 if (square0.magicNum > 0.5F) {
 categoryData.hasGrass = true;
 }

 return true;
 }
 }

 void update(IsoGridSquare square0, ErosionData.Square square1, ErosionCategory.Data data, ErosionData.Chunk var4, int int0) {
 StreetCracks.CategoryData categoryData = (StreetCracks.CategoryData)data;
 if (int0 >= categoryData.spawnTime && !categoryData.doNothing) {
 IsoObject object = square0.getFloor();
 if (categoryData.gameObj >= 0 && categoryData.gameObj < this->crackObjs.size() && object != nullptr) {
 ErosionObjOverlay erosionObjOverlay = this->crackObjs.get(categoryData.gameObj);
 int int1 = categoryData.maxStage;
 int int2 = (int)Math.floor((int0 - categoryData.spawnTime) / (erosionObjOverlay.cycleTime / (int1 + 1.0F));
 if (int2 < categoryData.stage) {
 int2 = categoryData.stage;
 }

 if (int2 >= erosionObjOverlay.stages) {
 int2 = erosionObjOverlay.stages - 1;
 }

 if (int2 != categoryData.stage) {
 int int3 = categoryData.curID;
 int int4 = erosionObjOverlay.setOverlay(object, int3, int2, 0, 0.0F);
 if (int4 >= 0) {
 categoryData.curID = int4;
 }

 categoryData.stage = int2;
 } else if (!categoryData.hasGrass && int2 == erosionObjOverlay.stages - 1) {
 categoryData.doNothing = true;
 }

 if (categoryData.hasGrass) {
 ErosionObj erosionObj = this->objs.get(categoryData.gameObj);
 if (erosionObj != nullptr) {
 int int5 = this->currentSeason(square1.magicNum, erosionObj);
 bool boolean0 = false;
 bool boolean1 = false;
 this->updateObj(square1, data, square0, erosionObj, boolean0, int2, int5, boolean1);
 }
 }
 } else {
 categoryData.doNothing = true;
 }
 }
 }

 void init() {
 for (int int0 = 0; int0 < 100; int0++) {
 this->spawnChance[int0] = int0 >= 40 ? (int)this->clerp((int0 - 40) / 60.0F, 0.0F, 60.0F) : 0;
 }

 this->seasonDisp[5].season1 = 5;
 this->seasonDisp[5].season2 = 0;
 this->seasonDisp[5].split = false;
 this->seasonDisp[1].season1 = 1;
 this->seasonDisp[1].season2 = 0;
 this->seasonDisp[1].split = false;
 this->seasonDisp[2].season1 = 2;
 this->seasonDisp[2].season2 = 4;
 this->seasonDisp[2].split = true;
 this->seasonDisp[4].season1 = 4;
 this->seasonDisp[4].season2 = 5;
 this->seasonDisp[4].split = true;
 std::string string = "d_streetcracks_1_";
 int[] ints = new int[]{5, 1, 2, 4};

 for (int int1 = 0; int1 <= 7; int1++) {
 ErosionObjOverlaySprites erosionObjOverlaySprites = new ErosionObjOverlaySprites(3, "StreeCracks");
 ErosionObjSprites erosionObjSprites = new ErosionObjSprites(3, "CrackGrass", false, false, false);

 for (int int2 = 0; int2 <= 2; int2++) {
 for (int int3 = 0; int3 <= ints.length; int3++) {
 int int4 = int3 * 24 + int2 * 8 + int1;
 if (int3 == 0) {
 erosionObjOverlaySprites.setSprite(int2, string + int4, 0);
 } else {
 erosionObjSprites.setBase(int2, string + int4, ints[int3 - 1]);
 }
 }
 }

 this->crackObjs.add(new ErosionObjOverlay(erosionObjOverlaySprites, 60, false);
 this->objs.add(new ErosionObj(erosionObjSprites, 60, 0.0F, 0.0F, false);
 }
 }

 protected ErosionCategory.Data allocData() {
 return new StreetCracks.CategoryData();
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
 int curID = -999999;
 bool hasGrass;

 void save(ByteBuffer byteBuffer) {
 super.save(byteBuffer);
 byteBuffer.put((byte)this->gameObj);
 byteBuffer.put((byte)this->maxStage);
 byteBuffer.putShort((short)this->spawnTime);
 byteBuffer.putInt(this->curID);
 byteBuffer.put((byte)(this->hasGrass ? 1 : 0);
 }

 void load(ByteBuffer byteBuffer, int int0) {
 super.load(byteBuffer, int0);
 this->gameObj = byteBuffer.get();
 this->maxStage = byteBuffer.get();
 this->spawnTime = byteBuffer.getShort();
 this->curID = byteBuffer.getInt();
 this->hasGrass = byteBuffer.get() == 1;
 }
 }
}
} // namespace categories
} // namespace erosion
} // namespace zombie
