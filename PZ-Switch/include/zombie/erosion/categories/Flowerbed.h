#pragma once
#include "zombie/erosion/ErosionData.h"
#include "zombie/erosion/ErosionMain.h"
#include "zombie/erosion/obj/ErosionObj.h"
#include "zombie/erosion/obj/ErosionObjSprites.h"
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

class Flowerbed : public ErosionCategory {
public:
private
 int[] tileID =
 new int[]{16, 17, 18, 19, 20, 21, 22, 23, 28, 29, 30, 31};
private
 ArrayList<ErosionObj> objs = std::make_unique<ArrayList<>>();

 bool replaceExistingObject(IsoGridSquare square0, ErosionData.Square square1,
 ErosionData.Chunk var3, bool var4, bool var5) {
 int int0 = square0.getObjects().size();

 for (int int1 = int0 - 1; int1 >= 0; int1--) {
 IsoSprite sprite = square0.getObjects().get(int1).getSprite();
 if (sprite != nullptr && sprite.getName() != nullptr) {
 if (sprite.getName().startsWith("f_flowerbed_1")) {
 int int2 =
 Integer.parseInt(sprite.getName().replace("f_flowerbed_1_", ""));
 if (int2 <= 23) {
 if (int2 >= 12) {
 int2 -= 12;
 }

 Flowerbed.CategoryData categoryData0 =
 (Flowerbed.CategoryData)this->setCatModData(square1);
 categoryData0.hasSpawned = true;
 categoryData0.gameObj = int2;
 categoryData0.dispSeason = -1;
 ErosionObj erosionObj0 = this->objs.get(categoryData0.gameObj);
 square0.getObjects().get(int1).setName(erosionObj0.name);
 return true;
 }
 }

 if (sprite.getName().startsWith("vegetation_ornamental_01")) {
 int int3 = Integer.parseInt(
 sprite.getName().replace("vegetation_ornamental_01_", ""));

 for (int int4 = 0; int4 < this->tileID.length; int4++) {
 if (this->tileID[int4] == int3) {
 Flowerbed.CategoryData categoryData1 =
 (Flowerbed.CategoryData)this->setCatModData(square1);
 categoryData1.hasSpawned = true;
 categoryData1.gameObj = int4;
 categoryData1.dispSeason = -1;
 ErosionObj erosionObj1 = this->objs.get(categoryData1.gameObj);
 square0.getObjects().get(int1).setName(erosionObj1.name);
 return true;
 }
 }
 }
 }
 }

 return false;
 }

 bool validateSpawn(IsoGridSquare var1, ErosionData.Square var2,
 ErosionData.Chunk var3, bool var4, bool var5, bool var6) {
 return false;
 }

 void update(IsoGridSquare square0, ErosionData.Square square1,
 ErosionCategory.Data data, ErosionData.Chunk var4, int var5) {
 Flowerbed.CategoryData categoryData = (Flowerbed.CategoryData)data;
 if (!categoryData.doNothing) {
 if (categoryData.gameObj >= 0 &&
 categoryData.gameObj < this->objs.size()) {
 ErosionObj erosionObj = this->objs.get(categoryData.gameObj);
 bool boolean0 = false;
 uint8_t byte0 = 0;
 int int0 = ErosionMain.getInstance().getSeasons().getSeason();
 bool boolean1 = false;
 if (int0 == 5) {
 IsoObject object = erosionObj.getObject(square0, false);
 if (object != nullptr) {
 object.setSprite(
 ErosionMain.getInstance().getSpriteManager().getSprite(
 "blends_natural_01_64"));
 object.setName(nullptr);
 }

 this->clearCatModData(square1);
 } else {
 this->updateObj(square1, data, square0, erosionObj, boolean0, byte0,
 int0, boolean1);
 }
 } else {
 this->clearCatModData(square1);
 }
 }
 }

 void init() {
 std::string string = "vegetation_ornamental_01_";

 for (int int0 = 0; int0 < this->tileID.length; int0++) {
 ErosionObjSprites erosionObjSprites =
 new ErosionObjSprites(1, "Flowerbed", false, false, false);
 erosionObjSprites.setBase(0, string + this->tileID[int0], 1);
 erosionObjSprites.setBase(0, string + this->tileID[int0], 2);
 erosionObjSprites.setBase(0, string + (this->tileID[int0] + 16), 4);
 ErosionObj erosionObj =
 new ErosionObj(erosionObjSprites, 30, 0.0F, 0.0F, false);
 this->objs.add(erosionObj);
 }
 }

protected
 ErosionCategory.Data allocData() { return new Flowerbed.CategoryData(); }

 void getObjectNames(ArrayList<String> arrayList) {
 for (int int0 = 0; int0 < this->objs.size(); int0++) {
 if (this->objs.get(int0).name != nullptr &&
 !arrayList.contains(this->objs.get(int0).name) {
 arrayList.add(this->objs.get(int0).name);
 }
 }
 }

private
 static class CategoryData extends ErosionCategory.Data {
 int gameObj;

 void save(ByteBuffer byteBuffer) {
 super.save(byteBuffer);
 byteBuffer.put((byte)this->gameObj);
 }

 void load(ByteBuffer byteBuffer, int int0) {
 super.load(byteBuffer, int0);
 this->gameObj = byteBuffer.get();
 }
 }
}
} // namespace categories
} // namespace erosion
} // namespace zombie
