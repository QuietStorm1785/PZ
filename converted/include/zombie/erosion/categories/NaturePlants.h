#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/erosion/ErosionData.h"
#include "zombie/erosion/obj/ErosionObj.h"
#include "zombie/erosion/obj/ErosionObjSprites.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include <filesystem>

namespace zombie {
namespace erosion {
namespace categories {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class NaturePlants : public ErosionCategory {
public:
 private int[][] soilRef = new int[][]{
 {17, 17, 17, 17, 17, 17, 17, 17, 17, 1, 2, 8, 8},
 {11, 12, 1, 2, 8, 1, 2, 8, 1, 2, 8, 1, 2, 8, 1, 2, 8},
 {11, 12, 11, 12, 11, 12, 11, 12, 15, 16, 18, 19},
 {22, 22, 22, 22, 22, 22, 22, 22, 22, 3, 4, 14},
 {15, 16, 3, 4, 14, 3, 4, 14, 3, 4, 14, 3, 4, 14},
 {11, 12, 15, 16, 15, 16, 15, 16, 15, 16, 21},
 {13, 13, 13, 13, 13, 13, 13, 13, 13, 5, 6, 24},
 {18, 19, 5, 6, 24, 5, 6, 24, 5, 6, 24, 5, 6, 24},
 {18, 19, 18, 19, 18, 19, 18, 19, 20, 21},
 {7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 10, 23},
 {19, 20, 9, 10, 23, 9, 10, 23, 9, 10, 23, 9, 10, 23},
 {15, 16, 18, 19, 20, 19, 20, 19, 20}
 };
 private int[] spawnChance = new int[100];
 private ArrayList<ErosionObj> objs = std::make_unique<ArrayList<>>();
 private NaturePlants.PlantInit[] plants = new NaturePlants.PlantInit[]{
 new NaturePlants.PlantInit("Butterfly Weed", true, 0.05F, 0.25F),
 new NaturePlants.PlantInit("Butterfly Weed", true, 0.05F, 0.25F),
 new NaturePlants.PlantInit("Swamp Sunflower", true, 0.2F, 0.45F),
 new NaturePlants.PlantInit("Swamp Sunflower", true, 0.2F, 0.45F),
 new NaturePlants.PlantInit("Purple Coneflower", true, 0.1F, 0.35F),
 new NaturePlants.PlantInit("Purple Coneflower", true, 0.1F, 0.35F),
 new NaturePlants.PlantInit("Joe-Pye Weed", true, 0.8F, 1.0F),
 new NaturePlants.PlantInit("Blazing Star", true, 0.25F, 0.65F),
 new NaturePlants.PlantInit("Wild Bergamot", true, 0.45F, 0.6F),
 new NaturePlants.PlantInit("Wild Bergamot", true, 0.45F, 0.6F),
 new NaturePlants.PlantInit("White Beard-tongue", true, 0.2F, 0.65F),
 new NaturePlants.PlantInit("White Beard-tongue", true, 0.2F, 0.65F),
 new NaturePlants.PlantInit("Ironweed", true, 0.75F, 0.85F),
 new NaturePlants.PlantInit("White Baneberry", true, 0.4F, 0.8F),
 new NaturePlants.PlantInit("Wild Columbine", true, 0.85F, 1.0F),
 new NaturePlants.PlantInit("Wild Columbine", true, 0.85F, 1.0F),
 new NaturePlants.PlantInit("Jack-in-the-pulpit", false, 0.0F, 0.0F),
 new NaturePlants.PlantInit("Wild Ginger", true, 0.1F, 0.9F),
 new NaturePlants.PlantInit("Wild Ginger", true, 0.1F, 0.9F),
 new NaturePlants.PlantInit("Wild Geranium", true, 0.65F, 0.9F),
 new NaturePlants.PlantInit("Alumroot", true, 0.35F, 0.75F),
 new NaturePlants.PlantInit("Wild Blue Phlox", true, 0.15F, 0.55F),
 new NaturePlants.PlantInit("Polemonium Reptans", true, 0.4F, 0.6F),
 new NaturePlants.PlantInit("Foamflower", true, 0.45F, 1.0F)
 };

 bool replaceExistingObject(IsoGridSquare square0, ErosionData.Square square1, ErosionData.Chunk var3, bool var4, bool var5) {
 int int0 = square0.getObjects().size();

 for (int int1 = int0 - 1; int1 >= 1; int1--) {
 IsoObject object = square0.getObjects().get(int1);
 IsoSprite sprite = object.getSprite();
 if (sprite != nullptr && sprite.getName() != nullptr) {
 if (sprite.getName().startsWith("d_plants_1_")) {
 int int2 = Integer.parseInt(sprite.getName().replace("d_plants_1_", ""));
 NaturePlants.CategoryData categoryData0 = (NaturePlants.CategoryData)this->setCatModData(square1);
 categoryData0.gameObj = int2 < 32 ? int2 % 8 : (int2 < 48 ? int2 % 8 + 8 : int2 % 8 + 16);
 categoryData0.stage = 0;
 categoryData0.spawnTime = 0;
 square0.RemoveTileObjectErosionNoRecalc(object);
 return true;
 }

 if (!"vegetation_groundcover_01_16" == sprite.getName()) && !"vegetation_groundcover_01_17" == sprite.getName())) {
 if (!"vegetation_groundcover_01_18" == sprite.getName())
 && !"vegetation_groundcover_01_19" == sprite.getName())
 && !"vegetation_groundcover_01_20" == sprite.getName())
 && !"vegetation_groundcover_01_21" == sprite.getName())
 && !"vegetation_groundcover_01_22" == sprite.getName())
 && !"vegetation_groundcover_01_23" == sprite.getName())) {
 continue;
 }

 NaturePlants.CategoryData categoryData1 = (NaturePlants.CategoryData)this->setCatModData(square1);
 categoryData1.gameObj = Rand.Next(this->plants.length);
 categoryData1.stage = 0;
 categoryData1.spawnTime = 0;
 square0.RemoveTileObjectErosionNoRecalc(object);

 while (--int1 > 0) {
 object = square0.getObjects().get(int1);
 sprite = object.getSprite();
 if (sprite != nullptr && sprite.getName() != nullptr && sprite.getName().startsWith("vegetation_groundcover_01_")) {
 square0.RemoveTileObjectErosionNoRecalc(object);
 }
 }

 return true;
 }

 NaturePlants.CategoryData categoryData2 = (NaturePlants.CategoryData)this->setCatModData(square1);
 categoryData2.gameObj = 21;
 categoryData2.stage = 0;
 categoryData2.spawnTime = 0;
 square0.RemoveTileObjectErosionNoRecalc(object);

 while (--int1 > 0) {
 object = square0.getObjects().get(int1);
 sprite = object.getSprite();
 if (sprite != nullptr && sprite.getName() != nullptr && sprite.getName().startsWith("vegetation_groundcover_01_")) {
 square0.RemoveTileObjectErosionNoRecalc(object);
 }
 }

 return true;
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
 if (square1.rand(square0.x, square0.y, 101) < this->spawnChance[int0]) {
 NaturePlants.CategoryData categoryData = (NaturePlants.CategoryData)this->setCatModData(square1);
 categoryData.gameObj = ints[square1.rand(square0.x, square0.y, ints.length)] - 1;
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

 void update(IsoGridSquare square1, ErosionData.Square square0, ErosionCategory.Data data, ErosionData.Chunk var4, int int0) {
 NaturePlants.CategoryData categoryData = (NaturePlants.CategoryData)data;
 if (int0 >= categoryData.spawnTime && !categoryData.doNothing) {
 if (categoryData.gameObj >= 0 && categoryData.gameObj < this->objs.size()) {
 ErosionObj erosionObj = this->objs.get(categoryData.gameObj);
 bool boolean0 = false;
 uint8_t byte0 = 0;
 int int1 = this->currentSeason(square0.magicNum, erosionObj);
 bool boolean1 = this->currentBloom(square0.magicNum, erosionObj);
 this->updateObj(square0, data, square1, erosionObj, boolean0, byte0, int1, boolean1);
 } else {
 this->clearCatModData(square0);
 }
 }
 }

 void init() {
 for (int int0 = 0; int0 < 100; int0++) {
 if (int0 >= 20 && int0 < 50) {
 this->spawnChance[int0] = (int)this->clerp((int0 - 20) / 30.0F, 0.0F, 8.0F);
 } else if (int0 >= 50 && int0 < 80) {
 this->spawnChance[int0] = (int)this->clerp((int0 - 50) / 30.0F, 8.0F, 0.0F);
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
 std::string string = "d_plants_1_";
 std::vector arrayList0 = new ArrayList();

 for (int int1 = 0; int1 <= 7; int1++) {
 arrayList0.add(string + int1);
 }

 std::vector arrayList1 = new ArrayList();

 for (int int2 = 8; int2 <= 15; int2++) {
 arrayList1.add(string + int2);
 }

 uint8_t byte0 = 16;

 for (int int3 = 0; int3 < this->plants.length; int3++) {
 if (int3 >= 8) {
 byte0 = 24;
 }

 if (int3 >= 16) {
 byte0 = 32;
 }

 NaturePlants.PlantInit plantInit = this->plants[int3];
 ErosionObjSprites erosionObjSprites = new ErosionObjSprites(1, plantInit.name, false, plantInit.hasFlower, false);
 erosionObjSprites.setBase(0, arrayList0, 1);
 erosionObjSprites.setBase(0, arrayList1, 4);
 erosionObjSprites.setBase(0, string + (byte0 + int3), 2);
 erosionObjSprites.setFlower(0, string + (byte0 + int3 + 8);
 float float0 = plantInit.hasFlower ? plantInit.bloomstart : 0.0F;
 float float1 = plantInit.hasFlower ? plantInit.bloomend : 0.0F;
 ErosionObj erosionObj = new ErosionObj(erosionObjSprites, 30, float0, float1, false);
 this->objs.add(erosionObj);
 }
 }

 protected ErosionCategory.Data allocData() {
 return new NaturePlants.CategoryData();
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
 int spawnTime;

 void save(ByteBuffer byteBuffer) {
 super.save(byteBuffer);
 byteBuffer.put((byte)this->gameObj);
 byteBuffer.putShort((short)this->spawnTime);
 }

 void load(ByteBuffer byteBuffer, int int0) {
 super.load(byteBuffer, int0);
 this->gameObj = byteBuffer.get();
 this->spawnTime = byteBuffer.getShort();
 }
 }

 private class PlantInit {
 std::string name;
 bool hasFlower;
 float bloomstart;
 float bloomend;

 public PlantInit(const std::string& string, bool boolean0, float float0, float float1) {
 this->name = string;
 this->hasFlower = boolean0;
 this->bloomstart = float0;
 this->bloomend = float1;
 }
 }
}
} // namespace categories
} // namespace erosion
} // namespace zombie
