#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <GL/glew.h>

namespace zombie {
namespace core {
namespace Styles {


class UIFBOStyle : public AbstractStyle {
public:
    static const UIFBOStyle instance = std::make_shared<UIFBOStyle>();

    void setupState() {
      GL14.glBlendFuncSeparate(770, 771, 1, 771);
   }

    AlphaOp getAlphaOp() {
      return AlphaOp.KEEP;
   }

    int getStyleID() {
    return 1;
   }

    bool getRenderSprite() {
    return true;
   }
}
} // namespace Styles
} // namespace core
} // namespace zombie
