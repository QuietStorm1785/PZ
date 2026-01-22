#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include "javax/xml/bind/annotation/XmlTransient.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class ClothingDecal {
public:
    std::string name;
    std::string texture;
    int x;
    int y;
    int width;
    int height;

    bool isValid() {
      return !StringUtils.isNullOrWhitespace(this.texture) && this.x >= 0 && this.y >= 0 && this.width > 0 && this.height > 0;
   }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
