#pragma once
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/interfaces/IListBoxItem.h"
#include <algorithm>
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

class TraitFactory {
public:
public
 static LinkedHashMap<String, TraitFactory.Trait> TraitMap =
 std::make_unique<LinkedHashMap<>>();

 static void init() {}

 static void setMutualExclusive(std::string_view a, std::string_view b) {
 TraitMap.get(a).MutuallyExclusive.add(b);
 TraitMap.get(b).MutuallyExclusive.add(a);
 }

 static void sortList() {
 LinkedList linkedList = new LinkedList<>(TraitMap.entrySet());
 Collections.sort(linkedList, new Comparator<Entry<String, TraitFactory.Trait>>() {
 int compare(TraitFactory.Trait> entry1, TraitFactory.Trait> entry0) {
 return ((TraitFactory.Trait)entry1.getValue()).name.compareTo(((TraitFactory.Trait)entry0.getValue()).name);
 }
 });
 LinkedHashMap linkedHashMap = new LinkedHashMap();

 for (auto &entry : linkedList)
 linkedHashMap.put((String)entry.getKey(),
 (TraitFactory.Trait)entry.getValue());
 }

 TraitMap = linkedHashMap;
 }

 public
 static TraitFactory.Trait addTrait(String type, String name, int cost,
 String desc, boolean profession) {
 TraitFactory.Trait trait =
 new TraitFactory.Trait(type, name, cost, desc, profession, false);
 TraitMap.put(type, trait);
 return trait;
 }

 public
 static TraitFactory.Trait addTrait(String type, String name, int cost,
 String desc, boolean profession,
 boolean removeInMP) {
 TraitFactory.Trait trait = new TraitFactory.Trait(
 type, name, cost, desc, profession, removeInMP);
 TraitMap.put(type, trait);
 return trait;
 }

 public
 static ArrayList<TraitFactory.Trait> getTraits() {
 std::vector arrayList = new ArrayList();

 for (TraitFactory.Trait trait : TraitMap.values()) {
 arrayList.add(trait);
 }

 return arrayList;
 }

 public
 static TraitFactory.Trait getTrait(String name) {
 return TraitMap.containsKey(name) ? TraitMap.get(name) : nullptr;
 }

 static void Reset() { TraitMap.clear(); }

 public
 static class Trait implements IListBoxItem {
 std::string traitID;
 std::string name;
 int cost;
 std::string description;
 bool prof;
 Texture texture = nullptr;
 bool removeInMP = false;
 private
 List<String> freeRecipes = std::make_unique<ArrayList<>>();
 public
 ArrayList<String> MutuallyExclusive = new ArrayList<>(0);
 public
 HashMap<PerkFactory.Perk, Integer> XPBoostMap =
 std::make_unique<HashMap<>>();

 void addXPBoost(PerkFactory.Perk perk, int level) {
 if (perk != nullptr && perk != PerkFactory.Perks.None &&
 perk != PerkFactory.Perks.MAX) {
 this->XPBoostMap.put(perk, level);
 } else {
 DebugLog.General.warn(
 "invalid perk passed to Trait.addXPBoost trait=%s perk=%s",
 this->name, perk);
 }
 }

 public
 List<String> getFreeRecipes() { return this->freeRecipes; }

 void setFreeRecipes(List<String> _freeRecipes) {
 this->freeRecipes = _freeRecipes;
 }

 public
 Trait(std::string_view tr, std::string_view _name, int _cost,
 std::string_view desc, bool _prof, bool _removeInMP) {
 this->traitID = tr;
 this->name = _name;
 this->cost = _cost;
 this->description = desc;
 this->prof = _prof;
 this->texture = Texture.getSharedTexture(
 "media/ui/Traits/trait_" +
 this->traitID.toLowerCase(Locale.ENGLISH) + ".png");
 if (this->texture.empty()) {
 this->texture =
 Texture.getSharedTexture("media/ui/Traits/trait_generic.png");
 }

 this->removeInMP = _removeInMP;
 }

 std::string getType() { return this->traitID; }

 Texture getTexture() { return this->texture; }

 std::string getLabel() { return this->name; }

 std::string getLeftLabel() { return this->name; }

 std::string getRightLabel() {
 int int0 = this->cost;
 if (int0 == 0) {
 return "";
 } else {
 std::string string = "+";
 if (int0 > 0) {
 string = "-";
 } else if (int0 == 0) {
 string = "";
 }

 if (int0 < 0) {
 int0 = -int0;
 }

 return string + new Integer(int0).toString();
 }
 }

 int getCost() { return this->cost; }

 bool isFree() { return this->prof; }

 std::string getDescription() { return this->description; }

 void setDescription(std::string_view desc) {
 this->description = desc;
 }

 public
 ArrayList<String> getMutuallyExclusiveTraits() {
 return this->MutuallyExclusive;
 }

 public
 HashMap<PerkFactory.Perk, Integer> getXPBoostMap() {
 return this->XPBoostMap;
 }

 bool isRemoveInMP() { return this->removeInMP; }

 void setRemoveInMP(bool _removeInMP) {
 this->removeInMP = _removeInMP;
 }
 }
 }
 } // namespace traits
 } // namespace characters
 } // namespace zombie
