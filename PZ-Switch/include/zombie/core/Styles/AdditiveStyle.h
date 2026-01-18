#pragma once
#include "zombie/IndieGL.h"
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

class AdditiveStyle : public AbstractStyle {
public:
 static const long serialVersionUID = 1L;
 static const AdditiveStyle instance = new AdditiveStyle();

 void setupState() { IndieGL.glBlendFuncA(1, 771); }

 void resetState() { IndieGL.glBlendFuncA(770, 771); }

 AlphaOp getAlphaOp() { return AlphaOp.KEEP; }

 int getStyleID() { return 3; }

 bool getRenderSprite() { return true; }
}
} // namespace Styles
} // namespace core
} // namespace zombie
