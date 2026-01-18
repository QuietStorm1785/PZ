#pragma once
#include "zombie/util/Lambda.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace traits {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TraitCollection {
public:
private
 List<String> m_activeTraitNames = std::make_unique<ArrayList<>>();
private
 List<TraitCollection.TraitSlot> m_traits =
 std::make_unique<ArrayList<>>();

 bool remove(void *o) { return this->remove(String.valueOf(o); }

 bool remove(const std::string &name) {
 int int0 = this->indexOfTrait(name);
 if (int0 > -1) {
 this->deactivateTraitSlot(int0);
 }

 return int0 > -1;
 }

 void addAll(Collection<? extends) {
 PZArrayUtil.forEach(c, this::add);
 }

 void removeAll(Collection<?> c) {
 PZArrayUtil.forEach(c, this ::remove);
 }

 void clear() {
 PZArrayUtil.forEach(this->m_traits, traitSlot->traitSlot.m_isSet = false);
 this->m_activeTraitNames.clear();
 }

 int size() { return this->m_activeTraitNames.size(); }

 bool isEmpty() { return this->m_activeTraitNames.empty(); }

 bool contains(void *o) { return this->contains(String.valueOf(o); }

 bool contains(const std::string &trait) {
 int int0 = this->indexOfTrait(trait);
 return int0 > -1 && this->getSlotInternal(int0).m_isSet;
 }

 void add(const std::string &trait) {
 if (trait != nullptr) {
 this->getOrCreateSlotInternal(trait).m_isSet = true;
 this->m_activeTraitNames.add(trait);
 }
 }

 std::string get(int n) { return this->m_activeTraitNames.get(n); }

 void set(const std::string &name, bool val) {
 if (val) {
 this->add(name);
 } else {
 this->remove(name);
 }
 }

 public
 TraitCollection.TraitSlot getTraitSlot(String name) {
 return StringUtils.isNullOrWhitespace(name)
 ? nullptr
 : this->getOrCreateSlotInternal(name);
 }

 int indexOfTrait(const std::string &string) {
 return PZArrayUtil.indexOf(
 this->m_traits,
 Lambda.predicate(string, TraitCollection.TraitSlot::isName);
 }

 private
 TraitCollection.TraitSlot getSlotInternal(int int0) {
 return this->m_traits.get(int0);
 }

 private
 TraitCollection.TraitSlot getOrCreateSlotInternal(String string) {
 int int0 = this->indexOfTrait(string);
 if (int0 == -1) {
 int0 = this->m_traits.size();
 this->m_traits.add(new TraitCollection.TraitSlot(string);
 }

 return this->getSlotInternal(int0);
 }

 void deactivateTraitSlot(int int0) {
 TraitCollection.TraitSlot traitSlot = this->getSlotInternal(int0);
 traitSlot.m_isSet = false;
 int int1 = PZArrayUtil.indexOf(
 this->m_activeTraitNames,
 Lambda.predicate(traitSlot.Name, String::equalsIgnoreCase);
 if (int1 != -1) {
 this->m_activeTraitNames.remove(int1);
 }
 }

 std::string toString() {
 return "TraitCollection(" +
 PZArrayUtil.arrayToString(this->m_activeTraitNames, "", "", ", ") +
 ")";
 }

 class TraitSlot {
 const std::string Name;
 bool m_isSet;

 private
 TraitSlot(const std::string &string) {
 this->Name = string;
 this->m_isSet = false;
 }

 bool isName(const std::string &name) {
 return StringUtils.equalsIgnoreCase(this->Name, name);
 }

 bool isSet() { return this->m_isSet; }

 void set(bool val) {
 if (this->m_isSet != val) {
 TraitCollection.this->set(this->Name, val);
 }
 }

 std::string toString() {
 return "TraitSlot(" + this->Name + ":" + this->m_isSet + ")";
 }
 }
}
} // namespace traits
} // namespace characters
} // namespace zombie
