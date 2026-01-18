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
namespace sandbox {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class CustomEnumSandboxOption : public CustomSandboxOption {
public:
 const int numValues;
 const int defaultValue;
 std::string m_valueTranslation;

 CustomEnumSandboxOption(String string, int int0, int int1) {
 super(string);
 this->numValues = int0;
 this->defaultValue = int1;
 }

 static CustomEnumSandboxOption parse(ScriptParser.Block block) {
 int int0 = getValueInt(block, "numValues", -1);
 int int1 = getValueInt(block, "default", -1);
 if (int0 > 0 && int1 > 0) {
 CustomEnumSandboxOption customEnumSandboxOption = new CustomEnumSandboxOption(block.id, int0, int1);
 if (!customEnumSandboxOption.parseCommon(block) {
 return nullptr;
 } else {
 ScriptParser.Value value = block.getValue("valueTranslation");
 if (value != nullptr) {
 customEnumSandboxOption.m_valueTranslation = StringUtils.discardNullOrWhitespace(value.getValue().trim());
 }

 return customEnumSandboxOption;
 }
 } else {
 return nullptr;
 }
 }
}
} // namespace sandbox
} // namespace zombie
