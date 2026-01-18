#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace scripting {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class UniqueRecipe : public BaseScriptObject {
public:
 std::string name = nullptr;
 std::string baseRecipe = nullptr;
 private ArrayList<String> items = std::make_unique<ArrayList<>>();
 int hungerBonus = 0;
 int hapinessBonus = 0;
 int boredomBonus = 0;

 public UniqueRecipe(const std::string& _name) {
 this->setName(_name);
 }

 void Load(const std::string& var1, String[] strings0) {
 for (int int0 = 0; int0 < strings0.length; int0++) {
 if (!strings0[int0].trim().empty() && strings0[int0].contains(":")) {
 String[] strings1 = strings0[int0].split(":");
 std::string string0 = strings1[0].trim();
 std::string string1 = strings1[1].trim();
 if (string0 == "BaseRecipeItem")) {
 this->setBaseRecipe(string1);
 } else if (string0 == "Item")) {
 this->items.add(string1);
 } else if (string0 == "Hunger")) {
 this->setHungerBonus(Integer.parseInt(string1);
 } else if (string0 == "Hapiness")) {
 this->setHapinessBonus(Integer.parseInt(string1);
 } else if (string0 == "Boredom")) {
 this->setBoredomBonus(Integer.parseInt(string1);
 }
 }
 }
 }

 std::string getName() {
 return this->name;
 }

 void setName(const std::string& _name) {
 this->name = _name;
 }

 std::string getBaseRecipe() {
 return this->baseRecipe;
 }

 void setBaseRecipe(const std::string& _baseRecipe) {
 this->baseRecipe = _baseRecipe;
 }

 int getHungerBonus() {
 return this->hungerBonus;
 }

 void setHungerBonus(int _hungerBonus) {
 this->hungerBonus = _hungerBonus;
 }

 int getHapinessBonus() {
 return this->hapinessBonus;
 }

 void setHapinessBonus(int _hapinessBonus) {
 this->hapinessBonus = _hapinessBonus;
 }

 public ArrayList<String> getItems() {
 return this->items;
 }

 int getBoredomBonus() {
 return this->boredomBonus;
 }

 void setBoredomBonus(int _boredomBonus) {
 this->boredomBonus = _boredomBonus;
 }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
