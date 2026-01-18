#include "zombie/iso/areas/IsoBuilding.h"

namespace zombie {
namespace iso {
namespace areas {

int IsoBuilding::getRoomsNumber() {
 // TODO: Implement getRoomsNumber
 return 0;
}

public IsoBuilding::IsoBuilding() {
 // TODO: Implement IsoBuilding
 return nullptr;
}

int IsoBuilding::getID() {
 // TODO: Implement getID
 return 0;
}

void IsoBuilding::TriggerAlarm() {
 // TODO: Implement TriggerAlarm
}

public IsoBuilding::IsoBuilding(IsoCell cell) {
 // TODO: Implement IsoBuilding
 return nullptr;
}

bool IsoBuilding::ContainsAllItems(Stack<String> items) {
 // TODO: Implement ContainsAllItems
 return false;
}

float IsoBuilding::ScoreBuildingPersonSpecific(SurvivorDesc desc, bool bFarGood) {
 // TODO: Implement ScoreBuildingPersonSpecific
 return 0;
}

BuildingDef IsoBuilding::getDef() {
 // TODO: Implement getDef
 return nullptr;
}

void IsoBuilding::update() {
 // TODO: Implement update
}

void IsoBuilding::AddRoom(IsoRoom room) {
 // TODO: Implement AddRoom
}

void IsoBuilding::CalculateExits() {
 // TODO: Implement CalculateExits
}

void IsoBuilding::CalculateWindows() {
 // TODO: Implement CalculateWindows
}

void IsoBuilding::FillContainers() {
 // TODO: Implement FillContainers
}

ItemContainer IsoBuilding::getContainerWith(ItemType itemType) {
 // TODO: Implement getContainerWith
 return nullptr;
}

IsoRoom IsoBuilding::getRandomRoom() {
 // TODO: Implement getRandomRoom
 return nullptr;
}

BuildingScore IsoBuilding::ScoreBuildingGeneral(BuildingScore buildingScore) {
 // TODO: Implement ScoreBuildingGeneral
 return nullptr;
}

IsoGridSquare IsoBuilding::getFreeTile() {
 // TODO: Implement getFreeTile
 return nullptr;
}

bool IsoBuilding::hasWater() {
 // TODO: Implement hasWater
 return false;
}

void IsoBuilding::CreateFrom(BuildingDef building, LotHeader info) {
 // TODO: Implement CreateFrom
}

void IsoBuilding::setAllExplored(bool b) {
 // TODO: Implement setAllExplored
}

bool IsoBuilding::isAllExplored() {
 // TODO: Implement isAllExplored
 return false;
}

void IsoBuilding::addWindow(IsoWindow obj, bool bOtherTile, IsoGridSquare from, IsoBuilding building) {
 // TODO: Implement addWindow
}

void IsoBuilding::addWindow(IsoWindow obj, bool bOtherTile) {
 // TODO: Implement addWindow
}

void IsoBuilding::addDoor(IsoDoor obj, bool bOtherTile, IsoGridSquare from, IsoBuilding building) {
 // TODO: Implement addDoor
}

void IsoBuilding::addDoor(IsoDoor obj, bool bOtherTile) {
 // TODO: Implement addDoor
}

bool IsoBuilding::isResidential() {
 // TODO: Implement isResidential
 return false;
}

bool IsoBuilding::containsRoom(const std::string& room) {
 // TODO: Implement containsRoom
 return false;
}

IsoRoom IsoBuilding::getRandomRoom(const std::string& room) {
 // TODO: Implement getRandomRoom
 return nullptr;
}

ItemContainer IsoBuilding::getRandomContainer(const std::string& type) {
 // TODO: Implement getRandomContainer
 return nullptr;
}

IsoWindow IsoBuilding::getRandomFirstFloorWindow() {
 // TODO: Implement getRandomFirstFloorWindow
 return nullptr;
}

bool IsoBuilding::isToxic() {
 // TODO: Implement isToxic
 return false;
}

void IsoBuilding::setToxic(bool _isToxic) {
 // TODO: Implement setToxic
}

void IsoBuilding::forceAwake() {
 // TODO: Implement forceAwake
}

} // namespace areas
} // namespace iso
} // namespace zombie
