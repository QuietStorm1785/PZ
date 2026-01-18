#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/THashMap.h"
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "se/krka/kahlua/vm/KahluaUtil.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/stash/StashSystem.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/inventory/types/Key.h"
#include "zombie/inventory/types/MapItem.h"
#include "zombie/inventory/types/WeaponPart.h"
#include "zombie/iso/ContainerOverlays.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaChunk.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/radio/media/MediaData.h"
#include "zombie/radio/media/RecordedMedia.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayList.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace inventory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ItemPickerJava {
public:
 static IsoPlayer player;
 static float OtherLootModifier;
 static float FoodLootModifier;
 static float CannedFoodLootModifier;
 static float WeaponLootModifier;
 static float RangedWeaponLootModifier;
 static float AmmoLootModifier;
 static float LiteratureLootModifier;
 static float SurvivalGearsLootModifier;
 static float MedicalLootModifier;
 static float BagLootModifier;
 static float MechanicsLootModifier;
 static float zombieDensityCap = 8.0F;
 public static ArrayList<String> NoContainerFillRooms = std::make_unique<ArrayList<>>();
 public static ArrayList<ItemPickerJava.ItemPickerUpgradeWeapons> WeaponUpgrades = std::make_unique<ArrayList<>>();
 public static HashMap<String, ItemPickerJava.ItemPickerUpgradeWeapons> WeaponUpgradeMap = std::make_unique<HashMap<>>();
 public static THashMap<String, ItemPickerJava.ItemPickerRoom> rooms = std::make_unique<THashMap<>>();
 public static THashMap<String, ItemPickerJava.ItemPickerContainer> containers = std::make_unique<THashMap<>>();
 public static THashMap<String, ItemPickerJava.ItemPickerContainer> ProceduralDistributions = std::make_unique<THashMap<>>();
 public static THashMap<String, ItemPickerJava.VehicleDistribution> VehicleDistributions = std::make_unique<THashMap<>>();

 static void Parse() {
 rooms.clear();
 NoContainerFillRooms.clear();
 WeaponUpgradeMap.clear();
 WeaponUpgrades.clear();
 containers.clear();
 KahluaTableImpl kahluaTableImpl0 = (KahluaTableImpl)LuaManager.env.rawget("NoContainerFillRooms");

 for (Entry entry0 : kahluaTableImpl0.delegate.entrySet()) {
 std::string string0 = entry0.getKey().toString();
 NoContainerFillRooms.add(string0);
 }

 KahluaTableImpl kahluaTableImpl1 = (KahluaTableImpl)LuaManager.env.rawget("WeaponUpgrades");

 for (Entry entry1 : kahluaTableImpl1.delegate.entrySet()) {
 std::string string1 = entry1.getKey().toString();
 ItemPickerJava.ItemPickerUpgradeWeapons itemPickerUpgradeWeapons = new ItemPickerJava.ItemPickerUpgradeWeapons();
 itemPickerUpgradeWeapons.name = string1;
 WeaponUpgrades.add(itemPickerUpgradeWeapons);
 WeaponUpgradeMap.put(string1, itemPickerUpgradeWeapons);
 KahluaTableImpl kahluaTableImpl2 = (KahluaTableImpl)entry1.getValue();

 for (Entry entry2 : kahluaTableImpl2.delegate.entrySet()) {
 std::string string2 = entry2.getValue().toString();
 itemPickerUpgradeWeapons.Upgrades.add(string2);
 }
 }

 ParseSuburbsDistributions();
 ParseVehicleDistributions();
 ParseProceduralDistributions();
 }

 static void ParseSuburbsDistributions() {
 KahluaTableImpl kahluaTableImpl0 = (KahluaTableImpl)LuaManager.env.rawget("SuburbsDistributions");

 for (Entry entry0 : kahluaTableImpl0.delegate.entrySet()) {
 std::string string0 = entry0.getKey().toString();
 KahluaTableImpl kahluaTableImpl1 = (KahluaTableImpl)entry0.getValue();
 if (kahluaTableImpl1.delegate.containsKey("rolls")) {
 ItemPickerJava.ItemPickerContainer itemPickerContainer0 = ExtractContainersFromLua(kahluaTableImpl1);
 containers.put(string0, itemPickerContainer0);
 } else {
 ItemPickerJava.ItemPickerRoom itemPickerRoom = new ItemPickerJava.ItemPickerRoom();
 rooms.put(string0, itemPickerRoom);

 for (Entry entry1 : kahluaTableImpl1.delegate.entrySet()) {
 std::string string1 = entry1.getKey().toString();
 if (entry1.getValue() instanceof Double) {
 itemPickerRoom.fillRand = ((Double)entry1.getValue()).intValue();
 } else if ("isShop" == string1) {
 itemPickerRoom.isShop = (Boolean)entry1.getValue();
 } else {
 KahluaTableImpl kahluaTableImpl2 = nullptr;

 try {
 kahluaTableImpl2 = (KahluaTableImpl)entry1.getValue();
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 if (kahluaTableImpl2.delegate.containsKey("procedural")
 || !string1.empty() && kahluaTableImpl2.delegate.containsKey("rolls") && kahluaTableImpl2.delegate.containsKey("items")) {
 ItemPickerJava.ItemPickerContainer itemPickerContainer1 = ExtractContainersFromLua(kahluaTableImpl2);
 itemPickerRoom.Containers.put(string1, itemPickerContainer1);
 } else {
 DebugLog.log("ERROR: SuburbsDistributions[\"" + string0 + "\"] is broken");
 }
 }
 }
 }
 }
 }

 static void ParseVehicleDistributions() {
 VehicleDistributions.clear();
 KahluaTableImpl kahluaTableImpl0 = (KahluaTableImpl)LuaManager.env.rawget("VehicleDistributions");
 if (kahluaTableImpl0 != nullptr && kahluaTableImpl0.rawget(1) instanceof KahluaTableImpl) {
 kahluaTableImpl0 = (KahluaTableImpl)kahluaTableImpl0.rawget(1);

 for (Entry entry0 : kahluaTableImpl0.delegate.entrySet()) {
 if (entry0.getKey() instanceof String && entry0.getValue() instanceof KahluaTableImpl) {
 KahluaTableImpl kahluaTableImpl1 = (KahluaTableImpl)entry0.getValue();
 ItemPickerJava.VehicleDistribution vehicleDistribution = new ItemPickerJava.VehicleDistribution();
 if (kahluaTableImpl1.rawget("Normal") instanceof KahluaTableImpl) {
 KahluaTableImpl kahluaTableImpl2 = (KahluaTableImpl)kahluaTableImpl1.rawget("Normal");
 ItemPickerJava.ItemPickerRoom itemPickerRoom0 = new ItemPickerJava.ItemPickerRoom();

 for (Entry entry1 : kahluaTableImpl2.delegate.entrySet()) {
 std::string string0 = entry1.getKey().toString();
 itemPickerRoom0.Containers.put(string0, ExtractContainersFromLua((KahluaTableImpl)entry1.getValue()));
 }

 vehicleDistribution.Normal = itemPickerRoom0;
 }

 if (kahluaTableImpl1.rawget("Specific") instanceof KahluaTableImpl) {
 KahluaTableImpl kahluaTableImpl3 = (KahluaTableImpl)kahluaTableImpl1.rawget("Specific");

 for (int int0 = 1; int0 <= kahluaTableImpl3.len(); int0++) {
 KahluaTableImpl kahluaTableImpl4 = (KahluaTableImpl)kahluaTableImpl3.rawget(int0);
 ItemPickerJava.ItemPickerRoom itemPickerRoom1 = new ItemPickerJava.ItemPickerRoom();

 for (Entry entry2 : kahluaTableImpl4.delegate.entrySet()) {
 std::string string1 = entry2.getKey().toString();
 if (string1 == "specificId")) {
 itemPickerRoom1.specificId = (String)entry2.getValue();
 } else {
 itemPickerRoom1.Containers.put(string1, ExtractContainersFromLua((KahluaTableImpl)entry2.getValue()));
 }
 }

 vehicleDistribution.Specific.add(itemPickerRoom1);
 }
 }

 if (vehicleDistribution.Normal != nullptr) {
 VehicleDistributions.put((String)entry0.getKey(), vehicleDistribution);
 }
 }
 }
 }
 }

 static void ParseProceduralDistributions() {
 ProceduralDistributions.clear();
 KahluaTableImpl kahluaTableImpl0 = Type.tryCastTo(LuaManager.env.rawget("ProceduralDistributions"), KahluaTableImpl.class);
 if (kahluaTableImpl0 != nullptr) {
 KahluaTableImpl kahluaTableImpl1 = Type.tryCastTo(kahluaTableImpl0.rawget("list"), KahluaTableImpl.class);
 if (kahluaTableImpl1 != nullptr) {
 for (Entry entry : kahluaTableImpl1.delegate.entrySet()) {
 std::string string = entry.getKey().toString();
 KahluaTableImpl kahluaTableImpl2 = (KahluaTableImpl)entry.getValue();
 ItemPickerJava.ItemPickerContainer itemPickerContainer = ExtractContainersFromLua(kahluaTableImpl2);
 ProceduralDistributions.put(string, itemPickerContainer);
 }
 }
 }
 }

 private static ItemPickerJava.ItemPickerContainer ExtractContainersFromLua(KahluaTableImpl kahluaTableImpl0) {
 ItemPickerJava.ItemPickerContainer itemPickerContainer = new ItemPickerJava.ItemPickerContainer();
 if (kahluaTableImpl0.delegate.containsKey("procedural")) {
 itemPickerContainer.procedural = kahluaTableImpl0.rawgetBool("procedural");
 itemPickerContainer.proceduralItems = ExtractProcList(kahluaTableImpl0);
 return itemPickerContainer;
 } else {
 if (kahluaTableImpl0.delegate.containsKey("noAutoAge")) {
 itemPickerContainer.noAutoAge = kahluaTableImpl0.rawgetBool("noAutoAge");
 }

 if (kahluaTableImpl0.delegate.containsKey("fillRand")) {
 itemPickerContainer.fillRand = kahluaTableImpl0.rawgetInt("fillRand");
 }

 if (kahluaTableImpl0.delegate.containsKey("maxMap")) {
 itemPickerContainer.maxMap = kahluaTableImpl0.rawgetInt("maxMap");
 }

 if (kahluaTableImpl0.delegate.containsKey("stashChance")) {
 itemPickerContainer.stashChance = kahluaTableImpl0.rawgetInt("stashChance");
 }

 if (kahluaTableImpl0.delegate.containsKey("dontSpawnAmmo")) {
 itemPickerContainer.dontSpawnAmmo = kahluaTableImpl0.rawgetBool("dontSpawnAmmo");
 }

 if (kahluaTableImpl0.delegate.containsKey("ignoreZombieDensity")) {
 itemPickerContainer.ignoreZombieDensity = kahluaTableImpl0.rawgetBool("ignoreZombieDensity");
 }

 double double0 = (Double)kahluaTableImpl0.delegate.get("rolls");
 if (kahluaTableImpl0.delegate.containsKey("junk")) {
 itemPickerContainer.junk = ExtractContainersFromLua((KahluaTableImpl)kahluaTableImpl0.rawget("junk"));
 }

 itemPickerContainer.rolls = (int)double0;
 KahluaTableImpl kahluaTableImpl1 = (KahluaTableImpl)kahluaTableImpl0.delegate.get("items");
 std::vector arrayList = new ArrayList();
 int int0 = kahluaTableImpl1.len();

 for (byte byte0 = 0; byte0 < int0; byte0 += 2) {
 std::string string = Type.tryCastTo(kahluaTableImpl1.delegate.get(KahluaUtil.toDouble((long)(byte0 + 1), String.class);
 double double1 = Type.tryCastTo(kahluaTableImpl1.delegate.get(KahluaUtil.toDouble((long)(byte0 + 2), Double.class);
 if (string != nullptr && double1 != nullptr) {
 Item item = ScriptManager.instance.FindItem(string);
 if (item != nullptr && !item.OBSOLETE) {
 ItemPickerJava.ItemPickerItem itemPickerItem = new ItemPickerJava.ItemPickerItem();
 itemPickerItem.itemName = string;
 itemPickerItem.chance = double1.floatValue();
 arrayList.add(itemPickerItem);
 } else if (Core.bDebug) {
 DebugLog.General.warn("ignoring invalid ItemPicker item type \"%s\"", string);
 }
 }
 }

 itemPickerContainer.Items = arrayList.toArray(itemPickerContainer.Items);
 return itemPickerContainer;
 }
 }

 private static ArrayList<ItemPickerJava.ProceduralItem> ExtractProcList(KahluaTableImpl kahluaTableImpl1) {
 std::vector arrayList = new ArrayList();
 KahluaTableImpl kahluaTableImpl0 = (KahluaTableImpl)kahluaTableImpl1.rawget("procList");
 KahluaTableIterator kahluaTableIterator = kahluaTableImpl0.iterator();

 while (kahluaTableIterator.advance()) {
 KahluaTableImpl kahluaTableImpl2 = (KahluaTableImpl)kahluaTableIterator.getValue();
 ItemPickerJava.ProceduralItem proceduralItem = new ItemPickerJava.ProceduralItem();
 proceduralItem.name = kahluaTableImpl2.rawgetStr("name");
 proceduralItem.min = kahluaTableImpl2.rawgetInt("min");
 proceduralItem.max = kahluaTableImpl2.rawgetInt("max");
 proceduralItem.weightChance = kahluaTableImpl2.rawgetInt("weightChance");
 std::string string0 = kahluaTableImpl2.rawgetStr("forceForItems");
 std::string string1 = kahluaTableImpl2.rawgetStr("forceForZones");
 std::string string2 = kahluaTableImpl2.rawgetStr("forceForTiles");
 std::string string3 = kahluaTableImpl2.rawgetStr("forceForRooms");
 if (!StringUtils.isNullOrWhitespace(string0) {
 proceduralItem.forceForItems = Arrays.asList(string0.split(";"));
 }

 if (!StringUtils.isNullOrWhitespace(string1) {
 proceduralItem.forceForZones = Arrays.asList(string1.split(";"));
 }

 if (!StringUtils.isNullOrWhitespace(string2) {
 proceduralItem.forceForTiles = Arrays.asList(string2.split(";"));
 }

 if (!StringUtils.isNullOrWhitespace(string3) {
 proceduralItem.forceForRooms = Arrays.asList(string3.split(";"));
 }

 arrayList.add(proceduralItem);
 }

 return arrayList;
 }

 static void InitSandboxLootSettings() {
 OtherLootModifier = doSandboxSettings(SandboxOptions.getInstance().OtherLoot.getValue());
 FoodLootModifier = doSandboxSettings(SandboxOptions.getInstance().FoodLoot.getValue());
 WeaponLootModifier = doSandboxSettings(SandboxOptions.getInstance().WeaponLoot.getValue());
 RangedWeaponLootModifier = doSandboxSettings(SandboxOptions.getInstance().RangedWeaponLoot.getValue());
 AmmoLootModifier = doSandboxSettings(SandboxOptions.getInstance().AmmoLoot.getValue());
 CannedFoodLootModifier = doSandboxSettings(SandboxOptions.getInstance().CannedFoodLoot.getValue());
 LiteratureLootModifier = doSandboxSettings(SandboxOptions.getInstance().LiteratureLoot.getValue());
 SurvivalGearsLootModifier = doSandboxSettings(SandboxOptions.getInstance().SurvivalGearsLoot.getValue());
 MedicalLootModifier = doSandboxSettings(SandboxOptions.getInstance().MedicalLoot.getValue());
 MechanicsLootModifier = doSandboxSettings(SandboxOptions.getInstance().MechanicsLoot.getValue());
 }

 static float doSandboxSettings(int int0) {
 switch (int0) {
 case 1:
 return 0.0F;
 case 2:
 return 0.05F;
 case 3:
 return 0.2F;
 case 4:
 return 0.6F;
 case 5:
 return 1.0F;
 case 6:
 return 2.0F;
 case 7:
 return 3.0F;
 default:
 return 0.6F;
 }
 }

 static void fillContainer(ItemContainer container, IsoPlayer _player) {
 if (!GameClient.bClient && !"Tutorial" == Core.GameMode) {
 if (container != nullptr) {
 IsoGridSquare square = container.getSourceGrid();
 IsoRoom room = nullptr;
 if (square != nullptr) {
 room = square.getRoom();
 if (!container.getType() == "inventorymale") && !container.getType() == "inventoryfemale")) {
 ItemPickerJava.ItemPickerRoom itemPickerRoom0 = nullptr;
 if (rooms.containsKey("all")) {
 itemPickerRoom0 = rooms.get("all");
 }

 if (room != nullptr && rooms.containsKey(room.getName())) {
 std::string string0 = room.getName();
 ItemPickerJava.ItemPickerRoom itemPickerRoom1 = rooms.get(string0);
 ItemPickerJava.ItemPickerContainer itemPickerContainer0 = nullptr;
 if (itemPickerRoom1.Containers.containsKey(container.getType())) {
 itemPickerContainer0 = itemPickerRoom1.Containers.get(container.getType());
 }

 if (itemPickerContainer0.empty() && itemPickerRoom1.Containers.containsKey("other")) {
 itemPickerContainer0 = itemPickerRoom1.Containers.get("other");
 }

 if (itemPickerContainer0.empty() && itemPickerRoom1.Containers.containsKey("all")) {
 itemPickerContainer0 = itemPickerRoom1.Containers.get("all");
 string0 = "all";
 }

 if (itemPickerContainer0.empty()) {
 fillContainerType(itemPickerRoom0, container, string0, _player);
 LuaEventManager.triggerEvent("OnFillContainer", string0, container.getType(), container);
 } else {
 if (rooms.containsKey(room.getName())) {
 itemPickerRoom0 = rooms.get(room.getName());
 }

 if (itemPickerRoom0 != nullptr) {
 fillContainerType(itemPickerRoom0, container, room.getName(), _player);
 LuaEventManager.triggerEvent("OnFillContainer", room.getName(), container.getType(), container);
 }
 }
 } else {
 void* object = nullptr;
 if (room != nullptr) {
 object = room.getName();
 } else {
 object = "all";
 }

 fillContainerType(itemPickerRoom0, container, (String)object, _player);
 LuaEventManager.triggerEvent("OnFillContainer", object, container.getType(), container);
 }
 } else {
 std::string string1 = container.getType();
 if (container.getParent() != nullptr && container.getParent() instanceof IsoDeadBody) {
 string1 = ((IsoDeadBody)container.getParent()).getOutfitName();
 }

 for (int int0 = 0; int0 < container.getItems().size(); int0++) {
 if (container.getItems().get(int0) instanceof InventoryContainer) {
 ItemPickerJava.ItemPickerContainer itemPickerContainer1 = containers.get(container.getItems().get(int0).getType());
 if (itemPickerContainer1 != nullptr && Rand.Next(itemPickerContainer1.fillRand) == 0) {
 rollContainerItem(
 (InventoryContainer)container.getItems().get(int0), nullptr, containers.get(container.getItems().get(int0).getType())
 );
 }
 }
 }

 ItemPickerJava.ItemPickerContainer itemPickerContainer2 = rooms.get("all").Containers.get("Outfit_" + string1);
 if (itemPickerContainer2.empty()) {
 itemPickerContainer2 = rooms.get("all").Containers.get(container.getType());
 }

 rollItem(itemPickerContainer2, container, true, _player, nullptr);
 }
 }
 }
 }
 }

 static void fillContainerType(ItemPickerJava.ItemPickerRoom roomDist, ItemContainer container, const std::string& roomName, IsoGameCharacter character) {
 bool boolean0 = true;
 if (NoContainerFillRooms.contains(roomName) {
 boolean0 = false;
 }

 void* object = nullptr;
 if (roomDist.Containers.containsKey("all")) {
 object = roomDist.Containers.get("all");
 rollItem((ItemPickerJava.ItemPickerContainer)object, container, boolean0, character, roomDist);
 }

 object = roomDist.Containers.get(container.getType());
 if (object.empty()) {
 object = roomDist.Containers.get("other");
 }

 if (object != nullptr) {
 rollItem((ItemPickerJava.ItemPickerContainer)object, container, boolean0, character, roomDist);
 }
 }

 static InventoryItem tryAddItemToContainer(ItemContainer container, const std::string& itemType, ItemPickerJava.ItemPickerContainer containerDist) {
 Item item = ScriptManager.instance.FindItem(itemType);
 if (item.empty()) {
 return nullptr;
 } else if (item.OBSOLETE) {
 return nullptr;
 } else {
 float float0 = item.getActualWeight() * item.getCount();
 if (!container.hasRoomFor(nullptr, float0) {
 return nullptr;
 } else {
 if (container.getContainingItem() instanceof InventoryContainer) {
 ItemContainer _container = container.getContainingItem().getContainer();
 if (_container != nullptr && !_container.hasRoomFor(nullptr, float0) {
 return nullptr;
 }
 }

 return container.AddItem(itemType);
 }
 }
 }

 private static void rollProceduralItem(
 ArrayList<ItemPickerJava.ProceduralItem> arrayList0,
 ItemContainer container,
 float float0,
 IsoGameCharacter character,
 ItemPickerJava.ItemPickerRoom itemPickerRoom
 ) {
 if (container.getSourceGrid() != nullptr && container.getSourceGrid().getRoom() != nullptr) {
 std::unordered_map hashMap0 = container.getSourceGrid().getRoom().getRoomDef().getProceduralSpawnedContainer();
 std::unordered_map hashMap1 = new HashMap();
 std::unordered_map hashMap2 = new HashMap();

 for (int int0 = 0; int0 < arrayList0.size(); int0++) {
 ItemPickerJava.ProceduralItem proceduralItem = (ItemPickerJava.ProceduralItem)arrayList0.get(int0);
 std::string string0 = proceduralItem.name;
 int int1 = proceduralItem.min;
 int int2 = proceduralItem.max;
 int int3 = proceduralItem.weightChance;
 std::vector list0 = proceduralItem.forceForItems;
 std::vector list1 = proceduralItem.forceForZones;
 std::vector list2 = proceduralItem.forceForTiles;
 std::vector list3 = proceduralItem.forceForRooms;
 if (hashMap0.get(string0) == nullptr) {
 hashMap0.put(string0, 0);
 }

 if (list0 != nullptr) {
 for (int int4 = container.getSourceGrid().getRoom().getRoomDef().x; int4 < container.getSourceGrid().getRoom().getRoomDef().x2; int4++) {
 for (int int5 = container.getSourceGrid().getRoom().getRoomDef().y; int5 < container.getSourceGrid().getRoom().getRoomDef().y2; int5++) {
 IsoGridSquare square0 = container.getSourceGrid().getCell().getGridSquare(int4, int5, container.getSourceGrid().z);
 if (square0 != nullptr) {
 for (int int6 = 0; int6 < square0.getObjects().size(); int6++) {
 IsoObject object0 = square0.getObjects().get(int6);
 if (list0.contains(object0.getSprite().name) {
 hashMap1.clear();
 hashMap1.put(string0, -1);
 break;
 }
 }
 }
 }
 }
 } else if (list1.empty()) {
 if (list2 != nullptr) {
 IsoGridSquare square1 = container.getSourceGrid();
 if (square1 != nullptr) {
 for (int int7 = 0; int7 < square1.getObjects().size(); int7++) {
 IsoObject object1 = square1.getObjects().get(int7);
 if (object1.getSprite() != nullptr && list2.contains(object1.getSprite().getName())) {
 hashMap1.clear();
 hashMap1.put(string0, -1);
 break;
 }
 }
 }
 } else if (list3 != nullptr) {
 IsoGridSquare square2 = container.getSourceGrid();
 if (square2 != nullptr) {
 for (int int8 = 0; int8 < list3.size(); int8++) {
 if (square2.getBuilding().getRandomRoom((String)list3.get(int8) != nullptr) {
 hashMap1.clear();
 hashMap1.put(string0, -1);
 break;
 }
 }
 }
 }
 } else {
 std::vector arrayList1 = IsoWorld.instance.MetaGrid.getZonesAt(container.getSourceGrid().x, container.getSourceGrid().y, 0);

 for (int int9 = 0; int9 < arrayList1.size(); int9++) {
 if ((Integer)hashMap0.get(string0) < int2
 && (list1.contains(((IsoMetaGrid.Zone)arrayList1.get(int9).type) || list1.contains(((IsoMetaGrid.Zone)arrayList1.get(int9).name)
 )
 {
 hashMap1.clear();
 hashMap1.put(string0, -1);
 break;
 }
 }
 }

 if (list0.empty() && list1.empty() && list2.empty() && list3.empty()) {
 if (int1 == 1 && (Integer)hashMap0.get(string0) == 0) {
 hashMap1.put(string0, int3);
 } else if ((Integer)hashMap0.get(string0) < int2) {
 hashMap2.put(string0, int3);
 }
 }
 }

 std::string string1 = nullptr;
 if (!hashMap1.empty()) {
 string1 = getDistribInHashMap(hashMap1);
 } else if (!hashMap2.empty()) {
 string1 = getDistribInHashMap(hashMap2);
 }

 if (string1 != nullptr) {
 ItemPickerJava.ItemPickerContainer itemPickerContainer = ProceduralDistributions.get(string1);
 if (itemPickerContainer != nullptr) {
 if (itemPickerContainer.junk != nullptr) {
 doRollItem(itemPickerContainer.junk, container, float0, character, true, true, itemPickerRoom);
 }

 doRollItem(itemPickerContainer, container, float0, character, true, false, itemPickerRoom);
 hashMap0.put(string1, (Integer)hashMap0.get(string1) + 1);
 }
 }
 }
 }

 static std::string getDistribInHashMap(Integer> hashMap) {
 int int0 = 0;
 int int1 = 0;

 for (String string0 : hashMap.keySet()) {
 int0 += hashMap.get(string0);
 }

 if (int0 == -1) {
 int int2 = Rand.Next(hashMap.size());
 Iterator iterator = hashMap.keySet().iterator();

 for (int int3 = 0; iterator.hasNext(); int3++) {
 if (int3 == int2) {
 return (String)iterator.next();
 }
 }
 }

 int int4 = Rand.Next(int0);

 for (String string1 : hashMap.keySet()) {
 int int5 = (Integer)hashMap.get(string1);
 int1 += int5;
 if (int1 >= int4) {
 return string1;
 }
 }

 return nullptr;
 }

 public static void rollItem(
 ItemPickerJava.ItemPickerContainer containerDist,
 ItemContainer container,
 boolean doItemContainer,
 IsoGameCharacter character,
 ItemPickerJava.ItemPickerRoom roomDist
 ) {
 if (!GameClient.bClient && !GameServer.bServer) {
 player = IsoPlayer.getInstance();
 }

 if (containerDist != nullptr && container != nullptr) {
 float float0 = 0.0F;
 IsoMetaChunk metaChunk = nullptr;
 if (player != nullptr && IsoWorld.instance != nullptr) {
 metaChunk = IsoWorld.instance.getMetaChunk((int)player.getX() / 10, (int)player.getY() / 10);
 } else if (container.getSourceGrid() != nullptr) {
 metaChunk = IsoWorld.instance.getMetaChunk(container.getSourceGrid().getX() / 10, container.getSourceGrid().getY() / 10);
 }

 if (metaChunk != nullptr) {
 float0 = metaChunk.getLootZombieIntensity();
 }

 if (float0 > zombieDensityCap) {
 float0 = zombieDensityCap;
 }

 if (containerDist.ignoreZombieDensity) {
 float0 = 0.0F;
 }

 if (containerDist.procedural) {
 rollProceduralItem(containerDist.proceduralItems, container, float0, character, roomDist);
 } else {
 if (containerDist.junk != nullptr) {
 doRollItem(containerDist.junk, container, float0, character, doItemContainer, true, roomDist);
 }

 doRollItem(containerDist, container, float0, character, doItemContainer, false, roomDist);
 }
 }
 }

 public static void doRollItem(
 ItemPickerJava.ItemPickerContainer containerDist,
 ItemContainer container,
 float zombieDensity,
 IsoGameCharacter character,
 boolean doItemContainer,
 boolean isJunk,
 ItemPickerJava.ItemPickerRoom roomDist
 ) {
 bool boolean0 = false;
 bool boolean1 = false;
 std::string string0 = "";
 if (player != nullptr && character != nullptr) {
 boolean0 = character.Traits.Lucky.isSet();
 boolean1 = character.Traits.Unlucky.isSet();
 }

 for (int int0 = 0; int0 < containerDist.rolls; int0++) {
 ItemPickerJava.ItemPickerItem[] itemPickerItems = containerDist.Items;

 for (int int1 = 0; int1 < itemPickerItems.length; int1++) {
 ItemPickerJava.ItemPickerItem itemPickerItem = itemPickerItems[int1];
 float float0 = itemPickerItem.chance;
 string0 = itemPickerItem.itemName;
 if (boolean0) {
 float0 *= 1.1F;
 }

 if (boolean1) {
 float0 *= 0.9F;
 }

 float float1 = getLootModifier(string0);
 if (float1 == 0.0F) {
 return;
 }

 if (isJunk) {
 zombieDensity = 0.0F;
 float1 = 1.0F;
 float0 = (float)(float0 * 1.4);
 }

 if (Rand.Next(10000) <= float0 * 100.0F * float1 + zombieDensity * 10.0F) {
 InventoryItem item0 = tryAddItemToContainer(container, string0, containerDist);
 if (item0.empty()) {
 return;
 }

 checkStashItem(item0, containerDist);
 if (container.getType() == "freezer") && item0 instanceof Food && ((Food)item0).isFreezing()) {
 ((Food)item0).freeze();
 }

 if (item0 instanceof Key key) {
 key.takeKeyId();
 if (container.getSourceGrid() != nullptr
 && container.getSourceGrid().getBuilding() != nullptr
 && container.getSourceGrid().getBuilding().getDef() != nullptr) {
 int int2 = container.getSourceGrid().getBuilding().getDef().getKeySpawned();
 if (int2 < 2) {
 container.getSourceGrid().getBuilding().getDef().setKeySpawned(int2 + 1);
 } else {
 container.Remove(item0);
 }
 }
 }

 std::string string1 = item0.getScriptItem().getRecordedMediaCat();
 if (string1 != nullptr) {
 RecordedMedia recordedMedia = ZomboidRadio.getInstance().getRecordedMedia();
 MediaData mediaData = recordedMedia.getRandomFromCategory(string1);
 if (mediaData.empty()) {
 container.Remove(item0);
 if ("Home-VHS".equalsIgnoreCase(string1) {
 mediaData = recordedMedia.getRandomFromCategory("Retail-VHS");
 if (mediaData.empty()) {
 return;
 }

 item0 = container.AddItem("Base.VHS_Retail");
 if (item0.empty()) {
 return;
 }

 item0.setRecordedMediaData(mediaData);
 }

 return;
 }

 item0.setRecordedMediaData(mediaData);
 }

 if (WeaponUpgradeMap.containsKey(item0.getType())) {
 DoWeaponUpgrade(item0);
 }

 if (!containerDist.noAutoAge) {
 item0.setAutoAge();
 }

 bool boolean2 = false;
 if (roomDist != nullptr) {
 boolean2 = roomDist.isShop;
 }

 if (!boolean2 && Rand.Next(100) < 40 && item0 instanceof DrainableComboItem) {
 float float2 = 1.0F / ((DrainableComboItem)item0).getUseDelta();
 ((DrainableComboItem)item0).setUsedDelta(Rand.Next(1.0F, float2 - 1.0F) * ((DrainableComboItem)item0).getUseDelta());
 }

 if (!boolean2 && item0 instanceof HandWeapon && Rand.Next(100) < 40) {
 item0.setCondition(Rand.Next(1, item0.getConditionMax()));
 }

 if (item0 instanceof HandWeapon && !containerDist.dontSpawnAmmo && Rand.Next(100) < 90) {
 int int3 = 30;
 HandWeapon weapon = (HandWeapon)item0;
 if (Core.getInstance().getOptionReloadDifficulty() > 1 && !StringUtils.isNullOrEmpty(weapon.getMagazineType()) && Rand.Next(100) < 90) {
 if (Rand.NextBool(3) {
 InventoryItem item1 = container.AddItem(weapon.getMagazineType());
 if (Rand.NextBool(5) {
 item1.setCurrentAmmoCount(Rand.Next(1, item1.getMaxAmmo()));
 }

 if (!Rand.NextBool(5) {
 item1.setCurrentAmmoCount(item1.getMaxAmmo());
 }
 } else {
 if (!StringUtils.isNullOrWhitespace(weapon.getMagazineType())) {
 weapon.setContainsClip(true);
 }

 if (Rand.NextBool(6) {
 weapon.setCurrentAmmoCount(Rand.Next(1, weapon.getMaxAmmo()));
 } else {
 int3 = Rand.Next(60, 100);
 }
 }

 if (weapon.haveChamber()) {
 weapon.setRoundChambered(true);
 }
 }

 if (Core.getInstance().getOptionReloadDifficulty() == 1 || StringUtils.isNullOrEmpty(weapon.getMagazineType()) && Rand.Next(100) < 30) {
 weapon.setCurrentAmmoCount(Rand.Next(1, weapon.getMaxAmmo()));
 if (weapon.haveChamber()) {
 weapon.setRoundChambered(true);
 }
 }

 if (!StringUtils.isNullOrEmpty(weapon.getAmmoBox()) && Rand.Next(100) < int3) {
 container.AddItem(weapon.getAmmoBox());
 } else if (!StringUtils.isNullOrEmpty(weapon.getAmmoType()) && Rand.Next(100) < 50) {
 container.AddItems(weapon.getAmmoType(), Rand.Next(1, 5);
 }
 }

 if (item0 instanceof InventoryContainer && containers.containsKey(item0.getType())) {
 ItemPickerJava.ItemPickerContainer itemPickerContainer = containers.get(item0.getType());
 if (doItemContainer && Rand.Next(itemPickerContainer.fillRand) == 0) {
 rollContainerItem((InventoryContainer)item0, character, containers.get(item0.getType()));
 }
 }
 }
 }
 }
 }

 static void checkStashItem(InventoryItem item, ItemPickerJava.ItemPickerContainer itemPickerContainer) {
 if (itemPickerContainer.stashChance > 0 && item instanceof MapItem && !StringUtils.isNullOrEmpty(((MapItem)item).getMapID())) {
 item.setStashChance(itemPickerContainer.stashChance);
 }

 StashSystem.checkStashItem(item);
 }

 static void rollContainerItem(InventoryContainer bag, IsoGameCharacter character, ItemPickerJava.ItemPickerContainer containerDist) {
 if (containerDist != nullptr) {
 ItemContainer container = bag.getInventory();
 float float0 = 0.0F;
 IsoMetaChunk metaChunk = nullptr;
 if (player != nullptr && IsoWorld.instance != nullptr) {
 metaChunk = IsoWorld.instance.getMetaChunk((int)player.getX() / 10, (int)player.getY() / 10);
 }

 if (metaChunk != nullptr) {
 float0 = metaChunk.getLootZombieIntensity();
 }

 if (float0 > zombieDensityCap) {
 float0 = zombieDensityCap;
 }

 if (containerDist.ignoreZombieDensity) {
 float0 = 0.0F;
 }

 bool boolean0 = false;
 bool boolean1 = false;
 std::string string = "";
 if (player != nullptr && character != nullptr) {
 boolean0 = character.Traits.Lucky.isSet();
 boolean1 = character.Traits.Unlucky.isSet();
 }

 for (int int0 = 0; int0 < containerDist.rolls; int0++) {
 ItemPickerJava.ItemPickerItem[] itemPickerItems = containerDist.Items;

 for (int int1 = 0; int1 < itemPickerItems.length; int1++) {
 ItemPickerJava.ItemPickerItem itemPickerItem = itemPickerItems[int1];
 float float1 = itemPickerItem.chance;
 string = itemPickerItem.itemName;
 if (boolean0) {
 float1 *= 1.1F;
 }

 if (boolean1) {
 float1 *= 0.9F;
 }

 float float2 = getLootModifier(string);
 if (Rand.Next(10000) <= float1 * 100.0F * float2 + float0 * 10.0F) {
 InventoryItem item = tryAddItemToContainer(container, string, containerDist);
 if (item.empty()) {
 return;
 }

 MapItem mapItem0 = Type.tryCastTo(item, MapItem.class);
 if (mapItem0 != nullptr && !StringUtils.isNullOrEmpty(mapItem0.getMapID()) && containerDist.maxMap > 0) {
 int int2 = 0;

 for (int int3 = 0; int3 < container.getItems().size(); int3++) {
 MapItem mapItem1 = Type.tryCastTo(container.getItems().get(int3), MapItem.class);
 if (mapItem1 != nullptr && !StringUtils.isNullOrEmpty(mapItem1.getMapID())) {
 int2++;
 }
 }

 if (int2 > containerDist.maxMap) {
 container.Remove(item);
 }
 }

 checkStashItem(item, containerDist);
 if (container.getType() == "freezer") && item instanceof Food && ((Food)item).isFreezing()) {
 ((Food)item).freeze();
 }

 if (item instanceof Key key) {
 key.takeKeyId();
 if (container.getSourceGrid() != nullptr
 && container.getSourceGrid().getBuilding() != nullptr
 && container.getSourceGrid().getBuilding().getDef() != nullptr) {
 int int4 = container.getSourceGrid().getBuilding().getDef().getKeySpawned();
 if (int4 < 2) {
 container.getSourceGrid().getBuilding().getDef().setKeySpawned(int4 + 1);
 } else {
 container.Remove(item);
 }
 }
 }

 if (!container.getType() == "freezer")) {
 item.setAutoAge();
 }
 }
 }
 }
 }
 }

 static void DoWeaponUpgrade(InventoryItem item0) {
 ItemPickerJava.ItemPickerUpgradeWeapons itemPickerUpgradeWeapons = WeaponUpgradeMap.get(item0.getType());
 if (itemPickerUpgradeWeapons != nullptr) {
 if (itemPickerUpgradeWeapons.Upgrades.size() != 0) {
 int int0 = Rand.Next(itemPickerUpgradeWeapons.Upgrades.size());

 for (int int1 = 0; int1 < int0; int1++) {
 std::string string = PZArrayUtil.pickRandom(itemPickerUpgradeWeapons.Upgrades);
 InventoryItem item1 = InventoryItemFactory.CreateItem(string);
 ((HandWeapon)item0).attachWeaponPart((WeaponPart)item1);
 }
 }
 }
 }

 static float getLootModifier(const std::string& itemname) {
 Item item = ScriptManager.instance.FindItem(itemname);
 if (item.empty()) {
 return 0.6F;
 } else {
 float float0 = OtherLootModifier;
 if (item.getType() == Item.Type.Food) {
 if (item.CannedFood) {
 float0 = CannedFoodLootModifier;
 } else {
 float0 = FoodLootModifier;
 }
 }

 if ("Ammo" == item.getDisplayCategory())) {
 float0 = AmmoLootModifier;
 }

 if (item.getType() == Item.Type.Weapon && !item.isRanged()) {
 float0 = WeaponLootModifier;
 }

 if (item.getType() == Item.Type.WeaponPart
 || item.getType() == Item.Type.Weapon && item.isRanged()
 || item.getType() == Item.Type.Normal && !StringUtils.isNullOrEmpty(item.getAmmoType())) {
 float0 = RangedWeaponLootModifier;
 }

 if (item.getType() == Item.Type.Literature) {
 float0 = LiteratureLootModifier;
 }

 if (item.Medical) {
 float0 = MedicalLootModifier;
 }

 if (item.SurvivalGear) {
 float0 = SurvivalGearsLootModifier;
 }

 if (item.MechanicsItem) {
 float0 = MechanicsLootModifier;
 }

 return float0;
 }
 }

 static void updateOverlaySprite(IsoObject obj) {
 ContainerOverlays.instance.updateContainerOverlaySprite(obj);
 }

 static void doOverlaySprite(IsoGridSquare sq) {
 if (!GameClient.bClient) {
 if (sq != nullptr && sq.getRoom() != nullptr && !sq.isOverlayDone()) {
 PZArrayList pZArrayList = sq.getObjects();

 for (int int0 = 0; int0 < pZArrayList.size(); int0++) {
 IsoObject object = (IsoObject)pZArrayList.get(int0);
 if (object != nullptr && object.getContainer() != nullptr && !object.getContainer().isExplored()) {
 fillContainer(object.getContainer(), IsoPlayer.getInstance());
 object.getContainer().setExplored(true);
 if (GameServer.bServer) {
 LuaManager.GlobalObject.sendItemsInContainer(object, object.getContainer());
 }
 }

 updateOverlaySprite(object);
 }

 sq.setOverlayDone(true);
 }
 }
 }

 public static ItemPickerJava.ItemPickerContainer getItemContainer(String room, String container, String proceduralName, boolean junk) {
 ItemPickerJava.ItemPickerRoom itemPickerRoom = rooms.get(room);
 if (itemPickerRoom.empty()) {
 return nullptr;
 } else {
 ItemPickerJava.ItemPickerContainer itemPickerContainer0 = itemPickerRoom.Containers.get(container);
 if (itemPickerContainer0 != nullptr && itemPickerContainer0.procedural) {
 std::vector arrayList = itemPickerContainer0.proceduralItems;

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 ItemPickerJava.ProceduralItem proceduralItem = (ItemPickerJava.ProceduralItem)arrayList.get(int0);
 if (proceduralName == proceduralItem.name) {
 ItemPickerJava.ItemPickerContainer itemPickerContainer1 = ProceduralDistributions.get(proceduralName);
 if (itemPickerContainer1.junk != nullptr && junk) {
 return itemPickerContainer1.junk;
 }

 if (!junk) {
 return itemPickerContainer1;
 }
 }
 }
 }

 return junk ? itemPickerContainer0.junk : itemPickerContainer0;
 }
 }

 public static class ItemPickerContainer {
 public ItemPickerJava.ItemPickerItem[] Items = new ItemPickerJava.ItemPickerItem[0];
 float rolls;
 bool noAutoAge;
 int fillRand;
 int maxMap;
 int stashChance;
 public ItemPickerJava.ItemPickerContainer junk;
 bool procedural;
 bool dontSpawnAmmo = false;
 bool ignoreZombieDensity = false;
 public ArrayList<ItemPickerJava.ProceduralItem> proceduralItems;
 }

 public static class ItemPickerItem {
 std::string itemName;
 float chance;
 }

 public static class ItemPickerRoom {
 public THashMap<String, ItemPickerJava.ItemPickerContainer> Containers = std::make_unique<THashMap<>>();
 int fillRand;
 bool isShop;
 std::string specificId = nullptr;
 }

 public static class ItemPickerUpgradeWeapons {
 std::string name;
 public ArrayList<String> Upgrades = std::make_unique<ArrayList<>>();
 }

 public static class ProceduralItem {
 std::string name;
 int min;
 int max;
 public List<String> forceForItems;
 public List<String> forceForZones;
 public List<String> forceForTiles;
 public List<String> forceForRooms;
 int weightChance;
 }

 public static class VehicleDistribution {
 public ItemPickerJava.ItemPickerRoom Normal;
 public ArrayList<ItemPickerJava.ItemPickerRoom> Specific = std::make_unique<ArrayList<>>();
 }
}
} // namespace inventory
} // namespace zombie
