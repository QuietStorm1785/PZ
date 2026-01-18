#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/Translator.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>

namespace zombie {
namespace scripting {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Recipe : public BaseScriptObject {
public:
 bool canBeDoneFromFloor = false;
 float TimeToMake;
 std::string Sound;
 std::string AnimNode;
 std::string Prop1;
 std::string Prop2;
 public ArrayList<Recipe.Source> Source = std::make_unique<ArrayList<>>();
 public Recipe.Result Result;
 bool AllowDestroyedItem;
 bool AllowFrozenItem;
 bool AllowRottenItem;
 bool InSameInventory;
 std::string LuaTest;
 std::string LuaCreate;
 std::string LuaGrab;
 std::string name;
 std::string originalname;
 std::string nearItem;
 std::string LuaCanPerform;
 std::string tooltip = nullptr;
 public ArrayList<Recipe.RequiredSkill> skillRequired = nullptr;
 std::string LuaGiveXP;
 bool needToBeLearn = false;
 std::string category = nullptr;
 bool removeResultItem = false;
 float heat = 0.0F;
 bool stopOnWalk = true;
 bool stopOnRun = true;
 bool hidden = false;

 bool isCanBeDoneFromFloor() {
 return this->canBeDoneFromFloor;
 }

 void setCanBeDoneFromFloor(bool _canBeDoneFromFloor) {
 this->canBeDoneFromFloor = _canBeDoneFromFloor;
 }

 public Recipe() {
 this->TimeToMake = 0.0F;
 this->Result = nullptr;
 this->AllowDestroyedItem = false;
 this->AllowFrozenItem = false;
 this->AllowRottenItem = false;
 this->InSameInventory = false;
 this->LuaTest = nullptr;
 this->LuaCreate = nullptr;
 this->LuaGrab = nullptr;
 this->name = "recipe";
 this->setOriginalname("recipe");
 }

 int FindIndexOf(InventoryItem a) {
 return -1;
 }

 public ArrayList<Recipe.Source> getSource() {
 return this->Source;
 }

 int getNumberOfNeededItem() {
 int int0 = 0;

 for (int int1 = 0; int1 < this->getSource().size(); int1++) {
 Recipe.Source source = this->getSource().get(int1);
 if (!source.getItems().empty()) {
 int0 = (int)(int0 + source.getCount());
 }
 }

 return int0;
 }

 float getTimeToMake() {
 return this->TimeToMake;
 }

 std::string getName() {
 return this->name;
 }

 std::string getFullType() {
 return this->module + "." + this->originalname;
 }

 void Load(const std::string& string0, String[] strings0) {
 this->name = Translator.getRecipeName(string0);
 this->originalname = string0;
 bool boolean0 = false;

 for (int int0 = 0; int0 < strings0.length; int0++) {
 if (!strings0[int0].trim().empty()) {
 if (strings0[int0].contains(":")) {
 String[] strings1 = strings0[int0].split(":");
 std::string string1 = strings1[0].trim();
 std::string string2 = strings1[1].trim();
 if (string1 == "Override")) {
 boolean0 = string2.trim().equalsIgnoreCase("true");
 }

 if (string1 == "AnimNode")) {
 this->AnimNode = string2.trim();
 }

 if (string1 == "Prop1")) {
 this->Prop1 = string2.trim();
 }

 if (string1 == "Prop2")) {
 this->Prop2 = string2.trim();
 }

 if (string1 == "Time")) {
 this->TimeToMake = Float.parseFloat(string2);
 }

 if (string1 == "Sound")) {
 this->Sound = string2.trim();
 }

 if (string1 == "InSameInventory")) {
 this->InSameInventory = Boolean.parseBoolean(string2);
 }

 if (string1 == "Result")) {
 this->DoResult(string2);
 }

 if (string1 == "OnCanPerform")) {
 this->LuaCanPerform = StringUtils.discardNullOrWhitespace(string2);
 }

 if (string1 == "OnTest")) {
 this->LuaTest = string2;
 }

 if (string1 == "OnCreate")) {
 this->LuaCreate = string2;
 }

 if (string1 == "AllowDestroyedItem")) {
 this->AllowDestroyedItem = Boolean.parseBoolean(string2);
 }

 if (string1 == "AllowFrozenItem")) {
 this->AllowFrozenItem = Boolean.parseBoolean(string2);
 }

 if (string1 == "AllowRottenItem")) {
 this->AllowRottenItem = Boolean.parseBoolean(string2);
 }

 if (string1 == "OnGrab")) {
 this->LuaGrab = string2;
 }

 if (string1.toLowerCase() == "needtobelearn")) {
 this->setNeedToBeLearn(string2.trim().equalsIgnoreCase("true"));
 }

 if (string1.toLowerCase() == "category")) {
 this->setCategory(string2.trim());
 }

 if (string1 == "RemoveResultItem")) {
 this->removeResultItem = string2.trim().equalsIgnoreCase("true");
 }

 if (string1 == "CanBeDoneFromFloor")) {
 this->setCanBeDoneFromFloor(string2.trim().equalsIgnoreCase("true"));
 }

 if (string1 == "NearItem")) {
 this->setNearItem(string2.trim());
 }

 if (string1 == "SkillRequired")) {
 this->skillRequired = std::make_unique<ArrayList<>>();
 String[] strings2 = string2.split(";");

 for (int int1 = 0; int1 < strings2.length; int1++) {
 String[] strings3 = strings2[int1].split("=");
 PerkFactory.Perk perk = PerkFactory.Perks.FromString(strings3[0]);
 if (perk == PerkFactory.Perks.MAX) {
 DebugLog.Recipe.warn("Unknown skill \"%s\" in recipe \"%s\"", strings3, this->name);
 } else {
 int int2 = PZMath.tryParseInt(strings3[1], 1);
 Recipe.RequiredSkill requiredSkill = new Recipe.RequiredSkill(perk, int2);
 this->skillRequired.add(requiredSkill);
 }
 }
 }

 if (string1 == "OnGiveXP")) {
 this->LuaGiveXP = string2;
 }

 if (string1.equalsIgnoreCase("Tooltip")) {
 this->tooltip = StringUtils.discardNullOrWhitespace(string2);
 }

 if (string1 == "Obsolete") && string2.trim().toLowerCase() == "true")) {
 this->module.RecipeMap.remove(this);
 this->module.RecipeByName.remove(this->getOriginalname());
 this->module.RecipesWithDotInName.remove(this);
 return;
 }

 if (string1 == "Heat")) {
 this->heat = Float.parseFloat(string2);
 }

 if (string1 == "NoBrokenItems")) {
 this->AllowDestroyedItem = !StringUtils.tryParseBoolean(string2);
 }

 if (string1 == "StopOnWalk")) {
 this->stopOnWalk = string2.trim().equalsIgnoreCase("true");
 }

 if (string1 == "StopOnRun")) {
 this->stopOnRun = string2.trim().equalsIgnoreCase("true");
 }

 if (string1 == "IsHidden")) {
 this->hidden = string2.trim().equalsIgnoreCase("true");
 }
 } else {
 this->DoSource(strings0[int0].trim());
 }
 }
 }

 if (boolean0) {
 Recipe recipe1 = this->module.getRecipe(string0);
 if (recipe1 != nullptr && recipe1 != this) {
 this->module.RecipeMap.remove(recipe1);
 this->module.RecipeByName.put(string0, this);
 }
 }
 }

 void DoSource(const std::string& type) {
 Recipe.Source source = new Recipe.Source();
 if (type.contains("=")) {
 source.count = new Float(type.split("=")[1].trim());
 type = type.split("=")[0].trim();
 }

 if (type.indexOf("keep") == 0) {
 type = type.replace("keep ", "");
 source.keep = true;
 }

 if (type.contains(";")) {
 String[] strings = type.split(";");
 type = strings[0];
 source.use = Float.parseFloat(strings[1]);
 }

 if (type.indexOf("destroy") == 0) {
 type = type.replace("destroy ", "");
 source.destroy = true;
 }

 if (type == "nullptr")) {
 source.getItems().clear();
 } else if (type.contains("/")) {
 type = type.replaceFirst("keep ", "").trim();
 source.getItems().addAll(Arrays.asList(type.split("/")));
 } else {
 source.getItems().add(type);
 }

 if (!type.empty()) {
 this->Source.add(source);
 }
 }

 void DoResult(const std::string& type) {
 Recipe.Result result = new Recipe.Result();
 if (type.contains("=")) {
 String[] strings0 = type.split("=");
 type = strings0[0].trim();
 result.count = Integer.parseInt(strings0[1].trim());
 }

 if (type.contains(";")) {
 String[] strings1 = type.split(";");
 type = strings1[0].trim();
 result.drainableCount = Integer.parseInt(strings1[1].trim());
 }

 if (type.contains(".")) {
 result.type = type.split("\\.")[1];
 result.module = type.split("\\.")[0];
 } else {
 result.type = type;
 }

 this->Result = result;
 }

 public Recipe.Result getResult() {
 return this->Result;
 }

 std::string getSound() {
 return this->Sound;
 }

 void setSound(const std::string& sound) {
 this->Sound = sound;
 }

 std::string getOriginalname() {
 return this->originalname;
 }

 void setOriginalname(const std::string& _originalname) {
 this->originalname = _originalname;
 }

 bool needToBeLearn() {
 return this->needToBeLearn;
 }

 void setNeedToBeLearn(bool _needToBeLearn) {
 this->needToBeLearn = _needToBeLearn;
 }

 std::string getCategory() {
 return this->category;
 }

 void setCategory(const std::string& _category) {
 this->category = _category;
 }

 public ArrayList<String> getRequiredSkills() {
 std::vector arrayList = nullptr;
 if (this->skillRequired != nullptr) {
 arrayList = std::make_unique<ArrayList>();

 for (int int0 = 0; int0 < this->skillRequired.size(); int0++) {
 Recipe.RequiredSkill requiredSkill = this->skillRequired.get(int0);
 PerkFactory.Perk perk = PerkFactory.getPerk(requiredSkill.perk);
 if (perk == nullptr) {
 arrayList.add(requiredSkill.perk.name + " " + requiredSkill.level);
 } else {
 std::string string = perk.name + " " + requiredSkill.level;
 arrayList.add(string);
 }
 }
 }

 return arrayList;
 }

 int getRequiredSkillCount() {
 return this->skillRequired == nullptr ? 0 : this->skillRequired.size();
 }

 public Recipe.RequiredSkill getRequiredSkill(int index) {
 return this->skillRequired != nullptr && index >= 0 && index < this->skillRequired.size() ? this->skillRequired.get(index) : nullptr;
 }

 void clearRequiredSkills() {
 if (this->skillRequired != nullptr) {
 this->skillRequired.clear();
 }
 }

 void addRequiredSkill(PerkFactory.Perk perk, int level) {
 if (this->skillRequired == nullptr) {
 this->skillRequired = std::make_unique<ArrayList<>>();
 }

 this->skillRequired.add(new Recipe.RequiredSkill(perk, level);
 }

 public Recipe.Source findSource(String sourceFullType) {
 for (int int0 = 0; int0 < this->Source.size(); int0++) {
 Recipe.Source source = this->Source.get(int0);

 for (int int1 = 0; int1 < source.getItems().size(); int1++) {
 if (source.getItems().get(int1) == sourceFullType) {
 return source;
 }
 }
 }

 return nullptr;
 }

 bool isDestroy(const std::string& sourceFullType) {
 Recipe.Source source = this->findSource(sourceFullType);
 if (source != nullptr) {
 return source.isDestroy();
 } else {
 throw RuntimeException("recipe " + this->getOriginalname() + " doesn't use item " + sourceFullType);
 }
 }

 bool isKeep(const std::string& sourceFullType) {
 Recipe.Source source = this->findSource(sourceFullType);
 if (source != nullptr) {
 return source.isKeep();
 } else {
 throw RuntimeException("recipe " + this->getOriginalname() + " doesn't use item " + sourceFullType);
 }
 }

 float getHeat() {
 return this->heat;
 }

 bool noBrokenItems() {
 return !this->AllowDestroyedItem;
 }

 bool isAllowDestroyedItem() {
 return this->AllowDestroyedItem;
 }

 void setAllowDestroyedItem(bool allow) {
 this->AllowDestroyedItem = allow;
 }

 bool isAllowFrozenItem() {
 return this->AllowFrozenItem;
 }

 void setAllowFrozenItem(bool allow) {
 this->AllowFrozenItem = allow;
 }

 bool isAllowRottenItem() {
 return this->AllowRottenItem;
 }

 void setAllowRottenItem(bool boolean0) {
 this->AllowRottenItem = boolean0;
 }

 int getWaterAmountNeeded() {
 Recipe.Source source = this->findSource("Water");
 return source != nullptr ? (int)source.getCount() : 0;
 }

 std::string getNearItem() {
 return this->nearItem;
 }

 void setNearItem(const std::string& _nearItem) {
 this->nearItem = _nearItem;
 }

 std::string getCanPerform() {
 return this->LuaCanPerform;
 }

 void setCanPerform(const std::string& functionName) {
 this->LuaCanPerform = functionName;
 }

 std::string getLuaTest() {
 return this->LuaTest;
 }

 void setLuaTest(const std::string& functionName) {
 this->LuaTest = functionName;
 }

 std::string getLuaCreate() {
 return this->LuaCreate;
 }

 void setLuaCreate(const std::string& functionName) {
 this->LuaCreate = functionName;
 }

 std::string getLuaGrab() {
 return this->LuaGrab;
 }

 void setLuaGrab(const std::string& functionName) {
 this->LuaGrab = functionName;
 }

 std::string getLuaGiveXP() {
 return this->LuaGiveXP;
 }

 void setLuaGiveXP(const std::string& functionName) {
 this->LuaGiveXP = functionName;
 }

 bool isRemoveResultItem() {
 return this->removeResultItem;
 }

 void setRemoveResultItem(bool _removeResultItem) {
 this->removeResultItem = _removeResultItem;
 }

 std::string getAnimNode() {
 return this->AnimNode;
 }

 void setAnimNode(const std::string& animNode) {
 this->AnimNode = animNode;
 }

 std::string getProp1() {
 return this->Prop1;
 }

 void setProp1(const std::string& prop1) {
 this->Prop1 = prop1;
 }

 std::string getProp2() {
 return this->Prop2;
 }

 void setProp2(const std::string& prop2) {
 this->Prop2 = prop2;
 }

 std::string getTooltip() {
 return this->tooltip;
 }

 void setStopOnWalk(bool stop) {
 this->stopOnWalk = stop;
 }

 bool isStopOnWalk() {
 return this->stopOnWalk;
 }

 void setStopOnRun(bool stop) {
 this->stopOnRun = stop;
 }

 bool isStopOnRun() {
 return this->stopOnRun;
 }

 void setIsHidden(bool hide) {
 this->hidden = hide;
 }

 bool isHidden() {
 return this->hidden;
 }

 bool isInSameInventory() {
 return this->InSameInventory;
 }

 public static class RequiredSkill {
 private PerkFactory.Perk perk;
 const int level;

 public RequiredSkill(PerkFactory.Perk _perk, int _level) {
 this->perk = _perk;
 this->level = _level;
 }

 public PerkFactory.Perk getPerk() {
 return this->perk;
 }

 int getLevel() {
 return this->level;
 }
 }

 public static class Result {
 std::string module = nullptr;
 std::string type;
 int count = 1;
 int drainableCount = 0;

 std::string getType() {
 return this->type;
 }

 void setType(const std::string& _type) {
 this->type = _type;
 }

 int getCount() {
 return this->count;
 }

 void setCount(int _count) {
 this->count = _count;
 }

 std::string getModule() {
 return this->module;
 }

 void setModule(const std::string& _module) {
 this->module = _module;
 }

 std::string getFullType() {
 return this->module + "." + this->type;
 }

 int getDrainableCount() {
 return this->drainableCount;
 }

 void setDrainableCount(int _count) {
 this->drainableCount = _count;
 }
 }

 public static class Source {
 bool keep = false;
 private ArrayList<String> items = std::make_unique<ArrayList<>>();
 bool destroy = false;
 float count = 1.0F;
 float use = 0.0F;

 bool isDestroy() {
 return this->destroy;
 }

 void setDestroy(bool _destroy) {
 this->destroy = _destroy;
 }

 bool isKeep() {
 return this->keep;
 }

 void setKeep(bool _keep) {
 this->keep = _keep;
 }

 float getCount() {
 return this->count;
 }

 void setCount(float _count) {
 this->count = _count;
 }

 float getUse() {
 return this->use;
 }

 void setUse(float _use) {
 this->use = _use;
 }

 public ArrayList<String> getItems() {
 return this->items;
 }

 std::string getOnlyItem() {
 if (this->items.size() != 1) {
 throw RuntimeException("items.size() == " + this->items.size());
 } else {
 return this->items.get(0);
 }
 }
 }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
