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

class CustomStringSandboxOption : public CustomSandboxOption {
public:
  const std::string defaultValue;

  CustomStringSandboxOption(String string0, String string1) {
    super(string0);
    this.defaultValue = string1;
  }

  static CustomStringSandboxOption parse(ScriptParser.Block block) {
    ScriptParser.Value value = block.getValue("default");
    if (value == nullptr) {
      return null;
    } else {
      CustomStringSandboxOption customStringSandboxOption =
          new CustomStringSandboxOption(block.id, value.getValue().trim());
      return !customStringSandboxOption.parseCommon(block)
                 ? nullptr
                 : customStringSandboxOption;
    }
  }
}
} // namespace sandbox
} // namespace zombie
