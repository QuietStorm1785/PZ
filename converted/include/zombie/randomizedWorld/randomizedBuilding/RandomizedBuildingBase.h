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
#include "zombie/VirtualZombieManager.h"
#include "zombie/ZombieSpawnRecorder.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/IHumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/WeaponPart.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/SpawnPoints.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/objects/IsoBarricade.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/randomizedWorld/RandomizedWorldBase.h"
#include <iterator>

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class RandomizedBuildingBase : public RandomizedWorldBase {
public:
 int chance = 0;
 static int totalChance = 0;
 private static HashMap<RandomizedBuildingBase, Integer> rbMap = std::make_unique<HashMap<>>();
 static const int KBBuildingX = 10744;
 static const int KBBuildingY = 9409;
 bool alwaysDo = false;
 private static HashMap<String, String> weaponsList = std::make_unique<HashMap<>>();

 void randomizeBuilding(BuildingDef def) {
 def.bAlarmed = false;
 }

 void init() {
 if (weaponsList.empty()) {
 weaponsList.put("Base.Shotgun", "Base.ShotgunShellsBox");
 weaponsList.put("Base.Pistol", "Base.Bullets9mmBox");
 weaponsList.put("Base.Pistol2", "Base.Bullets45Box");
 weaponsList.put("Base.Pistol3", "Base.Bullets44Box");
 weaponsList.put("Base.VarmintRifle", "Base.223Box");
 weaponsList.put("Base.HuntingRifle", "Base.308Box");
 }
 }

 static void initAllRBMapChance() {
 for (int int0 = 0; int0 < IsoWorld.instance.getRandomizedBuildingList().size(); int0++) {
 totalChance = totalChance + IsoWorld.instance.getRandomizedBuildingList().get(int0).getChance();
 rbMap.put(IsoWorld.instance.getRandomizedBuildingList().get(int0), IsoWorld.instance.getRandomizedBuildingList().get(int0).getChance());
 }
 }

 /**
 * Don't do any building change in a player's building Also check if the building have a bathroom, a kitchen and a bedroom This is ignored for the alwaysDo building (so i can do stuff in spiffo, pizzawhirled, etc..)
 */
 bool isValid(BuildingDef def, bool force) {
 this->debugLine = "";
 if (GameClient.bClient) {
 return false;
 } else if (def.isAllExplored() && !force) {
 return false;
 } else {
 if (!GameServer.bServer) {
 if (!force
 && IsoPlayer.getInstance().getSquare() != nullptr
 && IsoPlayer.getInstance().getSquare().getBuilding() != nullptr
 && IsoPlayer.getInstance().getSquare().getBuilding().def == def) {
 this->customizeStartingHouse(IsoPlayer.getInstance().getSquare().getBuilding().def);
 return false;
 }
 } else if (!force) {
 for (int int0 = 0; int0 < GameServer.Players.size(); int0++) {
 IsoPlayer player = GameServer.Players.get(int0);
 if (player.getSquare() != nullptr && player.getSquare().getBuilding() != nullptr && player.getSquare().getBuilding().def == def) {
 return false;
 }
 }
 }

 bool boolean0 = false;
 bool boolean1 = false;
 bool boolean2 = false;

 for (int int1 = 0; int1 < def.rooms.size(); int1++) {
 RoomDef roomDef = def.rooms.get(int1);
 if ("bedroom" == roomDef.name) {
 boolean0 = true;
 }

 if ("kitchen" == roomDef.name) || "livingroom" == roomDef.name) {
 boolean1 = true;
 }

 if ("bathroom" == roomDef.name) {
 boolean2 = true;
 }
 }

 if (!boolean0) {
 this->debugLine = this->debugLine + "no bedroom ";
 }

 if (!boolean2) {
 this->debugLine = this->debugLine + "no bathroom ";
 }

 if (!boolean1) {
 this->debugLine = this->debugLine + "no living room or kitchen ";
 }

 return boolean0 && boolean2 && boolean1;
 }
 }

 void customizeStartingHouse(BuildingDef var1) {
 }

 int getMinimumDays() {
 return this->minimumDays;
 }

 void setMinimumDays(int minimumDays) {
 this->minimumDays = minimumDays;
 }

 int getMinimumRooms() {
 return this->minimumRooms;
 }

 void setMinimumRooms(int minimumRooms) {
 this->minimumRooms = minimumRooms;
 }

 static void ChunkLoaded(IsoBuilding building) {
 if (!GameClient.bClient && building.def != nullptr && !building.def.seen && building.def.isFullyStreamedIn()) {
 if (GameServer.bServer && GameServer.Players.empty()) {
 return;
 }

 for (int int0 = 0; int0 < building.Rooms.size(); int0++) {
 if (building.Rooms.get(int0).def.bExplored) {
 return;
 }
 }

 if (!building.def.isAnyChunkNewlyLoaded()) {
 building.def.seen = true;
 return;
 }

 std::vector arrayList = new ArrayList();

 for (int int1 = 0; int1 < IsoWorld.instance.getRandomizedBuildingList().size(); int1++) {
 RandomizedBuildingBase randomizedBuildingBase0 = IsoWorld.instance.getRandomizedBuildingList().get(int1);
 if (randomizedBuildingBase0.isAlwaysDo() && randomizedBuildingBase0.isValid(building.def, false) {
 arrayList.add(randomizedBuildingBase0);
 }
 }

 building.def.seen = true;
 if (building.def.x == 10744 && building.def.y == 9409 && Rand.Next(100) < 31) {
 RBKateAndBaldspot rBKateAndBaldspot = new RBKateAndBaldspot();
 rBKateAndBaldspot.randomizeBuilding(building.def);
 return;
 }

 if (!arrayList.empty()) {
 RandomizedBuildingBase randomizedBuildingBase1 = (RandomizedBuildingBase)arrayList.get(Rand.Next(0, arrayList.size()));
 if (randomizedBuildingBase1 != nullptr) {
 randomizedBuildingBase1.randomizeBuilding(building.def);
 return;
 }
 }

 if (GameServer.bServer && SpawnPoints.instance.isSpawnBuilding(building.getDef())) {
 return;
 }

 RandomizedBuildingBase randomizedBuildingBase2 = IsoWorld.instance.getRBBasic();
 if ("Tutorial" == Core.GameMode) {
 return;
 }

 try {
 uint8_t byte0 = 10;
 switch (SandboxOptions.instance.SurvivorHouseChance.getValue()) {
 case 1:
 return;
 case 2:
 byte0 -= 5;
 case 3:
 default:
 break;
 case 4:
 byte0 += 5;
 break;
 case 5:
 byte0 += 10;
 break;
 case 6:
 byte0 += 20;
 }

 if (Rand.Next(100) <= byte0) {
 if (totalChance == 0) {
 initAllRBMapChance();
 }

 randomizedBuildingBase2 = getRandomStory();
 if (randomizedBuildingBase2.empty()) {
 return;
 }
 }

 if (randomizedBuildingBase2.isValid(building.def, false) && randomizedBuildingBase2.isTimeValid(false) {
 randomizedBuildingBase2.randomizeBuilding(building.def);
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }
 }

 int getChance() {
 return this->chance;
 }

 void setChance(int _chance) {
 this->chance = _chance;
 }

 bool isAlwaysDo() {
 return this->alwaysDo;
 }

 void setAlwaysDo(bool _alwaysDo) {
 this->alwaysDo = _alwaysDo;
 }

 static RandomizedBuildingBase getRandomStory() {
 int int0 = Rand.Next(totalChance);
 Iterator iterator = rbMap.keySet().iterator();
 int int1 = 0;

 while (iterator.hasNext()) {
 RandomizedBuildingBase randomizedBuildingBase = (RandomizedBuildingBase)iterator.next();
 int1 += rbMap.get(randomizedBuildingBase);
 if (int0 < int1) {
 return randomizedBuildingBase;
 }
 }

 return nullptr;
 }

 public ArrayList<IsoZombie> addZombiesOnSquare(int totalZombies, String outfit, Integer femaleChance, IsoGridSquare square) {
 if (!IsoWorld.getZombiesDisabled() && !"Tutorial" == Core.GameMode) {
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < totalZombies; int0++) {
 VirtualZombieManager.instance.choices.clear();
 VirtualZombieManager.instance.choices.add(square);
 IsoZombie zombie0 = VirtualZombieManager.instance.createRealZombieAlways(IsoDirections.getRandom().index(), false);
 if (zombie0 != nullptr) {
 if ("Kate" == outfit) || "Bob" == outfit) || "Raider" == outfit) {
 zombie0.doDirtBloodEtc = false;
 }

 if (femaleChance != nullptr) {
 zombie0.setFemaleEtc(Rand.Next(100) < femaleChance);
 }

 if (outfit != nullptr) {
 zombie0.dressInPersistentOutfit(outfit);
 zombie0.bDressInRandomOutfit = false;
 } else {
 zombie0.bDressInRandomOutfit = true;
 }

 arrayList.add(zombie0);
 }
 }

 ZombieSpawnRecorder.instance.record(arrayList, this->getClass().getSimpleName());
 return arrayList;
 } else {
 return nullptr;
 }
 }

 /**
 * If you specify a outfit, make sure it works for both gender! (or force femaleChance to 0 or 1 if it's gender-specific)
 * 
 * @param def buildingDef
 * @param totalZombies zombies to spawn (if 0 we gonna randomize it)
 * @param outfit force zombies spanwed in a specific outfit (not mandatory)
 * @param femaleChance force female zombies (if not set it'll be 50% chance, you can set it to 0 to exclude female from spawning, or 100 to force only female)
 * @param room force spawn zombies inside a certain room (not mandatory)
 */
 public ArrayList<IsoZombie> addZombies(BuildingDef def, int totalZombies, String outfit, Integer femaleChance, RoomDef room) {
 bool boolean0 = room == nullptr;
 std::vector arrayList = new ArrayList();
 if (!IsoWorld.getZombiesDisabled() && !"Tutorial" == Core.GameMode) {
 if (room.empty()) {
 room = this->getRandomRoom(def, 6);
 }

 int int0 = 2;
 int int1 = room.area / 2;
 if (totalZombies == 0) {
 if (SandboxOptions.instance.Zombies.getValue() == 1) {
 int1 += 4;
 } else if (SandboxOptions.instance.Zombies.getValue() == 2) {
 int1 += 3;
 } else if (SandboxOptions.instance.Zombies.getValue() == 3) {
 int1 += 2;
 } else if (SandboxOptions.instance.Zombies.getValue() == 5) {
 int1 -= 4;
 }

 if (int1 > 8) {
 int1 = 8;
 }

 if (int1 < int0) {
 int1 = int0 + 1;
 }
 } else {
 int0 = totalZombies;
 int1 = totalZombies;
 }

 int int2 = Rand.Next(int0, int1);

 for (int int3 = 0; int3 < int2; int3++) {
 IsoGridSquare square = getRandomSpawnSquare(room);
 if (square.empty()) {
 break;
 }

 VirtualZombieManager.instance.choices.clear();
 VirtualZombieManager.instance.choices.add(square);
 IsoZombie zombie0 = VirtualZombieManager.instance.createRealZombieAlways(IsoDirections.getRandom().index(), false);
 if (zombie0 != nullptr) {
 if (femaleChance != nullptr) {
 zombie0.setFemaleEtc(Rand.Next(100) < femaleChance);
 }

 if (outfit != nullptr) {
 zombie0.dressInPersistentOutfit(outfit);
 zombie0.bDressInRandomOutfit = false;
 } else {
 zombie0.bDressInRandomOutfit = true;
 }

 arrayList.add(zombie0);
 if (boolean0) {
 room = this->getRandomRoom(def, 6);
 }
 }
 }

 ZombieSpawnRecorder.instance.record(arrayList, this->getClass().getSimpleName());
 return arrayList;
 } else {
 return arrayList;
 }
 }

 HandWeapon addRandomRangedWeapon(ItemContainer container, bool addBulletsInGun, bool addBoxInContainer, bool attachPart) {
 if (weaponsList.empty() || weaponsList.empty()) {
 this->init();
 }

 std::vector arrayList = new ArrayList<>(weaponsList.keySet());
 std::string string = (String)arrayList.get(Rand.Next(0, arrayList.size()));
 HandWeapon weapon = this->addWeapon(string, addBulletsInGun);
 if (weapon.empty()) {
 return nullptr;
 } else {
 if (addBoxInContainer) {
 container.addItem(InventoryItemFactory.CreateItem(weaponsList.get(string));
 }

 if (attachPart) {
 KahluaTable table0 = (KahluaTable)LuaManager.env.rawget("WeaponUpgrades");
 if (table0.empty()) {
 return nullptr;
 }

 KahluaTable table1 = (KahluaTable)table0.rawget(weapon.getType());
 if (table1.empty()) {
 return nullptr;
 }

 int int0 = Rand.Next(1, table1.len() + 1);

 for (int int1 = 1; int1 <= int0; int1++) {
 int int2 = Rand.Next(table1.len()) + 1;
 WeaponPart weaponPart = (WeaponPart)InventoryItemFactory.CreateItem((String)table1.rawget(int2);
 weapon.attachWeaponPart(weaponPart);
 }
 }

 return weapon;
 }
 }

 void spawnItemsInContainers(BuildingDef def, const std::string& distribName, int _chance) {
 std::vector arrayList = new ArrayList();
 ItemPickerJava.ItemPickerRoom itemPickerRoom = ItemPickerJava.rooms.get(distribName);
 IsoCell cell = IsoWorld.instance.CurrentCell;

 for (int int0 = def.x - 1; int0 < def.x2 + 1; int0++) {
 for (int int1 = def.y - 1; int1 < def.y2 + 1; int1++) {
 for (int int2 = 0; int2 < 8; int2++) {
 IsoGridSquare square = cell.getGridSquare(int0, int1, int2);
 if (square != nullptr) {
 for (int int3 = 0; int3 < square.getObjects().size(); int3++) {
 IsoObject object = square.getObjects().get(int3);
 if (Rand.Next(100) <= _chance
 && object.getContainer() != nullptr
 && square.getRoom() != nullptr
 && square.getRoom().getName() != nullptr
 && itemPickerRoom.Containers.containsKey(object.getContainer().getType())) {
 object.getContainer().clear();
 arrayList.add(object.getContainer());
 object.getContainer().setExplored(true);
 }
 }
 }
 }
 }
 }

 for (int int4 = 0; int4 < arrayList.size(); int4++) {
 ItemContainer container = (ItemContainer)arrayList.get(int4);
 ItemPickerJava.fillContainerType(itemPickerRoom, container, "", nullptr);
 ItemPickerJava.updateOverlaySprite(container.getParent());
 if (GameServer.bServer) {
 GameServer.sendItemsInContainer(container.getParent(), container);
 }
 }
 }

 void removeAllZombies(BuildingDef buildingDef) {
 for (int int0 = buildingDef.x - 1; int0 < buildingDef.x + buildingDef.x2 + 1; int0++) {
 for (int int1 = buildingDef.y - 1; int1 < buildingDef.y + buildingDef.y2 + 1; int1++) {
 for (int int2 = 0; int2 < 8; int2++) {
 IsoGridSquare square = this->getSq(int0, int1, int2);
 if (square != nullptr) {
 for (int int3 = 0; int3 < square.getMovingObjects().size(); int3++) {
 square.getMovingObjects().remove(int3);
 int3--;
 }
 }
 }
 }
 }
 }

 IsoWindow getWindow(IsoGridSquare sq) {
 for (int int0 = 0; int0 < sq.getObjects().size(); int0++) {
 IsoObject object = sq.getObjects().get(int0);
 if (object instanceof IsoWindow) {
 return (IsoWindow)object;
 }
 }

 return nullptr;
 }

 IsoDoor getDoor(IsoGridSquare sq) {
 for (int int0 = 0; int0 < sq.getObjects().size(); int0++) {
 IsoObject object = sq.getObjects().get(int0);
 if (object instanceof IsoDoor) {
 return (IsoDoor)object;
 }
 }

 return nullptr;
 }

 void addBarricade(IsoGridSquare sq, int numPlanks) {
 for (int int0 = 0; int0 < sq.getObjects().size(); int0++) {
 IsoObject object = sq.getObjects().get(int0);
 if (object instanceof IsoDoor) {
 if (!((IsoDoor)object).isBarricadeAllowed()) {
 continue;
 }

 IsoGridSquare square0 = sq.getRoom() == nullptr ? sq : ((IsoDoor)object).getOppositeSquare();
 if (square0 != nullptr && square0.getRoom() == nullptr) {
 bool boolean0 = square0 != sq;
 IsoBarricade barricade0 = IsoBarricade.AddBarricadeToObject((IsoDoor)object, boolean0);
 if (barricade0 != nullptr) {
 for (int int1 = 0; int1 < numPlanks; int1++) {
 barricade0.addPlank(nullptr, nullptr);
 }

 if (GameServer.bServer) {
 barricade0.transmitCompleteItemToClients();
 }
 }
 }
 }

 if (object instanceof IsoWindow && ((IsoWindow)object).isBarricadeAllowed()) {
 IsoGridSquare square1 = sq.getRoom() == nullptr ? sq : ((IsoWindow)object).getOppositeSquare();
 bool boolean1 = square1 != sq;
 IsoBarricade barricade1 = IsoBarricade.AddBarricadeToObject((IsoWindow)object, boolean1);
 if (barricade1 != nullptr) {
 for (int int2 = 0; int2 < numPlanks; int2++) {
 barricade1.addPlank(nullptr, nullptr);
 }

 if (GameServer.bServer) {
 barricade1.transmitCompleteItemToClients();
 }
 }
 }
 }
 }

 InventoryItem addWorldItem(const std::string& item, IsoGridSquare sq, float xoffset, float yoffset, float zoffset) {
 return this->addWorldItem(item, sq, xoffset, yoffset, zoffset, 0);
 }

 InventoryItem addWorldItem(const std::string& item, IsoGridSquare sq, float xoffset, float yoffset, float zoffset, int worldZ) {
 if (item != nullptr && sq != nullptr) {
 InventoryItem _item = InventoryItemFactory.CreateItem(item);
 if (_item != nullptr) {
 _item.setAutoAge();
 _item.setWorldZRotation(worldZ);
 if (_item instanceof HandWeapon) {
 _item.setCondition(Rand.Next(2, _item.getConditionMax()));
 }

 return sq.AddWorldInventoryItem(_item, xoffset, yoffset, zoffset);
 } else {
 return nullptr;
 }
 } else {
 return nullptr;
 }
 }

 InventoryItem addWorldItem(const std::string& item, IsoGridSquare sq, IsoObject obj) {
 if (item != nullptr && sq != nullptr) {
 float float0 = 0.0F;
 if (obj != nullptr) {
 float0 = obj.getSurfaceOffsetNoTable() / 96.0F;
 }

 InventoryItem _item = InventoryItemFactory.CreateItem(item);
 if (_item != nullptr) {
 _item.setAutoAge();
 return sq.AddWorldInventoryItem(_item, Rand.Next(0.3F, 0.9F), Rand.Next(0.3F, 0.9F), float0);
 } else {
 return nullptr;
 }
 } else {
 return nullptr;
 }
 }

 bool isTableFor3DItems(IsoObject obj, IsoGridSquare sq) {
 return obj.getSurfaceOffsetNoTable() > 0.0F
 && obj.getContainer() == nullptr
 && sq.getProperties().Val("waterAmount") == nullptr
 && !obj.hasWater()
 && obj.getProperties().Val("BedType") == nullptr;
 }

 public static class HumanCorpse extends IsoGameCharacter implements IHumanVisual {
 const HumanVisual humanVisual = new HumanVisual(this);
 const ItemVisuals itemVisuals = new ItemVisuals();
 bool isSkeleton = false;

 public HumanCorpse(IsoCell cell, float float0, float float1, float float2) {
 super(cell, float0, float1, float2);
 cell.getObjectList().remove(this);
 cell.getAddList().remove(this);
 }

 void dressInNamedOutfit(const std::string& string) {
 this->getHumanVisual().dressInNamedOutfit(string, this->itemVisuals);
 this->getHumanVisual().synchWithOutfit(this->getHumanVisual().getOutfit());
 }

 HumanVisual getHumanVisual() {
 return this->humanVisual;
 }

 HumanVisual getVisual() {
 return this->humanVisual;
 }

 void Dressup(SurvivorDesc var1) {
 this->wornItems.setFromItemVisuals(this->itemVisuals);
 this->wornItems.addItemsToItemContainer(this->inventory);
 }

 bool isSkeleton() {
 return this->isSkeleton;
 }
 }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
