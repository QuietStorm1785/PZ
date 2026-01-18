#include "zombie/characters/AttachedItems/AttachedLocationGroup.h"
#include "zombie/characters/AttachedItems/AttachedLocation.h"
#include "java/lang/exceptions.h"

namespace zombie {
namespace characters {
namespace AttachedItems {

AttachedLocationGroup::AttachedLocationGroup(const std::string &_id) : id(_id) {
 if (_id.empty()) {
 throw IllegalArgumentException("id is empty");
 }
}

std::shared_ptr<AttachedLocation> AttachedLocationGroup::getLocation(const std::string &locationId) {
 for (int i = 0; i < (int)this->locations.size(); i++) {
 auto attachedLocation = this->locations[i];
 if (attachedLocation && attachedLocation->getId() == locationId) {
 return attachedLocation;
 }
 }
 return nullptr;
}

std::shared_ptr<AttachedLocation> AttachedLocationGroup::getOrCreateLocation(const std::string &locationId) {
 auto attachedLocation = this->getLocation(locationId);
 if (!attachedLocation) {
 attachedLocation = std::make_shared<AttachedLocation>(this, locationId);
 this->locations.push_back(attachedLocation);
 }
 return attachedLocation;
}

std::shared_ptr<AttachedLocation> AttachedLocationGroup::getLocationByIndex(int index) {
 if (index >= 0 && index < (int)this->size()) {
 return this->locations[index];
 }
 return nullptr;
}

int AttachedLocationGroup::size() const {
 return this->locations.size();
}

int AttachedLocationGroup::indexOf(const std::string &locationId) {
 for (int i = 0; i < (int)this->locations.size(); i++) {
 auto attachedLocation = this->locations[i];
 if (attachedLocation && attachedLocation->getId() == locationId) {
 return i;
 }
 }
 return -1;
}

void AttachedLocationGroup::checkValid(const std::string &locationId) {
 if (locationId.empty()) {
 throw IllegalArgumentException("locationId is empty");
 }
 if (this->indexOf(locationId) == -1) {
 throw RuntimeException("no such location \"" + locationId + "\"");
 }
}

} // namespace AttachedItems
} // namespace characters
} // namespace zombie
