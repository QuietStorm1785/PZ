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


class TransparentStyle : public AbstractStyle {
public:
    static const long serialVersionUID = 1L;
    static const TransparentStyle instance = std::make_shared<TransparentStyle>();

    void setupState() {
      IndieGL.glBlendFuncA(770, 771);
   }

    void resetState() {
   }

    AlphaOp getAlphaOp() {
      return AlphaOp.KEEP;
   }

    int getStyleID() {
    return 2;
   }

    bool getRenderSprite() {
    return true;
   }
}
} // namespace Styles
} // namespace core
} // namespace zombie
