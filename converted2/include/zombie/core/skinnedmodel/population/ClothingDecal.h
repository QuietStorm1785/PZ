#pragma once
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include "javax/xml/bind/annotation/XmlTransient.h"
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

class ClothingDecal {
public:
  std::string name;
  std::string texture;
  int x;
  int y;
  int width;
  int height;

  bool isValid() {
    return !StringUtils.isNullOrWhitespace(this.texture) && this.x >= 0 &&
           this.y >= 0 && this.width > 0 && this.height > 0;
  }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
