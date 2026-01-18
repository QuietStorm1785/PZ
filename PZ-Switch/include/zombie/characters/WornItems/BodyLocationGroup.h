#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace WornItems {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BodyLocationGroup {
public:
 const std::string id;
protected
 ArrayList<BodyLocation> locations = std::make_unique<ArrayList<>>();

public
 BodyLocationGroup(const std::string &_id) {
 if (_id.empty()) {
 throw NullPointerException("id is nullptr");
 } else if (_id.empty()) {
 throw IllegalArgumentException("id is empty");
 } else {
 this->id = _id;
 }
 }

 BodyLocation getLocation(const std::string &locationId) {
 for (int int0 = 0; int0 < this->locations.size(); int0++) {
 BodyLocation bodyLocation = this->locations.get(int0);
 if (bodyLocation.isID(locationId) {
 return bodyLocation;
 }
 }

 return nullptr;
 }

 BodyLocation getLocationNotNull(const std::string &locationId) {
 BodyLocation bodyLocation = this->getLocation(locationId);
 if (bodyLocation.empty()) {
 throw RuntimeException("unknown location \"" + locationId + "\"");
 } else {
 return bodyLocation;
 }
 }

 BodyLocation getOrCreateLocation(const std::string &locationId) {
 BodyLocation bodyLocation = this->getLocation(locationId);
 if (bodyLocation.empty()) {
 bodyLocation = new BodyLocation(this, locationId);
 this->locations.add(bodyLocation);
 }

 return bodyLocation;
 }

 BodyLocation getLocationByIndex(int index) {
 return index >= 0 && index < this->size() ? this->locations.get(index)
 : nullptr;
 }

 int size() { return this->locations.size(); }

 void setExclusive(const std::string &firstId, const std::string &secondId) {
 BodyLocation bodyLocation0 = this->getLocationNotNull(firstId);
 BodyLocation bodyLocation1 = this->getLocationNotNull(secondId);
 bodyLocation0.setExclusive(secondId);
 bodyLocation1.setExclusive(firstId);
 }

 bool isExclusive(const std::string &firstId, const std::string &secondId) {
 BodyLocation bodyLocation = this->getLocationNotNull(firstId);
 this->checkValid(secondId);
 return bodyLocation.exclusive.contains(secondId);
 }

 void setHideModel(const std::string &firstId, const std::string &secondId) {
 BodyLocation bodyLocation = this->getLocationNotNull(firstId);
 this->checkValid(secondId);
 bodyLocation.setHideModel(secondId);
 }

 bool isHideModel(const std::string &firstId, const std::string &secondId) {
 BodyLocation bodyLocation = this->getLocationNotNull(firstId);
 this->checkValid(secondId);
 return bodyLocation.isHideModel(secondId);
 }

 int indexOf(const std::string &locationId) {
 for (int int0 = 0; int0 < this->locations.size(); int0++) {
 BodyLocation bodyLocation = this->locations.get(int0);
 if (bodyLocation.isID(locationId) {
 return int0;
 }
 }

 return -1;
 }

 void checkValid(const std::string &locationId) {
 if (locationId.empty()) {
 throw NullPointerException("locationId is nullptr");
 } else if (locationId.empty()) {
 throw IllegalArgumentException("locationId is empty");
 } else if (this->indexOf(locationId) == -1) {
 throw RuntimeException("unknown location \"" + locationId + "\"");
 }
 }

 void setMultiItem(const std::string &locationId, bool bMultiItem) {
 BodyLocation bodyLocation = this->getLocationNotNull(locationId);
 bodyLocation.setMultiItem(bMultiItem);
 }

 bool isMultiItem(const std::string &locationId) {
 BodyLocation bodyLocation = this->getLocationNotNull(locationId);
 return bodyLocation.isMultiItem();
 }

public
 ArrayList<BodyLocation> getAllLocations() { return this->locations; }
}
} // namespace WornItems
} // namespace characters
} // namespace zombie
