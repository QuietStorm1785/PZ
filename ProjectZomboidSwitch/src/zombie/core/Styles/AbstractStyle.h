#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace Styles {

class AbstractStyle {
public:
    static const long serialVersionUID = 1L;

    bool getRenderSprite() {
    return false;
   }

    AlphaOp getAlphaOp() {
    return nullptr;
   }

    int getStyleID() {
      return this.hashCode();
   }

    void resetState() {
   }

    void setupState() {
   }

    GeometryData build() {
    return nullptr;
   }

    void render(int var1, int var2) {
   }
}
} // namespace Styles
} // namespace core
} // namespace zombie
