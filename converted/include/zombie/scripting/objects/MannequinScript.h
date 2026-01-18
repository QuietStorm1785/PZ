#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/scripting/ScriptParser.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace scripting {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class MannequinScript : public BaseScriptObject {
public:
 std::string name;
 bool bFemale = true;
 std::string modelScriptName;
 std::string texture;
 std::string animSet;
 std::string animState;
 std::string pose;
 std::string outfit;

 std::string getName() {
 return this->name;
 }

 bool isFemale() {
 return this->bFemale;
 }

 void setFemale(bool b) {
 this->bFemale = b;
 }

 std::string getModelScriptName() {
 return this->modelScriptName;
 }

 void setModelScriptName(const std::string& str) {
 this->modelScriptName = StringUtils.discardNullOrWhitespace(str);
 }

 std::string getTexture() {
 return this->texture;
 }

 void setTexture(const std::string& str) {
 this->texture = StringUtils.discardNullOrWhitespace(str);
 }

 std::string getAnimSet() {
 return this->animSet;
 }

 void setAnimSet(const std::string& str) {
 this->animSet = StringUtils.discardNullOrWhitespace(str);
 }

 std::string getAnimState() {
 return this->animState;
 }

 void setAnimState(const std::string& str) {
 this->animState = StringUtils.discardNullOrWhitespace(str);
 }

 std::string getPose() {
 return this->pose;
 }

 void setPose(const std::string& str) {
 this->pose = StringUtils.discardNullOrWhitespace(str);
 }

 std::string getOutfit() {
 return this->outfit;
 }

 void setOutfit(const std::string& str) {
 this->outfit = StringUtils.discardNullOrWhitespace(str);
 }

 void Load(const std::string& _name, const std::string& totalFile) {
 this->name = _name;
 ScriptParser.Block block = ScriptParser.parse(totalFile);
 block = block.children.get(0);

 for (ScriptParser.Value value : block.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("female".equalsIgnoreCase(string0) {
 this->bFemale = StringUtils.tryParseBoolean(string1);
 } else if ("model".equalsIgnoreCase(string0) {
 this->modelScriptName = StringUtils.discardNullOrWhitespace(string1);
 } else if ("texture".equalsIgnoreCase(string0) {
 this->texture = StringUtils.discardNullOrWhitespace(string1);
 } else if ("animSet".equalsIgnoreCase(string0) {
 this->animSet = StringUtils.discardNullOrWhitespace(string1);
 } else if ("animState".equalsIgnoreCase(string0) {
 this->animState = StringUtils.discardNullOrWhitespace(string1);
 } else if ("pose".equalsIgnoreCase(string0) {
 this->pose = StringUtils.discardNullOrWhitespace(string1);
 } else if ("outfit".equalsIgnoreCase(string0) {
 this->outfit = StringUtils.discardNullOrWhitespace(string1);
 }
 }
 }

 void reset() {
 this->modelScriptName = nullptr;
 this->texture = nullptr;
 this->animSet = nullptr;
 this->animState = nullptr;
 this->pose = nullptr;
 this->outfit = nullptr;
 }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
