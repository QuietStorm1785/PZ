#pragma once
#include "zombie/util/StringUtils.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BeardStyle {
public:
  std::string name = "";
  std::string model;
  std::string texture = "F_Hair_White";
  int level = 0;
public
  ArrayList<String> trimChoices = std::make_unique<ArrayList<>>();
  bool growReference = false;

  bool isValid() {
    return !StringUtils.isNullOrWhitespace(this.model) &&
           !StringUtils.isNullOrWhitespace(this.texture);
  }

  int getLevel() { return this.level; }

  std::string getName() { return this.name; }

public
  ArrayList<String> getTrimChoices() { return this.trimChoices; }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
