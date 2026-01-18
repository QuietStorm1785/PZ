#include "zombie/characters/AttachedItems/AttachedWeaponDefinitions.h"

namespace zombie {
namespace characters {
namespace AttachedItems {

void AttachedWeaponDefinitions::checkDirty() {
  // TODO: Implement checkDirty
}

void AttachedWeaponDefinitions::addRandomAttachedWeapon(IsoZombie zombie0) {
  // TODO: Implement addRandomAttachedWeapon
}

void AttachedWeaponDefinitions::addAttachedWeapon(
    AttachedWeaponDefinition attachedWeaponDefinition, IsoZombie zombie0) {
  // TODO: Implement addAttachedWeapon
}

AttachedWeaponDefinition AttachedWeaponDefinitions::pickRandomInList(
    ArrayList<AttachedWeaponDefinition> arrayList1, IsoZombie zombie0) {
  // TODO: Implement pickRandomInList
  return nullptr;
}

bool AttachedWeaponDefinitions::outfitHasItem(IsoZombie zombie0,
                                              const std::string &string) {
  // TODO: Implement outfitHasItem
  return false;
}

void AttachedWeaponDefinitions::init() {
  // TODO: Implement init
}

AttachedWeaponCustomOutfit
AttachedWeaponDefinitions::initOutfit(const std::string &string,
                                      KahluaTableImpl kahluaTableImpl0) {
  // TODO: Implement initOutfit
  return nullptr;
}

AttachedWeaponDefinition
AttachedWeaponDefinitions::init(const std::string &string,
                                KahluaTableImpl kahluaTableImpl0) {
  // TODO: Implement init
  return nullptr;
}

void AttachedWeaponDefinitions::tableToArrayList(KahluaTable table,
                                                 const std::string &string,
                                                 ArrayList<String> arrayList) {
  // TODO: Implement tableToArrayList
}

} // namespace AttachedItems
} // namespace characters
} // namespace zombie
