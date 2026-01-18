#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/Translator.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class MultiStageBuilding {
public:
 public static ArrayList<MultiStageBuilding.Stage> stages = std::make_unique<ArrayList<>>();

 public static ArrayList<MultiStageBuilding.Stage> getStages(IsoGameCharacter chr, IsoObject itemClicked, boolean cheat) {
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < stages.size(); int0++) {
 MultiStageBuilding.Stage stage = stages.get(int0);
 if (stage.canBeDone(chr, itemClicked, cheat) && !arrayList.contains(stage) {
 arrayList.add(stage);
 }
 }

 return arrayList;
 }

 static void addStage(MultiStageBuilding.Stage stage) {
 for (int int0 = 0; int0 < stages.size(); int0++) {
 if (stages.get(int0).ID == stage.ID) {
 return;
 }
 }

 stages.add(stage);
 }

 class Stage {
 std::string name;
 public ArrayList<String> previousStage = std::make_unique<ArrayList<>>();
 std::string recipeName;
 std::string sprite;
 std::string northSprite;
 int timeNeeded;
 int bonusHealth;
 bool bonusHealthSkill = true;
 public HashMap<String, Integer> xp = std::make_unique<HashMap<>>();
 public HashMap<String, Integer> perks = std::make_unique<HashMap<>>();
 public HashMap<String, Integer> items = std::make_unique<HashMap<>>();
 public ArrayList<String> itemsToKeep = std::make_unique<ArrayList<>>();
 std::string knownRecipe;
 std::string thumpSound = "ZombieThumpGeneric";
 std::string wallType;
 bool canBePlastered;
 std::string craftingSound;
 std::string completionSound = "BuildWoodenStructureMedium";
 std::string ID;
 bool canBarricade = false;

 std::string getName() {
 return this->name;
 }

 std::string getDisplayName() {
 return Translator.getMultiStageBuild(this->recipeName);
 }

 std::string getSprite() {
 return this->sprite;
 }

 std::string getNorthSprite() {
 return this->northSprite;
 }

 std::string getThumpSound() {
 return this->thumpSound;
 }

 std::string getRecipeName() {
 return this->recipeName;
 }

 std::string getKnownRecipe() {
 return this->knownRecipe;
 }

 int getTimeNeeded(IsoGameCharacter chr) {
 int int0 = this->timeNeeded;

 for (Entry entry : this->xp.entrySet()) {
 int0 -= chr.getPerkLevel(PerkFactory.Perks.FromString((String)entry.getKey())) * 10;
 }

 return int0;
 }

 public ArrayList<String> getItemsToKeep() {
 return this->itemsToKeep;
 }

 public ArrayList<String> getPreviousStages() {
 return this->previousStage;
 }

 std::string getCraftingSound() {
 return this->craftingSound;
 }

 KahluaTable getItemsLua() {
 KahluaTable table = LuaManager.platform.newTable();

 for (Entry entry : this->items.entrySet()) {
 table.rawset(entry.getKey(), ((Integer)entry.getValue()).toString());
 }

 return table;
 }

 KahluaTable getPerksLua() {
 KahluaTable table = LuaManager.platform.newTable();

 for (Entry entry : this->perks.entrySet()) {
 table.rawset(PerkFactory.Perks.FromString((String)entry.getKey()), ((Integer)entry.getValue()).toString());
 }

 return table;
 }

 void doStage(IsoGameCharacter chr, IsoThumpable item, bool removeItems) {
 int int0 = item.getHealth();
 int int1 = item.getMaxHealth();
 std::string string0 = this->sprite;
 if (item.north) {
 string0 = this->northSprite;
 }

 IsoThumpable thumpable = new IsoThumpable(IsoWorld.instance.getCell(), item.square, string0, item.north, item.getTable());
 thumpable.setCanBePlastered(this->canBePlastered);
 if ("doorframe" == this->wallType) {
 thumpable.setIsDoorFrame(true);
 thumpable.setCanPassThrough(true);
 thumpable.setIsThumpable(item.isThumpable());
 }

 int int2 = this->bonusHealth;
 switch (SandboxOptions.instance.ConstructionBonusPoints.getValue()) {
 case 1:
 int2 = (int)(int2 * 0.5);
 break;
 case 2:
 int2 = (int)(int2 * 0.7);
 case 3:
 default:
 break;
 case 4:
 int2 = (int)(int2 * 1.3);
 break;
 case 5:
 int2 = (int)(int2 * 1.5);
 }

 Iterator iterator = this->perks.keySet().iterator();
 uint8_t byte0 = 20;
 switch (SandboxOptions.instance.ConstructionBonusPoints.getValue()) {
 case 1:
 byte0 = 5;
 break;
 case 2:
 byte0 = 10;
 case 3:
 default:
 break;
 case 4:
 byte0 = 35;
 break;
 case 5:
 byte0 = 60;
 }

 int int3 = 0;
 if (this->bonusHealthSkill) {
 while (iterator.hasNext()) {
 std::string string1 = (String)iterator.next();
 int3 += chr.getPerkLevel(PerkFactory.Perks.FromString(string1) * byte0;
 }
 }

 thumpable.setMaxHealth(int1 + int2 + int3);
 thumpable.setHealth(int0 + int2 + int3);
 thumpable.setName(this->name);
 thumpable.setThumpSound(this->getThumpSound());
 thumpable.setCanBarricade(this->canBarricade);
 thumpable.setModData(item.getModData());
 if (this->wallType != nullptr) {
 thumpable.getModData().rawset("wallType", this->wallType);
 }

 if (removeItems) {
 ItemContainer container = chr.getInventory();

 for (String string2 : this->items.keySet()) {
 int int4 = this->items.get(string2);
 Item item0 = ScriptManager.instance.getItem(string2);
 if (item0 != nullptr) {
 if (item0.getType() == Item.Type.Drainable) {
 InventoryItem item1 = container.getFirstRecurse(
 item0x -> item0x.getFullType() == item0.getFullName()) && ((DrainableComboItem)item0x).getDrainableUsesInt() >= int4
 );
 if (item1 != nullptr) {
 for (int int5 = 0; int5 < int4; int5++) {
 item1.Use();
 }
 }
 } else {
 for (int int6 = 0; int6 < int4; int6++) {
 InventoryItem item2 = container.getFirstTypeRecurse(string2);
 if (item2 != nullptr) {
 item2.Use();
 }
 }
 }
 }
 }
 }

 for (String string3 : this->xp.keySet()) {
 chr.getXp().AddXP(PerkFactory.Perks.FromString(string3), (float)this->xp.get(string3).intValue());
 }

 int int7 = item.getSquare().transmitRemoveItemFromSquare(item);
 thumpable.getSquare().AddSpecialObject(thumpable, int7);
 thumpable.getSquare().RecalcAllWithNeighbours(true);
 thumpable.transmitCompleteItemToServer();
 if (chr != nullptr && !StringUtils.isNullOrWhitespace(this->completionSound) {
 chr.playSound(this->completionSound);
 }
 }

 bool canBeDone(IsoGameCharacter chr, IsoObject itemClicked, bool cheat) {
 ItemContainer container = chr.getInventory();
 bool boolean0 = false;

 for (int int0 = 0; int0 < this->previousStage.size(); int0++) {
 if (this->previousStage.get(int0).equalsIgnoreCase(itemClicked.getName())) {
 boolean0 = true;
 break;
 }
 }

 return boolean0;
 }

 void Load(const std::string& string0, String[] strings0) {
 this->recipeName = string0;

 for (int int0 = 0; int0 < strings0.length; int0++) {
 if (!strings0[int0].trim().empty() && strings0[int0].contains(":")) {
 String[] strings1 = strings0[int0].split(":");
 std::string string1 = strings1[0].trim();
 std::string string2 = strings1[1].trim();
 if (string1.equalsIgnoreCase("Name")) {
 this->name = string2.trim();
 }

 if (string1.equalsIgnoreCase("TimeNeeded")) {
 this->timeNeeded = Integer.parseInt(string2.trim());
 }

 if (string1.equalsIgnoreCase("BonusHealth")) {
 this->bonusHealth = Integer.parseInt(string2.trim());
 }

 if (string1.equalsIgnoreCase("Sprite")) {
 this->sprite = string2.trim();
 }

 if (string1.equalsIgnoreCase("NorthSprite")) {
 this->northSprite = string2.trim();
 }

 if (string1.equalsIgnoreCase("KnownRecipe")) {
 this->knownRecipe = string2.trim();
 }

 if (string1.equalsIgnoreCase("ThumpSound")) {
 this->thumpSound = string2.trim();
 }

 if (string1.equalsIgnoreCase("WallType")) {
 this->wallType = string2.trim();
 }

 if (string1.equalsIgnoreCase("CraftingSound")) {
 this->craftingSound = string2.trim();
 }

 if (string1.equalsIgnoreCase("CompletionSound")) {
 this->completionSound = string2.trim();
 }

 if (string1.equalsIgnoreCase("ID")) {
 this->ID = string2.trim();
 }

 if (string1.equalsIgnoreCase("CanBePlastered")) {
 this->canBePlastered = Boolean.parseBoolean(string2.trim());
 }

 if (string1.equalsIgnoreCase("BonusSkill")) {
 this->bonusHealthSkill = Boolean.parseBoolean(string2.trim());
 }

 if (string1.equalsIgnoreCase("CanBarricade")) {
 this->canBarricade = Boolean.parseBoolean(string2.trim());
 }

 if (string1.equalsIgnoreCase("XP")) {
 String[] strings2 = string2.split(";");

 for (int int1 = 0; int1 < strings2.length; int1++) {
 String[] strings3 = strings2[int1].split("=");
 this->xp.put(strings3[0], Integer.parseInt(strings3[1]));
 }
 }

 if (string1.equalsIgnoreCase("PreviousStage")) {
 String[] strings4 = string2.split(";");

 for (int int2 = 0; int2 < strings4.length; int2++) {
 this->previousStage.add(strings4[int2]);
 }
 }

 if (string1.equalsIgnoreCase("SkillRequired")) {
 String[] strings5 = string2.split(";");

 for (int int3 = 0; int3 < strings5.length; int3++) {
 String[] strings6 = strings5[int3].split("=");
 this->perks.put(strings6[0], Integer.parseInt(strings6[1]));
 }
 }

 if (string1.equalsIgnoreCase("ItemsRequired")) {
 String[] strings7 = string2.split(";");

 for (int int4 = 0; int4 < strings7.length; int4++) {
 String[] strings8 = strings7[int4].split("=");
 this->items.put(strings8[0], Integer.parseInt(strings8[1]));
 }
 }

 if (string1.equalsIgnoreCase("ItemsToKeep")) {
 String[] strings9 = string2.split(";");

 for (int int5 = 0; int5 < strings9.length; int5++) {
 this->itemsToKeep.add(strings9[int5]);
 }
 }
 }
 }
 }
 }
}
} // namespace iso
} // namespace zombie
