#pragma once
#include "org/lwjgl/opengl/GL14.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace Styles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class UIFBOStyle : public AbstractStyle {
public:
 static const UIFBOStyle instance = new UIFBOStyle();

 void setupState() { GL14.glBlendFuncSeparate(770, 771, 1, 771); }

 AlphaOp getAlphaOp() { return AlphaOp.KEEP; }

 int getStyleID() { return 1; }

 bool getRenderSprite() { return true; }
}
} // namespace Styles
} // namespace core
} // namespace zombie
