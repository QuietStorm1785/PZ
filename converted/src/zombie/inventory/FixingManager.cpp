#include "zombie/inventory/FixingManager.h"

namespace zombie {
namespace inventory {

InventoryItem FixingManager::fixItem(InventoryItem brokenItem,
                                     IsoGameCharacter chr, Fixing fixing,
                                     Fixing.Fixer fixer) {
  // TODO: Implement fixItem
  return nullptr;
}

void FixingManager::addXp(IsoGameCharacter character, Fixing.Fixer fixer) {
  // TODO: Implement addXp
}

void FixingManager::useFixer(IsoGameCharacter chr, Fixing.Fixer fixer,
                             InventoryItem brokenItem) {
  // TODO: Implement useFixer
}

double FixingManager::getChanceOfFail(InventoryItem brokenItem,
                                      IsoGameCharacter chr, Fixing fixing,
                                      Fixing.Fixer fixer) {
  // TODO: Implement getChanceOfFail
  return 0;
}

double FixingManager::getCondRepaired(InventoryItem brokenItem,
                                      IsoGameCharacter chr, Fixing fixing,
                                      Fixing.Fixer fixer) {
  // TODO: Implement getCondRepaired
  return 0;
}

} // namespace inventory
} // namespace zombie
