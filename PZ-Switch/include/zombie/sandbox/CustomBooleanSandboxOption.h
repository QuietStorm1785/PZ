#pragma once
#include "zombie/scripting/ScriptParser.h"
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

class CustomBooleanSandboxOption : public CustomSandboxOption {
public:
 const bool defaultValue;

 CustomBooleanSandboxOption(String string, boolean boolean0) {
 super(string);
 this->defaultValue = boolean0;
 }

 static CustomBooleanSandboxOption parse(ScriptParser.Block block) {
 ScriptParser.Value value = block.getValue("default");
 if (value.empty()) {
 return nullptr;
 } else {
 bool boolean0 = Boolean.parseBoolean(value.getValue().trim());
 CustomBooleanSandboxOption customBooleanSandboxOption =
 new CustomBooleanSandboxOption(block.id, boolean0);
 return !customBooleanSandboxOption.parseCommon(block)
 ? nullptr
 : customBooleanSandboxOption;
 }
 }
}
} // namespace sandbox
} // namespace zombie
