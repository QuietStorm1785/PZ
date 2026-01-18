#include "zombie/inventory/types/Literature.h"

namespace zombie {
namespace inventory {
namespace types {

public
Literature::Literature(const std::string &module, const std::string &name,
                       const std::string &itemType,
                       const std::string &texName) {
  // TODO: Implement Literature
  return nullptr;
}

public
Literature::Literature(const std::string &module, const std::string &name,
                       const std::string &itemType, Item item) {
  // TODO: Implement Literature
  return nullptr;
}

bool Literature::IsLiterature() {
  // TODO: Implement IsLiterature
  return false;
}

int Literature::getSaveType() {
  // TODO: Implement getSaveType
  return 0;
}

std::string Literature::getCategory() {
  // TODO: Implement getCategory
  return "";
}

void Literature::update() {
  // TODO: Implement update
}

bool Literature::finishupdate() {
  // TODO: Implement finishupdate
  return false;
}

void Literature::DoTooltip(ObjectTooltip tooltipUI,
                           ObjectTooltip.Layout layout) {
  // TODO: Implement DoTooltip
}

void Literature::save(ByteBuffer output, bool net) {
  // TODO: Implement save
}

void Literature::load(ByteBuffer input, int WorldVersion) {
  // TODO: Implement load
}

float Literature::getBoredomChange() {
  // TODO: Implement getBoredomChange
  return 0;
}

float Literature::getUnhappyChange() {
  // TODO: Implement getUnhappyChange
  return 0;
}

float Literature::getStressChange() {
  // TODO: Implement getStressChange
  return 0;
}

int Literature::getNumberOfPages() {
  // TODO: Implement getNumberOfPages
  return 0;
}

void Literature::setNumberOfPages(int _numberOfPages) {
  // TODO: Implement setNumberOfPages
}

std::string Literature::getBookName() {
  // TODO: Implement getBookName
  return "";
}

void Literature::setBookName(const std::string &_bookName) {
  // TODO: Implement setBookName
}

int Literature::getLvlSkillTrained() {
  // TODO: Implement getLvlSkillTrained
  return 0;
}

void Literature::setLvlSkillTrained(int lvlSkillTrained) {
  // TODO: Implement setLvlSkillTrained
}

int Literature::getNumLevelsTrained() {
  // TODO: Implement getNumLevelsTrained
  return 0;
}

void Literature::setNumLevelsTrained(int numLevelsTrained) {
  // TODO: Implement setNumLevelsTrained
}

int Literature::getMaxLevelTrained() {
  // TODO: Implement getMaxLevelTrained
  return 0;
}

std::string Literature::getSkillTrained() {
  // TODO: Implement getSkillTrained
  return "";
}

void Literature::setSkillTrained(const std::string &skillTrained) {
  // TODO: Implement setSkillTrained
}

int Literature::getAlreadyReadPages() {
  // TODO: Implement getAlreadyReadPages
  return 0;
}

void Literature::setAlreadyReadPages(int _alreadyReadPages) {
  // TODO: Implement setAlreadyReadPages
}

bool Literature::canBeWrite() {
  // TODO: Implement canBeWrite
  return false;
}

void Literature::setCanBeWrite(bool _canBeWrite) {
  // TODO: Implement setCanBeWrite
}

void Literature::setCustomPages(String > _customPages) {
  // TODO: Implement setCustomPages
}

void Literature::addPage(int index, const std::string &text) {
  // TODO: Implement addPage
}

std::string Literature::seePage(int index) {
  // TODO: Implement seePage
  return "";
}

std::string Literature::getLockedBy() {
  // TODO: Implement getLockedBy
  return "";
}

void Literature::setLockedBy(const std::string &_lockedBy) {
  // TODO: Implement setLockedBy
}

int Literature::getPageToWrite() {
  // TODO: Implement getPageToWrite
  return 0;
}

void Literature::setPageToWrite(int _pageToWrite) {
  // TODO: Implement setPageToWrite
}

void Literature::setTeachedRecipes(List<String> _teachedRecipes) {
  // TODO: Implement setTeachedRecipes
}

} // namespace types
} // namespace inventory
} // namespace zombie
