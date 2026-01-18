#pragma once
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/interfaces/IListBoxItem.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace professions {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ProfessionFactory {
public:
public
 static LinkedHashMap<String, ProfessionFactory.Profession> ProfessionMap =
 std::make_unique<LinkedHashMap<>>();

 static void init() {}

public
 static ProfessionFactory.Profession
 addProfession(String type, String name, String IconPath, int points) {
 ProfessionFactory.Profession profession =
 new ProfessionFactory.Profession(type, name, IconPath, points, "");
 ProfessionMap.put(type, profession);
 return profession;
 }

public
 static ProfessionFactory.Profession getProfession(String type) {
 for (ProfessionFactory.Profession profession : ProfessionMap.values()) {
 if (profession.type == type) {
 return profession;
 }
 }

 return nullptr;
 }

public
 static ArrayList<ProfessionFactory.Profession> getProfessions() {
 std::vector arrayList = new ArrayList();

 for (ProfessionFactory.Profession profession : ProfessionMap.values()) {
 arrayList.add(profession);
 }

 return arrayList;
 }

 static void Reset() { ProfessionMap.clear(); }

public
 static class Profession implements IListBoxItem {
 std::string type;
 std::string name;
 int cost;
 std::string description;
 std::string IconPath;
 Texture texture = nullptr;
 public
 Stack<String> FreeTraitStack = std::make_unique<Stack<>>();
 private
 List<String> freeRecipes = std::make_unique<ArrayList<>>();
 public
 HashMap<PerkFactory.Perk, Integer> XPBoostMap =
 std::make_unique<HashMap<>>();

 public
 Profession(const std::string &_type, const std::string &_name,
 const std::string &IconPathname, int _cost,
 const std::string &desc) {
 this->type = _type;
 this->name = _name;
 this->IconPath = IconPathname;
 if (!IconPathname == "")) {
 this->texture = Texture.trygetTexture(IconPathname);
 }

 this->cost = _cost;
 this->description = desc;
 }

 Texture getTexture() { return this->texture; }

 void addFreeTrait(const std::string &trait) {
 this->FreeTraitStack.add(trait);
 }

 public
 ArrayList<String> getFreeTraits() {
 std::vector arrayList = new ArrayList();
 arrayList.addAll(this->FreeTraitStack);
 return arrayList;
 }

 std::string getLabel() { return this->getName(); }

 std::string getIconPath() { return this->IconPath; }

 std::string getLeftLabel() { return this->getName(); }

 std::string getRightLabel() {
 int int0 = this->getCost();
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

 return string + int0;
 }
 }

 /**
 * @return the type
 */
 std::string getType() { return this->type; }

 /**
 *
 * @param _type the type to set
 */
 void setType(const std::string &_type) { this->type = _type; }

 /**
 * @return the name
 */
 std::string getName() { return this->name; }

 /**
 *
 * @param _name the name to set
 */
 void setName(const std::string &_name) { this->name = _name; }

 /**
 * @return the cost
 */
 int getCost() { return this->cost; }

 /**
 *
 * @param _cost the cost to set
 */
 void setCost(int _cost) { this->cost = _cost; }

 /**
 * @return the description
 */
 std::string getDescription() { return this->description; }

 /**
 *
 * @param _description the description to set
 */
 void setDescription(const std::string &_description) {
 this->description = _description;
 }

 /**
 *
 * @param _IconPath the IconPath to set
 */
 void setIconPath(const std::string &_IconPath) {
 this->IconPath = _IconPath;
 }

 /**
 * @return the FreeTraitStack
 */
 public
 Stack<String> getFreeTraitStack() { return this->FreeTraitStack; }

 void addXPBoost(PerkFactory.Perk perk, int level) {
 if (perk != nullptr && perk != PerkFactory.Perks.None &&
 perk != PerkFactory.Perks.MAX) {
 this->XPBoostMap.put(perk, level);
 } else {
 DebugLog.General.warn("invalid perk passed to Profession.addXPBoost "
 "profession=%s perk=%s",
 this->name, perk);
 }
 }

 public
 HashMap<PerkFactory.Perk, Integer> getXPBoostMap() {
 return this->XPBoostMap;
 }

 /**
 *
 * @param _FreeTraitStack the FreeTraitStack to set
 */
 void setFreeTraitStack(Stack<String> _FreeTraitStack) {
 this->FreeTraitStack = _FreeTraitStack;
 }

 public
 List<String> getFreeRecipes() { return this->freeRecipes; }

 void setFreeRecipes(List<String> _freeRecipes) {
 this->freeRecipes = _freeRecipes;
 }
 }
}
} // namespace professions
} // namespace characters
} // namespace zombie
