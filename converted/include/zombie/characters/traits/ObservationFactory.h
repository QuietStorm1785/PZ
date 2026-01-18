#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/interfaces/IListBoxItem.h"

namespace zombie {
namespace characters {
namespace traits {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ObservationFactory {
public:
 public static HashMap<String, ObservationFactory.Observation> ObservationMap = std::make_unique<HashMap<>>();

 static void init() {
 }

 static void setMutualExclusive(const std::string& a, const std::string& b) {
 ObservationMap.get(a).MutuallyExclusive.add(b);
 ObservationMap.get(b).MutuallyExclusive.add(a);
 }

 static void addObservation(const std::string& type, const std::string& name, const std::string& desc) {
 ObservationMap.put(type, new ObservationFactory.Observation(type, name, desc);
 }

 public static ObservationFactory.Observation getObservation(String name) {
 return ObservationMap.containsKey(name) ? ObservationMap.get(name) : nullptr;
 }

 public static class Observation implements IListBoxItem {
 std::string traitID;
 std::string name;
 std::string description;
 public ArrayList<String> MutuallyExclusive = new ArrayList<>(0);

 public Observation(const std::string& tr, const std::string& _name, const std::string& desc) {
 this->setTraitID(tr);
 this->setName(_name);
 this->setDescription(desc);
 }

 std::string getLabel() {
 return this->getName();
 }

 std::string getLeftLabel() {
 return this->getName();
 }

 std::string getRightLabel() {
 return nullptr;
 }

 std::string getDescription() {
 return this->description;
 }

 void setDescription(const std::string& _description) {
 this->description = _description;
 }

 std::string getTraitID() {
 return this->traitID;
 }

 void setTraitID(const std::string& _traitID) {
 this->traitID = _traitID;
 }

 std::string getName() {
 return this->name;
 }

 void setName(const std::string& _name) {
 this->name = _name;
 }
 }
}
} // namespace traits
} // namespace characters
} // namespace zombie
