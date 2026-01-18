#include "zombie/inventory/ItemContainer.h"

namespace zombie {
namespace inventory {

public
ItemContainer::ItemContainer(int _ID, const std::string &containerName,
 IsoGridSquare square, IsoObject _parent) {
 // TODO: Implement ItemContainer
 return nullptr;
}

public
ItemContainer::ItemContainer(const std::string &containerName,
 IsoGridSquare square, IsoObject _parent) {
 // TODO: Implement ItemContainer
 return nullptr;
}

public
ItemContainer::ItemContainer(int _ID) {
 // TODO: Implement ItemContainer
 return nullptr;
}

public
ItemContainer::ItemContainer() {
 // TODO: Implement ItemContainer
 return nullptr;
}

float ItemContainer::floatingPointCorrection(float val) {
 // TODO: Implement floatingPointCorrection
 return 0;
}

int ItemContainer::getCapacity() {
 // TODO: Implement getCapacity
 return 0;
}

void ItemContainer::setCapacity(int int0) {
 // TODO: Implement setCapacity
}

InventoryItem ItemContainer::FindAndReturnWaterItem(int uses) {
 // TODO: Implement FindAndReturnWaterItem
 return nullptr;
}

InventoryItem ItemContainer::getItemFromTypeRecurse(const std::string &_type) {
 // TODO: Implement getItemFromTypeRecurse
 return nullptr;
}

int ItemContainer::getEffectiveCapacity(IsoGameCharacter chr) {
 // TODO: Implement getEffectiveCapacity
 return 0;
}

bool ItemContainer::hasRoomFor(IsoGameCharacter chr, InventoryItem item) {
 // TODO: Implement hasRoomFor
 return false;
}

bool ItemContainer::hasRoomFor(IsoGameCharacter chr, float weightVal) {
 // TODO: Implement hasRoomFor
 return false;
}

return ItemContainer::floatingPointCorrection() {
 // TODO: Implement floatingPointCorrection
 return nullptr;
}

bool ItemContainer::isItemAllowed(InventoryItem item) {
 // TODO: Implement isItemAllowed
 return false;
}

bool ItemContainer::isRemoveItemAllowed(InventoryItem item) {
 // TODO: Implement isRemoveItemAllowed
 return false;
}

bool ItemContainer::isExplored() {
 // TODO: Implement isExplored
 return false;
}

void ItemContainer::setExplored(bool b) {
 // TODO: Implement setExplored
}

bool ItemContainer::isInCharacterInventory(IsoGameCharacter chr) {
 // TODO: Implement isInCharacterInventory
 return false;
}

bool ItemContainer::isInside(InventoryItem item) {
 // TODO: Implement isInside
 return false;
}

InventoryItem ItemContainer::getContainingItem() {
 // TODO: Implement getContainingItem
 return nullptr;
}

InventoryItem ItemContainer::DoAddItem(InventoryItem item) {
 // TODO: Implement DoAddItem
 return nullptr;
}

InventoryItem ItemContainer::DoAddItemBlind(InventoryItem item) {
 // TODO: Implement DoAddItemBlind
 return nullptr;
}

void ItemContainer::AddItems(InventoryItem item, int use) {
 // TODO: Implement AddItems
}

int ItemContainer::getNumberOfItem(const std::string &findItem,
 bool includeReplaceOnDeplete) {
 // TODO: Implement getNumberOfItem
 return 0;
}

int ItemContainer::getNumberOfItem(const std::string &findItem) {
 // TODO: Implement getNumberOfItem
 return 0;
}

int ItemContainer::getNumberOfItem(const std::string &findItem,
 bool includeReplaceOnDeplete,
 ArrayList<ItemContainer> containers) {
 // TODO: Implement getNumberOfItem
 return 0;
}

int ItemContainer::getNumberOfItem(const std::string &findItem,
 bool includeReplaceOnDeplete,
 bool insideInv) {
 // TODO: Implement getNumberOfItem
 return 0;
}

InventoryItem ItemContainer::addItem(InventoryItem item) {
 // TODO: Implement addItem
 return nullptr;
}

InventoryItem ItemContainer::AddItem(InventoryItem item) {
 // TODO: Implement AddItem
 return nullptr;
}

InventoryItem ItemContainer::AddItemBlind(InventoryItem item) {
 // TODO: Implement AddItemBlind
 return nullptr;
}

InventoryItem ItemContainer::AddItem(const std::string &_type) {
 // TODO: Implement AddItem
 return nullptr;
}

bool ItemContainer::AddItem(const std::string &_type, float useDelta) {
 // TODO: Implement AddItem
 return false;
}

bool ItemContainer::contains(InventoryItem item) {
 // TODO: Implement contains
 return false;
}

bool ItemContainer::containsWithModule(const std::string &moduleType) {
 // TODO: Implement containsWithModule
 return false;
}

bool ItemContainer::containsWithModule(const std::string &moduleType,
 bool withDeltaLeft) {
 // TODO: Implement containsWithModule
 return false;
}

void ItemContainer::removeItemOnServer(InventoryItem item) {
 // TODO: Implement removeItemOnServer
}

void ItemContainer::addItemOnServer(InventoryItem item) {
 // TODO: Implement addItemOnServer
}

bool ItemContainer::contains(InventoryItem itemToFind, bool doInv) {
 // TODO: Implement contains
 return false;
}

bool ItemContainer::contains(const std::string &_type, bool doInv) {
 // TODO: Implement contains
 return false;
}

bool ItemContainer::containsType(const std::string &_type) {
 // TODO: Implement containsType
 return false;
}

bool ItemContainer::containsTypeRecurse(const std::string &_type) {
 // TODO: Implement containsTypeRecurse
 return false;
}

bool ItemContainer::testBroken(bool boolean0, InventoryItem item) {
 // TODO: Implement testBroken
 return false;
}

bool ItemContainer::contains(const std::string &_type, bool doInv,
 bool ignoreBroken) {
 // TODO: Implement contains
 return false;
}

bool ItemContainer::contains(const std::string &_type) {
 // TODO: Implement contains
 return false;
}

InventoryItem
ItemContainer::getBestOf(ItemContainer.InventoryItemList inventoryItemList,
 Comparator<InventoryItem> comparator) {
 // TODO: Implement getBestOf
 return nullptr;
}

InventoryItem ItemContainer::getBest(Predicate<InventoryItem> predicate,
 Comparator<InventoryItem> comparator) {
 // TODO: Implement getBest
 return nullptr;
}

InventoryItem
ItemContainer::getBestRecurse(Predicate<InventoryItem> predicate,
 Comparator<InventoryItem> comparator) {
 // TODO: Implement getBestRecurse
 return nullptr;
}

InventoryItem ItemContainer::getBestType(const std::string &_type,
 Comparator<InventoryItem> comparator) {
 // TODO: Implement getBestType
 return nullptr;
}

InventoryItem
ItemContainer::getBestTypeRecurse(const std::string &_type,
 Comparator<InventoryItem> comparator) {
 // TODO: Implement getBestTypeRecurse
 return nullptr;
}

InventoryItem ItemContainer::getBestEval(LuaClosure predicateObj,
 LuaClosure comparatorObj) {
 // TODO: Implement getBestEval
 return nullptr;
}

InventoryItem ItemContainer::getBestEvalRecurse(LuaClosure predicateObj,
 LuaClosure comparatorObj) {
 // TODO: Implement getBestEvalRecurse
 return nullptr;
}

InventoryItem ItemContainer::getBestEvalArg(LuaClosure predicateObj,
 LuaClosure comparatorObj,
 void *arg) {
 // TODO: Implement getBestEvalArg
 return nullptr;
}

InventoryItem ItemContainer::getBestEvalArgRecurse(LuaClosure predicateObj,
 LuaClosure comparatorObj,
 void *arg) {
 // TODO: Implement getBestEvalArgRecurse
 return nullptr;
}

InventoryItem ItemContainer::getBestTypeEval(const std::string &_type,
 LuaClosure comparatorObj) {
 // TODO: Implement getBestTypeEval
 return nullptr;
}

InventoryItem ItemContainer::getBestTypeEvalRecurse(const std::string &_type,
 LuaClosure comparatorObj) {
 // TODO: Implement getBestTypeEvalRecurse
 return nullptr;
}

InventoryItem ItemContainer::getBestTypeEvalArg(const std::string &_type,
 LuaClosure comparatorObj,
 void *arg) {
 // TODO: Implement getBestTypeEvalArg
 return nullptr;
}

InventoryItem ItemContainer::getBestTypeEvalArgRecurse(const std::string &_type,
 LuaClosure comparatorObj,
 void *arg) {
 // TODO: Implement getBestTypeEvalArgRecurse
 return nullptr;
}

InventoryItem
ItemContainer::getBestCondition(Predicate<InventoryItem> predicate) {
 // TODO: Implement getBestCondition
 return nullptr;
}

InventoryItem
ItemContainer::getBestConditionRecurse(Predicate<InventoryItem> predicate) {
 // TODO: Implement getBestConditionRecurse
 return nullptr;
}

InventoryItem ItemContainer::getBestCondition(const std::string &_type) {
 // TODO: Implement getBestCondition
 return nullptr;
}

InventoryItem ItemContainer::getBestConditionRecurse(const std::string &_type) {
 // TODO: Implement getBestConditionRecurse
 return nullptr;
}

InventoryItem ItemContainer::getBestConditionEval(LuaClosure functionObj) {
 // TODO: Implement getBestConditionEval
 return nullptr;
}

InventoryItem
ItemContainer::getBestConditionEvalRecurse(LuaClosure functionObj) {
 // TODO: Implement getBestConditionEvalRecurse
 return nullptr;
}

InventoryItem ItemContainer::getBestConditionEvalArg(LuaClosure functionObj,
 void *arg) {
 // TODO: Implement getBestConditionEvalArg
 return nullptr;
}

InventoryItem
ItemContainer::getBestConditionEvalArgRecurse(LuaClosure functionObj,
 void *arg) {
 // TODO: Implement getBestConditionEvalArgRecurse
 return nullptr;
}

InventoryItem ItemContainer::getFirstEval(LuaClosure functionObj) {
 // TODO: Implement getFirstEval
 return nullptr;
}

InventoryItem ItemContainer::getFirstEvalArg(LuaClosure functionObj,
 void *arg) {
 // TODO: Implement getFirstEvalArg
 return nullptr;
}

bool ItemContainer::containsEval(LuaClosure functionObj) {
 // TODO: Implement containsEval
 return false;
}

bool ItemContainer::containsEvalArg(LuaClosure functionObj, void *arg) {
 // TODO: Implement containsEvalArg
 return false;
}

bool ItemContainer::containsEvalRecurse(LuaClosure functionObj) {
 // TODO: Implement containsEvalRecurse
 return false;
}

bool ItemContainer::containsEvalArgRecurse(LuaClosure functionObj, void *arg) {
 // TODO: Implement containsEvalArgRecurse
 return false;
}

bool ItemContainer::containsTag(const std::string &tag) {
 // TODO: Implement containsTag
 return false;
}

bool ItemContainer::containsTagEval(const std::string &tag,
 LuaClosure functionObj) {
 // TODO: Implement containsTagEval
 return false;
}

bool ItemContainer::containsTagRecurse(const std::string &tag) {
 // TODO: Implement containsTagRecurse
 return false;
}

bool ItemContainer::containsTagEvalRecurse(const std::string &tag,
 LuaClosure functionObj) {
 // TODO: Implement containsTagEvalRecurse
 return false;
}

bool ItemContainer::containsTagEvalArgRecurse(const std::string &tag,
 LuaClosure functionObj,
 void *arg) {
 // TODO: Implement containsTagEvalArgRecurse
 return false;
}

bool ItemContainer::containsTypeEvalRecurse(const std::string &_type,
 LuaClosure functionObj) {
 // TODO: Implement containsTypeEvalRecurse
 return false;
}

bool ItemContainer::containsTypeEvalArgRecurse(const std::string &_type,
 LuaClosure functionObj,
 void *arg) {
 // TODO: Implement containsTypeEvalArgRecurse
 return false;
}

bool ItemContainer::compareType(const std::string &string0,
 const std::string &string1) {
 // TODO: Implement compareType
 return false;
}

bool ItemContainer::compareType(const std::string &string, InventoryItem item) {
 // TODO: Implement compareType
 return false;
}

InventoryItem ItemContainer::getFirst(Predicate<InventoryItem> predicate) {
 // TODO: Implement getFirst
 return nullptr;
}

InventoryItem
ItemContainer::getFirstRecurse(Predicate<InventoryItem> predicate) {
 // TODO: Implement getFirstRecurse
 return nullptr;
}

int ItemContainer::getCount(Predicate<InventoryItem> predicate) {
 // TODO: Implement getCount
 return 0;
}

int ItemContainer::getCountRecurse(Predicate<InventoryItem> predicate) {
 // TODO: Implement getCountRecurse
 return 0;
}

int ItemContainer::getCountTag(const std::string &tag) {
 // TODO: Implement getCountTag
 return 0;
}

int ItemContainer::getCountTagEval(const std::string &tag,
 LuaClosure functionObj) {
 // TODO: Implement getCountTagEval
 return 0;
}

int ItemContainer::getCountTagEvalArg(const std::string &tag,
 LuaClosure functionObj, void *arg) {
 // TODO: Implement getCountTagEvalArg
 return 0;
}

int ItemContainer::getCountTagRecurse(const std::string &tag) {
 // TODO: Implement getCountTagRecurse
 return 0;
}

int ItemContainer::getCountTagEvalRecurse(const std::string &tag,
 LuaClosure functionObj) {
 // TODO: Implement getCountTagEvalRecurse
 return 0;
}

int ItemContainer::getCountTagEvalArgRecurse(const std::string &tag,
 LuaClosure functionObj,
 void *arg) {
 // TODO: Implement getCountTagEvalArgRecurse
 return 0;
}

int ItemContainer::getCountType(const std::string &_type) {
 // TODO: Implement getCountType
 return 0;
}

int ItemContainer::getCountTypeEval(const std::string &_type,
 LuaClosure functionObj) {
 // TODO: Implement getCountTypeEval
 return 0;
}

int ItemContainer::getCountTypeEvalArg(const std::string &_type,
 LuaClosure functionObj, void *arg) {
 // TODO: Implement getCountTypeEvalArg
 return 0;
}

int ItemContainer::getCountTypeRecurse(const std::string &_type) {
 // TODO: Implement getCountTypeRecurse
 return 0;
}

int ItemContainer::getCountTypeEvalRecurse(const std::string &_type,
 LuaClosure functionObj) {
 // TODO: Implement getCountTypeEvalRecurse
 return 0;
}

int ItemContainer::getCountTypeEvalArgRecurse(const std::string &_type,
 LuaClosure functionObj,
 void *arg) {
 // TODO: Implement getCountTypeEvalArgRecurse
 return 0;
}

int ItemContainer::getCountEval(LuaClosure functionObj) {
 // TODO: Implement getCountEval
 return 0;
}

int ItemContainer::getCountEvalArg(LuaClosure functionObj, void *arg) {
 // TODO: Implement getCountEvalArg
 return 0;
}

int ItemContainer::getCountEvalRecurse(LuaClosure functionObj) {
 // TODO: Implement getCountEvalRecurse
 return 0;
}

int ItemContainer::getCountEvalArgRecurse(LuaClosure functionObj, void *arg) {
 // TODO: Implement getCountEvalArgRecurse
 return 0;
}

InventoryItem ItemContainer::getFirstCategory(const std::string &category) {
 // TODO: Implement getFirstCategory
 return nullptr;
}

InventoryItem
ItemContainer::getFirstCategoryRecurse(const std::string &category) {
 // TODO: Implement getFirstCategoryRecurse
 return nullptr;
}

InventoryItem ItemContainer::getFirstEvalRecurse(LuaClosure functionObj) {
 // TODO: Implement getFirstEvalRecurse
 return nullptr;
}

InventoryItem ItemContainer::getFirstEvalArgRecurse(LuaClosure functionObj,
 void *arg) {
 // TODO: Implement getFirstEvalArgRecurse
 return nullptr;
}

InventoryItem ItemContainer::getFirstTag(const std::string &tag) {
 // TODO: Implement getFirstTag
 return nullptr;
}

InventoryItem ItemContainer::getFirstTagRecurse(const std::string &tag) {
 // TODO: Implement getFirstTagRecurse
 return nullptr;
}

InventoryItem ItemContainer::getFirstTagEval(const std::string &tag,
 LuaClosure functionObj) {
 // TODO: Implement getFirstTagEval
 return nullptr;
}

InventoryItem ItemContainer::getFirstTagEvalRecurse(const std::string &tag,
 LuaClosure functionObj) {
 // TODO: Implement getFirstTagEvalRecurse
 return nullptr;
}

InventoryItem ItemContainer::getFirstTagEvalArgRecurse(const std::string &tag,
 LuaClosure functionObj,
 void *arg) {
 // TODO: Implement getFirstTagEvalArgRecurse
 return nullptr;
}

InventoryItem ItemContainer::getFirstType(const std::string &_type) {
 // TODO: Implement getFirstType
 return nullptr;
}

InventoryItem ItemContainer::getFirstTypeRecurse(const std::string &_type) {
 // TODO: Implement getFirstTypeRecurse
 return nullptr;
}

InventoryItem ItemContainer::getFirstTypeEval(const std::string &_type,
 LuaClosure functionObj) {
 // TODO: Implement getFirstTypeEval
 return nullptr;
}

InventoryItem ItemContainer::getFirstTypeEvalRecurse(const std::string &_type,
 LuaClosure functionObj) {
 // TODO: Implement getFirstTypeEvalRecurse
 return nullptr;
}

InventoryItem
ItemContainer::getFirstTypeEvalArgRecurse(const std::string &_type,
 LuaClosure functionObj, void *arg) {
 // TODO: Implement getFirstTypeEvalArgRecurse
 return nullptr;
}

InventoryItem
ItemContainer::FindAndReturnCategory(const std::string &category) {
 // TODO: Implement FindAndReturnCategory
 return nullptr;
}

InventoryItem
ItemContainer::FindAndReturn(const std::string &_type,
 ArrayList<InventoryItem> itemToCheck) {
 // TODO: Implement FindAndReturn
 return nullptr;
}

InventoryItem ItemContainer::FindAndReturn(const std::string &_type) {
 // TODO: Implement FindAndReturn
 return nullptr;
}

InventoryItem ItemContainer::FindAndReturnStack(const std::string &_type) {
 // TODO: Implement FindAndReturnStack
 return nullptr;
}

InventoryItem ItemContainer::FindAndReturnStack(InventoryItem itemlike) {
 // TODO: Implement FindAndReturnStack
 return nullptr;
}

bool ItemContainer::HasType(ItemType itemType) {
 // TODO: Implement HasType
 return false;
}

void ItemContainer::Remove(InventoryItem item) {
 // TODO: Implement Remove
}

void ItemContainer::DoRemoveItem(InventoryItem item) {
 // TODO: Implement DoRemoveItem
}

void ItemContainer::Remove(const std::string &itemTypes) {
 // TODO: Implement Remove
}

InventoryItem ItemContainer::Remove(ItemType itemType) {
 // TODO: Implement Remove
 return nullptr;
}

InventoryItem ItemContainer::Find(ItemType itemType) {
 // TODO: Implement Find
 return nullptr;
}

void ItemContainer::RemoveAll(const std::string &itemType) {
 // TODO: Implement RemoveAll
}

bool ItemContainer::RemoveOneOf(const std::string &String, bool insideInv) {
 // TODO: Implement RemoveOneOf
 return false;
}

void ItemContainer::RemoveOneOf(const std::string &String) {
 // TODO: Implement RemoveOneOf
}

int ItemContainer::getWeight() {
 // TODO: Implement getWeight
 return 0;
}

float ItemContainer::getContentsWeight() {
 // TODO: Implement getContentsWeight
 return 0;
}

float ItemContainer::getMaxWeight() {
 // TODO: Implement getMaxWeight
 return 0;
}

float ItemContainer::getCapacityWeight() {
 // TODO: Implement getCapacityWeight
 return 0;
}

bool ItemContainer::isEmpty() {
 // TODO: Implement isEmpty
 return false;
}

bool ItemContainer::isMicrowave() {
 // TODO: Implement isMicrowave
 return false;
}

bool ItemContainer::isSquareInRoom(IsoGridSquare square) {
 // TODO: Implement isSquareInRoom
 return false;
}

bool ItemContainer::isSquarePowered(IsoGridSquare square0) {
 // TODO: Implement isSquarePowered
 return false;
}

bool ItemContainer::isPowered() {
 // TODO: Implement isPowered
 return false;
}

float ItemContainer::getTemprature() {
 // TODO: Implement getTemprature
 return 0;
}

bool ItemContainer::isTemperatureChanging() {
 // TODO: Implement isTemperatureChanging
 return false;
}

bool ItemContainer::isDrawDirty() {
 // TODO: Implement isDrawDirty
 return false;
}

void ItemContainer::setDrawDirty(bool b) {
 // TODO: Implement setDrawDirty
}

InventoryItem ItemContainer::getBestWeapon(SurvivorDesc desc) {
 // TODO: Implement getBestWeapon
 return nullptr;
}

InventoryItem ItemContainer::getBestWeapon() {
 // TODO: Implement getBestWeapon
 return nullptr;
}

float ItemContainer::getTotalFoodScore(SurvivorDesc desc) {
 // TODO: Implement getTotalFoodScore
 return 0;
}

float ItemContainer::getTotalWeaponScore(SurvivorDesc desc) {
 // TODO: Implement getTotalWeaponScore
 return 0;
}

InventoryItem ItemContainer::getBestFood(SurvivorDesc descriptor) {
 // TODO: Implement getBestFood
 return nullptr;
}

InventoryItem ItemContainer::getBestBandage(SurvivorDesc descriptor) {
 // TODO: Implement getBestBandage
 return nullptr;
}

int ItemContainer::getNumItems(const std::string &item) {
 // TODO: Implement getNumItems
 return 0;
}

bool ItemContainer::isActive() {
 // TODO: Implement isActive
 return false;
}

void ItemContainer::setActive(bool _active) {
 // TODO: Implement setActive
}

bool ItemContainer::isDirty() {
 // TODO: Implement isDirty
 return false;
}

void ItemContainer::setDirty(bool _dirty) {
 // TODO: Implement setDirty
}

bool ItemContainer::isIsDevice() {
 // TODO: Implement isIsDevice
 return false;
}

void ItemContainer::setIsDevice(bool _IsDevice) {
 // TODO: Implement setIsDevice
}

float ItemContainer::getAgeFactor() {
 // TODO: Implement getAgeFactor
 return 0;
}

void ItemContainer::setAgeFactor(float _ageFactor) {
 // TODO: Implement setAgeFactor
}

float ItemContainer::getCookingFactor() {
 // TODO: Implement getCookingFactor
 return 0;
}

void ItemContainer::setCookingFactor(float _CookingFactor) {
 // TODO: Implement setCookingFactor
}

void ItemContainer::setItems(ArrayList<InventoryItem> _Items) {
 // TODO: Implement setItems
}

IsoObject ItemContainer::getParent() {
 // TODO: Implement getParent
 return nullptr;
}

void ItemContainer::setParent(IsoObject _parent) {
 // TODO: Implement setParent
}

IsoGridSquare ItemContainer::getSourceGrid() {
 // TODO: Implement getSourceGrid
 return nullptr;
}

void ItemContainer::setSourceGrid(IsoGridSquare _SourceGrid) {
 // TODO: Implement setSourceGrid
}

std::string ItemContainer::getType() {
 // TODO: Implement getType
 return "";
}

void ItemContainer::setType(const std::string &_type) {
 // TODO: Implement setType
}

void ItemContainer::clear() {
 // TODO: Implement clear
}

int ItemContainer::getWaterContainerCount() {
 // TODO: Implement getWaterContainerCount
 return 0;
}

InventoryItem ItemContainer::FindWaterSource() {
 // TODO: Implement FindWaterSource
 return nullptr;
}

int ItemContainer::getItemCount(const std::string &_type) {
 // TODO: Implement getItemCount
 return 0;
}

int ItemContainer::getItemCountRecurse(const std::string &_type) {
 // TODO: Implement getItemCountRecurse
 return 0;
}

int ItemContainer::getItemCount(const std::string &_type, bool doBags) {
 // TODO: Implement getItemCount
 return 0;
}

int ItemContainer::getUses(ItemContainer.InventoryItemList inventoryItemList) {
 // TODO: Implement getUses
 return 0;
}

int ItemContainer::getUsesRecurse(Predicate<InventoryItem> predicate) {
 // TODO: Implement getUsesRecurse
 return 0;
}

int ItemContainer::getUsesType(const std::string &_type) {
 // TODO: Implement getUsesType
 return 0;
}

int ItemContainer::getUsesTypeRecurse(const std::string &_type) {
 // TODO: Implement getUsesTypeRecurse
 return 0;
}

int ItemContainer::getWeightReduction() {
 // TODO: Implement getWeightReduction
 return 0;
}

void ItemContainer::setWeightReduction(int _weightReduction) {
 // TODO: Implement setWeightReduction
}

void ItemContainer::removeAllItems() {
 // TODO: Implement removeAllItems
}

bool ItemContainer::containsRecursive(InventoryItem item) {
 // TODO: Implement containsRecursive
 return false;
}

int ItemContainer::getItemCountFromTypeRecurse(const std::string &_type) {
 // TODO: Implement getItemCountFromTypeRecurse
 return 0;
}

float ItemContainer::getCustomTemperature() {
 // TODO: Implement getCustomTemperature
 return 0;
}

void ItemContainer::setCustomTemperature(float newTemp) {
 // TODO: Implement setCustomTemperature
}

InventoryItem ItemContainer::getItemFromType(const std::string &_type,
 IsoGameCharacter chr,
 bool notEquipped,
 bool ignoreBroken,
 bool includeInv) {
 // TODO: Implement getItemFromType
 return nullptr;
}

InventoryItem ItemContainer::getItemFromType(const std::string &_type,
 bool ignoreBroken,
 bool includeInv) {
 // TODO: Implement getItemFromType
 return nullptr;
}

InventoryItem ItemContainer::getItemFromType(const std::string &_type) {
 // TODO: Implement getItemFromType
 return nullptr;
}

void ItemContainer::sendContentsToRemoteContainer() {
 // TODO: Implement sendContentsToRemoteContainer
}

void ItemContainer::requestSync() {
 // TODO: Implement requestSync
}

void ItemContainer::requestServerItemsForContainer() {
 // TODO: Implement requestServerItemsForContainer
}

void ItemContainer::sendContentsToRemoteContainer(UdpConnection connection) {
 // TODO: Implement sendContentsToRemoteContainer
}

InventoryItem ItemContainer::getItemWithIDRecursiv(int id) {
 // TODO: Implement getItemWithIDRecursiv
 return nullptr;
}

InventoryItem ItemContainer::getItemWithID(int id) {
 // TODO: Implement getItemWithID
 return nullptr;
}

bool ItemContainer::removeItemWithID(int id) {
 // TODO: Implement removeItemWithID
 return false;
}

bool ItemContainer::containsID(int id) {
 // TODO: Implement containsID
 return false;
}

bool ItemContainer::removeItemWithIDRecurse(int id) {
 // TODO: Implement removeItemWithIDRecurse
 return false;
}

bool ItemContainer::isHasBeenLooted() {
 // TODO: Implement isHasBeenLooted
 return false;
}

void ItemContainer::setHasBeenLooted(bool _hasBeenLooted) {
 // TODO: Implement setHasBeenLooted
}

std::string ItemContainer::getOpenSound() {
 // TODO: Implement getOpenSound
 return "";
}

void ItemContainer::setOpenSound(const std::string &_openSound) {
 // TODO: Implement setOpenSound
}

std::string ItemContainer::getCloseSound() {
 // TODO: Implement getCloseSound
 return "";
}

void ItemContainer::setCloseSound(const std::string &_closeSound) {
 // TODO: Implement setCloseSound
}

std::string ItemContainer::getPutSound() {
 // TODO: Implement getPutSound
 return "";
}

void ItemContainer::setPutSound(const std::string &_putSound) {
 // TODO: Implement setPutSound
}

InventoryItem ItemContainer::haveThisKeyId(int keyId) {
 // TODO: Implement haveThisKeyId
 return nullptr;
}

std::string ItemContainer::getOnlyAcceptCategory() {
 // TODO: Implement getOnlyAcceptCategory
 return "";
}

void ItemContainer::setOnlyAcceptCategory(
 const std::string &onlyAcceptCategory) {
 // TODO: Implement setOnlyAcceptCategory
}

std::string ItemContainer::getAcceptItemFunction() {
 // TODO: Implement getAcceptItemFunction
 return "";
}

void ItemContainer::setAcceptItemFunction(const std::string &functionName) {
 // TODO: Implement setAcceptItemFunction
}

IsoGameCharacter ItemContainer::getCharacter() {
 // TODO: Implement getCharacter
 return nullptr;
}

void ItemContainer::emptyIt() {
 // TODO: Implement emptyIt
}

InventoryItem ItemContainer::getItemById(long id) {
 // TODO: Implement getItemById
 return nullptr;
}

void ItemContainer::addItemsToProcessItems() {
 // TODO: Implement addItemsToProcessItems
}

void ItemContainer::removeItemsFromProcessItems() {
 // TODO: Implement removeItemsFromProcessItems
}

bool ItemContainer::isExistYet() {
 // TODO: Implement isExistYet
 return false;
}

std::string ItemContainer::getContainerPosition() {
 // TODO: Implement getContainerPosition
 return "";
}

void ItemContainer::setContainerPosition(
 const std::string &_containerPosition) {
 // TODO: Implement setContainerPosition
}

std::string ItemContainer::getFreezerPosition() {
 // TODO: Implement getFreezerPosition
 return "";
}

void ItemContainer::setFreezerPosition(const std::string &_freezerPosition) {
 // TODO: Implement setFreezerPosition
}

VehiclePart ItemContainer::getVehiclePart() {
 // TODO: Implement getVehiclePart
 return nullptr;
}

bool ItemContainer::test(InventoryItem item) {
 // TODO: Implement test
 return false;
}

int ItemContainer::compare(InventoryItem item1, InventoryItem item0) {
 // TODO: Implement compare
 return 0;
}

int ItemContainer::compare(InventoryItem item0, InventoryItem item1) {
 // TODO: Implement compare
 return 0;
}

bool ItemContainer::test(InventoryItem item) {
 // TODO: Implement test
 return false;
}

int ItemContainer::compare(InventoryItem item0, InventoryItem item1) {
 // TODO: Implement compare
 return 0;
}

bool ItemContainer::test(InventoryItem item) {
 // TODO: Implement test
 return false;
}

bool ItemContainer::equals(void *object) {
 // TODO: Implement equals
 return false;
}

public
ItemContainer::InventoryItemListPool() {
 // TODO: Implement InventoryItemListPool
 return nullptr;
}

void ItemContainer::release(ItemContainer.InventoryItemList inventoryItemList) {
 // TODO: Implement release
}

bool ItemContainer::test(InventoryItem item) {
 // TODO: Implement test
 return false;
}

bool ItemContainer::test(InventoryItem item) {
 // TODO: Implement test
 return false;
}

bool ItemContainer::test(InventoryItem item) {
 // TODO: Implement test
 return false;
}

bool ItemContainer::test(InventoryItem item) {
 // TODO: Implement test
 return false;
}

bool ItemContainer::test(InventoryItem item) {
 // TODO: Implement test
 return false;
}

bool ItemContainer::test(InventoryItem item) {
 // TODO: Implement test
 return false;
}

} // namespace inventory
} // namespace zombie
