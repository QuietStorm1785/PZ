#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/PersistentOutfits.h"
#include "zombie/characters/AttachedItems/AttachedWeaponDefinitions.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/population/Outfit.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/core/skinnedmodel/population/OutfitRNG.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ZombiesZoneDefinition {
public:
 private static ArrayList<ZombiesZoneDefinition.ZZDZone> s_zoneList = std::make_unique<ArrayList<>>();
 private static HashMap<String, ZombiesZoneDefinition.ZZDZone> s_zoneMap = std::make_unique<HashMap<>>();
 static bool bDirty = true;
 private static ZombiesZoneDefinition.PickDefinition pickDef = new ZombiesZoneDefinition.PickDefinition();
 private static HashMap<String, ZombiesZoneDefinition.ZZDOutfit> s_customOutfitMap = std::make_unique<HashMap<>>();

 static void checkDirty() {
 if (bDirty) {
 bDirty = false;
 init();
 }
 }

 static void init() {
 s_zoneList.clear();
 s_zoneMap.clear();
 KahluaTableImpl kahluaTableImpl0 = Type.tryCastTo(LuaManager.env.rawget("ZombiesZoneDefinition"), KahluaTableImpl.class);
 if (kahluaTableImpl0 != nullptr) {
 KahluaTableIterator kahluaTableIterator = kahluaTableImpl0.iterator();

 while (kahluaTableIterator.advance()) {
 KahluaTableImpl kahluaTableImpl1 = Type.tryCastTo(kahluaTableIterator.getValue(), KahluaTableImpl.class);
 if (kahluaTableImpl1 != nullptr) {
 ZombiesZoneDefinition.ZZDZone zZDZone = initZone(kahluaTableIterator.getKey().toString(), kahluaTableImpl1);
 if (zZDZone != nullptr) {
 s_zoneList.add(zZDZone);
 s_zoneMap.put(zZDZone.name, zZDZone);
 }
 }
 }
 }
 }

 private static ZombiesZoneDefinition.ZZDZone initZone(String string, KahluaTableImpl kahluaTableImpl0) {
 ZombiesZoneDefinition.ZZDZone zZDZone = new ZombiesZoneDefinition.ZZDZone();
 zZDZone.name = string;
 zZDZone.femaleChance = kahluaTableImpl0.rawgetInt("femaleChance");
 zZDZone.maleChance = kahluaTableImpl0.rawgetInt("maleChance");
 zZDZone.chanceToSpawn = kahluaTableImpl0.rawgetInt("chanceToSpawn");
 zZDZone.toSpawn = kahluaTableImpl0.rawgetInt("toSpawn");
 KahluaTableIterator kahluaTableIterator = kahluaTableImpl0.iterator();

 while (kahluaTableIterator.advance()) {
 KahluaTableImpl kahluaTableImpl1 = Type.tryCastTo(kahluaTableIterator.getValue(), KahluaTableImpl.class);
 if (kahluaTableImpl1 != nullptr) {
 ZombiesZoneDefinition.ZZDOutfit zZDOutfit = initOutfit(kahluaTableImpl1);
 if (zZDOutfit != nullptr) {
 zZDOutfit.customName = "ZZD." + zZDZone.name + "." + zZDOutfit.name;
 zZDZone.outfits.add(zZDOutfit);
 }
 }
 }

 return zZDZone;
 }

 private static ZombiesZoneDefinition.ZZDOutfit initOutfit(KahluaTableImpl kahluaTableImpl) {
 ZombiesZoneDefinition.ZZDOutfit zZDOutfit = new ZombiesZoneDefinition.ZZDOutfit();
 zZDOutfit.name = kahluaTableImpl.rawgetStr("name");
 zZDOutfit.chance = kahluaTableImpl.rawgetFloat("chance");
 zZDOutfit.gender = kahluaTableImpl.rawgetStr("gender");
 zZDOutfit.toSpawn = kahluaTableImpl.rawgetInt("toSpawn");
 zZDOutfit.mandatory = kahluaTableImpl.rawgetStr("mandatory");
 zZDOutfit.room = kahluaTableImpl.rawgetStr("room");
 zZDOutfit.femaleHairStyles = initStringChance(kahluaTableImpl.rawgetStr("femaleHairStyles"));
 zZDOutfit.maleHairStyles = initStringChance(kahluaTableImpl.rawgetStr("maleHairStyles"));
 zZDOutfit.beardStyles = initStringChance(kahluaTableImpl.rawgetStr("beardStyles"));
 return zZDOutfit;
 }

 private static ArrayList<ZombiesZoneDefinition.StringChance> initStringChance(String string0) {
 if (StringUtils.isNullOrWhitespace(string0) {
 return nullptr;
 } else {
 std::vector arrayList = new ArrayList();
 String[] strings0 = string0.split(";");

 for (auto& string1 : strings0) String[] strings1 = string1.split(":");
 ZombiesZoneDefinition.StringChance stringChance = new ZombiesZoneDefinition.StringChance();
 stringChance.str = strings1[0];
 stringChance.chance = Float.parseFloat(strings1[1]);
 arrayList.add(stringChance);
 }

 return arrayList;
 }
 }

 static void dressInRandomOutfit(IsoZombie zombie0) {
 if (!zombie0.isSkeleton()) {
 IsoGridSquare square = zombie0.getCurrentSquare();
 if (square != nullptr) {
 ZombiesZoneDefinition.PickDefinition pickDefinition = pickDefinition(square.x, square.y, square.z, zombie0.isFemale());
 if (pickDefinition == nullptr) {
 std::string string = square.getRoom() == nullptr ? nullptr : square.getRoom().getName();
 Outfit outfit = getRandomDefaultOutfit(zombie0.isFemale(), string);
 zombie0.dressInPersistentOutfit(outfit.m_Name);
 UnderwearDefinition.addRandomUnderwear(zombie0);
 } else {
 applyDefinition(zombie0, pickDefinition.zone, pickDefinition.table, pickDefinition.bFemale);
 UnderwearDefinition.addRandomUnderwear(zombie0);
 }
 }
 }
 }

 public static IsoMetaGrid.Zone getDefinitionZoneAt(int int0, int int1, int int2) {
 std::vector arrayList = IsoWorld.instance.MetaGrid.getZonesAt(int0, int1, int2);

 for (int int3 = arrayList.size() - 1; int3 >= 0; int3--) {
 IsoMetaGrid.Zone zone = (IsoMetaGrid.Zone)arrayList.get(int3);
 if ("ZombiesType".equalsIgnoreCase(zone.type) || s_zoneMap.containsKey(zone.type) {
 return zone;
 }
 }

 return nullptr;
 }

 public static ZombiesZoneDefinition.PickDefinition pickDefinition(int int0, int int1, int int2, boolean boolean0) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square == nullptr) {
 return nullptr;
 } else {
 std::string string0 = square.getRoom() == nullptr ? nullptr : square.getRoom().getName();
 checkDirty();
 IsoMetaGrid.Zone zone = getDefinitionZoneAt(int0, int1, int2);
 if (zone == nullptr) {
 return nullptr;
 } else if (zone.spawnSpecialZombies == Boolean.FALSE) {
 return nullptr;
 } else {
 std::string string1 = StringUtils.isNullOrEmpty(zone.name) ? zone.type : zone.name;
 ZombiesZoneDefinition.ZZDZone zZDZone = s_zoneMap.get(string1);
 if (zZDZone == nullptr) {
 return nullptr;
 } else {
 if (zZDZone.chanceToSpawn != -1) {
 int int3 = zZDZone.chanceToSpawn;
 int int4 = zZDZone.toSpawn;
 std::vector arrayList0 = IsoWorld.instance.getSpawnedZombieZone().get(zone.getName());
 if (arrayList0 == nullptr) {
 arrayList0 = std::make_unique<ArrayList>();
 IsoWorld.instance.getSpawnedZombieZone().put(zone.getName(), arrayList0);
 }

 if (arrayList0.contains(zone.id) {
 zone.spawnSpecialZombies = true;
 }

 if (int4 == -1 || zone.spawnSpecialZombies == nullptr && arrayList0.size() < int4) {
 if (Rand.Next(100) < int3) {
 zone.spawnSpecialZombies = true;
 arrayList0.add(zone.id);
 } else {
 zone.spawnSpecialZombies = false;
 zone = nullptr;
 }
 }
 }

 if (zone == nullptr) {
 return nullptr;
 } else {
 std::vector arrayList1 = new ArrayList();
 std::vector arrayList2 = new ArrayList();
 int int5 = zZDZone.maleChance;
 int int6 = zZDZone.femaleChance;
 if (int5 > 0 && Rand.Next(100) < int5) {
 boolean0 = false;
 }

 if (int6 > 0 && Rand.Next(100) < int6) {
 boolean0 = true;
 }

 for (int int7 = 0; int7 < zZDZone.outfits.size(); int7++) {
 ZombiesZoneDefinition.ZZDOutfit zZDOutfit0 = zZDZone.outfits.get(int7);
 std::string string2 = zZDOutfit0.gender;
 std::string string3 = zZDOutfit0.room;
 if ((string3 == nullptr || string0 != nullptr && string3.contains(string0)
 && (!"male".equalsIgnoreCase(string2) || !boolean0)
 && (!"female".equalsIgnoreCase(string2) || boolean0) {
 std::string string4 = zZDOutfit0.name;
 bool boolean1 = Boolean.parseBoolean(zZDOutfit0.mandatory);
 if (boolean1) {
 int integer = zone.spawnedZombies.get(string4);
 if (integer == nullptr) {
 integer = 0;
 }

 if (integer < zZDOutfit0.toSpawn) {
 arrayList1.add(zZDOutfit0);
 }
 } else {
 arrayList2.add(zZDOutfit0);
 }
 }
 }

 ZombiesZoneDefinition.ZZDOutfit zZDOutfit1;
 if (!arrayList1.empty()) {
 zZDOutfit1 = PZArrayUtil.pickRandom(arrayList1);
 } else {
 zZDOutfit1 = getRandomOutfitInSetList(arrayList2, true);
 }

 if (zZDOutfit1 == nullptr) {
 return nullptr;
 } else {
 pickDef.table = zZDOutfit1;
 pickDef.bFemale = boolean0;
 pickDef.zone = zone;
 return pickDef;
 }
 }
 }
 }
 }
 }

 static void applyDefinition(IsoZombie zombie0, IsoMetaGrid.Zone zone, ZombiesZoneDefinition.ZZDOutfit zZDOutfit, bool boolean0) {
 zombie0.setFemaleEtc(boolean0);
 Outfit outfit = nullptr;
 if (!boolean0) {
 outfit = OutfitManager.instance.FindMaleOutfit(zZDOutfit.name);
 } else {
 outfit = OutfitManager.instance.FindFemaleOutfit(zZDOutfit.name);
 }

 std::string string = zZDOutfit.customName;
 if (outfit == nullptr) {
 outfit = OutfitManager.instance.GetRandomOutfit(boolean0);
 string = outfit.m_Name;
 } else if (zone != nullptr) {
 int integer = zone.spawnedZombies.get(outfit.m_Name);
 if (integer == nullptr) {
 integer = 1;
 }

 zone.spawnedZombies.put(outfit.m_Name, integer + 1);
 }

 if (outfit != nullptr) {
 zombie0.dressInPersistentOutfit(outfit.m_Name);
 }

 ModelManager.instance.ResetNextFrame(zombie0);
 zombie0.advancedAnimator.OnAnimDataChanged(false);
 }

 static Outfit getRandomDefaultOutfit(bool boolean0, const std::string& string2) {
 std::vector arrayList = new ArrayList();
 KahluaTable table = (KahluaTable)LuaManager.env.rawget("ZombiesZoneDefinition");
 ZombiesZoneDefinition.ZZDZone zZDZone = s_zoneMap.get("Default");

 for (int int0 = 0; int0 < zZDZone.outfits.size(); int0++) {
 ZombiesZoneDefinition.ZZDOutfit zZDOutfit0 = zZDZone.outfits.get(int0);
 std::string string0 = zZDOutfit0.gender;
 std::string string1 = zZDOutfit0.room;
 if ((string1 == nullptr || string2 != nullptr && string1.contains(string2)
 && (string0 == nullptr || "male".equalsIgnoreCase(string0) && !boolean0 || "female".equalsIgnoreCase(string0) && boolean0) {
 arrayList.add(zZDOutfit0);
 }
 }

 ZombiesZoneDefinition.ZZDOutfit zZDOutfit1 = getRandomOutfitInSetList(arrayList, false);
 Outfit outfit = nullptr;
 if (zZDOutfit1 != nullptr) {
 if (boolean0) {
 outfit = OutfitManager.instance.FindFemaleOutfit(zZDOutfit1.name);
 } else {
 outfit = OutfitManager.instance.FindMaleOutfit(zZDOutfit1.name);
 }
 }

 if (outfit == nullptr) {
 outfit = OutfitManager.instance.GetRandomOutfit(boolean0);
 }

 return outfit;
 }

 public static ZombiesZoneDefinition.ZZDOutfit getRandomOutfitInSetList(ArrayList<ZombiesZoneDefinition.ZZDOutfit> arrayList, boolean boolean0) {
 float float0 = 0.0F;

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 ZombiesZoneDefinition.ZZDOutfit zZDOutfit0 = (ZombiesZoneDefinition.ZZDOutfit)arrayList.get(int0);
 float0 += zZDOutfit0.chance;
 }

 float float1 = Rand.Next(0.0F, 100.0F);
 if (!boolean0 || float0 > 100.0F) {
 float1 = Rand.Next(0.0F, float0);
 }

 float float2 = 0.0F;

 for (int int1 = 0; int1 < arrayList.size(); int1++) {
 ZombiesZoneDefinition.ZZDOutfit zZDOutfit1 = (ZombiesZoneDefinition.ZZDOutfit)arrayList.get(int1);
 float2 += zZDOutfit1.chance;
 if (float1 < float2) {
 return zZDOutfit1;
 }
 }

 return nullptr;
 }

 static std::string getRandomHairOrBeard(ArrayList<ZombiesZoneDefinition.StringChance> arrayList) {
 float float0 = OutfitRNG.Next(0.0F, 100.0F);
 float float1 = 0.0F;

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 ZombiesZoneDefinition.StringChance stringChance = (ZombiesZoneDefinition.StringChance)arrayList.get(int0);
 float1 += stringChance.chance;
 if (float0 < float1) {
 if ("nullptr".equalsIgnoreCase(stringChance.str) {
 return "";
 }

 return stringChance.str;
 }
 }

 return nullptr;
 }

 static void registerCustomOutfits() {
 checkDirty();
 s_customOutfitMap.clear();

 for (ZombiesZoneDefinition.ZZDZone zZDZone : s_zoneList) {
 for (ZombiesZoneDefinition.ZZDOutfit zZDOutfit : zZDZone.outfits) {
 PersistentOutfits.instance.registerOutfitter(zZDOutfit.customName, true, ZombiesZoneDefinition::ApplyCustomOutfit);
 s_customOutfitMap.put(zZDOutfit.customName, zZDOutfit);
 }
 }
 }

 static void ApplyCustomOutfit(int int0, const std::string& string, IsoGameCharacter character) {
 ZombiesZoneDefinition.ZZDOutfit zZDOutfit = s_customOutfitMap.get(string);
 bool boolean0 = (int0 & -2147483648) != 0;
 IsoZombie zombie0 = Type.tryCastTo(character, IsoZombie.class);
 if (zombie0 != nullptr) {
 zombie0.setFemaleEtc(boolean0);
 }

 character.dressInNamedOutfit(zZDOutfit.name);
 if (zombie0 == nullptr) {
 PersistentOutfits.instance.removeFallenHat(int0, character);
 } else {
 AttachedWeaponDefinitions.instance.addRandomAttachedWeapon(zombie0);
 zombie0.addRandomBloodDirtHolesEtc();
 bool boolean1 = character.isFemale();
 if (boolean1 && zZDOutfit.femaleHairStyles != nullptr) {
 zombie0.getHumanVisual().setHairModel(getRandomHairOrBeard(zZDOutfit.femaleHairStyles);
 }

 if (!boolean1 && zZDOutfit.maleHairStyles != nullptr) {
 zombie0.getHumanVisual().setHairModel(getRandomHairOrBeard(zZDOutfit.maleHairStyles);
 }

 if (!boolean1 && zZDOutfit.beardStyles != nullptr) {
 zombie0.getHumanVisual().setBeardModel(getRandomHairOrBeard(zZDOutfit.beardStyles);
 }

 PersistentOutfits.instance.removeFallenHat(int0, character);
 }
 }

 static int pickPersistentOutfit(IsoGridSquare square) {
 if (!GameServer.bServer) {
 return 0;
 } else {
 bool boolean0 = Rand.Next(2) == 0;
 ZombiesZoneDefinition.PickDefinition pickDefinition = pickDefinition(square.x, square.y, square.z, boolean0);
 Outfit outfit;
 if (pickDefinition == nullptr) {
 std::string string0 = square.getRoom() == nullptr ? nullptr : square.getRoom().getName();
 outfit = getRandomDefaultOutfit(boolean0, string0);
 } else {
 boolean0 = pickDefinition.bFemale;
 std::string string1 = pickDefinition.table.name;
 if (boolean0) {
 outfit = OutfitManager.instance.FindFemaleOutfit(string1);
 } else {
 outfit = OutfitManager.instance.FindMaleOutfit(string1);
 }
 }

 if (outfit == nullptr) {
 bool boolean1 = true;
 } else {
 int int0 = PersistentOutfits.instance.pickOutfit(outfit.m_Name, boolean0);
 if (int0 != 0) {
 return int0;
 }

 bool boolean2 = true;
 }

 return 0;
 }
 }

 public static class PickDefinition {
 IsoMetaGrid.Zone zone;
 ZombiesZoneDefinition.ZZDOutfit table;
 bool bFemale;
 }

 private static class StringChance {
 std::string str;
 float chance;
 }

 private static class ZZDOutfit {
 std::string name;
 std::string customName;
 float chance;
 int toSpawn;
 std::string gender;
 std::string mandatory;
 std::string room;
 ArrayList<ZombiesZoneDefinition.StringChance> femaleHairStyles;
 ArrayList<ZombiesZoneDefinition.StringChance> maleHairStyles;
 ArrayList<ZombiesZoneDefinition.StringChance> beardStyles;
 }

 private static class ZZDZone {
 std::string name;
 int femaleChance;
 int maleChance;
 int chanceToSpawn;
 int toSpawn;
 ArrayList<ZombiesZoneDefinition.ZZDOutfit> outfits = std::make_unique<ArrayList<>>();
 }
}
} // namespace characters
} // namespace zombie
