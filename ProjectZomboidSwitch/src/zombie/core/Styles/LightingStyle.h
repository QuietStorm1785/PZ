#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/IndieGL.h"

namespace zombie {
namespace core {
namespace Styles {


class LightingStyle : public AbstractStyle {
public:
    static const long serialVersionUID = 1L;
    static const LightingStyle instance = std::make_shared<LightingStyle>();

    void setupState() {
      IndieGL.glBlendFuncA(0, 768);
   }

    void resetState() {
      IndieGL.glBlendFuncA(770, 771);
   }

    AlphaOp getAlphaOp() {
      return AlphaOp.KEEP;
   }

    int getStyleID() {
    return 3;
   }

    bool getRenderSprite() {
    return true;
   }
}
} // namespace Styles
} // namespace core
} // namespace zombie
