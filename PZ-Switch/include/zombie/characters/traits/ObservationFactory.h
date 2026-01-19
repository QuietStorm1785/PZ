#pragma once
#include "zombie/interfaces/IListBoxItem.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace traits {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ObservationFactory {
public:
public
 static HashMap<String, ObservationFactory.Observation> ObservationMap =
 std::make_unique<HashMap<>>();

 static void init() {}

 static void setMutualExclusive(std::string_view a, std::string_view b) {
 ObservationMap.get(a).MutuallyExclusive.add(b);
 ObservationMap.get(b).MutuallyExclusive.add(a);
 }

 static void addObservation(std::string_view type, std::string_view name,
 std::string_view desc) {
 ObservationMap.put(type,
 new ObservationFactory.Observation(type, name, desc);
 }

public
 static ObservationFactory.Observation getObservation(String name) {
 return ObservationMap.containsKey(name) ? ObservationMap.get(name)
 : nullptr;
 }

public
 static class Observation implements IListBoxItem {
 std::string traitID;
 std::string name;
 std::string description;
 public
 ArrayList<String> MutuallyExclusive = new ArrayList<>(0);

 public
 Observation(std::string_view tr, std::string_view _name,
 std::string_view desc) {
 this->setTraitID(tr);
 this->setName(_name);
 this->setDescription(desc);
 }

 std::string getLabel() { return this->getName(); }

 std::string getLeftLabel() { return this->getName(); }

 std::string getRightLabel() { return nullptr; }

 std::string getDescription() { return this->description; }

 void setDescription(std::string_view _description) {
 this->description = _description;
 }

 std::string getTraitID() { return this->traitID; }

 void setTraitID(std::string_view _traitID) { this->traitID = _traitID; }

 std::string getName() { return this->name; }

 void setName(std::string_view _name) { this->name = _name; }
 }
}
} // namespace traits
} // namespace characters
} // namespace zombie
