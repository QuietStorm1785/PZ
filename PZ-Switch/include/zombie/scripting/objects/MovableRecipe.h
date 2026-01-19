#pragma once
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/debug/DebugLog.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace scripting {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.
 */
class MovableRecipe : public Recipe {
public:
 bool isValid = false;
 std::string worldSprite = "";
private
 PerkFactory.Perk xpPerk = PerkFactory.Perks.MAX;
private
 Recipe.Source primaryTools;
private
 Recipe.Source secondaryTools;

public
 MovableRecipe() {
 this->AnimNode = "Disassemble";
 this->removeResultItem = true;
 this->AllowDestroyedItem = false;
 this->name = "Disassemble Movable";
 this->setCanBeDoneFromFloor(false);
 }

 void setResult(std::string_view resultItem, int count) {
 Recipe.Result result = new Recipe.Result();
 result.count = count;
 if (resultItem.contains(".")) {
 result.type = resultItem.split("\\.")[1];
 result.module = resultItem.split("\\.")[0];
 } else {
 DebugLog.log("MovableRecipe invalid result item. item = " + resultItem);
 }

 this->Result = result;
 }

 void setSource(std::string_view sourceItem) {
 Recipe.Source source = new Recipe.Source();
 source.getItems().add(sourceItem);
 this->Source.add(source);
 }

 void setTool(std::string_view tools, bool isPrimary) {
 Recipe.Source source = new Recipe.Source();
 source.keep = true;
 if (tools.contains("/")) {
 tools = tools.replaceFirst("keep ", "").trim();
 source.getItems().addAll(Arrays.asList(tools.split("/")));
 } else {
 source.getItems().add(tools);
 }

 if (isPrimary) {
 this->primaryTools = source;
 } else {
 this->secondaryTools = source;
 }

 this->Source.add(source);
 }

public
 Recipe.Source getPrimaryTools() { return this->primaryTools; }

public
 Recipe.Source getSecondaryTools() { return this->secondaryTools; }

 void setRequiredSkill(PerkFactory.Perk perk, int level) {
 Recipe.RequiredSkill requiredSkill = new Recipe.RequiredSkill(perk, level);
 this->skillRequired.add(requiredSkill);
 }

 void setXpPerk(PerkFactory.Perk perk) { this->xpPerk = perk; }

public
 PerkFactory.Perk getXpPerk() { return this->xpPerk; }

 bool hasXpPerk() { return this->xpPerk != PerkFactory.Perks.MAX; }

 void setOnCreate(std::string_view onCreate) { this->LuaCreate = onCreate; }

 void setOnXP(std::string_view onXP) { this->LuaGiveXP = onXP; }

 void setTime(float time) { this->TimeToMake = time; }

 void setName(std::string_view name) { this->name = name; }

 std::string getWorldSprite() { return this->worldSprite; }

 void setWorldSprite(std::string_view _worldSprite) {
 this->worldSprite = _worldSprite;
 }

 bool isValid() { return this->isValid; }

 void setValid(bool valid) { this->isValid = valid; }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
