#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/integration/LuaReturn.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SystemDisabler.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/types/AlarmClock.h"
#include "zombie/inventory/types/AlarmClockClothing.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/inventory/types/Drainable.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/inventory/types/Key.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoBarbecue.h"
#include "zombie/iso/objects/IsoCompost.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoFireplace.h"
#include "zombie/iso/objects/IsoMannequin.h"
#include "zombie/iso/objects/IsoStove.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehiclePart.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ItemContainer {
public:
 private static ArrayList<InventoryItem> tempList = std::make_unique<ArrayList<>>();
 private static ArrayList<IsoObject> s_tempObjects = std::make_unique<ArrayList<>>();
 bool active = false;
 bool dirty = true;
 bool IsDevice = false;
 float ageFactor = 1.0F;
 float CookingFactor = 1.0F;
 int Capacity = 50;
 InventoryItem containingItem = nullptr;
 public ArrayList<InventoryItem> Items = std::make_unique<ArrayList<>>();
 public ArrayList<InventoryItem> IncludingObsoleteItems = std::make_unique<ArrayList<>>();
 IsoObject parent = nullptr;
 IsoGridSquare SourceGrid = nullptr;
 VehiclePart vehiclePart = nullptr;
 InventoryContainer inventoryContainer = nullptr;
 bool bExplored = false;
 std::string type = "none";
 int ID = 0;
 bool drawDirty = true;
 float customTemperature = 0.0F;
 bool hasBeenLooted = false;
 std::string openSound = nullptr;
 std::string closeSound = nullptr;
 std::string putSound = nullptr;
 std::string OnlyAcceptCategory = nullptr;
 std::string AcceptItemFunction = nullptr;
 int weightReduction = 0;
 std::string containerPosition = nullptr;
 std::string freezerPosition = nullptr;
 private static ThreadLocal<ItemContainer.Comparators> TL_comparators = ThreadLocal.withInitial(ItemContainer.Comparators::new);
 private static ThreadLocal<ItemContainer.InventoryItemListPool> TL_itemListPool = ThreadLocal.withInitial(ItemContainer.InventoryItemListPool::new);
 private static ThreadLocal<ItemContainer.Predicates> TL_predicates = ThreadLocal.withInitial(ItemContainer.Predicates::new);

 public ItemContainer(int _ID, const std::string& containerName, IsoGridSquare square, IsoObject _parent) {
 this->ID = _ID;
 this->parent = _parent;
 this->type = containerName;
 this->SourceGrid = square;
 if (containerName == "fridge")) {
 this->ageFactor = 0.02F;
 this->CookingFactor = 0.0F;
 }
 }

 public ItemContainer(const std::string& containerName, IsoGridSquare square, IsoObject _parent) {
 this->ID = -1;
 this->parent = _parent;
 this->type = containerName;
 this->SourceGrid = square;
 if (containerName == "fridge")) {
 this->ageFactor = 0.02F;
 this->CookingFactor = 0.0F;
 }
 }

 public ItemContainer(int _ID) {
 this->ID = _ID;
 }

 public ItemContainer() {
 this->ID = -1;
 }

 static float floatingPointCorrection(float val) {
 uint8_t byte0 = 100;
 float float0 = val * byte0;
 return (float)((int)(float0 - (int)float0 >= 0.5F ? float0 + 1.0F : float0) / byte0;
 }

 int getCapacity() {
 return this->Capacity;
 }

 void setCapacity(int int0) {
 this->Capacity = int0;
 }

 InventoryItem FindAndReturnWaterItem(int uses) {
 for (int int0 = 0; int0 < this->getItems().size(); int0++) {
 InventoryItem item = this->getItems().get(int0);
 if (item instanceof DrainableComboItem && item.isWaterSource()) {
 DrainableComboItem drainableComboItem = (DrainableComboItem)item;
 if (drainableComboItem.getDrainableUsesInt() >= uses) {
 return item;
 }
 }
 }

 return nullptr;
 }

 InventoryItem getItemFromTypeRecurse(const std::string& _type) {
 return this->getFirstTypeRecurse(_type);
 }

 int getEffectiveCapacity(IsoGameCharacter chr) {
 if (chr != nullptr && !(this->parent instanceof IsoGameCharacter) && !(this->parent instanceof IsoDeadBody) && !"floor" == this->getType())) {
 if (chr.Traits.Organized.isSet()) {
 return (int)Math.max(this->Capacity * 1.3F, (float)(this->Capacity + 1);
 }

 if (chr.Traits.Disorganized.isSet()) {
 return (int)Math.max(this->Capacity * 0.7F, 1.0F);
 }
 }

 return this->Capacity;
 }

 bool hasRoomFor(IsoGameCharacter chr, InventoryItem item) {
 if (this->vehiclePart != nullptr && this->vehiclePart.getId().contains("Seat") && this->Items.empty() && item.getUnequippedWeight() <= 50.0F) {
 return true;
 } else if (floatingPointCorrection(this->getCapacityWeight()) + item.getUnequippedWeight() <= this->getEffectiveCapacity(chr) {
 return this->getContainingItem() != nullptr
 && this->getContainingItem().getEquipParent() != nullptr
 && this->getContainingItem().getEquipParent().getInventory() != nullptr
 && !this->getContainingItem().getEquipParent().getInventory().contains(item)
 ? floatingPointCorrection(this->getContainingItem().getEquipParent().getInventory().getCapacityWeight()) + item.getUnequippedWeight()
 <= this->getContainingItem().getEquipParent().getInventory().getEffectiveCapacity(chr)
 : true;
 } else {
 return false;
 }
 }

 bool hasRoomFor(IsoGameCharacter chr, float weightVal) {
 return floatingPointCorrection();
 }

 bool isItemAllowed(InventoryItem item) {
 if (item.empty()) {
 return false;
 } else {
 std::string string0 = this->getOnlyAcceptCategory();
 if (string0 != nullptr && !string0.equalsIgnoreCase(item.getCategory())) {
 return false;
 } else {
 std::string string1 = this->getAcceptItemFunction();
 if (string1 != nullptr) {
 void* object = LuaManager.getFunctionObject(string1);
 if (object != nullptr) {
 bool boolean0 = LuaManager.caller.protectedCallBoolean(LuaManager.thread, object, this, item);
 if (boolean0 != Boolean.TRUE) {
 return false;
 }
 }
 }

 if (this->parent != nullptr && !this->parent.isItemAllowedInContainer(this, item) {
 return false;
 } else if (this->getType() == "clothingrack") && !(item instanceof Clothing) {
 return false;
 } else if (this->getParent() != nullptr
 && this->getParent().getProperties() != nullptr
 && this->getParent().getProperties().Val("CustomName") != nullptr
 && this->getParent().getProperties().Val("CustomName") == "Toaster")
 && !item.hasTag("FitsToaster")) {
 return false;
 } else {
 if (this->getParent() != nullptr && this->getParent().getProperties() != nullptr && this->getParent().getProperties().Val("GroupName") != nullptr) {
 boolean boolean1 = this->getParent().getProperties().Val("GroupName") == "Coffee")
 || this->getParent().getProperties().Val("GroupName") == "Espresso");
 if (boolean1 && !item.hasTag("CoffeeMaker")) {
 return false;
 }
 }

 return true;
 }
 }
 }
 }

 bool isRemoveItemAllowed(InventoryItem item) {
 return item = = nullptr ? false : this->parent == nullptr || this->parent.isRemoveItemAllowedFromContainer(this, item);
 }

 bool isExplored() {
 return this->bExplored;
 }

 void setExplored(bool b) {
 this->bExplored = b;
 }

 bool isInCharacterInventory(IsoGameCharacter chr) {
 if (chr.getInventory() == this) {
 return true;
 } else {
 if (this->containingItem != nullptr) {
 if (chr.getInventory().contains(this->containingItem, true) {
 return true;
 }

 if (this->containingItem.getContainer() != nullptr) {
 return this->containingItem.getContainer().isInCharacterInventory(chr);
 }
 }

 return false;
 }
 }

 bool isInside(InventoryItem item) {
 if (this->containingItem.empty()) {
 return false;
 } else {
 return this->containingItem == item ? true : this->containingItem.getContainer() != nullptr && this->containingItem.getContainer().isInside(item);
 }
 }

 InventoryItem getContainingItem() {
 return this->containingItem;
 }

 InventoryItem DoAddItem(InventoryItem item) {
 return this->AddItem(item);
 }

 InventoryItem DoAddItemBlind(InventoryItem item) {
 return this->AddItem(item);
 }

 public ArrayList<InventoryItem> AddItems(String item, int use) {
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < use; int0++) {
 InventoryItem _item = this->AddItem(item);
 if (_item != nullptr) {
 arrayList.add(_item);
 }
 }

 return arrayList;
 }

 void AddItems(InventoryItem item, int use) {
 for (int int0 = 0; int0 < use; int0++) {
 this->AddItem(item.getFullType());
 }
 }

 int getNumberOfItem(const std::string& findItem, bool includeReplaceOnDeplete) {
 return this->getNumberOfItem(findItem, includeReplaceOnDeplete, false);
 }

 int getNumberOfItem(const std::string& findItem) {
 return this->getNumberOfItem(findItem, false);
 }

 int getNumberOfItem(const std::string& findItem, bool includeReplaceOnDeplete, ArrayList<ItemContainer> containers) {
 int int0 = this->getNumberOfItem(findItem, includeReplaceOnDeplete);
 if (containers != nullptr) {
 for (auto& container : containers) if (container != this) {
 int0 += container.getNumberOfItem(findItem, includeReplaceOnDeplete);
 }
 }
 }

 return int0;
 }

 int getNumberOfItem(const std::string& findItem, bool includeReplaceOnDeplete, bool insideInv) {
 int int0 = 0;

 for (int int1 = 0; int1 < this->Items.size(); int1++) {
 InventoryItem item = this->Items.get(int1);
 if (item.getFullType() == findItem) || item.getType() == findItem) {
 int0++;
 } else if (insideInv && item instanceof InventoryContainer) {
 int0 += ((InventoryContainer)item).getItemContainer().getNumberOfItem(findItem);
 } else if (includeReplaceOnDeplete && item instanceof DrainableComboItem && ((DrainableComboItem)item).getReplaceOnDeplete() != nullptr) {
 DrainableComboItem drainableComboItem = (DrainableComboItem)item;
 if (drainableComboItem.getReplaceOnDepleteFullType() == findItem) || drainableComboItem.getReplaceOnDeplete() == findItem) {
 int0++;
 }
 }
 }

 return int0;
 }

 InventoryItem addItem(InventoryItem item) {
 return this->AddItem(item);
 }

 InventoryItem AddItem(InventoryItem item) {
 if (item.empty()) {
 return nullptr;
 } else if (this->containsID(item.id) {
 System.out.println("Error, container already has id");
 return this->getItemWithID(item.id);
 } else {
 this->drawDirty = true;
 if (this->parent != nullptr) {
 this->dirty = true;
 }

 if (this->parent != nullptr && !(this->parent instanceof IsoGameCharacter) {
 this->parent.DirtySlice();
 }

 if (item.container != nullptr) {
 item.container.Remove(item);
 }

 item.container = this;
 this->Items.add(item);
 if (IsoWorld.instance.CurrentCell != nullptr) {
 IsoWorld.instance.CurrentCell.addToProcessItems(item);
 }

 return item;
 }
 }

 InventoryItem AddItemBlind(InventoryItem item) {
 if (item.empty()) {
 return nullptr;
 } else if (item.getWeight() + this->getCapacityWeight() > this->getCapacity()) {
 return nullptr;
 } else {
 if (this->parent != nullptr && !(this->parent instanceof IsoGameCharacter) {
 this->parent.DirtySlice();
 }

 this->Items.add(item);
 return item;
 }
 }

 InventoryItem AddItem(const std::string& _type) {
 this->drawDirty = true;
 if (this->parent != nullptr && !(this->parent instanceof IsoGameCharacter) {
 this->dirty = true;
 }

 Item item0 = ScriptManager.instance.FindItem(_type);
 if (item0.empty()) {
 DebugLog.log("ERROR: ItemContainer.AddItem: can't find " + _type);
 return nullptr;
 } else if (item0.OBSOLETE) {
 return nullptr;
 } else {
 InventoryItem item1 = nullptr;
 int int0 = item0.getCount();

 for (int int1 = 0; int1 < int0; int1++) {
 item1 = InventoryItemFactory.CreateItem(_type);
 if (item1.empty()) {
 return nullptr;
 }

 item1.container = this;
 this->Items.add(item1);
 if (item1 instanceof Food) {
 ((Food)item1).setHeat(this->getTemprature());
 }

 if (IsoWorld.instance.CurrentCell != nullptr) {
 IsoWorld.instance.CurrentCell.addToProcessItems(item1);
 }
 }

 return item1;
 }
 }

 bool AddItem(const std::string& _type, float useDelta) {
 this->drawDirty = true;
 if (this->parent != nullptr && !(this->parent instanceof IsoGameCharacter) {
 this->dirty = true;
 }

 InventoryItem item = InventoryItemFactory.CreateItem(_type);
 if (item.empty()) {
 return false;
 } else {
 if (item instanceof Drainable) {
 ((Drainable)item).setUsedDelta(useDelta);
 }

 item.container = this;
 this->Items.add(item);
 return true;
 }
 }

 bool contains(InventoryItem item) {
 return this->Items.contains(item);
 }

 bool containsWithModule(const std::string& moduleType) {
 return this->containsWithModule(moduleType, false);
 }

 bool containsWithModule(const std::string& moduleType, bool withDeltaLeft) {
 std::string string0 = moduleType;
 std::string string1 = "Base";
 if (moduleType.contains(".")) {
 string1 = moduleType.split("\\.")[0];
 string0 = moduleType.split("\\.")[1];
 }

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.empty()) {
 this->Items.remove(int0);
 int0--;
 } else if (item.type == string0.trim())
 && string1 == item.getModule())
 && (!withDeltaLeft || !(item instanceof DrainableComboItem) || !(((DrainableComboItem)item).getUsedDelta() <= 0.0F)) {
 return true;
 }
 }

 return false;
 }

 void removeItemOnServer(InventoryItem item) {
 if (GameClient.bClient) {
 if (this->containingItem != nullptr && this->containingItem.getWorldItem() != nullptr) {
 GameClient.instance.addToItemRemoveSendBuffer(this->containingItem.getWorldItem(), this, item);
 } else {
 GameClient.instance.addToItemRemoveSendBuffer(this->parent, this, item);
 }
 }
 }

 void addItemOnServer(InventoryItem item) {
 if (GameClient.bClient) {
 if (this->containingItem != nullptr && this->containingItem.getWorldItem() != nullptr) {
 GameClient.instance.addToItemSendBuffer(this->containingItem.getWorldItem(), this, item);
 } else {
 GameClient.instance.addToItemSendBuffer(this->parent, this, item);
 }
 }
 }

 bool contains(InventoryItem itemToFind, bool doInv) {
 ItemContainer.InventoryItemList inventoryItemList = TL_itemListPool.get().alloc();

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.empty()) {
 this->Items.remove(int0);
 int0--;
 } else {
 if (item == itemToFind) {
 TL_itemListPool.get().release(inventoryItemList);
 return true;
 }

 if (doInv && item instanceof InventoryContainer && ((InventoryContainer)item).getInventory() != nullptr && !inventoryItemList.contains(item) {
 inventoryItemList.add(item);
 }
 }
 }

 for (int int1 = 0; int1 < inventoryItemList.size(); int1++) {
 ItemContainer container = ((InventoryContainer)inventoryItemList.get(int1).getInventory();
 if (container.contains(itemToFind, doInv) {
 TL_itemListPool.get().release(inventoryItemList);
 return true;
 }
 }

 TL_itemListPool.get().release(inventoryItemList);
 return false;
 }

 bool contains(const std::string& _type, bool doInv) {
 return this->contains(_type, doInv, false);
 }

 bool containsType(const std::string& _type) {
 return this->contains(_type, false, false);
 }

 bool containsTypeRecurse(const std::string& _type) {
 return this->contains(_type, true, false);
 }

 bool testBroken(bool boolean0, InventoryItem item) {
 return !boolean0 ? true : !item.isBroken();
 }

 bool contains(const std::string& _type, bool doInv, bool ignoreBroken) {
 ItemContainer.InventoryItemList inventoryItemList = TL_itemListPool.get().alloc();
 if (_type.contains("Type:")) {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item0 = this->Items.get(int0);
 if (_type.contains("Food") && item0 instanceof Food) {
 TL_itemListPool.get().release(inventoryItemList);
 return true;
 }

 if (_type.contains("Weapon") && item0 instanceof HandWeapon && this->testBroken(ignoreBroken, item0) {
 TL_itemListPool.get().release(inventoryItemList);
 return true;
 }

 if (_type.contains("AlarmClock") && item0 instanceof AlarmClock) {
 TL_itemListPool.get().release(inventoryItemList);
 return true;
 }

 if (_type.contains("AlarmClockClothing") && item0 instanceof AlarmClockClothing) {
 TL_itemListPool.get().release(inventoryItemList);
 return true;
 }

 if (doInv && item0 instanceof InventoryContainer && ((InventoryContainer)item0).getInventory() != nullptr && !inventoryItemList.contains(item0) {
 inventoryItemList.add(item0);
 }
 }
 } else if (_type.contains("/")) {
 String[] strings = _type.split("/");

 for (auto& string : strings) for (int int1 = 0; int1 < this->Items.size(); int1++) {
 InventoryItem item1 = this->Items.get(int1);
 if (compareType(string.trim(), item1) && this->testBroken(ignoreBroken, item1) {
 TL_itemListPool.get().release(inventoryItemList);
 return true;
 }

 if (doInv
 && item1 instanceof InventoryContainer
 && ((InventoryContainer)item1).getInventory() != nullptr
 && !inventoryItemList.contains(item1) {
 inventoryItemList.add(item1);
 }
 }
 }
 } else {
 for (int int2 = 0; int2 < this->Items.size(); int2++) {
 InventoryItem item2 = this->Items.get(int2);
 if (item2.empty()) {
 this->Items.remove(int2);
 int2--;
 } else {
 if (compareType(_type.trim(), item2) && this->testBroken(ignoreBroken, item2) {
 TL_itemListPool.get().release(inventoryItemList);
 return true;
 }

 if (doInv
 && item2 instanceof InventoryContainer
 && ((InventoryContainer)item2).getInventory() != nullptr
 && !inventoryItemList.contains(item2) {
 inventoryItemList.add(item2);
 }
 }
 }
 }

 for (int int3 = 0; int3 < inventoryItemList.size(); int3++) {
 ItemContainer container = ((InventoryContainer)inventoryItemList.get(int3).getInventory();
 if (container.contains(_type, doInv, ignoreBroken) {
 TL_itemListPool.get().release(inventoryItemList);
 return true;
 }
 }

 TL_itemListPool.get().release(inventoryItemList);
 return false;
 }

 bool contains(const std::string& _type) {
 return this->contains(_type, false);
 }

 static InventoryItem getBestOf(ItemContainer.InventoryItemList inventoryItemList, Comparator<InventoryItem> comparator) {
 if (inventoryItemList != nullptr && !inventoryItemList.empty()) {
 InventoryItem item0 = inventoryItemList.get(0);

 for (int int0 = 1; int0 < inventoryItemList.size(); int0++) {
 InventoryItem item1 = inventoryItemList.get(int0);
 if (comparator.compare(item1, item0) > 0) {
 item0 = item1;
 }
 }

 return item0;
 } else {
 return nullptr;
 }
 }

 InventoryItem getBest(Predicate<InventoryItem> predicate, Comparator<InventoryItem> comparator) {
 ItemContainer.InventoryItemList inventoryItemList = TL_itemListPool.get().alloc();
 this->getAll(predicate, inventoryItemList);
 InventoryItem item = getBestOf(inventoryItemList, comparator);
 TL_itemListPool.get().release(inventoryItemList);
 return item;
 }

 InventoryItem getBestRecurse(Predicate<InventoryItem> predicate, Comparator<InventoryItem> comparator) {
 ItemContainer.InventoryItemList inventoryItemList = TL_itemListPool.get().alloc();
 this->getAllRecurse(predicate, inventoryItemList);
 InventoryItem item = getBestOf(inventoryItemList, comparator);
 TL_itemListPool.get().release(inventoryItemList);
 return item;
 }

 InventoryItem getBestType(const std::string& _type, Comparator<InventoryItem> comparator) {
 ItemContainer.TypePredicate typePredicate = TL_predicates.get().type.alloc().init(_type);

 InventoryItem item;
 try {
 item = this->getBest(typePredicate, comparator);
 } finally {
 TL_predicates.get().type.release(typePredicate);
 }

 return item;
 }

 InventoryItem getBestTypeRecurse(const std::string& _type, Comparator<InventoryItem> comparator) {
 ItemContainer.TypePredicate typePredicate = TL_predicates.get().type.alloc().init(_type);

 InventoryItem item;
 try {
 item = this->getBestRecurse(typePredicate, comparator);
 } finally {
 TL_predicates.get().type.release(typePredicate);
 }

 return item;
 }

 InventoryItem getBestEval(LuaClosure predicateObj, LuaClosure comparatorObj) {
 ItemContainer.EvalPredicate evalPredicate = TL_predicates.get().eval.alloc().init(predicateObj);
 ItemContainer.EvalComparator evalComparator = TL_comparators.get().eval.alloc().init(comparatorObj);

 InventoryItem item;
 try {
 item = this->getBest(evalPredicate, evalComparator);
 } finally {
 TL_predicates.get().eval.release(evalPredicate);
 TL_comparators.get().eval.release(evalComparator);
 }

 return item;
 }

 InventoryItem getBestEvalRecurse(LuaClosure predicateObj, LuaClosure comparatorObj) {
 ItemContainer.EvalPredicate evalPredicate = TL_predicates.get().eval.alloc().init(predicateObj);
 ItemContainer.EvalComparator evalComparator = TL_comparators.get().eval.alloc().init(comparatorObj);

 InventoryItem item;
 try {
 item = this->getBestRecurse(evalPredicate, evalComparator);
 } finally {
 TL_predicates.get().eval.release(evalPredicate);
 TL_comparators.get().eval.release(evalComparator);
 }

 return item;
 }

 InventoryItem getBestEvalArg(LuaClosure predicateObj, LuaClosure comparatorObj, void* arg) {
 ItemContainer.EvalArgPredicate evalArgPredicate = TL_predicates.get().evalArg.alloc().init(predicateObj, arg);
 ItemContainer.EvalArgComparator evalArgComparator = TL_comparators.get().evalArg.alloc().init(comparatorObj, arg);

 InventoryItem item;
 try {
 item = this->getBest(evalArgPredicate, evalArgComparator);
 } finally {
 TL_predicates.get().evalArg.release(evalArgPredicate);
 TL_comparators.get().evalArg.release(evalArgComparator);
 }

 return item;
 }

 InventoryItem getBestEvalArgRecurse(LuaClosure predicateObj, LuaClosure comparatorObj, void* arg) {
 ItemContainer.EvalArgPredicate evalArgPredicate = TL_predicates.get().evalArg.alloc().init(predicateObj, arg);
 ItemContainer.EvalArgComparator evalArgComparator = TL_comparators.get().evalArg.alloc().init(comparatorObj, arg);

 InventoryItem item;
 try {
 item = this->getBestRecurse(evalArgPredicate, evalArgComparator);
 } finally {
 TL_predicates.get().evalArg.release(evalArgPredicate);
 TL_comparators.get().evalArg.release(evalArgComparator);
 }

 return item;
 }

 InventoryItem getBestTypeEval(const std::string& _type, LuaClosure comparatorObj) {
 ItemContainer.TypePredicate typePredicate = TL_predicates.get().type.alloc().init(_type);
 ItemContainer.EvalComparator evalComparator = TL_comparators.get().eval.alloc().init(comparatorObj);

 InventoryItem item;
 try {
 item = this->getBest(typePredicate, evalComparator);
 } finally {
 TL_predicates.get().type.release(typePredicate);
 TL_comparators.get().eval.release(evalComparator);
 }

 return item;
 }

 InventoryItem getBestTypeEvalRecurse(const std::string& _type, LuaClosure comparatorObj) {
 ItemContainer.TypePredicate typePredicate = TL_predicates.get().type.alloc().init(_type);
 ItemContainer.EvalComparator evalComparator = TL_comparators.get().eval.alloc().init(comparatorObj);

 InventoryItem item;
 try {
 item = this->getBestRecurse(typePredicate, evalComparator);
 } finally {
 TL_predicates.get().type.release(typePredicate);
 TL_comparators.get().eval.release(evalComparator);
 }

 return item;
 }

 InventoryItem getBestTypeEvalArg(const std::string& _type, LuaClosure comparatorObj, void* arg) {
 ItemContainer.TypePredicate typePredicate = TL_predicates.get().type.alloc().init(_type);
 ItemContainer.EvalArgComparator evalArgComparator = TL_comparators.get().evalArg.alloc().init(comparatorObj, arg);

 InventoryItem item;
 try {
 item = this->getBest(typePredicate, evalArgComparator);
 } finally {
 TL_predicates.get().type.release(typePredicate);
 TL_comparators.get().evalArg.release(evalArgComparator);
 }

 return item;
 }

 InventoryItem getBestTypeEvalArgRecurse(const std::string& _type, LuaClosure comparatorObj, void* arg) {
 ItemContainer.TypePredicate typePredicate = TL_predicates.get().type.alloc().init(_type);
 ItemContainer.EvalArgComparator evalArgComparator = TL_comparators.get().evalArg.alloc().init(comparatorObj, arg);

 InventoryItem item;
 try {
 item = this->getBestRecurse(typePredicate, evalArgComparator);
 } finally {
 TL_predicates.get().type.release(typePredicate);
 TL_comparators.get().evalArg.release(evalArgComparator);
 }

 return item;
 }

 InventoryItem getBestCondition(Predicate<InventoryItem> predicate) {
 ItemContainer.ConditionComparator conditionComparator = TL_comparators.get().condition.alloc();
 InventoryItem item = this->getBest(predicate, conditionComparator);
 TL_comparators.get().condition.release(conditionComparator);
 if (item != nullptr && item.getCondition() <= 0) {
 item = nullptr;
 }

 return item;
 }

 InventoryItem getBestConditionRecurse(Predicate<InventoryItem> predicate) {
 ItemContainer.ConditionComparator conditionComparator = TL_comparators.get().condition.alloc();
 InventoryItem item = this->getBestRecurse(predicate, conditionComparator);
 TL_comparators.get().condition.release(conditionComparator);
 if (item != nullptr && item.getCondition() <= 0) {
 item = nullptr;
 }

 return item;
 }

 InventoryItem getBestCondition(const std::string& _type) {
 ItemContainer.TypePredicate typePredicate = TL_predicates.get().type.alloc().init(_type);
 InventoryItem item = this->getBestCondition(typePredicate);
 TL_predicates.get().type.release(typePredicate);
 return item;
 }

 InventoryItem getBestConditionRecurse(const std::string& _type) {
 ItemContainer.TypePredicate typePredicate = TL_predicates.get().type.alloc().init(_type);
 InventoryItem item = this->getBestConditionRecurse(typePredicate);
 TL_predicates.get().type.release(typePredicate);
 return item;
 }

 InventoryItem getBestConditionEval(LuaClosure functionObj) {
 ItemContainer.EvalPredicate evalPredicate = TL_predicates.get().eval.alloc().init(functionObj);
 InventoryItem item = this->getBestCondition(evalPredicate);
 TL_predicates.get().eval.release(evalPredicate);
 return item;
 }

 InventoryItem getBestConditionEvalRecurse(LuaClosure functionObj) {
 ItemContainer.EvalPredicate evalPredicate = TL_predicates.get().eval.alloc().init(functionObj);
 InventoryItem item = this->getBestConditionRecurse(evalPredicate);
 TL_predicates.get().eval.release(evalPredicate);
 return item;
 }

 InventoryItem getBestConditionEvalArg(LuaClosure functionObj, void* arg) {
 ItemContainer.EvalArgPredicate evalArgPredicate = TL_predicates.get().evalArg.alloc().init(functionObj, arg);
 InventoryItem item = this->getBestCondition(evalArgPredicate);
 TL_predicates.get().evalArg.release(evalArgPredicate);
 return item;
 }

 InventoryItem getBestConditionEvalArgRecurse(LuaClosure functionObj, void* arg) {
 ItemContainer.EvalArgPredicate evalArgPredicate = TL_predicates.get().evalArg.alloc().init(functionObj, arg);
 InventoryItem item = this->getBestConditionRecurse(evalArgPredicate);
 TL_predicates.get().evalArg.release(evalArgPredicate);
 return item;
 }

 InventoryItem getFirstEval(LuaClosure functionObj) {
 ItemContainer.EvalPredicate evalPredicate = TL_predicates.get().eval.alloc().init(functionObj);
 InventoryItem item = this->getFirst(evalPredicate);
 TL_predicates.get().eval.release(evalPredicate);
 return item;
 }

 InventoryItem getFirstEvalArg(LuaClosure functionObj, void* arg) {
 ItemContainer.EvalArgPredicate evalArgPredicate = TL_predicates.get().evalArg.alloc().init(functionObj, arg);
 InventoryItem item = this->getFirst(evalArgPredicate);
 TL_predicates.get().evalArg.release(evalArgPredicate);
 return item;
 }

 bool containsEval(LuaClosure functionObj) {
 return this->getFirstEval(functionObj) != nullptr;
 }

 bool containsEvalArg(LuaClosure functionObj, void* arg) {
 return this->getFirstEvalArg(functionObj, arg) != nullptr;
 }

 bool containsEvalRecurse(LuaClosure functionObj) {
 return this->getFirstEvalRecurse(functionObj) != nullptr;
 }

 bool containsEvalArgRecurse(LuaClosure functionObj, void* arg) {
 return this->getFirstEvalArgRecurse(functionObj, arg) != nullptr;
 }

 bool containsTag(const std::string& tag) {
 return this->getFirstTag(tag) != nullptr;
 }

 bool containsTagEval(const std::string& tag, LuaClosure functionObj) {
 return this->getFirstTagEval(tag, functionObj) != nullptr;
 }

 bool containsTagRecurse(const std::string& tag) {
 return this->getFirstTagRecurse(tag) != nullptr;
 }

 bool containsTagEvalRecurse(const std::string& tag, LuaClosure functionObj) {
 return this->getFirstTagEvalRecurse(tag, functionObj) != nullptr;
 }

 bool containsTagEvalArgRecurse(const std::string& tag, LuaClosure functionObj, void* arg) {
 return this->getFirstTagEvalArgRecurse(tag, functionObj, arg) != nullptr;
 }

 bool containsTypeEvalRecurse(const std::string& _type, LuaClosure functionObj) {
 return this->getFirstTypeEvalRecurse(_type, functionObj) != nullptr;
 }

 bool containsTypeEvalArgRecurse(const std::string& _type, LuaClosure functionObj, void* arg) {
 return this->getFirstTypeEvalArgRecurse(_type, functionObj, arg) != nullptr;
 }

 static bool compareType(const std::string& string0, const std::string& string1) {
 if (string0 != nullptr && string0.contains("/")) {
 int int0 = string0.indexOf(string1);
 if (int0 == -1) {
 return false;
 } else {
 char char0 = int0 > 0 ? string0.charAt(int0 - 1) : 0;
 char char1 = int0 + string1.length() < string0.length() ? string0.charAt(int0 + string1.length()) : 0;
 return char0 = = 0 && char1 == '/' || char0 == '/' && char1 == 0 || char0 == '/' && char1 == '/';
 }
 } else {
 return string0 == string1);
 }
 }

 static bool compareType(const std::string& string, InventoryItem item) {
 return string != nullptr && string.indexOf(46) == -1
 ? compareType(string, item.getType())
 : compareType(string, item.getFullType()) || compareType(string, item.getType());
 }

 InventoryItem getFirst(Predicate<InventoryItem> predicate) {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.empty()) {
 this->Items.remove(int0);
 int0--;
 } else if (predicate.test(item) {
 return item;
 }
 }

 return nullptr;
 }

 InventoryItem getFirstRecurse(Predicate<InventoryItem> predicate) {
 ItemContainer.InventoryItemList inventoryItemList = TL_itemListPool.get().alloc();

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item0 = this->Items.get(int0);
 if (item0.empty()) {
 this->Items.remove(int0);
 int0--;
 } else {
 if (predicate.test(item0) {
 TL_itemListPool.get().release(inventoryItemList);
 return item0;
 }

 if (item0 instanceof InventoryContainer) {
 inventoryItemList.add(item0);
 }
 }
 }

 for (int int1 = 0; int1 < inventoryItemList.size(); int1++) {
 ItemContainer container = ((InventoryContainer)inventoryItemList.get(int1).getInventory();
 InventoryItem item1 = container.getFirstRecurse(predicate);
 if (item1 != nullptr) {
 TL_itemListPool.get().release(inventoryItemList);
 return item1;
 }
 }

 TL_itemListPool.get().release(inventoryItemList);
 return nullptr;
 }

 public ArrayList<InventoryItem> getSome(Predicate<InventoryItem> predicate, int count, ArrayList<InventoryItem> result) {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.empty()) {
 this->Items.remove(int0);
 int0--;
 } else if (predicate.test(item) {
 result.add(item);
 if (result.size() >= count) {
 break;
 }
 }
 }

 return result;
 }

 public ArrayList<InventoryItem> getSomeRecurse(Predicate<InventoryItem> predicate, int count, ArrayList<InventoryItem> result) {
 ItemContainer.InventoryItemList inventoryItemList = TL_itemListPool.get().alloc();

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.empty()) {
 this->Items.remove(int0);
 int0--;
 } else {
 if (predicate.test(item) {
 result.add(item);
 if (result.size() >= count) {
 TL_itemListPool.get().release(inventoryItemList);
 return result;
 }
 }

 if (item instanceof InventoryContainer) {
 inventoryItemList.add(item);
 }
 }
 }

 for (int int1 = 0; int1 < inventoryItemList.size(); int1++) {
 ItemContainer container = ((InventoryContainer)inventoryItemList.get(int1).getInventory();
 container.getSomeRecurse(predicate, count, result);
 if (result.size() >= count) {
 break;
 }
 }

 TL_itemListPool.get().release(inventoryItemList);
 return result;
 }

 public ArrayList<InventoryItem> getAll(Predicate<InventoryItem> predicate, ArrayList<InventoryItem> result) {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.empty()) {
 this->Items.remove(int0);
 int0--;
 } else if (predicate.test(item) {
 result.add(item);
 }
 }

 return result;
 }

 public ArrayList<InventoryItem> getAllRecurse(Predicate<InventoryItem> predicate, ArrayList<InventoryItem> result) {
 ItemContainer.InventoryItemList inventoryItemList = TL_itemListPool.get().alloc();

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.empty()) {
 this->Items.remove(int0);
 int0--;
 } else {
 if (predicate.test(item) {
 result.add(item);
 }

 if (item instanceof InventoryContainer) {
 inventoryItemList.add(item);
 }
 }
 }

 for (int int1 = 0; int1 < inventoryItemList.size(); int1++) {
 ItemContainer container = ((InventoryContainer)inventoryItemList.get(int1).getInventory();
 container.getAllRecurse(predicate, result);
 }

 TL_itemListPool.get().release(inventoryItemList);
 return result;
 }

 int getCount(Predicate<InventoryItem> predicate) {
 ItemContainer.InventoryItemList inventoryItemList = TL_itemListPool.get().alloc();
 this->getAll(predicate, inventoryItemList);
 int int0 = inventoryItemList.size();
 TL_itemListPool.get().release(inventoryItemList);
 return int0;
 }

 int getCountRecurse(Predicate<InventoryItem> predicate) {
 ItemContainer.InventoryItemList inventoryItemList = TL_itemListPool.get().alloc();
 this->getAllRecurse(predicate, inventoryItemList);
 int int0 = inventoryItemList.size();
 TL_itemListPool.get().release(inventoryItemList);
 return int0;
 }

 int getCountTag(const std::string& tag) {
 ItemContainer.TagPredicate tagPredicate = TL_predicates.get().tag.alloc().init(tag);
 int int0 = this->getCount(tagPredicate);
 TL_predicates.get().tag.release(tagPredicate);
 return int0;
 }

 int getCountTagEval(const std::string& tag, LuaClosure functionObj) {
 ItemContainer.TagEvalPredicate tagEvalPredicate = TL_predicates.get().tagEval.alloc().init(tag, functionObj);
 int int0 = this->getCount(tagEvalPredicate);
 TL_predicates.get().tagEval.release(tagEvalPredicate);
 return int0;
 }

 int getCountTagEvalArg(const std::string& tag, LuaClosure functionObj, void* arg) {
 ItemContainer.TagEvalArgPredicate tagEvalArgPredicate = TL_predicates.get().tagEvalArg.alloc().init(tag, functionObj, arg);
 int int0 = this->getCount(tagEvalArgPredicate);
 TL_predicates.get().tagEvalArg.release(tagEvalArgPredicate);
 return int0;
 }

 int getCountTagRecurse(const std::string& tag) {
 ItemContainer.TagPredicate tagPredicate = TL_predicates.get().tag.alloc().init(tag);
 int int0 = this->getCountRecurse(tagPredicate);
 TL_predicates.get().tag.release(tagPredicate);
 return int0;
 }

 int getCountTagEvalRecurse(const std::string& tag, LuaClosure functionObj) {
 ItemContainer.TagEvalPredicate tagEvalPredicate = TL_predicates.get().tagEval.alloc().init(tag, functionObj);
 int int0 = this->getCountRecurse(tagEvalPredicate);
 TL_predicates.get().tagEval.release(tagEvalPredicate);
 return int0;
 }

 int getCountTagEvalArgRecurse(const std::string& tag, LuaClosure functionObj, void* arg) {
 ItemContainer.TagEvalArgPredicate tagEvalArgPredicate = TL_predicates.get().tagEvalArg.alloc().init(tag, functionObj, arg);
 int int0 = this->getCountRecurse(tagEvalArgPredicate);
 TL_predicates.get().tagEvalArg.release(tagEvalArgPredicate);
 return int0;
 }

 int getCountType(const std::string& _type) {
 ItemContainer.TypePredicate typePredicate = TL_predicates.get().type.alloc().init(_type);
 int int0 = this->getCount(typePredicate);
 TL_predicates.get().type.release(typePredicate);
 return int0;
 }

 int getCountTypeEval(const std::string& _type, LuaClosure functionObj) {
 ItemContainer.TypeEvalPredicate typeEvalPredicate = TL_predicates.get().typeEval.alloc().init(_type, functionObj);
 int int0 = this->getCount(typeEvalPredicate);
 TL_predicates.get().typeEval.release(typeEvalPredicate);
 return int0;
 }

 int getCountTypeEvalArg(const std::string& _type, LuaClosure functionObj, void* arg) {
 ItemContainer.TypeEvalArgPredicate typeEvalArgPredicate = TL_predicates.get().typeEvalArg.alloc().init(_type, functionObj, arg);
 int int0 = this->getCount(typeEvalArgPredicate);
 TL_predicates.get().typeEvalArg.release(typeEvalArgPredicate);
 return int0;
 }

 int getCountTypeRecurse(const std::string& _type) {
 ItemContainer.TypePredicate typePredicate = TL_predicates.get().type.alloc().init(_type);
 int int0 = this->getCountRecurse(typePredicate);
 TL_predicates.get().type.release(typePredicate);
 return int0;
 }

 int getCountTypeEvalRecurse(const std::string& _type, LuaClosure functionObj) {
 ItemContainer.TypeEvalPredicate typeEvalPredicate = TL_predicates.get().typeEval.alloc().init(_type, functionObj);
 int int0 = this->getCountRecurse(typeEvalPredicate);
 TL_predicates.get().typeEval.release(typeEvalPredicate);
 return int0;
 }

 int getCountTypeEvalArgRecurse(const std::string& _type, LuaClosure functionObj, void* arg) {
 ItemContainer.TypeEvalArgPredicate typeEvalArgPredicate = TL_predicates.get().typeEvalArg.alloc().init(_type, functionObj, arg);
 int int0 = this->getCountRecurse(typeEvalArgPredicate);
 TL_predicates.get().typeEvalArg.release(typeEvalArgPredicate);
 return int0;
 }

 int getCountEval(LuaClosure functionObj) {
 ItemContainer.EvalPredicate evalPredicate = TL_predicates.get().eval.alloc().init(functionObj);
 int int0 = this->getCount(evalPredicate);
 TL_predicates.get().eval.release(evalPredicate);
 return int0;
 }

 int getCountEvalArg(LuaClosure functionObj, void* arg) {
 ItemContainer.EvalArgPredicate evalArgPredicate = TL_predicates.get().evalArg.alloc().init(functionObj, arg);
 int int0 = this->getCount(evalArgPredicate);
 TL_predicates.get().evalArg.release(evalArgPredicate);
 return int0;
 }

 int getCountEvalRecurse(LuaClosure functionObj) {
 ItemContainer.EvalPredicate evalPredicate = TL_predicates.get().eval.alloc().init(functionObj);
 int int0 = this->getCountRecurse(evalPredicate);
 TL_predicates.get().eval.release(evalPredicate);
 return int0;
 }

 int getCountEvalArgRecurse(LuaClosure functionObj, void* arg) {
 ItemContainer.EvalArgPredicate evalArgPredicate = TL_predicates.get().evalArg.alloc().init(functionObj, arg);
 int int0 = this->getCountRecurse(evalArgPredicate);
 TL_predicates.get().evalArg.release(evalArgPredicate);
 return int0;
 }

 InventoryItem getFirstCategory(const std::string& category) {
 ItemContainer.CategoryPredicate categoryPredicate = TL_predicates.get().category.alloc().init(category);
 InventoryItem item = this->getFirst(categoryPredicate);
 TL_predicates.get().category.release(categoryPredicate);
 return item;
 }

 InventoryItem getFirstCategoryRecurse(const std::string& category) {
 ItemContainer.CategoryPredicate categoryPredicate = TL_predicates.get().category.alloc().init(category);
 InventoryItem item = this->getFirstRecurse(categoryPredicate);
 TL_predicates.get().category.release(categoryPredicate);
 return item;
 }

 InventoryItem getFirstEvalRecurse(LuaClosure functionObj) {
 ItemContainer.EvalPredicate evalPredicate = TL_predicates.get().eval.alloc().init(functionObj);
 InventoryItem item = this->getFirstRecurse(evalPredicate);
 TL_predicates.get().eval.release(evalPredicate);
 return item;
 }

 InventoryItem getFirstEvalArgRecurse(LuaClosure functionObj, void* arg) {
 ItemContainer.EvalArgPredicate evalArgPredicate = TL_predicates.get().evalArg.alloc().init(functionObj, arg);
 InventoryItem item = this->getFirstRecurse(evalArgPredicate);
 TL_predicates.get().evalArg.release(evalArgPredicate);
 return item;
 }

 InventoryItem getFirstTag(const std::string& tag) {
 ItemContainer.TagPredicate tagPredicate = TL_predicates.get().tag.alloc().init(tag);
 InventoryItem item = this->getFirst(tagPredicate);
 TL_predicates.get().tag.release(tagPredicate);
 return item;
 }

 InventoryItem getFirstTagRecurse(const std::string& tag) {
 ItemContainer.TagPredicate tagPredicate = TL_predicates.get().tag.alloc().init(tag);
 InventoryItem item = this->getFirstRecurse(tagPredicate);
 TL_predicates.get().tag.release(tagPredicate);
 return item;
 }

 InventoryItem getFirstTagEval(const std::string& tag, LuaClosure functionObj) {
 ItemContainer.TagEvalPredicate tagEvalPredicate = TL_predicates.get().tagEval.alloc().init(tag, functionObj);
 InventoryItem item = this->getFirstRecurse(tagEvalPredicate);
 TL_predicates.get().tagEval.release(tagEvalPredicate);
 return item;
 }

 InventoryItem getFirstTagEvalRecurse(const std::string& tag, LuaClosure functionObj) {
 ItemContainer.TagEvalPredicate tagEvalPredicate = TL_predicates.get().tagEval.alloc().init(tag, functionObj);
 InventoryItem item = this->getFirstRecurse(tagEvalPredicate);
 TL_predicates.get().tagEval.release(tagEvalPredicate);
 return item;
 }

 InventoryItem getFirstTagEvalArgRecurse(const std::string& tag, LuaClosure functionObj, void* arg) {
 ItemContainer.TagEvalArgPredicate tagEvalArgPredicate = TL_predicates.get().tagEvalArg.alloc().init(tag, functionObj, arg);
 InventoryItem item = this->getFirstRecurse(tagEvalArgPredicate);
 TL_predicates.get().tagEvalArg.release(tagEvalArgPredicate);
 return item;
 }

 InventoryItem getFirstType(const std::string& _type) {
 ItemContainer.TypePredicate typePredicate = TL_predicates.get().type.alloc().init(_type);
 InventoryItem item = this->getFirst(typePredicate);
 TL_predicates.get().type.release(typePredicate);
 return item;
 }

 InventoryItem getFirstTypeRecurse(const std::string& _type) {
 ItemContainer.TypePredicate typePredicate = TL_predicates.get().type.alloc().init(_type);
 InventoryItem item = this->getFirstRecurse(typePredicate);
 TL_predicates.get().type.release(typePredicate);
 return item;
 }

 InventoryItem getFirstTypeEval(const std::string& _type, LuaClosure functionObj) {
 ItemContainer.TypeEvalPredicate typeEvalPredicate = TL_predicates.get().typeEval.alloc().init(_type, functionObj);
 InventoryItem item = this->getFirstRecurse(typeEvalPredicate);
 TL_predicates.get().typeEval.release(typeEvalPredicate);
 return item;
 }

 InventoryItem getFirstTypeEvalRecurse(const std::string& _type, LuaClosure functionObj) {
 ItemContainer.TypeEvalPredicate typeEvalPredicate = TL_predicates.get().typeEval.alloc().init(_type, functionObj);
 InventoryItem item = this->getFirstRecurse(typeEvalPredicate);
 TL_predicates.get().typeEval.release(typeEvalPredicate);
 return item;
 }

 InventoryItem getFirstTypeEvalArgRecurse(const std::string& _type, LuaClosure functionObj, void* arg) {
 ItemContainer.TypeEvalArgPredicate typeEvalArgPredicate = TL_predicates.get().typeEvalArg.alloc().init(_type, functionObj, arg);
 InventoryItem item = this->getFirstRecurse(typeEvalArgPredicate);
 TL_predicates.get().typeEvalArg.release(typeEvalArgPredicate);
 return item;
 }

 public ArrayList<InventoryItem> getSomeCategory(String category, int count, ArrayList<InventoryItem> result) {
 ItemContainer.CategoryPredicate categoryPredicate = TL_predicates.get().category.alloc().init(category);
 std::vector arrayList = this->getSome(categoryPredicate, count, result);
 TL_predicates.get().category.release(categoryPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeCategoryRecurse(String category, int count, ArrayList<InventoryItem> result) {
 ItemContainer.CategoryPredicate categoryPredicate = TL_predicates.get().category.alloc().init(category);
 std::vector arrayList = this->getSomeRecurse(categoryPredicate, count, result);
 TL_predicates.get().category.release(categoryPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeTag(String tag, int count, ArrayList<InventoryItem> result) {
 ItemContainer.TagPredicate tagPredicate = TL_predicates.get().tag.alloc().init(tag);
 std::vector arrayList = this->getSome(tagPredicate, count, result);
 TL_predicates.get().tag.release(tagPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeTagEval(String tag, LuaClosure functionObj, int count, ArrayList<InventoryItem> result) {
 ItemContainer.TagEvalPredicate tagEvalPredicate = TL_predicates.get().tagEval.alloc().init(tag, functionObj);
 std::vector arrayList = this->getSome(tagEvalPredicate, count, result);
 TL_predicates.get().tagEval.release(tagEvalPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeTagEvalArg(String tag, LuaClosure functionObj, Object arg, int count, ArrayList<InventoryItem> result) {
 ItemContainer.TagEvalArgPredicate tagEvalArgPredicate = TL_predicates.get().tagEvalArg.alloc().init(tag, functionObj, arg);
 std::vector arrayList = this->getSome(tagEvalArgPredicate, count, result);
 TL_predicates.get().tagEvalArg.release(tagEvalArgPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeTagRecurse(String tag, int count, ArrayList<InventoryItem> result) {
 ItemContainer.TagPredicate tagPredicate = TL_predicates.get().tag.alloc().init(tag);
 std::vector arrayList = this->getSomeRecurse(tagPredicate, count, result);
 TL_predicates.get().tag.release(tagPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeTagEvalRecurse(String tag, LuaClosure functionObj, int count, ArrayList<InventoryItem> result) {
 ItemContainer.TagEvalPredicate tagEvalPredicate = TL_predicates.get().tagEval.alloc().init(tag, functionObj);
 std::vector arrayList = this->getSomeRecurse(tagEvalPredicate, count, result);
 TL_predicates.get().tagEval.release(tagEvalPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeTagEvalArgRecurse(String tag, LuaClosure functionObj, Object arg, int count, ArrayList<InventoryItem> result) {
 ItemContainer.TagEvalArgPredicate tagEvalArgPredicate = TL_predicates.get().tagEvalArg.alloc().init(tag, functionObj, arg);
 std::vector arrayList = this->getSomeRecurse(tagEvalArgPredicate, count, result);
 TL_predicates.get().tagEvalArg.release(tagEvalArgPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeType(String _type, int count, ArrayList<InventoryItem> result) {
 ItemContainer.TypePredicate typePredicate = TL_predicates.get().type.alloc().init(_type);
 std::vector arrayList = this->getSome(typePredicate, count, result);
 TL_predicates.get().type.release(typePredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeTypeEval(String _type, LuaClosure functionObj, int count, ArrayList<InventoryItem> result) {
 ItemContainer.TypeEvalPredicate typeEvalPredicate = TL_predicates.get().typeEval.alloc().init(_type, functionObj);
 std::vector arrayList = this->getSome(typeEvalPredicate, count, result);
 TL_predicates.get().typeEval.release(typeEvalPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeTypeEvalArg(String _type, LuaClosure functionObj, Object arg, int count, ArrayList<InventoryItem> result) {
 ItemContainer.TypeEvalArgPredicate typeEvalArgPredicate = TL_predicates.get().typeEvalArg.alloc().init(_type, functionObj, arg);
 std::vector arrayList = this->getSome(typeEvalArgPredicate, count, result);
 TL_predicates.get().typeEvalArg.release(typeEvalArgPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeTypeRecurse(String _type, int count, ArrayList<InventoryItem> result) {
 ItemContainer.TypePredicate typePredicate = TL_predicates.get().type.alloc().init(_type);
 std::vector arrayList = this->getSomeRecurse(typePredicate, count, result);
 TL_predicates.get().type.release(typePredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeTypeEvalRecurse(String _type, LuaClosure functionObj, int count, ArrayList<InventoryItem> result) {
 ItemContainer.TypeEvalPredicate typeEvalPredicate = TL_predicates.get().typeEval.alloc().init(_type, functionObj);
 std::vector arrayList = this->getSomeRecurse(typeEvalPredicate, count, result);
 TL_predicates.get().typeEval.release(typeEvalPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeTypeEvalArgRecurse(String _type, LuaClosure functionObj, Object arg, int count, ArrayList<InventoryItem> result) {
 ItemContainer.TypeEvalArgPredicate typeEvalArgPredicate = TL_predicates.get().typeEvalArg.alloc().init(_type, functionObj, arg);
 std::vector arrayList = this->getSomeRecurse(typeEvalArgPredicate, count, result);
 TL_predicates.get().typeEvalArg.release(typeEvalArgPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeEval(LuaClosure functionObj, int count, ArrayList<InventoryItem> result) {
 ItemContainer.EvalPredicate evalPredicate = TL_predicates.get().eval.alloc().init(functionObj);
 std::vector arrayList = this->getSome(evalPredicate, count, result);
 TL_predicates.get().eval.release(evalPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeEvalArg(LuaClosure functionObj, Object arg, int count, ArrayList<InventoryItem> result) {
 ItemContainer.EvalArgPredicate evalArgPredicate = TL_predicates.get().evalArg.alloc().init(functionObj, arg);
 std::vector arrayList = this->getSome(evalArgPredicate, count, result);
 TL_predicates.get().evalArg.release(evalArgPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeEvalRecurse(LuaClosure functionObj, int count, ArrayList<InventoryItem> result) {
 ItemContainer.EvalPredicate evalPredicate = TL_predicates.get().eval.alloc().init(functionObj);
 std::vector arrayList = this->getSomeRecurse(evalPredicate, count, result);
 TL_predicates.get().eval.release(evalPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeEvalArgRecurse(LuaClosure functionObj, Object arg, int count, ArrayList<InventoryItem> result) {
 ItemContainer.EvalArgPredicate evalArgPredicate = TL_predicates.get().evalArg.alloc().init(functionObj, arg);
 std::vector arrayList = this->getSomeRecurse(evalArgPredicate, count, result);
 TL_predicates.get().evalArg.release(evalArgPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllCategory(String category, ArrayList<InventoryItem> result) {
 ItemContainer.CategoryPredicate categoryPredicate = TL_predicates.get().category.alloc().init(category);
 std::vector arrayList = this->getAll(categoryPredicate, result);
 TL_predicates.get().category.release(categoryPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllCategoryRecurse(String category, ArrayList<InventoryItem> result) {
 ItemContainer.CategoryPredicate categoryPredicate = TL_predicates.get().category.alloc().init(category);
 std::vector arrayList = this->getAllRecurse(categoryPredicate, result);
 TL_predicates.get().category.release(categoryPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllTag(String tag, ArrayList<InventoryItem> result) {
 ItemContainer.TagPredicate tagPredicate = TL_predicates.get().tag.alloc().init(tag);
 std::vector arrayList = this->getAll(tagPredicate, result);
 TL_predicates.get().tag.release(tagPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllTagEval(String tag, LuaClosure functionObj, ArrayList<InventoryItem> result) {
 ItemContainer.TagEvalPredicate tagEvalPredicate = TL_predicates.get().tagEval.alloc().init(tag, functionObj);
 std::vector arrayList = this->getAll(tagEvalPredicate, result);
 TL_predicates.get().tagEval.release(tagEvalPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllTagEvalArg(String tag, LuaClosure functionObj, Object arg, ArrayList<InventoryItem> result) {
 ItemContainer.TagEvalArgPredicate tagEvalArgPredicate = TL_predicates.get().tagEvalArg.alloc().init(tag, functionObj, arg);
 std::vector arrayList = this->getAll(tagEvalArgPredicate, result);
 TL_predicates.get().tagEvalArg.release(tagEvalArgPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllTagRecurse(String tag, ArrayList<InventoryItem> result) {
 ItemContainer.TagPredicate tagPredicate = TL_predicates.get().tag.alloc().init(tag);
 std::vector arrayList = this->getAllRecurse(tagPredicate, result);
 TL_predicates.get().tag.release(tagPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllTagEvalRecurse(String tag, LuaClosure functionObj, ArrayList<InventoryItem> result) {
 ItemContainer.TagEvalPredicate tagEvalPredicate = TL_predicates.get().tagEval.alloc().init(tag, functionObj);
 std::vector arrayList = this->getAllRecurse(tagEvalPredicate, result);
 TL_predicates.get().tagEval.release(tagEvalPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllTagEvalArgRecurse(String tag, LuaClosure functionObj, Object arg, ArrayList<InventoryItem> result) {
 ItemContainer.TagEvalArgPredicate tagEvalArgPredicate = TL_predicates.get().tagEvalArg.alloc().init(tag, functionObj, arg);
 std::vector arrayList = this->getAllRecurse(tagEvalArgPredicate, result);
 TL_predicates.get().tagEvalArg.release(tagEvalArgPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllType(String _type, ArrayList<InventoryItem> result) {
 ItemContainer.TypePredicate typePredicate = TL_predicates.get().type.alloc().init(_type);
 std::vector arrayList = this->getAll(typePredicate, result);
 TL_predicates.get().type.release(typePredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllTypeEval(String _type, LuaClosure functionObj, ArrayList<InventoryItem> result) {
 ItemContainer.TypeEvalPredicate typeEvalPredicate = TL_predicates.get().typeEval.alloc().init(_type, functionObj);
 std::vector arrayList = this->getAll(typeEvalPredicate, result);
 TL_predicates.get().typeEval.release(typeEvalPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllTypeEvalArg(String _type, LuaClosure functionObj, Object arg, ArrayList<InventoryItem> result) {
 ItemContainer.TypeEvalArgPredicate typeEvalArgPredicate = TL_predicates.get().typeEvalArg.alloc().init(_type, functionObj, arg);
 std::vector arrayList = this->getAll(typeEvalArgPredicate, result);
 TL_predicates.get().typeEvalArg.release(typeEvalArgPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllTypeRecurse(String _type, ArrayList<InventoryItem> result) {
 ItemContainer.TypePredicate typePredicate = TL_predicates.get().type.alloc().init(_type);
 std::vector arrayList = this->getAllRecurse(typePredicate, result);
 TL_predicates.get().type.release(typePredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllTypeEvalRecurse(String _type, LuaClosure functionObj, ArrayList<InventoryItem> result) {
 ItemContainer.TypeEvalPredicate typeEvalPredicate = TL_predicates.get().typeEval.alloc().init(_type, functionObj);
 std::vector arrayList = this->getAllRecurse(typeEvalPredicate, result);
 TL_predicates.get().typeEval.release(typeEvalPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllTypeEvalArgRecurse(String _type, LuaClosure functionObj, Object arg, ArrayList<InventoryItem> result) {
 ItemContainer.TypeEvalArgPredicate typeEvalArgPredicate = TL_predicates.get().typeEvalArg.alloc().init(_type, functionObj, arg);
 std::vector arrayList = this->getAllRecurse(typeEvalArgPredicate, result);
 TL_predicates.get().typeEvalArg.release(typeEvalArgPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllEval(LuaClosure functionObj, ArrayList<InventoryItem> result) {
 ItemContainer.EvalPredicate evalPredicate = TL_predicates.get().eval.alloc().init(functionObj);
 std::vector arrayList = this->getAll(evalPredicate, result);
 TL_predicates.get().eval.release(evalPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllEvalArg(LuaClosure functionObj, Object arg, ArrayList<InventoryItem> result) {
 ItemContainer.EvalArgPredicate evalArgPredicate = TL_predicates.get().evalArg.alloc().init(functionObj, arg);
 std::vector arrayList = this->getAll(evalArgPredicate, result);
 TL_predicates.get().evalArg.release(evalArgPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllEvalRecurse(LuaClosure functionObj, ArrayList<InventoryItem> result) {
 ItemContainer.EvalPredicate evalPredicate = TL_predicates.get().eval.alloc().init(functionObj);
 std::vector arrayList = this->getAllRecurse(evalPredicate, result);
 TL_predicates.get().eval.release(evalPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getAllEvalArgRecurse(LuaClosure functionObj, Object arg, ArrayList<InventoryItem> result) {
 ItemContainer.EvalArgPredicate evalArgPredicate = TL_predicates.get().evalArg.alloc().init(functionObj, arg);
 std::vector arrayList = this->getAllRecurse(evalArgPredicate, result);
 TL_predicates.get().evalArg.release(evalArgPredicate);
 return arrayList;
 }

 public ArrayList<InventoryItem> getSomeCategory(String category, int count) {
 return this->getSomeCategory(category, count, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getSomeEval(LuaClosure functionObj, int count) {
 return this->getSomeEval(functionObj, count, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getSomeEvalArg(LuaClosure functionObj, Object arg, int count) {
 return this->getSomeEvalArg(functionObj, arg, count, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getSomeTypeEval(String _type, LuaClosure functionObj, int count) {
 return this->getSomeTypeEval(_type, functionObj, count, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getSomeTypeEvalArg(String _type, LuaClosure functionObj, Object arg, int count) {
 return this->getSomeTypeEvalArg(_type, functionObj, arg, count, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getSomeEvalRecurse(LuaClosure functionObj, int count) {
 return this->getSomeEvalRecurse(functionObj, count, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getSomeEvalArgRecurse(LuaClosure functionObj, Object arg, int count) {
 return this->getSomeEvalArgRecurse(functionObj, arg, count, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getSomeTag(String tag, int count) {
 return this->getSomeTag(tag, count, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getSomeTagRecurse(String tag, int count) {
 return this->getSomeTagRecurse(tag, count, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getSomeTagEvalRecurse(String tag, LuaClosure functionObj, int count) {
 return this->getSomeTagEvalRecurse(tag, functionObj, count, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getSomeTagEvalArgRecurse(String tag, LuaClosure functionObj, Object arg, int count) {
 return this->getSomeTagEvalArgRecurse(tag, functionObj, arg, count, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getSomeType(String _type, int count) {
 return this->getSomeType(_type, count, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getSomeTypeRecurse(String _type, int count) {
 return this->getSomeTypeRecurse(_type, count, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getSomeTypeEvalRecurse(String _type, LuaClosure functionObj, int count) {
 return this->getSomeTypeEvalRecurse(_type, functionObj, count, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getSomeTypeEvalArgRecurse(String _type, LuaClosure functionObj, Object arg, int count) {
 return this->getSomeTypeEvalArgRecurse(_type, functionObj, arg, count, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getAll(Predicate<InventoryItem> predicate) {
 return this->getAll(predicate, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getAllCategory(String category) {
 return this->getAllCategory(category, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getAllEval(LuaClosure functionObj) {
 return this->getAllEval(functionObj, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getAllEvalArg(LuaClosure functionObj, Object arg) {
 return this->getAllEvalArg(functionObj, arg, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getAllTagEval(String _type, LuaClosure functionObj) {
 return this->getAllTagEval(_type, functionObj, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getAllTagEvalArg(String _type, LuaClosure functionObj, Object arg) {
 return this->getAllTagEvalArg(_type, functionObj, arg, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getAllTypeEval(String _type, LuaClosure functionObj) {
 return this->getAllTypeEval(_type, functionObj, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getAllTypeEvalArg(String _type, LuaClosure functionObj, Object arg) {
 return this->getAllTypeEvalArg(_type, functionObj, arg, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getAllEvalRecurse(LuaClosure functionObj) {
 return this->getAllEvalRecurse(functionObj, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getAllEvalArgRecurse(LuaClosure functionObj, Object arg) {
 return this->getAllEvalArgRecurse(functionObj, arg, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getAllType(String _type) {
 return this->getAllType(_type, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getAllTypeRecurse(String _type) {
 return this->getAllTypeRecurse(_type, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getAllTypeEvalRecurse(String _type, LuaClosure functionObj) {
 return this->getAllTypeEvalRecurse(_type, functionObj, std::make_unique<ArrayList<>>());
 }

 public ArrayList<InventoryItem> getAllTypeEvalArgRecurse(String _type, LuaClosure functionObj, Object arg) {
 return this->getAllTypeEvalArgRecurse(_type, functionObj, arg, std::make_unique<ArrayList<>>());
 }

 InventoryItem FindAndReturnCategory(const std::string& category) {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.getCategory() == category) {
 return item;
 }
 }

 return nullptr;
 }

 public ArrayList<InventoryItem> FindAndReturn(String _type, int count) {
 return this->getSomeType(_type, count);
 }

 InventoryItem FindAndReturn(const std::string& _type, ArrayList<InventoryItem> itemToCheck) {
 if (_type.empty()) {
 return nullptr;
 } else {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.type != nullptr && compareType(_type, item) && !itemToCheck.contains(item) {
 return item;
 }
 }

 return nullptr;
 }
 }

 InventoryItem FindAndReturn(const std::string& _type) {
 return this->getFirstType(_type);
 }

 public ArrayList<InventoryItem> FindAll(String _type) {
 return this->getAllType(_type);
 }

 InventoryItem FindAndReturnStack(const std::string& _type) {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item0 = this->Items.get(int0);
 if (compareType(_type, item0) {
 InventoryItem item1 = InventoryItemFactory.CreateItem(item0.module + "." + _type);
 if (item0.CanStack(item1) {
 return item0;
 }
 }
 }

 return nullptr;
 }

 InventoryItem FindAndReturnStack(InventoryItem itemlike) {
 std::string string = itemlike.type;

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if ((item.type.empty() ? string.empty() : item.type == string) && item.CanStack(itemlike) {
 return item;
 }
 }

 return nullptr;
 }

 bool HasType(ItemType itemType) {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.cat == itemType) {
 return true;
 }
 }

 return false;
 }

 void Remove(InventoryItem item) {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem _item = this->Items.get(int0);
 if (_item == item) {
 if (item.uses > 1) {
 item.uses--;
 } else {
 this->Items.remove(item);
 }

 item.container = nullptr;
 this->drawDirty = true;
 this->dirty = true;
 if (this->parent != nullptr) {
 this->dirty = true;
 }

 if (this->parent instanceof IsoDeadBody) {
 ((IsoDeadBody)this->parent).checkClothing(item);
 }

 if (this->parent instanceof IsoMannequin) {
 ((IsoMannequin)this->parent).checkClothing(item);
 }

 return;
 }
 }
 }

 void DoRemoveItem(InventoryItem item) {
 this->drawDirty = true;
 if (this->parent != nullptr) {
 this->dirty = true;
 }

 this->Items.remove(item);
 item.container = nullptr;
 if (this->parent instanceof IsoDeadBody) {
 ((IsoDeadBody)this->parent).checkClothing(item);
 }

 if (this->parent instanceof IsoMannequin) {
 ((IsoMannequin)this->parent).checkClothing(item);
 }
 }

 void Remove(const std::string& itemTypes) {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.type == itemTypes) {
 if (item.uses > 1) {
 item.uses--;
 } else {
 this->Items.remove(item);
 }

 item.container = nullptr;
 this->drawDirty = true;
 this->dirty = true;
 if (this->parent != nullptr) {
 this->dirty = true;
 }

 return;
 }
 }
 }

 InventoryItem Remove(ItemType itemType) {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.cat == itemType) {
 this->Items.remove(item);
 item.container = nullptr;
 this->drawDirty = true;
 this->dirty = true;
 if (this->parent != nullptr) {
 this->dirty = true;
 }

 return item;
 }
 }

 return nullptr;
 }

 InventoryItem Find(ItemType itemType) {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.cat == itemType) {
 return item;
 }
 }

 return nullptr;
 }

 /**
 * Remove all the item of the type in parameter inside the container Ex of itemType : Broccoli (no need the module like Base.Broccoli)
 */
 void RemoveAll(const std::string& itemType) {
 this->drawDirty = true;
 if (this->parent != nullptr) {
 this->dirty = true;
 }

 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item0 = this->Items.get(int0);
 if (item0.type == itemType) {
 item0.container = nullptr;
 arrayList.add(item0);
 this->dirty = true;
 }
 }

 for (auto& item1 : arrayList) this->Items.remove(item1);
 }
 }

 bool RemoveOneOf(const std::string& String, bool insideInv) {
 this->drawDirty = true;
 if (this->parent != nullptr && !(this->parent instanceof IsoGameCharacter) {
 this->dirty = true;
 }

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item0 = this->Items.get(int0);
 if (item0.getFullType() == String) || item0.type == String) {
 if (item0.uses > 1) {
 item0.uses--;
 } else {
 item0.container = nullptr;
 this->Items.remove(item0);
 }

 this->dirty = true;
 return true;
 }
 }

 if (insideInv) {
 for (int int1 = 0; int1 < this->Items.size(); int1++) {
 InventoryItem item1 = this->Items.get(int1);
 if (item1 instanceof InventoryContainer
 && ((InventoryContainer)item1).getItemContainer() != nullptr
 && ((InventoryContainer)item1).getItemContainer().RemoveOneOf(String, insideInv) {
 return true;
 }
 }
 }

 return false;
 }

 void RemoveOneOf(const std::string& String) {
 this->RemoveOneOf(String, true);
 }

 /** @deprecated */
 int getWeight() {
 if (this->parent instanceof IsoPlayer && ((IsoPlayer)this->parent).isGhostMode()) {
 return 0;
 } else {
 float float0 = 0.0F;

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 float0 += item.ActualWeight * item.uses;
 }

 return (int)(float0 * (this->weightReduction / 0.01F);
 }
 }

 float getContentsWeight() {
 float float0 = 0.0F;

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 float0 += item.getUnequippedWeight();
 }

 return float0;
 }

 float getMaxWeight() {
 return this->parent instanceof IsoGameCharacter ? ((IsoGameCharacter)this->parent).getMaxWeight() : this->Capacity;
 }

 float getCapacityWeight() {
 if (this->parent instanceof IsoPlayer) {
 if (Core.bDebug && ((IsoPlayer)this->parent).isGhostMode()
 || !((IsoPlayer)this->parent).isAccessLevel("None") && ((IsoPlayer)this->parent).isUnlimitedCarry()) {
 return 0.0F;
 }

 if (((IsoPlayer)this->parent).isUnlimitedCarry()) {
 return 0.0F;
 }
 }

 return this->parent instanceof IsoGameCharacter ? ((IsoGameCharacter)this->parent).getInventoryWeight() : this->getContentsWeight();
 }

 bool isEmpty() {
 return this->Items.empty() || this->Items.empty();
 }

 bool isMicrowave() {
 return "microwave" == this->getType());
 }

 bool isSquareInRoom(IsoGridSquare square) {
 return square = = nullptr ? false : square.getRoom() != nullptr;
 }

 bool isSquarePowered(IsoGridSquare square0) {
 if (square0.empty()) {
 return false;
 } else {
 bool boolean0 = IsoWorld.instance.isHydroPowerOn();
 if (boolean0 && square0.getRoom() != nullptr) {
 return true;
 } else if (square0.haveElectricity()) {
 return true;
 } else {
 if (boolean0 && square0.getRoom() == nullptr) {
 IsoGridSquare square1 = square0.nav[IsoDirections.N.index()];
 IsoGridSquare square2 = square0.nav[IsoDirections.S.index()];
 IsoGridSquare square3 = square0.nav[IsoDirections.W.index()];
 IsoGridSquare square4 = square0.nav[IsoDirections.E.index()];
 if (this->isSquareInRoom(square1) || this->isSquareInRoom(square2) || this->isSquareInRoom(square3) || this->isSquareInRoom(square4) {
 return true;
 }
 }

 return false;
 }
 }
 }

 bool isPowered() {
 if (this->parent != nullptr && this->parent.getObjectIndex() != -1) {
 IsoGridSquare square0 = this->parent.getSquare();
 if (this->isSquarePowered(square0) {
 return true;
 } else {
 this->parent.getSpriteGridObjects(s_tempObjects);

 for (int int0 = 0; int0 < s_tempObjects.size(); int0++) {
 IsoObject object = s_tempObjects.get(int0);
 if (object != this->parent) {
 IsoGridSquare square1 = object.getSquare();
 if (this->isSquarePowered(square1) {
 return true;
 }
 }
 }

 return false;
 }
 } else {
 return false;
 }
 }

 float getTemprature() {
 if (this->customTemperature != 0.0F) {
 return this->customTemperature;
 } else {
 bool boolean0 = false;
 if (this->getParent() != nullptr && this->getParent().getSprite() != nullptr) {
 boolean0 = this->getParent().getSprite().getProperties().Is("IsFridge");
 }

 if (this->isPowered()) {
 if (this->type == "fridge") || this->type == "freezer") || boolean0) {
 return 0.2F;
 }

 if (("stove" == this->type) || "microwave" == this->type) && this->parent instanceof IsoStove) {
 return ((IsoStove)this->parent).getCurrentTemperature() / 100.0F;
 }
 }

 if ("barbecue" == this->type) && this->parent instanceof IsoBarbecue) {
 return ((IsoBarbecue)this->parent).getTemperature();
 } else if ("fireplace" == this->type) && this->parent instanceof IsoFireplace) {
 return ((IsoFireplace)this->parent).getTemperature();
 } else if ("woodstove" == this->type) && this->parent instanceof IsoFireplace) {
 return ((IsoFireplace)this->parent).getTemperature();
 } else if ((this->type == "fridge") || this->type == "freezer") || boolean0)
 && GameTime.instance.NightsSurvived == SandboxOptions.instance.getElecShutModifier()
 && GameTime.instance.getTimeOfDay() < 13.0F) {
 float float0 = (GameTime.instance.getTimeOfDay() - 7.0F) / 6.0F;
 return GameTime.instance.Lerp(0.2F, 1.0F, float0);
 } else {
 return 1.0F;
 }
 }
 }

 bool isTemperatureChanging() {
 return this->parent instanceof IsoStove ? ((IsoStove)this->parent).isTemperatureChanging() : false;
 }

 public ArrayList<InventoryItem> save(ByteBuffer output, IsoGameCharacter noCompress) throws IOException {
 GameWindow.WriteString(output, this->type);
 output.put((byte)(this->bExplored ? 1 : 0);
 std::vector arrayList = CompressIdenticalItems.save(output, this->Items, nullptr);
 output.put((byte)(this->isHasBeenLooted() ? 1 : 0);
 output.putInt(this->Capacity);
 return arrayList;
 }

 public ArrayList<InventoryItem> save(ByteBuffer output) throws IOException {
 return this->save(output, nullptr);
 }

 public ArrayList<InventoryItem> load(ByteBuffer input, int WorldVersion) throws IOException {
 this->type = GameWindow.ReadString(input);
 this->bExplored = input.get() == 1;
 std::vector arrayList = CompressIdenticalItems.load(input, WorldVersion, this->Items, this->IncludingObsoleteItems);

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 item.container = this;
 }

 this->setHasBeenLooted(input.get() == 1);
 this->Capacity = input.getInt();
 this->dirty = false;
 return arrayList;
 }

 bool isDrawDirty() {
 return this->drawDirty;
 }

 void setDrawDirty(bool b) {
 this->drawDirty = b;
 }

 InventoryItem getBestWeapon(SurvivorDesc desc) {
 InventoryItem item0 = nullptr;
 float float0 = -1.0E7F;

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item1 = this->Items.get(int0);
 if (item1 instanceof HandWeapon) {
 float float1 = item1.getScore(desc);
 if (float1 >= float0) {
 float0 = float1;
 item0 = item1;
 }
 }
 }

 return item0;
 }

 InventoryItem getBestWeapon() {
 InventoryItem item0 = nullptr;
 float float0 = 0.0F;

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item1 = this->Items.get(int0);
 if (item1 instanceof HandWeapon) {
 float float1 = item1.getScore(nullptr);
 if (float1 >= float0) {
 float0 = float1;
 item0 = item1;
 }
 }
 }

 return item0;
 }

 float getTotalFoodScore(SurvivorDesc desc) {
 float float0 = 0.0F;

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item instanceof Food) {
 float0 += item.getScore(desc);
 }
 }

 return float0;
 }

 float getTotalWeaponScore(SurvivorDesc desc) {
 float float0 = 0.0F;

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item instanceof HandWeapon) {
 float0 += item.getScore(desc);
 }
 }

 return float0;
 }

 InventoryItem getBestFood(SurvivorDesc descriptor) {
 InventoryItem item0 = nullptr;
 float float0 = 0.0F;

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item1 = this->Items.get(int0);
 if (item1 instanceof Food) {
 float float1 = item1.getScore(descriptor);
 if (((Food)item1).isbDangerousUncooked() && !item1.isCooked()) {
 float1 *= 0.2F;
 }

 if (((Food)item1).Age > item1.OffAge) {
 float1 *= 0.2F;
 }

 if (float1 >= float0) {
 float0 = float1;
 item0 = item1;
 }
 }
 }

 return item0;
 }

 InventoryItem getBestBandage(SurvivorDesc descriptor) {
 InventoryItem item0 = nullptr;

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item1 = this->Items.get(int0);
 if (item1.isCanBandage()) {
 item0 = item1;
 break;
 }
 }

 return item0;
 }

 int getNumItems(const std::string& item) {
 int int0 = 0;
 if (item.contains("Type:")) {
 for (int int1 = 0; int1 < this->Items.size(); int1++) {
 InventoryItem item0 = this->Items.get(int1);
 if (item0 instanceof Food && item.contains("Food")) {
 int0 += item0.uses;
 }

 if (item0 instanceof HandWeapon && item.contains("Weapon")) {
 int0 += item0.uses;
 }
 }
 } else {
 for (int int2 = 0; int2 < this->Items.size(); int2++) {
 InventoryItem item1 = this->Items.get(int2);
 if (item1.type == item) {
 int0 += item1.uses;
 }
 }
 }

 return int0;
 }

 /**
 * @return the active
 */
 bool isActive() {
 return this->active;
 }

 /**
 * 
 * @param _active the active to set
 */
 void setActive(bool _active) {
 this->active = _active;
 }

 /**
 * @return the dirty
 */
 bool isDirty() {
 return this->dirty;
 }

 /**
 * 
 * @param _dirty the dirty to set
 */
 void setDirty(bool _dirty) {
 this->dirty = _dirty;
 }

 /**
 * @return the IsDevice
 */
 bool isIsDevice() {
 return this->IsDevice;
 }

 /**
 * 
 * @param _IsDevice the IsDevice to set
 */
 void setIsDevice(bool _IsDevice) {
 this->IsDevice = _IsDevice;
 }

 /**
 * @return the ageFactor
 */
 float getAgeFactor() {
 return this->ageFactor;
 }

 /**
 * 
 * @param _ageFactor the ageFactor to set
 */
 void setAgeFactor(float _ageFactor) {
 this->ageFactor = _ageFactor;
 }

 /**
 * @return the CookingFactor
 */
 float getCookingFactor() {
 return this->CookingFactor;
 }

 /**
 * 
 * @param _CookingFactor the CookingFactor to set
 */
 void setCookingFactor(float _CookingFactor) {
 this->CookingFactor = _CookingFactor;
 }

 /**
 * @return the Items
 */
 public ArrayList<InventoryItem> getItems() {
 return this->Items;
 }

 /**
 * 
 * @param _Items the Items to set
 */
 void setItems(ArrayList<InventoryItem> _Items) {
 this->Items = _Items;
 }

 /**
 * @return the parent
 */
 IsoObject getParent() {
 return this->parent;
 }

 /**
 * 
 * @param _parent the parent to set
 */
 void setParent(IsoObject _parent) {
 this->parent = _parent;
 }

 /**
 * @return the SourceGrid
 */
 IsoGridSquare getSourceGrid() {
 return this->SourceGrid;
 }

 /**
 * 
 * @param _SourceGrid the SourceGrid to set
 */
 void setSourceGrid(IsoGridSquare _SourceGrid) {
 this->SourceGrid = _SourceGrid;
 }

 /**
 * @return the type
 */
 std::string getType() {
 return this->type;
 }

 /**
 * 
 * @param _type the type to set
 */
 void setType(const std::string& _type) {
 this->type = _type;
 }

 void clear() {
 this->Items.clear();
 this->dirty = true;
 this->drawDirty = true;
 }

 int getWaterContainerCount() {
 int int0 = 0;

 for (int int1 = 0; int1 < this->Items.size(); int1++) {
 InventoryItem item = this->Items.get(int1);
 if (item.CanStoreWater) {
 int0++;
 }
 }

 return int0;
 }

 InventoryItem FindWaterSource() {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.isWaterSource()) {
 if (!(item instanceof Drainable) {
 return item;
 }

 if (((Drainable)item).getUsedDelta() > 0.0F) {
 return item;
 }
 }
 }

 return nullptr;
 }

 public ArrayList<InventoryItem> getAllWaterFillables() {
 tempList.clear();

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.CanStoreWater) {
 tempList.add(item);
 }
 }

 return tempList;
 }

 int getItemCount(const std::string& _type) {
 return this->getCountType(_type);
 }

 int getItemCountRecurse(const std::string& _type) {
 return this->getCountTypeRecurse(_type);
 }

 int getItemCount(const std::string& _type, bool doBags) {
 return doBags ? this->getCountTypeRecurse(_type) : this->getCountType(_type);
 }

 static int getUses(ItemContainer.InventoryItemList inventoryItemList) {
 int int0 = 0;

 for (int int1 = 0; int1 < inventoryItemList.size(); int1++) {
 DrainableComboItem drainableComboItem = Type.tryCastTo(inventoryItemList.get(int1), DrainableComboItem.class);
 if (drainableComboItem != nullptr) {
 int0 += drainableComboItem.getDrainableUsesInt();
 } else {
 int0++;
 }
 }

 return int0;
 }

 int getUsesRecurse(Predicate<InventoryItem> predicate) {
 ItemContainer.InventoryItemList inventoryItemList = TL_itemListPool.get().alloc();
 this->getAllRecurse(predicate, inventoryItemList);
 int int0 = getUses(inventoryItemList);
 TL_itemListPool.get().release(inventoryItemList);
 return int0;
 }

 int getUsesType(const std::string& _type) {
 ItemContainer.InventoryItemList inventoryItemList = TL_itemListPool.get().alloc();
 this->getAllType(_type, inventoryItemList);
 int int0 = getUses(inventoryItemList);
 TL_itemListPool.get().release(inventoryItemList);
 return int0;
 }

 int getUsesTypeRecurse(const std::string& _type) {
 ItemContainer.InventoryItemList inventoryItemList = TL_itemListPool.get().alloc();
 this->getAllTypeRecurse(_type, inventoryItemList);
 int int0 = getUses(inventoryItemList);
 TL_itemListPool.get().release(inventoryItemList);
 return int0;
 }

 int getWeightReduction() {
 return this->weightReduction;
 }

 void setWeightReduction(int _weightReduction) {
 _weightReduction = Math.min(_weightReduction, 100);
 _weightReduction = Math.max(_weightReduction, 0);
 this->weightReduction = _weightReduction;
 }

 void removeAllItems() {
 this->drawDirty = true;
 if (this->parent != nullptr) {
 this->dirty = true;
 }

 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 item.container = nullptr;
 }

 this->Items.clear();
 if (this->parent instanceof IsoDeadBody) {
 ((IsoDeadBody)this->parent).checkClothing(nullptr);
 }

 if (this->parent instanceof IsoMannequin) {
 ((IsoMannequin)this->parent).checkClothing(nullptr);
 }
 }

 bool containsRecursive(InventoryItem item) {
 for (int int0 = 0; int0 < this->getItems().size(); int0++) {
 InventoryItem _item = this->getItems().get(int0);
 if (_item == item) {
 return true;
 }

 if (_item instanceof InventoryContainer && ((InventoryContainer)_item).getInventory().containsRecursive(item) {
 return true;
 }
 }

 return false;
 }

 int getItemCountFromTypeRecurse(const std::string& _type) {
 int int0 = 0;

 for (int int1 = 0; int1 < this->getItems().size(); int1++) {
 InventoryItem item = this->getItems().get(int1);
 if (item.getFullType() == _type) {
 int0++;
 }

 if (item instanceof InventoryContainer) {
 int int2 = ((InventoryContainer)item).getInventory().getItemCountFromTypeRecurse(_type);
 int0 += int2;
 }
 }

 return int0;
 }

 float getCustomTemperature() {
 return this->customTemperature;
 }

 void setCustomTemperature(float newTemp) {
 this->customTemperature = newTemp;
 }

 InventoryItem getItemFromType(const std::string& _type, IsoGameCharacter chr, bool notEquipped, bool ignoreBroken, bool includeInv) {
 ItemContainer.InventoryItemList inventoryItemList = TL_itemListPool.get().alloc();
 if (_type.contains(".")) {
 _type = _type.split("\\.")[1];
 }

 for (int int0 = 0; int0 < this->getItems().size(); int0++) {
 InventoryItem item0 = this->getItems().get(int0);
 if (!item0.getFullType() == _type) && !item0.getType() == _type) {
 if (includeInv
 && item0 instanceof InventoryContainer
 && ((InventoryContainer)item0).getInventory() != nullptr
 && !inventoryItemList.contains(item0) {
 inventoryItemList.add(item0);
 }
 } else if ((!notEquipped || chr.empty() || !chr.isEquippedClothing(item0) && this->testBroken(ignoreBroken, item0) {
 TL_itemListPool.get().release(inventoryItemList);
 return item0;
 }
 }

 for (int int1 = 0; int1 < inventoryItemList.size(); int1++) {
 ItemContainer container = ((InventoryContainer)inventoryItemList.get(int1).getInventory();
 InventoryItem item1 = container.getItemFromType(_type, chr, notEquipped, ignoreBroken, includeInv);
 if (item1 != nullptr) {
 TL_itemListPool.get().release(inventoryItemList);
 return item1;
 }
 }

 TL_itemListPool.get().release(inventoryItemList);
 return nullptr;
 }

 InventoryItem getItemFromType(const std::string& _type, bool ignoreBroken, bool includeInv) {
 return this->getItemFromType(_type, nullptr, false, ignoreBroken, includeInv);
 }

 InventoryItem getItemFromType(const std::string& _type) {
 return this->getFirstType(_type);
 }

 public ArrayList<InventoryItem> getItemsFromType(String _type) {
 return this->getAllType(_type);
 }

 public ArrayList<InventoryItem> getItemsFromFullType(String _type) {
 return _type != nullptr && _type.contains(".") ? this->getAllType(_type) : std::make_unique<ArrayList<>>();
 }

 public ArrayList<InventoryItem> getItemsFromFullType(String _type, boolean includeInv) {
 if (_type != nullptr && _type.contains(".")) {
 return includeInv ? this->getAllTypeRecurse(_type) : this->getAllType(_type);
 } else {
 return std::make_unique<ArrayList<>>();
 }
 }

 public ArrayList<InventoryItem> getItemsFromType(String _type, boolean includeInv) {
 return includeInv ? this->getAllTypeRecurse(_type) : this->getAllType(_type);
 }

 public ArrayList<InventoryItem> getItemsFromCategory(String category) {
 return this->getAllCategory(category);
 }

 void sendContentsToRemoteContainer() {
 if (GameClient.bClient) {
 this->sendContentsToRemoteContainer(GameClient.connection);
 }
 }

 void requestSync() {
 if (GameClient.bClient) {
 if (this->parent.empty() || this->parent.square.empty() || this->parent.square.chunk.empty()) {
 return;
 }

 GameClient.instance.worldObjectsSyncReq.putRequestSyncIsoChunk(this->parent.square.chunk);
 }
 }

 void requestServerItemsForContainer() {
 if (this->parent != nullptr && this->parent.square != nullptr) {
 UdpConnection udpConnection = GameClient.connection;
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.RequestItemsForContainer.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(IsoPlayer.getInstance().OnlineID);
 byteBufferWriter.putUTF(this->type);
 if (this->parent.square.getRoom() != nullptr) {
 byteBufferWriter.putUTF(this->parent.square.getRoom().getName());
 } else {
 byteBufferWriter.putUTF("all");
 }

 byteBufferWriter.putInt(this->parent.square.getX());
 byteBufferWriter.putInt(this->parent.square.getY());
 byteBufferWriter.putInt(this->parent.square.getZ());
 int int0 = this->parent.square.getObjects().indexOf(this->parent);
 if (int0 == -1 && this->parent.square.getStaticMovingObjects().indexOf(this->parent) != -1) {
 byteBufferWriter.putShort((short)0);
 int0 = this->parent.square.getStaticMovingObjects().indexOf(this->parent);
 byteBufferWriter.putByte((byte)int0);
 } else if (this->parent instanceof IsoWorldInventoryObject) {
 byteBufferWriter.putShort((short)1);
 byteBufferWriter.putInt(((IsoWorldInventoryObject)this->parent).getItem().id);
 } else if (this->parent instanceof BaseVehicle) {
 byteBufferWriter.putShort((short)3);
 byteBufferWriter.putShort(((BaseVehicle)this->parent).VehicleID);
 byteBufferWriter.putByte((byte)this->vehiclePart.getIndex());
 } else {
 byteBufferWriter.putShort((short)2);
 byteBufferWriter.putByte((byte)int0);
 byteBufferWriter.putByte((byte)this->parent.getContainerIndex(this);
 }

 PacketTypes.PacketType.RequestItemsForContainer.send(udpConnection);
 }
 }

 void sendContentsToRemoteContainer(UdpConnection connection) {
 ByteBufferWriter byteBufferWriter = connection.startPacket();
 PacketTypes.PacketType.AddInventoryItemToContainer.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(0);
 bool boolean0 = false;
 byteBufferWriter.putInt(this->parent.square.getX());
 byteBufferWriter.putInt(this->parent.square.getY());
 byteBufferWriter.putInt(this->parent.square.getZ());
 byteBufferWriter.putByte((byte)this->parent.square.getObjects().indexOf(this->parent);

 try {
 CompressIdenticalItems.save(byteBufferWriter.bb, this->Items, nullptr);
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 PacketTypes.PacketType.AddInventoryItemToContainer.send(connection);
 }

 InventoryItem getItemWithIDRecursiv(int id) {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.id == id) {
 return item;
 }

 if (item instanceof InventoryContainer
 && ((InventoryContainer)item).getItemContainer() != nullptr
 && !((InventoryContainer)item).getItemContainer().getItems().empty()) {
 item = ((InventoryContainer)item).getItemContainer().getItemWithIDRecursiv(id);
 if (item != nullptr) {
 return item;
 }
 }
 }

 return nullptr;
 }

 InventoryItem getItemWithID(int id) {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.id == id) {
 return item;
 }
 }

 return nullptr;
 }

 bool removeItemWithID(int id) {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.id == id) {
 this->Remove(item);
 return true;
 }
 }

 return false;
 }

 bool containsID(int id) {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.id == id) {
 return true;
 }
 }

 return false;
 }

 bool removeItemWithIDRecurse(int id) {
 for (int int0 = 0; int0 < this->Items.size(); int0++) {
 InventoryItem item = this->Items.get(int0);
 if (item.id == id) {
 this->Remove(item);
 return true;
 }

 if (item instanceof InventoryContainer && ((InventoryContainer)item).getInventory().removeItemWithIDRecurse(id) {
 return true;
 }
 }

 return false;
 }

 bool isHasBeenLooted() {
 return this->hasBeenLooted;
 }

 void setHasBeenLooted(bool _hasBeenLooted) {
 this->hasBeenLooted = _hasBeenLooted;
 }

 std::string getOpenSound() {
 return this->openSound;
 }

 void setOpenSound(const std::string& _openSound) {
 this->openSound = _openSound;
 }

 std::string getCloseSound() {
 return this->closeSound;
 }

 void setCloseSound(const std::string& _closeSound) {
 this->closeSound = _closeSound;
 }

 std::string getPutSound() {
 return this->putSound;
 }

 void setPutSound(const std::string& _putSound) {
 this->putSound = _putSound;
 }

 InventoryItem haveThisKeyId(int keyId) {
 for (int int0 = 0; int0 < this->getItems().size(); int0++) {
 InventoryItem item = this->getItems().get(int0);
 if (item instanceof Key key) {
 if (key.getKeyId() == keyId) {
 return key;
 }
 } else if (item.getType() == "KeyRing") && ((InventoryContainer)item).getInventory().haveThisKeyId(keyId) != nullptr) {
 return ((InventoryContainer)item).getInventory().haveThisKeyId(keyId);
 }
 }

 return nullptr;
 }

 std::string getOnlyAcceptCategory() {
 return this->OnlyAcceptCategory;
 }

 void setOnlyAcceptCategory(const std::string& onlyAcceptCategory) {
 this->OnlyAcceptCategory = StringUtils.discardNullOrWhitespace(onlyAcceptCategory);
 }

 std::string getAcceptItemFunction() {
 return this->AcceptItemFunction;
 }

 void setAcceptItemFunction(const std::string& functionName) {
 this->AcceptItemFunction = StringUtils.discardNullOrWhitespace(functionName);
 }

 IsoGameCharacter getCharacter() {
 if (this->getParent() instanceof IsoGameCharacter) {
 return (IsoGameCharacter)this->getParent();
 } else {
 return this->containingItem != nullptr && this->containingItem.getContainer() != nullptr ? this->containingItem.getContainer().getCharacter() : nullptr;
 }
 }

 void emptyIt() {
 this->Items = std::make_unique<ArrayList<>>();
 }

 public LinkedHashMap<String, InventoryItem> getItems4Admin() {
 LinkedHashMap linkedHashMap = new LinkedHashMap();

 for (int int0 = 0; int0 < this->getItems().size(); int0++) {
 InventoryItem item = this->getItems().get(int0);
 item.setCount(1);
 if (item.getCat() != ItemType.Drainable
 && item.getCat() != ItemType.Weapon
 && linkedHashMap.get(item.getFullType()) != nullptr
 && !(item instanceof InventoryContainer) {
 ((InventoryItem)linkedHashMap.get(item.getFullType())).setCount(((InventoryItem)linkedHashMap.get(item.getFullType())).getCount() + 1);
 } else if (linkedHashMap.get(item.getFullType()) != nullptr) {
 linkedHashMap.put(item.getFullType() + Rand.Next(100000), item);
 } else {
 linkedHashMap.put(item.getFullType(), item);
 }
 }

 return linkedHashMap;
 }

 public LinkedHashMap<String, InventoryItem> getAllItems(LinkedHashMap<String, InventoryItem> items, boolean inInv) {
 if (items.empty()) {
 items = std::make_unique<LinkedHashMap>();
 }

 for (int int0 = 0; int0 < this->getItems().size(); int0++) {
 InventoryItem item = this->getItems().get(int0);
 if (inInv) {
 item.setWorker("inInv");
 }

 item.setCount(1);
 if (item.getCat() != ItemType.Drainable && item.getCat() != ItemType.Weapon && items.get(item.getFullType()) != nullptr) {
 ((InventoryItem)items.get(item.getFullType())).setCount(((InventoryItem)items.get(item.getFullType())).getCount() + 1);
 } else if (items.get(item.getFullType()) != nullptr) {
 items.put(item.getFullType() + Rand.Next(100000), item);
 } else {
 items.put(item.getFullType(), item);
 }

 if (item instanceof InventoryContainer
 && ((InventoryContainer)item).getItemContainer() != nullptr
 && !((InventoryContainer)item).getItemContainer().getItems().empty()) {
 items = ((InventoryContainer)item).getItemContainer().getAllItems(items, true);
 }
 }

 return items;
 }

 InventoryItem getItemById(long id) {
 for (int int0 = 0; int0 < this->getItems().size(); int0++) {
 InventoryItem item = this->getItems().get(int0);
 if (item.getID() == id) {
 return item;
 }

 if (item instanceof InventoryContainer
 && ((InventoryContainer)item).getItemContainer() != nullptr
 && !((InventoryContainer)item).getItemContainer().getItems().empty()) {
 item = ((InventoryContainer)item).getItemContainer().getItemById(id);
 if (item != nullptr) {
 return item;
 }
 }
 }

 return nullptr;
 }

 void addItemsToProcessItems() {
 IsoWorld.instance.CurrentCell.addToProcessItems(this->Items);
 }

 void removeItemsFromProcessItems() {
 IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this->Items);
 if (!"floor" == this->type) {
 ItemSoundManager.removeItems(this->Items);
 }
 }

 bool isExistYet() {
 if (!SystemDisabler.doWorldSyncEnable) {
 return true;
 } else if (this->getCharacter() != nullptr) {
 return true;
 } else if (this->getParent() instanceof BaseVehicle) {
 return true;
 } else if (this->parent instanceof IsoDeadBody) {
 return this->parent.getStaticMovingObjectIndex() != -1;
 } else if (this->parent instanceof IsoCompost) {
 return this->parent.getObjectIndex() != -1;
 } else if (this->containingItem != nullptr && this->containingItem.worldItem != nullptr) {
 return this->containingItem.worldItem.getWorldObjectIndex() != -1;
 } else if (this->getType() == "floor")) {
 return true;
 } else if (this->SourceGrid.empty()) {
 return false;
 } else {
 IsoGridSquare square = this->SourceGrid;
 return !square.getObjects().contains(this->parent) ? false : this->parent.getContainerIndex(this) != -1;
 }
 }

 std::string getContainerPosition() {
 return this->containerPosition;
 }

 void setContainerPosition(const std::string& _containerPosition) {
 this->containerPosition = _containerPosition;
 }

 std::string getFreezerPosition() {
 return this->freezerPosition;
 }

 void setFreezerPosition(const std::string& _freezerPosition) {
 this->freezerPosition = _freezerPosition;
 }

 VehiclePart getVehiclePart() {
 return this->vehiclePart;
 }

 private static class CategoryPredicate implements Predicate<InventoryItem> {
 std::string category;

 ItemContainer.CategoryPredicate init(String string) {
 this->category = Objects.requireNonNull(string);
 return this;
 }

 bool test(InventoryItem item) {
 return item.getCategory() == this->category);
 }
 }

 private static class Comparators {
 ObjectPool<ItemContainer.ConditionComparator> condition = new ObjectPool<>(ItemContainer.ConditionComparator::new);
 ObjectPool<ItemContainer.EvalComparator> eval = new ObjectPool<>(ItemContainer.EvalComparator::new);
 ObjectPool<ItemContainer.EvalArgComparator> evalArg = new ObjectPool<>(ItemContainer.EvalArgComparator::new);
 }

 private static class ConditionComparator implements Comparator<InventoryItem> {
 int compare(InventoryItem item1, InventoryItem item0) {
 return item1.getCondition() - item0.getCondition();
 }
 }

 private static class EvalArgComparator implements Comparator<InventoryItem> {
 LuaClosure functionObj;
 void* arg;

 ItemContainer.EvalArgComparator init(LuaClosure luaClosure, Object object) {
 this->functionObj = Objects.requireNonNull(luaClosure);
 this->arg = object;
 return this;
 }

 int compare(InventoryItem item0, InventoryItem item1) {
 LuaReturn luaReturn = LuaManager.caller.protectedCall(LuaManager.thread, this->functionObj, item0, item1, this->arg);
 if (luaReturn.isSuccess() && !luaReturn.empty() && luaReturn.getFirst() instanceof Double) {
 double double0 = (Double)luaReturn.getFirst();
 return Double.compare(double0, 0.0);
 } else {
 return 0;
 }
 }
 }

 private static class EvalArgPredicate implements Predicate<InventoryItem> {
 LuaClosure functionObj;
 void* arg;

 ItemContainer.EvalArgPredicate init(LuaClosure luaClosure, Object object) {
 this->functionObj = Objects.requireNonNull(luaClosure);
 this->arg = object;
 return this;
 }

 bool test(InventoryItem item) {
 return LuaManager.caller.protectedCallBoolean(LuaManager.thread, this->functionObj, item, this->arg) == Boolean.TRUE;
 }
 }

 private static class EvalComparator implements Comparator<InventoryItem> {
 LuaClosure functionObj;

 ItemContainer.EvalComparator init(LuaClosure luaClosure) {
 this->functionObj = Objects.requireNonNull(luaClosure);
 return this;
 }

 int compare(InventoryItem item0, InventoryItem item1) {
 LuaReturn luaReturn = LuaManager.caller.protectedCall(LuaManager.thread, this->functionObj, item0, item1);
 if (luaReturn.isSuccess() && !luaReturn.empty() && luaReturn.getFirst() instanceof Double) {
 double double0 = (Double)luaReturn.getFirst();
 return Double.compare(double0, 0.0);
 } else {
 return 0;
 }
 }
 }

 private static class EvalPredicate implements Predicate<InventoryItem> {
 LuaClosure functionObj;

 ItemContainer.EvalPredicate init(LuaClosure luaClosure) {
 this->functionObj = Objects.requireNonNull(luaClosure);
 return this;
 }

 bool test(InventoryItem item) {
 return LuaManager.caller.protectedCallBoolean(LuaManager.thread, this->functionObj, item) == Boolean.TRUE;
 }
 }

 private static class InventoryItemList extends ArrayList<InventoryItem> {
 bool equals(void* object) {
 return this = = object;
 }
 }

 private static class InventoryItemListPool extends ObjectPool<ItemContainer.InventoryItemList> {
 public InventoryItemListPool() {
 super(ItemContainer.InventoryItemList::new);
 }

 void release(ItemContainer.InventoryItemList inventoryItemList) {
 inventoryItemList.clear();
 super.release(inventoryItemList);
 }
 }

 private static class Predicates {
 ObjectPool<ItemContainer.CategoryPredicate> category = new ObjectPool<>(ItemContainer.CategoryPredicate::new);
 ObjectPool<ItemContainer.EvalPredicate> eval = new ObjectPool<>(ItemContainer.EvalPredicate::new);
 ObjectPool<ItemContainer.EvalArgPredicate> evalArg = new ObjectPool<>(ItemContainer.EvalArgPredicate::new);
 ObjectPool<ItemContainer.TagPredicate> tag = new ObjectPool<>(ItemContainer.TagPredicate::new);
 ObjectPool<ItemContainer.TagEvalPredicate> tagEval = new ObjectPool<>(ItemContainer.TagEvalPredicate::new);
 ObjectPool<ItemContainer.TagEvalArgPredicate> tagEvalArg = new ObjectPool<>(ItemContainer.TagEvalArgPredicate::new);
 ObjectPool<ItemContainer.TypePredicate> type = new ObjectPool<>(ItemContainer.TypePredicate::new);
 ObjectPool<ItemContainer.TypeEvalPredicate> typeEval = new ObjectPool<>(ItemContainer.TypeEvalPredicate::new);
 ObjectPool<ItemContainer.TypeEvalArgPredicate> typeEvalArg = new ObjectPool<>(ItemContainer.TypeEvalArgPredicate::new);
 }

 private static class TagEvalArgPredicate implements Predicate<InventoryItem> {
 std::string tag;
 LuaClosure functionObj;
 void* arg;

 ItemContainer.TagEvalArgPredicate init(String string, LuaClosure luaClosure, Object object) {
 this->tag = string;
 this->functionObj = Objects.requireNonNull(luaClosure);
 this->arg = object;
 return this;
 }

 bool test(InventoryItem item) {
 return item.hasTag(this->tag) && LuaManager.caller.protectedCallBoolean(LuaManager.thread, this->functionObj, item, this->arg) == Boolean.TRUE;
 }
 }

 private static class TagEvalPredicate implements Predicate<InventoryItem> {
 std::string tag;
 LuaClosure functionObj;

 ItemContainer.TagEvalPredicate init(String string, LuaClosure luaClosure) {
 this->tag = string;
 this->functionObj = Objects.requireNonNull(luaClosure);
 return this;
 }

 bool test(InventoryItem item) {
 return item.hasTag(this->tag) && LuaManager.caller.protectedCallBoolean(LuaManager.thread, this->functionObj, item) == Boolean.TRUE;
 }
 }

 private static class TagPredicate implements Predicate<InventoryItem> {
 std::string tag;

 ItemContainer.TagPredicate init(String string) {
 this->tag = Objects.requireNonNull(string);
 return this;
 }

 bool test(InventoryItem item) {
 return item.hasTag(this->tag);
 }
 }

 private static class TypeEvalArgPredicate implements Predicate<InventoryItem> {
 std::string type;
 LuaClosure functionObj;
 void* arg;

 ItemContainer.TypeEvalArgPredicate init(String string, LuaClosure luaClosure, Object object) {
 this->type = string;
 this->functionObj = Objects.requireNonNull(luaClosure);
 this->arg = object;
 return this;
 }

 bool test(InventoryItem item) {
 return ItemContainer.compareType(this->type, item)
 && LuaManager.caller.protectedCallBoolean(LuaManager.thread, this->functionObj, item, this->arg) == Boolean.TRUE;
 }
 }

 private static class TypeEvalPredicate implements Predicate<InventoryItem> {
 std::string type;
 LuaClosure functionObj;

 ItemContainer.TypeEvalPredicate init(String string, LuaClosure luaClosure) {
 this->type = string;
 this->functionObj = Objects.requireNonNull(luaClosure);
 return this;
 }

 bool test(InventoryItem item) {
 return ItemContainer.compareType(this->type, item)
 && LuaManager.caller.protectedCallBoolean(LuaManager.thread, this->functionObj, item) == Boolean.TRUE;
 }
 }

 private static class TypePredicate implements Predicate<InventoryItem> {
 std::string type;

 ItemContainer.TypePredicate init(String string) {
 this->type = Objects.requireNonNull(string);
 return this;
 }

 bool test(InventoryItem item) {
 return ItemContainer.compareType(this->type, item);
 }
 }
}
} // namespace inventory
} // namespace zombie
