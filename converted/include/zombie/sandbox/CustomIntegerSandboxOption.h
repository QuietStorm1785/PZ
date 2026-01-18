#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/scripting/ScriptParser.h"

namespace zombie {
namespace sandbox {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class CustomIntegerSandboxOption : public CustomSandboxOption {
public:
 const int min;
 const int max;
 const int defaultValue;

 CustomIntegerSandboxOption(String string, int int0, int int1, int int2) {
 super(string);
 this->min = int0;
 this->max = int1;
 this->defaultValue = int2;
 }

 static CustomIntegerSandboxOption parse(ScriptParser.Block block) {
 int int0 = getValueInt(block, "min", Integer.MIN_VALUE);
 int int1 = getValueInt(block, "max", Integer.MIN_VALUE);
 int int2 = getValueInt(block, "default", Integer.MIN_VALUE);
 if (int0 != Integer.MIN_VALUE && int1 != Integer.MIN_VALUE && int2 != Integer.MIN_VALUE) {
 CustomIntegerSandboxOption customIntegerSandboxOption = new CustomIntegerSandboxOption(block.id, int0, int1, int2);
 return !customIntegerSandboxOption.parseCommon(block) ? nullptr : customIntegerSandboxOption;
 } else {
 return nullptr;
 }
 }
}
} // namespace sandbox
} // namespace zombie
