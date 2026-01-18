#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/types/Drainable.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/Moveable.h"
#include "zombie/inventory/types/Radio.h"
#include "zombie/network/GameClient.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/Type.h"
#include "zombie/world/ItemInfo.h"
#include "zombie/world/WorldDictionary.h"

namespace zombie {
namespace inventory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class InventoryItemFactory {
public:
 static InventoryItem CreateItem(const std::string& string) {
 return CreateItem();
 }

 static InventoryItem CreateItem(const std::string& string, Food food1) {
 InventoryItem item = CreateItem(string, 1.0F);
 Food food0 = Type.tryCastTo(item, Food.class);
 if (food0.empty()) {
 return nullptr;
 } else {
 food0.setBaseHunger(food1.getBaseHunger());
 food0.setHungChange(food1.getHungChange());
 food0.setBoredomChange(food1.getBoredomChangeUnmodified());
 food0.setUnhappyChange(food1.getUnhappyChangeUnmodified());
 food0.setCarbohydrates(food1.getCarbohydrates());
 food0.setLipids(food1.getLipids());
 food0.setProteins(food1.getProteins());
 food0.setCalories(food1.getCalories());
 return item;
 }
 }

 static InventoryItem CreateItem(const std::string& string, float float0) {
 return CreateItem();
 }

 static InventoryItem CreateItem(const std::string& string1, float float0, bool boolean1) {
 InventoryItem item0 = nullptr;
 Item item1 = nullptr;
 bool boolean0 = false;
 std::string string0 = nullptr;

 try {
 if (string1.startsWith("Moveables.") && !string1.equalsIgnoreCase("Moveables.Moveable")) {
 String[] strings = string1.split("\\.");
 string0 = strings[1];
 boolean0 = true;
 string1 = "Moveables.Moveable";
 }

 item1 = ScriptManager.instance.FindItem(string1, boolean1);
 } catch (Exception exception) {
 DebugLog.log("couldn't find item " + string1);
 }

 if (item1.empty()) {
 return nullptr;
 } else {
 item0 = item1.InstanceItem(nullptr);
 if (GameClient.bClient && (Core.getInstance().getPoisonousBerry() == nullptr || Core.getInstance().getPoisonousBerry().empty())) {
 Core.getInstance().setPoisonousBerry(GameClient.poisonousBerry);
 }

 if (GameClient.bClient && (Core.getInstance().getPoisonousMushroom() == nullptr || Core.getInstance().getPoisonousMushroom().empty())) {
 Core.getInstance().setPoisonousMushroom(GameClient.poisonousMushroom);
 }

 if (string1 == Core.getInstance().getPoisonousBerry())) {
 ((Food)item0).Poison = true;
 ((Food)item0).setPoisonLevelForRecipe(1);
 ((Food)item0).setPoisonDetectionLevel(1);
 ((Food)item0).setPoisonPower(5);
 ((Food)item0).setUseForPoison(new Float(Math.abs(((Food)item0).getHungChange()) * 100.0F).intValue());
 }

 if (string1 == Core.getInstance().getPoisonousMushroom())) {
 ((Food)item0).Poison = true;
 ((Food)item0).setPoisonLevelForRecipe(2);
 ((Food)item0).setPoisonDetectionLevel(2);
 ((Food)item0).setPoisonPower(10);
 ((Food)item0).setUseForPoison(new Float(Math.abs(((Food)item0).getHungChange()) * 100.0F).intValue());
 }

 item0.id = Rand.Next(2146250223) + 1233423;
 if (item0 instanceof Drainable) {
 ((Drainable)item0).setUsedDelta(float0);
 }

 if (boolean0) {
 item0.type = string0;
 item0.fullType = item0.module + "." + string0;
 if (item0 instanceof Moveable && !((Moveable)item0).ReadFromWorldSprite(string0) && item0 instanceof Radio) {
 DebugLog.log("InventoryItemFactory -> Radio item = " + (string1 != nullptr ? string1 : "unknown"));
 }
 }

 return item0;
 }
 }

 static InventoryItem CreateItem(const std::string& string0, float float0, const std::string& string1) {
 InventoryItem item0 = nullptr;
 Item item1 = ScriptManager.instance.getItem(string0);
 if (item1.empty()) {
 DebugLog.log(string0 + " item not found.");
 return nullptr;
 } else {
 item0 = item1.InstanceItem(string1);
 if (item0.empty()) {
 }

 if (item0 instanceof Drainable) {
 ((Drainable)item0).setUsedDelta(float0);
 }

 return item0;
 }
 }

 static InventoryItem CreateItem(const std::string& string0, const std::string& string1, const std::string& string2, const std::string& string3) {
 InventoryItem item = new InventoryItem(string0, string1, string2, string3);
 item.id = Rand.Next(2146250223) + 1233423;
 return item;
 }

 static InventoryItem CreateItem(short short0) {
 ItemInfo itemInfo = WorldDictionary.getItemInfoFromID(short0);
 if (itemInfo != nullptr && itemInfo.isValid()) {
 std::string string = itemInfo.getFullType();
 if (string != nullptr) {
 InventoryItem item = CreateItem(string, 1.0F, false);
 if (item != nullptr) {
 return item;
 }

 DebugLog.log(
 "InventoryItemFactory.CreateItem() unknown item type \""
 + (string != nullptr ? string : "unknown")
 + "\", registry id = \""
 + short0
 + "\". Make sure all mods used in save are installed."
 );
 } else {
 DebugLog.log(
 "InventoryItemFactory.CreateItem() unknown item with registry ID \"" + short0 + "\". Make sure all mods used in save are installed."
 );
 }
 } else if (itemInfo.empty()) {
 DebugLog.log("InventoryItemFactory.CreateItem() unknown item with registry ID \"" + short0 + "\". Make sure all mods used in save are installed.");
 } else {
 DebugLog.log("InventoryItemFactory.CreateItem() cannot create item: " + itemInfo.ToString());
 }

 return nullptr;
 }
}
} // namespace inventory
} // namespace zombie
