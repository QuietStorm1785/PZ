#pragma once
#include "zombie/core/math/PZMath.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/util/StringUtils.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace sandbox {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class CustomSandboxOption {
public:
 const std::string m_id;
 std::string m_page;
 std::string m_translation;

 CustomSandboxOption(String string) { this->m_id = string; }

 static double getValueDouble(ScriptParser.Block block,
 const std::string &string, double double0) {
 ScriptParser.Value value = block.getValue(string);
 return value = =
 nullptr ? double0
 : PZMath.tryParseDouble(value.getValue().trim(), double0);
 }

 static float getValueFloat(ScriptParser.Block block,
 const std::string &string, float float0) {
 ScriptParser.Value value = block.getValue(string);
 return value = =
 nullptr ? float0
 : PZMath.tryParseFloat(value.getValue().trim(), float0);
 }

 static int getValueInt(ScriptParser.Block block, const std::string &string,
 int int0) {
 ScriptParser.Value value = block.getValue(string);
 return value = =
 nullptr ? int0 : PZMath.tryParseInt(value.getValue().trim(), int0);
 }

 bool parseCommon(ScriptParser.Block block) {
 ScriptParser.Value value0 = block.getValue("page");
 if (value0 != nullptr) {
 this->m_page =
 StringUtils.discardNullOrWhitespace(value0.getValue().trim());
 }

 ScriptParser.Value value1 = block.getValue("translation");
 if (value1 != nullptr) {
 this->m_translation =
 StringUtils.discardNullOrWhitespace(value1.getValue().trim());
 }

 return true;
 }
}
} // namespace sandbox
} // namespace zombie
