#include "zombie/characters/WornItems/BodyLocationGroup.h"

namespace zombie {
namespace characters {
namespace WornItems {

public
BodyLocationGroup::BodyLocationGroup(const std::string &_id) {
  // TODO: Implement BodyLocationGroup
  return nullptr;
}

BodyLocation BodyLocationGroup::getLocation(const std::string &locationId) {
  // TODO: Implement getLocation
  return nullptr;
}

BodyLocation
BodyLocationGroup::getLocationNotNull(const std::string &locationId) {
  // TODO: Implement getLocationNotNull
  return nullptr;
}

BodyLocation
BodyLocationGroup::getOrCreateLocation(const std::string &locationId) {
  // TODO: Implement getOrCreateLocation
  return nullptr;
}

BodyLocation BodyLocationGroup::getLocationByIndex(int index) {
  // TODO: Implement getLocationByIndex
  return nullptr;
}

int BodyLocationGroup::size() {
  // TODO: Implement size
  return 0;
}

void BodyLocationGroup::setExclusive(const std::string &firstId,
                                     const std::string &secondId) {
  // TODO: Implement setExclusive
}

bool BodyLocationGroup::isExclusive(const std::string &firstId,
                                    const std::string &secondId) {
  // TODO: Implement isExclusive
  return false;
}

void BodyLocationGroup::setHideModel(const std::string &firstId,
                                     const std::string &secondId) {
  // TODO: Implement setHideModel
}

bool BodyLocationGroup::isHideModel(const std::string &firstId,
                                    const std::string &secondId) {
  // TODO: Implement isHideModel
  return false;
}

int BodyLocationGroup::indexOf(const std::string &locationId) {
  // TODO: Implement indexOf
  return 0;
}

void BodyLocationGroup::checkValid(const std::string &locationId) {
  // TODO: Implement checkValid
}

void BodyLocationGroup::setMultiItem(const std::string &locationId,
                                     bool bMultiItem) {
  // TODO: Implement setMultiItem
}

bool BodyLocationGroup::isMultiItem(const std::string &locationId) {
  // TODO: Implement isMultiItem
  return false;
}

} // namespace WornItems
} // namespace characters
} // namespace zombie
