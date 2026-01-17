#include "zombie/randomizedWorld/randomizedBuilding/RBBasic.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {

void RBBasic::randomizeBuilding(BuildingDef def) {
  // TODO: Implement randomizeBuilding
}

void RBBasic::doLivingRoomStuff(IsoGridSquare square) {
  // TODO: Implement doLivingRoomStuff
}

void RBBasic::doBedroomStuff(IsoGridSquare square) {
  // TODO: Implement doBedroomStuff
}

void RBBasic::doKitchenStuff(IsoGridSquare square) {
  // TODO: Implement doKitchenStuff
}

void RBBasic::doBathroomStuff(IsoGridSquare square) {
  // TODO: Implement doBathroomStuff
}

void RBBasic::generateKitchenStoveClutter(IsoDirections directions,
                                          IsoObject object,
                                          IsoGridSquare square) {
  // TODO: Implement generateKitchenStoveClutter
}

void RBBasic::generateCounterClutter(IsoDirections directions, IsoObject object,
                                     IsoGridSquare square, String > hashMap) {
  // TODO: Implement generateCounterClutter
}

void RBBasic::generateSinkClutter(IsoDirections directions, IsoObject object,
                                  IsoGridSquare square, String > hashMap) {
  // TODO: Implement generateSinkClutter
}

IsoDirections RBBasic::getFacing(IsoSprite sprite) {
  // TODO: Implement getFacing
  return nullptr;
}

void RBBasic::checkForTableSpawn(BuildingDef buildingDef, IsoObject object) {
  // TODO: Implement checkForTableSpawn
}

IsoObject RBBasic::checkForTable(IsoGridSquare square, IsoObject object0) {
  // TODO: Implement checkForTable
  return nullptr;
}

void RBBasic::doProfessionStory(BuildingDef def,
                                const std::string &professionChoosed) {
  // TODO: Implement doProfessionStory
}

void RBBasic::addRandomDeadSurvivorStory(BuildingDef buildingDef) {
  // TODO: Implement addRandomDeadSurvivorStory
}

void RBBasic::initRDSMap(BuildingDef buildingDef) {
  // TODO: Implement initRDSMap
}

void RBBasic::doRandomDeadSurvivorStory(BuildingDef buildingDef,
                                        RandomizedDeadSurvivorBase DSDef) {
  // TODO: Implement doRandomDeadSurvivorStory
}

public
RBBasic::RBBasic() {
  // TODO: Implement RBBasic
  return nullptr;
}

} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
