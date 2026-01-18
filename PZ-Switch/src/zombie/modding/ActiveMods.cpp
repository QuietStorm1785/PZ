#include "zombie/modding/ActiveMods.h"

namespace zombie {
namespace modding {

int ActiveMods::count() {
 // TODO: Implement count
 return 0;
}

ActiveMods ActiveMods::getByIndex(int index) {
 // TODO: Implement getByIndex
 return nullptr;
}

ActiveMods ActiveMods::getById(const std::string &_id) {
 // TODO: Implement getById
 return nullptr;
}

int ActiveMods::indexOf(const std::string &_id) {
 // TODO: Implement indexOf
 return 0;
}

ActiveMods ActiveMods::create(const std::string &string) {
 // TODO: Implement create
 return nullptr;
}

void ActiveMods::requireValidId(const std::string &string) {
 // TODO: Implement requireValidId
}

void ActiveMods::setLoadedMods(ActiveMods activeMods) {
 // TODO: Implement setLoadedMods
}

bool ActiveMods::requiresResetLua(ActiveMods activeMods) {
 // TODO: Implement requiresResetLua
 return false;
}

void ActiveMods::renderUI() {
 // TODO: Implement renderUI
}

void ActiveMods::Reset() {
 // TODO: Implement Reset
}

public
ActiveMods::ActiveMods(const std::string &_id) {
 // TODO: Implement ActiveMods
 return nullptr;
}

void ActiveMods::clear() {
 // TODO: Implement clear
}

void ActiveMods::copyFrom(ActiveMods other) {
 // TODO: Implement copyFrom
}

void ActiveMods::setModActive(const std::string &modID, bool active) {
 // TODO: Implement setModActive
}

bool ActiveMods::isModActive(const std::string &modID) {
 // TODO: Implement isModActive
 return false;
}

void ActiveMods::removeMod(const std::string &modID) {
 // TODO: Implement removeMod
}

void ActiveMods::removeMapOrder(const std::string &folder) {
 // TODO: Implement removeMapOrder
}

void ActiveMods::checkMissingMods() {
 // TODO: Implement checkMissingMods
}

void ActiveMods::checkMissingMaps() {
 // TODO: Implement checkMissingMaps
}

} // namespace modding
} // namespace zombie
