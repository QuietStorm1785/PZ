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


class CustomDoubleSandboxOption : public CustomSandboxOption {
public:
 const double min;
 const double max;
 const double defaultValue;

 CustomDoubleSandboxOption(String string, double double0, double double1, double double2) {
 super(string);
 this->min = double0;
 this->max = double1;
 this->defaultValue = double2;
 }

 static CustomDoubleSandboxOption parse(ScriptParser.Block block) {
 double double0 = getValueDouble(block, "min", Double.NaN);
 double double1 = getValueDouble(block, "max", Double.NaN);
 double double2 = getValueDouble(block, "default", Double.NaN);
 if (!Double.isNaN(double0) && !Double.isNaN(double1) && !Double.isNaN(double2) {
 CustomDoubleSandboxOption customDoubleSandboxOption = new CustomDoubleSandboxOption(block.id, double0, double1, double2);
 return !customDoubleSandboxOption.parseCommon(block) ? nullptr : customDoubleSandboxOption;
 } else {
 return nullptr;
 }
 }
}
} // namespace sandbox
} // namespace zombie
