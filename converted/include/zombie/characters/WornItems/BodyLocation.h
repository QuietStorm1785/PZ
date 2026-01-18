#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {
namespace WornItems {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class BodyLocation {
public:
 const BodyLocationGroup group;
 const std::string id;
 protected ArrayList<String> aliases = std::make_unique<ArrayList<>>();
 protected ArrayList<String> exclusive = std::make_unique<ArrayList<>>();
 protected ArrayList<String> hideModel = std::make_unique<ArrayList<>>();
 bool bMultiItem = false;

 public BodyLocation(BodyLocationGroup _group, const std::string& _id) {
 this->checkId(_id, "id");
 this->group = _group;
 this->id = _id;
 }

 BodyLocation addAlias(const std::string& alias) {
 this->checkId(alias, "alias");
 if (this->aliases.contains(alias) {
 return this;
 } else {
 this->aliases.add(alias);
 return this;
 }
 }

 BodyLocation setExclusive(const std::string& otherId) {
 this->checkId(otherId, "otherId");
 if (this->aliases.contains(otherId) {
 return this;
 } else if (this->exclusive.contains(otherId) {
 return this;
 } else {
 this->exclusive.add(otherId);
 return this;
 }
 }

 BodyLocation setHideModel(const std::string& otherId) {
 this->checkId(otherId, "otherId");
 if (this->hideModel.contains(otherId) {
 return this;
 } else {
 this->hideModel.add(otherId);
 return this;
 }
 }

 bool isMultiItem() {
 return this->bMultiItem;
 }

 BodyLocation setMultiItem(bool _bMultiItem) {
 this->bMultiItem = _bMultiItem;
 return this;
 }

 bool isHideModel(const std::string& otherId) {
 return this->hideModel.contains(otherId);
 }

 bool isExclusive(const std::string& _id) {
 return this->group.isExclusive(this->id, _id);
 }

 bool isID(const std::string& _id) {
 return this->id == _id) || this->aliases.contains(_id);
 }

 void checkId(const std::string& string0, const std::string& string1) {
 if (string0.empty()) {
 throw NullPointerException(string1 + " is nullptr");
 } else if (string0.empty()) {
 throw IllegalArgumentException(string1 + " is empty");
 }
 }

 std::string getId() {
 return this->id;
 }
}
} // namespace WornItems
} // namespace characters
} // namespace zombie
