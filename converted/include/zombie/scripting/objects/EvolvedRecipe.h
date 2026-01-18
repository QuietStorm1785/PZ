#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/math/RoundingMode.h"
#include "java/text/DecimalFormat.h"
#include "java/text/NumberFormat.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/Translator.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace scripting {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class EvolvedRecipe : public BaseScriptObject {
public:
 static const DecimalFormat DECIMAL_FORMAT = (DecimalFormat)NumberFormat.getInstance(Locale.US);
 std::string name = nullptr;
 std::string DisplayName = nullptr;
 std::string originalname;
 int maxItems = 0;
 public Map<String, ItemRecipe> itemsList = std::make_unique<HashMap<>>();
 std::string resultItem = nullptr;
 std::string baseItem = nullptr;
 bool cookable = false;
 bool addIngredientIfCooked = false;
 bool canAddSpicesEmpty = false;
 std::string addIngredientSound = nullptr;
 bool hidden = false;
 bool allowFrozenItem = false;

 public EvolvedRecipe(const std::string& _name) {
 this->name = _name;
 }

 void Load(const std::string& string0, String[] strings0) {
 this->DisplayName = Translator.getRecipeName(string0);
 this->originalname = string0;

 for (int int0 = 0; int0 < strings0.length; int0++) {
 if (!strings0[int0].trim().empty() && strings0[int0].contains(":")) {
 String[] strings1 = strings0[int0].split(":");
 std::string string1 = strings1[0].trim();
 std::string string2 = strings1[1].trim();
 if (string1 == "BaseItem")) {
 this->baseItem = string2;
 } else if (string1 == "Name")) {
 this->DisplayName = Translator.getRecipeName(string2);
 this->originalname = string2;
 } else if (string1 == "ResultItem")) {
 this->resultItem = string2;
 if (!string2.contains(".")) {
 this->resultItem = string2;
 }
 } else if (string1 == "Cookable")) {
 this->cookable = true;
 } else if (string1 == "MaxItems")) {
 this->maxItems = Integer.parseInt(string2);
 } else if (string1 == "AddIngredientIfCooked")) {
 this->addIngredientIfCooked = Boolean.parseBoolean(string2);
 } else if (string1 == "AddIngredientSound")) {
 this->addIngredientSound = StringUtils.discardNullOrWhitespace(string2);
 } else if (string1 == "CanAddSpicesEmpty")) {
 this->canAddSpicesEmpty = Boolean.parseBoolean(string2);
 } else if (string1 == "IsHidden")) {
 this->hidden = Boolean.parseBoolean(string2);
 } else if (string1 == "AllowFrozenItem")) {
 this->allowFrozenItem = Boolean.parseBoolean(string2);
 }
 }
 }
 }

 bool needToBeCooked(InventoryItem itemTest) {
 ItemRecipe itemRecipe = this->getItemRecipe(itemTest);
 return itemRecipe = = nullptr ? true : itemRecipe.cooked == itemTest.isCooked() || itemRecipe.cooked == itemTest.isBurnt() || !itemRecipe.cooked;
 }

 public ArrayList<InventoryItem> getItemsCanBeUse(IsoGameCharacter chr, InventoryItem _baseItem, ArrayList<ItemContainer> containers) {
 int int0 = chr.getPerkLevel(PerkFactory.Perks.Cooking);
 if (containers.empty()) {
 containers = std::make_unique<ArrayList>();
 }

 std::vector arrayList = new ArrayList();
 Iterator iterator = this->itemsList.keySet().iterator();
 if (!containers.contains(chr.getInventory())) {
 containers.add(chr.getInventory());
 }

 while (iterator.hasNext()) {
 std::string string = (String)iterator.next();

 for (auto& container0 : containers) this->checkItemCanBeUse(container0, string, _baseItem, int0, arrayList);
 }
 }

 if (_baseItem.haveExtraItems() && _baseItem.getExtraItems().size() >= 3) {
 for (int int1 = 0; int1 < containers.size(); int1++) {
 ItemContainer container1 = (ItemContainer)containers.get(int1);

 for (int int2 = 0; int2 < container1.getItems().size(); int2++) {
 InventoryItem item = container1.getItems().get(int2);
 if (item instanceof Food && ((Food)item).getPoisonLevelForRecipe() != nullptr && chr.isKnownPoison(item) && !arrayList.contains(item) {
 arrayList.add(item);
 }
 }
 }
 }

 return arrayList;
 }

 void checkItemCanBeUse(ItemContainer container, const std::string& string, InventoryItem item1, int int1, ArrayList<InventoryItem> arrayList1) {
 std::vector arrayList0 = container.getItemsFromType(string);

 for (int int0 = 0; int0 < arrayList0.size(); int0++) {
 InventoryItem item0 = (InventoryItem)arrayList0.get(int0);
 bool boolean0 = false;
 if (item0 instanceof Food && this->itemsList.get(string).use != -1) {
 Food food = (Food)item0;
 if (food.isSpice()) {
 if (this->isResultItem(item1) {
 boolean0 = !this->isSpiceAdded(item1, food);
 } else if (this->canAddSpicesEmpty) {
 boolean0 = true;
 }

 if (food.isRotten() && int1 < 7) {
 boolean0 = false;
 }
 } else if ((!item1.haveExtraItems() || item1.extraItems.size() < this->maxItems) && (!food.isRotten() || int1 >= 7) {
 boolean0 = true;
 }

 if (food.isFrozen() && !this->allowFrozenItem) {
 boolean0 = false;
 }
 } else {
 boolean0 = true;
 }

 ItemRecipe itemRecipe = this->getItemRecipe(item0);
 if (boolean0) {
 arrayList1.add(item0);
 }
 }
 }

 InventoryItem addItem(InventoryItem _baseItem, InventoryItem usedItem, IsoGameCharacter chr) {
 int int0 = chr.getPerkLevel(PerkFactory.Perks.Cooking);
 if (!this->isResultItem(_baseItem) {
 InventoryItem item0 = _baseItem instanceof Food ? _baseItem : nullptr;
 InventoryItem item1 = InventoryItemFactory.CreateItem(this->resultItem);
 if (item1 != nullptr) {
 if (_baseItem instanceof HandWeapon) {
 item1.getModData().rawset("condition:" + _baseItem.getType(), (double)_baseItem.getCondition() / _baseItem.getConditionMax());
 }

 chr.getInventory().Remove(_baseItem);
 chr.getInventory().AddItem(item1);
 InventoryItem item2 = _baseItem;
 _baseItem = item1;
 if (item1 instanceof Food) {
 ((Food)item1).setCalories(0.0F);
 ((Food)item1).setCarbohydrates(0.0F);
 ((Food)item1).setProteins(0.0F);
 ((Food)item1).setLipids(0.0F);
 if (usedItem instanceof Food && ((Food)usedItem).getPoisonLevelForRecipe() != nullptr) {
 this->addPoison(usedItem, item1, chr);
 }

 ((Food)item1).setIsCookable(this->cookable);
 if (item0 != nullptr) {
 ((Food)item1).setHungChange(((Food)item0).getHungChange());
 ((Food)item1).setBaseHunger(((Food)item0).getBaseHunger());
 } else {
 ((Food)item1).setHungChange(0.0F);
 ((Food)item1).setBaseHunger(0.0F);
 }

 if (item2.isTaintedWater()) {
 item1.setTaintedWater(true);
 }

 if (item2 instanceof Food && item2.getOffAgeMax() != 1000000000 && item1.getOffAgeMax() != 1000000000) {
 float float0 = item2.getAge() / item2.getOffAgeMax();
 item1.setAge(item1.getOffAgeMax() * float0);
 }

 if (item0 instanceof Food) {
 ((Food)item1).setCalories(((Food)item0).getCalories());
 ((Food)item1).setProteins(((Food)item0).getProteins());
 ((Food)item1).setLipids(((Food)item0).getLipids());
 ((Food)item1).setCarbohydrates(((Food)item0).getCarbohydrates());
 ((Food)item1).setThirstChange(((Food)item0).getThirstChange());
 }
 }

 item1.setUnhappyChange(0.0F);
 item1.setBoredomChange(0.0F);
 }
 }

 if (this->itemsList.get(usedItem.getType()) != nullptr && this->itemsList.get(usedItem.getType()).use > -1) {
 if (!(usedItem instanceof Food) {
 usedItem.Use();
 } else {
 float float1 = this->itemsList.get(usedItem.getType()).use.intValue() / 100.0F;
 Food food0 = (Food)usedItem;
 Food food1 = (Food)_baseItem;
 bool boolean0 = food1.hasTag("HerbalTea") && food0.hasTag("HerbalTea");
 if (food0.isSpice() && _baseItem instanceof Food) {
 if (_baseItem instanceof Food && boolean0) {
 food1.setReduceFoodSickness(food1.getReduceFoodSickness() + food0.getReduceFoodSickness());
 food1.setPainReduction(food1.getPainReduction() + food0.getPainReduction());
 food1.setFluReduction(food1.getFluReduction() + food0.getFluReduction());
 if (food0.getEnduranceChange() > 0.0F) {
 food1.setEnduranceChange(food1.getEnduranceChange() + food0.getEnduranceChange());
 }

 if (food1.getReduceFoodSickness() > 12) {
 food1.setReduceFoodSickness(12);
 }
 }

 this->useSpice(food0, (Food)_baseItem, float1, int0);
 return _baseItem;
 }

 bool boolean1 = false;
 if (food0.isRotten()) {
 DecimalFormat decimalFormat0 = DECIMAL_FORMAT;
 decimalFormat0.setRoundingMode(RoundingMode.HALF_EVEN);
 if (int0 == 7 || int0 == 8) {
 float1 = Float.parseFloat(
 decimalFormat0.format(Math.abs(food0.getBaseHunger() - (food0.getBaseHunger() - 0.05F * food0.getBaseHunger()))).replace(",", ".")
 );
 } else if (int0 == 9 || int0 == 10) {
 float1 = Float.parseFloat(
 decimalFormat0.format(Math.abs(food0.getBaseHunger() - (food0.getBaseHunger() - 0.1F * food0.getBaseHunger()))).replace(",", ".")
 );
 }

 boolean1 = true;
 }

 if (Math.abs(food0.getHungerChange()) < float1) {
 DecimalFormat decimalFormat1 = DECIMAL_FORMAT;
 decimalFormat1.setRoundingMode(RoundingMode.DOWN);
 float1 = Math.abs(Float.parseFloat(decimalFormat1.format(food0.getHungerChange()).replace(",", ".")));
 boolean1 = true;
 }

 if (_baseItem instanceof Food) {
 if (usedItem instanceof Food && ((Food)usedItem).getPoisonLevelForRecipe() != nullptr) {
 this->addPoison(usedItem, _baseItem, chr);
 }

 food1.setHungChange(food1.getHungChange() - float1);
 food1.setBaseHunger(food1.getBaseHunger() - float1);
 if (food0.isbDangerousUncooked() && !food0.isCooked()) {
 food1.setbDangerousUncooked(true);
 }

 int int1 = 0;
 if (_baseItem.extraItems != nullptr) {
 for (int int2 = 0; int2 < _baseItem.extraItems.size(); int2++) {
 if (_baseItem.extraItems.get(int2) == usedItem.getFullType())) {
 int1++;
 }
 }
 }

 if (_baseItem.extraItems != nullptr && _baseItem.extraItems.size() - 2 > int0) {
 int1 += _baseItem.extraItems.size() - 2 - int0 * 3;
 }

 float float2 = float1 - 3 * int0 / 100.0F * float1;
 float float3 = Math.abs(float2 / food0.getHungChange());
 if (float3 > 1.0F) {
 float3 = 1.0F;
 }

 _baseItem.setUnhappyChange(((Food)_baseItem).getUnhappyChangeUnmodified() - (5 - int1 * 5);
 if (_baseItem.getUnhappyChange() > 25.0F) {
 _baseItem.setUnhappyChange(25.0F);
 }

 float float4 = int0 / 15.0F + 1.0F;
 food1.setCalories(food1.getCalories() + food0.getCalories() * float4 * float3);
 food1.setProteins(food1.getProteins() + food0.getProteins() * float4 * float3);
 food1.setCarbohydrates(food1.getCarbohydrates() + food0.getCarbohydrates() * float4 * float3);
 food1.setLipids(food1.getLipids() + food0.getLipids() * float4 * float3);
 float float5 = food0.getThirstChangeUnmodified() * float4 * float3;
 if (!food0.hasTag("DriedFood")) {
 food1.setThirstChange(food1.getThirstChangeUnmodified() + float5);
 }

 if (food0.isCooked()) {
 float2 = (float)(float2 / 1.3);
 }

 food0.setHungChange(food0.getHungChange() + float2);
 food0.setBaseHunger(food0.getBaseHunger() + float2);
 food0.setThirstChange(food0.getThirstChange() - float5);
 food0.setCalories(food0.getCalories() - food0.getCalories() * float3);
 food0.setProteins(food0.getProteins() - food0.getProteins() * float3);
 food0.setCarbohydrates(food0.getCarbohydrates() - food0.getCarbohydrates() * float3);
 food0.setLipids(food0.getLipids() - food0.getLipids() * float3);
 if (food1.hasTag("AlcoholicBeverage") && food0.isAlcoholic()) {
 food1.setAlcoholic(true);
 }

 if (boolean0) {
 food1.setReduceFoodSickness(food1.getReduceFoodSickness() + food0.getReduceFoodSickness());
 food1.setPainReduction(food1.getPainReduction() + food0.getPainReduction());
 food1.setFluReduction(food1.getFluReduction() + food0.getFluReduction());
 if (food1.getReduceFoodSickness() > 12) {
 food1.setReduceFoodSickness(12);
 }
 }

 if (food0.getHungerChange() >= -0.02 || boolean1) {
 usedItem.Use();
 }

 if (food0.getFatigueChange() < 0.0F) {
 _baseItem.setFatigueChange(food0.getFatigueChange() * float3);
 food0.setFatigueChange(food0.getFatigueChange() - food0.getFatigueChange() * float3);
 }

 if (food0.getPoisonPower() > 0) {
 food0.setPoisonPower((int)(food0.getPoisonPower() - food0.getPoisonPower() * float3 + 0.999);
 ((Food)_baseItem).setPoisonPower((int)(food0.getPoisonPower() * float3 + 0.999);
 }
 }
 }

 _baseItem.addExtraItem(usedItem.getFullType());
 } else if (usedItem instanceof Food && ((Food)usedItem).getPoisonLevelForRecipe() != nullptr) {
 this->addPoison(usedItem, _baseItem, chr);
 }

 this->checkUniqueRecipe(_baseItem);
 chr.getXp().AddXP(PerkFactory.Perks.Cooking, 3.0F);
 return _baseItem;
 }

 void checkUniqueRecipe(InventoryItem item) {
 if (item instanceof Food food) {
 std::stack stack = ScriptManager.instance.getAllUniqueRecipes();

 for (int int0 = 0; int0 < stack.size(); int0++) {
 std::vector arrayList = new ArrayList();
 UniqueRecipe uniqueRecipe = (UniqueRecipe)stack.get(int0);
 if (uniqueRecipe.getBaseRecipe() == item.getType())) {
 bool boolean0 = true;

 for (int int1 = 0; int1 < uniqueRecipe.getItems().size(); int1++) {
 bool boolean1 = false;

 for (int int2 = 0; int2 < food.getExtraItems().size(); int2++) {
 if (!arrayList.contains(int2) && food.getExtraItems().get(int2) == uniqueRecipe.getItems().get(int1) {
 boolean1 = true;
 arrayList.add(int2);
 break;
 }
 }

 if (!boolean1) {
 boolean0 = false;
 break;
 }
 }

 if (food.getExtraItems().size() == uniqueRecipe.getItems().size() && boolean0) {
 food.setName(uniqueRecipe.getName());
 if (food.hasTag("Beer")) {
 food.setName("Beer");
 }

 food.setBaseHunger(food.getBaseHunger() - uniqueRecipe.getHungerBonus() / 100.0F);
 food.setHungChange(food.getBaseHunger());
 food.setBoredomChange(food.getBoredomChangeUnmodified() - uniqueRecipe.getBoredomBonus());
 food.setUnhappyChange(food.getUnhappyChangeUnmodified() - uniqueRecipe.getHapinessBonus());
 food.setCustomName(true);
 }
 }
 }
 }
 }

 void addPoison(InventoryItem item0, InventoryItem item1, IsoGameCharacter character) {
 Food food0 = (Food)item0;
 if (item1 instanceof Food food1) {
 int int0 = food0.getPoisonLevelForRecipe() - character.getPerkLevel(PerkFactory.Perks.Cooking);
 if (int0 < 1) {
 int0 = 1;
 }

 float float0 = 0.0F;
 if (food0.getThirstChange() <= -0.01F) {
 float float1 = food0.getUseForPoison() / 100.0F;
 if (Math.abs(food0.getThirstChange()) < float1) {
 float1 = Math.abs(food0.getThirstChange());
 }

 float0 = Math.abs(float1 / food0.getThirstChange());
 float0 = new Float(Math.round(float0.doubleValue() * 100.0) / 100.0);
 food0.setThirstChange(food0.getThirstChange() + float1);
 if (food0.getThirstChange() > -0.01) {
 food0.Use();
 }
 } else if (food0.getBaseHunger() <= -0.01F) {
 float float2 = food0.getUseForPoison() / 100.0F;
 if (Math.abs(food0.getBaseHunger()) < float2) {
 float2 = Math.abs(food0.getThirstChange());
 }

 float0 = Math.abs(float2 / food0.getBaseHunger());
 float0 = new Float(Math.round(float0.doubleValue() * 100.0) / 100.0);
 }

 if (food1.getPoisonDetectionLevel() == -1) {
 food1.setPoisonDetectionLevel(0);
 }

 food1.setPoisonDetectionLevel(food1.getPoisonDetectionLevel() + int0);
 if (food1.getPoisonDetectionLevel() > 10) {
 food1.setPoisonDetectionLevel(10);
 }

 int int1 = new Float(float0 * (food0.getPoisonPower() / 100.0F) * 100.0F).intValue();
 food1.setPoisonPower(food1.getPoisonPower() + int1);
 food0.setPoisonPower(food0.getPoisonPower() - int1);
 }
 }

 void useSpice(Food food1, Food food0, float float1, int int0) {
 if (!this->isSpiceAdded(food0, food1) {
 if (food0.spices.empty()) {
 food0.spices = std::make_unique<ArrayList<>>();
 }

 food0.spices.add(food1.getFullType());
 float float0 = float1;
 if (food1.isRotten()) {
 DecimalFormat decimalFormat = DECIMAL_FORMAT;
 decimalFormat.setRoundingMode(RoundingMode.HALF_EVEN);
 if (int0 == 7 || int0 == 8) {
 float1 = Float.parseFloat(
 decimalFormat.format(Math.abs(food1.getBaseHunger() - (food1.getBaseHunger() - 0.05F * food1.getBaseHunger()))).replace(",", ".")
 );
 } else if (int0 == 9 || int0 == 10) {
 float1 = Float.parseFloat(
 decimalFormat.format(Math.abs(food1.getBaseHunger() - (food1.getBaseHunger() - 0.1F * food1.getBaseHunger()))).replace(",", ".")
 );
 }
 }

 float float2 = Math.abs(float1 / food1.getHungChange());
 if (float2 > 1.0F) {
 float2 = 1.0F;
 }

 float float3 = int0 / 15.0F + 1.0F;
 food0.setUnhappyChange(food0.getUnhappyChangeUnmodified() - float1 * 200.0F);
 food0.setBoredomChange(food0.getBoredomChangeUnmodified() - float1 * 200.0F);
 food0.setCalories(food0.getCalories() + food1.getCalories() * float3 * float2);
 food0.setProteins(food0.getProteins() + food1.getProteins() * float3 * float2);
 food0.setCarbohydrates(food0.getCarbohydrates() + food1.getCarbohydrates() * float3 * float2);
 food0.setLipids(food0.getLipids() + food1.getLipids() * float3 * float2);
 float2 = Math.abs(float0 / food1.getHungChange());
 if (float2 > 1.0F) {
 float2 = 1.0F;
 }

 food1.setCalories(food1.getCalories() - food1.getCalories() * float2);
 food1.setProteins(food1.getProteins() - food1.getProteins() * float2);
 food1.setCarbohydrates(food1.getCarbohydrates() - food1.getCarbohydrates() * float2);
 food1.setLipids(food1.getLipids() - food1.getLipids() * float2);
 food1.setHungChange(food1.getHungChange() + float0);
 if (food1.getHungerChange() > -0.01) {
 food1.Use();
 }
 }
 }

 ItemRecipe getItemRecipe(InventoryItem usedItem) {
 return this->itemsList.get(usedItem.getType());
 }

 std::string getName() {
 return this->DisplayName;
 }

 std::string getOriginalname() {
 return this->originalname;
 }

 std::string getUntranslatedName() {
 return this->name;
 }

 std::string getBaseItem() {
 return this->baseItem;
 }

 public Map<String, ItemRecipe> getItemsList() {
 return this->itemsList;
 }

 public ArrayList<ItemRecipe> getPossibleItems() {
 std::vector arrayList = new ArrayList();

 for (ItemRecipe itemRecipe : this->itemsList.values()) {
 arrayList.add(itemRecipe);
 }

 return arrayList;
 }

 std::string getResultItem() {
 return !this->resultItem.contains(".") ? this->resultItem : this->resultItem.split("\\.")[1];
 }

 std::string getFullResultItem() {
 return this->resultItem;
 }

 bool isCookable() {
 return this->cookable;
 }

 int getMaxItems() {
 return this->maxItems;
 }

 bool isResultItem(InventoryItem item) {
 return item = = nullptr ? false : this->getResultItem().equals(item.getType());
 }

 bool isSpiceAdded(InventoryItem _baseItem, InventoryItem spiceItem) {
 if (!this->isResultItem(_baseItem) {
 return false;
 } else if (!(_baseItem instanceof Food) || !(spiceItem instanceof Food) {
 return false;
 } else if (!((Food)spiceItem).isSpice()) {
 return false;
 } else {
 std::vector arrayList = ((Food)_baseItem).getSpices();
 return arrayList = = nullptr ? false : arrayList.contains(spiceItem.getFullType());
 }
 }

 std::string getAddIngredientSound() {
 return this->addIngredientSound;
 }

 void setIsHidden(bool hide) {
 this->hidden = hide;
 }

 bool isHidden() {
 return this->hidden;
 }

 bool isAllowFrozenItem() {
 return this->allowFrozenItem;
 }

 void setAllowFrozenItem(bool allow) {
 this->allowFrozenItem = allow;
 }

 static {
 DECIMAL_FORMAT.applyPattern("#.##");
 }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
